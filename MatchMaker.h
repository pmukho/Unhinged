// MatchMaker.h

#ifndef MATCHMAKER_INCLUDED
#define MATCHMAKER_INCLUDED

#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker {
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
	~MatchMaker();
	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
	const MemberDatabase* m_mdb;
	const AttributeTranslator* m_at;
};

#endif // MATCHMAKER_INCLUDED