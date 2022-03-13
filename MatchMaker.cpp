// MatchMaker.cpp

#include "MatchMaker.h"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "utility.h"

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
	: m_mdb(&mdb), m_at(&at)
{}

MatchMaker::~MatchMaker()
{}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
	//Find PersonProfile associated with Email
	const PersonProfile* ppOfInterest = m_mdb->GetMemberByEmail(email);
	
	//Find all compatible AttValPairs for each of PersonProfile's own, set ensures no duplicates
	std::unordered_set<AttValPair, Hash> membersToLookFor;
	for (int i = 0; i != ppOfInterest->GetNumAttValPairs(); i++) {
		AttValPair avSource;
		ppOfInterest->GetAttVal(i, avSource);
		std::vector<AttValPair> compatiblesVec = m_at->FindCompatibleAttValPairs(avSource);
		for (auto it = compatiblesVec.begin(); it != compatiblesVec.end(); it++) {
			membersToLookFor.insert(*it);
		}
	}

	std::unordered_map<std::string, int> emailToMatchCount;
	for (auto it = membersToLookFor.begin(); it != membersToLookFor.end(); it++) {
		std::vector<std::string> emailsWithMatchingPair = m_mdb->FindMatchingMembers(*it);
		for (auto it1 = emailsWithMatchingPair.begin(); it1 != emailsWithMatchingPair.end(); it1++) {
			if (*it1 != ppOfInterest->GetEmail()) emailToMatchCount[*it1]++;
		}
	}

	std::vector<EmailCount> rankedMatches;
	for (auto it = emailToMatchCount.begin(); it != emailToMatchCount.end(); it++) {
		if (it->second >= threshold) rankedMatches.push_back(EmailCount(it->first, it->second));
	}

	std::sort(rankedMatches.begin(), rankedMatches.end(), comp);

	return rankedMatches;
}