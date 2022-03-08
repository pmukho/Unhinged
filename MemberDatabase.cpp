// MemberDatabase.cpp 

#include "MemberDatabase.h"
#include "provided.h"
#include <fstream>
#include <iostream>
//#include <sstream>

MemberDatabase::MemberDatabase()
//	: m_rtreePProfile(new RadixTree<PersonProfile>)
	: m_rtreePProfile(RadixTree<PersonProfile>())
{}

MemberDatabase::~MemberDatabase()
{
	//delete m_rtreePProfile;
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
	std::ifstream databaseFile(filename);
	if (!databaseFile) {
		return false;
	}

	if (databaseFile.is_open()) {
		std::string name, email, att, val, skip;
		int attvalCount = 0;
		while (databaseFile.good()) {
			std::getline(databaseFile, name);
			std::getline(databaseFile, email);
			//if (m_rtreePProfile->search(email) != nullptr) { // email associated with existing member
			//	return false;
			//}
			//databaseFile >> attvalCount;
			//std::getline(databaseFile, skip);
			//PersonProfile toAddPP(name, email);
			////PersonProfile* toAddPP = new PersonProfile(name, email);
			//for (int i = 0; i != attvalCount; i++) {
			//	std::getline(databaseFile, att, ',');
			//	std::getline(databaseFile, val);
			//	toAddPP.AddAttValPair(AttValPair(att, val));
			//	//toAddPP->AddAttValPair(AttValPair(att, val));
			//}
			////m_rtreePProfile->insert(email, toAddPP);
			//m_rtreePProfile->insert(email, toAddPP);

			//std::getline(databaseFile, skip);

			//if (m_rtreePProfile->search(email) == nullptr) {
			if (m_rtreePProfile.search(email) == nullptr) {
				databaseFile >> attvalCount;
				std::getline(databaseFile, skip);
				//PersonProfile* profile = new PersonProfile(name, email);
				PersonProfile profile(name, email);
				for (int i = 0; i != attvalCount; i++) {
					std::getline(databaseFile, att, ',');
					std::getline(databaseFile, val);
					//profile->AddAttValPair(AttValPair(att, val));
					profile.AddAttValPair(AttValPair(att, val));
				}
				//m_rtreePProfile->insert(email, *profile);
				m_rtreePProfile.insert(email, profile);

				//delete profile;
				std::getline(databaseFile, skip);
			}
			else {
				return false;
			}
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
	//return m_rtreePProfile->search(email);
	return m_rtreePProfile.search(email);
}
