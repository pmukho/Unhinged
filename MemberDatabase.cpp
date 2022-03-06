// MemberDatabase.cpp 

#include "MemberDatabase.h"
#include "provided.h"
#include <fstream>
#include <sstream>

MemberDatabase::MemberDatabase()
	: m_rtreePProfile(new RadixTree<PersonProfile>)
{}

MemberDatabase::~MemberDatabase()
{
	delete m_rtreePProfile;
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
	std::ifstream databaseFile(filename);
	if (!databaseFile) {
		return false;
	}

	if (databaseFile.is_open()) {
		std::string name, email, att, val;
		int attvalCount = 0;
		while (databaseFile.good()) {
			std::getline(databaseFile, name);
			std::getline(databaseFile, email);
			if (m_rtreePProfile->search(email) != nullptr) { // email associated with existing member
				return false;
			}
			databaseFile >> attvalCount;
			PersonProfile toAddPP(name, email);
			for (int i = 0; i != attvalCount; i++) {
				std::getline(databaseFile, att, ',');
				std::getline(databaseFile, val);
				toAddPP.AddAttValPair(AttValPair(att, val));
			}
			m_rtreePProfile->insert(email, toAddPP);
		}
	}
	return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	std::vector<std::string> v;
	return v;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
	return m_rtreePProfile->search(email);
}
