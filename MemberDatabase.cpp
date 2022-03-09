// MemberDatabase.cpp 

#include "MemberDatabase.h"
#include "provided.h"
#include <fstream>
#include <iostream>

MemberDatabase::MemberDatabase()
	: m_rtreeEmailToPProfile(RadixTree<PersonProfile*>()), m_rtreeAttValToEmails(RadixTree<std::vector<std::string>*>()), 
	m_emailSet(std::set<std::string>()), m_attvalSet(std::set<std::string>())
{
	/*PersonProfile* p = new PersonProfile("test", "rand@gmail.com");
	p->AddAttValPair(AttValPair("trait","quirky"));
	m_rtreeEmailToPProfile.insert("rand@gmail.com", p);
	m_emailSet.insert("rand@gmail.com");*/
}

MemberDatabase::~MemberDatabase()
{
	for (auto it = m_emailSet.begin(); it != m_emailSet.end(); it++) {
		PersonProfile** pp = m_rtreeEmailToPProfile.search(*it);
		if (pp != nullptr) { // should never be the case
			delete (*pp);
		}
	}
	for (auto it = m_attvalSet.begin(); it != m_attvalSet.end(); it++) {
		std::vector<std::string>** emails = m_rtreeAttValToEmails.search(*it);
		if (emails != nullptr) { // should never be the case
			delete (*emails);
		}
	}
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
			if (m_rtreeEmailToPProfile.search(email) != nullptr) {
				return false;
			}
			m_emailSet.insert(email);
			PersonProfile* ppToAdd = new PersonProfile(name, email);
			databaseFile >> attvalCount;
			std::getline(databaseFile, skip);
			for (int i = 0; i != attvalCount; i++) {
				std::getline(databaseFile, att, ',');
				std::getline(databaseFile, val);
				ppToAdd->AddAttValPair(AttValPair(att, val));

				std::string attvalKey = att + val;
				std::vector<std::string>** emailVec = m_rtreeAttValToEmails.search(attvalKey);
				if (emailVec == nullptr) {
					m_rtreeAttValToEmails.insert(attvalKey, new std::vector<std::string>);
					emailVec = m_rtreeAttValToEmails.search(attvalKey);
					m_attvalSet.insert(attvalKey);
				}
				(*emailVec)->push_back(email);
			}
			std::getline(databaseFile, skip);
			m_rtreeEmailToPProfile.insert(email, ppToAdd);
		}
	}
	return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	std::string relevantAttVal = input.attribute + input.value;
	if (m_attvalSet.find(relevantAttVal) != m_attvalSet.end()) {
		return **m_rtreeAttValToEmails.search(relevantAttVal);
	}
	return std::vector<std::string>();
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
	if (m_emailSet.find(email) != m_emailSet.end()) {
		return *m_rtreeEmailToPProfile.search(email);
	}
	return nullptr;
}
