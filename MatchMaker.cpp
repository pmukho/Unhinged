// MatchMaker.cpp

#include "MatchMaker.h"
#include <unordered_set>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
	: m_mdb(new MemberDatabase(mdb)), m_at(new AttributeTranslator(at))
{}

MatchMaker::~MatchMaker()
{
	delete m_mdb;
	delete m_at;
}

std::vector<EmailCount> MatchMaker::IdenitfyRankedMatches(std::string email, int threshold) const
{
	const PersonProfile* ppOfInterest = m_mdb->GetMemberByEmail(email);
	//std::unordered_set<std::string>
	return std::vector<EmailCount>();
}