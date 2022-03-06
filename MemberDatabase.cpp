// MemberDatabase.cpp 

#include "MemberDatabase.h"

MemberDatabase::MemberDatabase()
	: m_rtreePProfile(new RadixTree<PersonProfile>)
{}

MemberDatabase::~MemberDatabase()
{
	delete m_rtreePProfile;
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
	return false;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	std::vector<std::string> v;
	return v;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
	return nullptr;
}
