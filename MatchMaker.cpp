// MatchMaker.cpp

#include "MatchMaker.h"

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
	return std::vector<EmailCount>();
}