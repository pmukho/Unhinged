// MemberDatabase.cpp 

#include "MemberDatabase.h"
#include "provided.h"
#include <fstream>
#include <iostream>

MemberDatabase::MemberDatabase()
	: m_rtreeEmailToProfile(new RadixTree<PersonProfile*>), m_rtreeAttValToEmails(new RadixTree<std::vector<std::string>*>),
	m_emailSet(new std::set<std::string>), m_attvalSet(new std::set<std::string>)
{}

MemberDatabase::~MemberDatabase()
{
	for (auto it = m_emailSet->begin(); it != m_emailSet->end(); it++) {
		PersonProfile** pp = m_rtreeEmailToProfile->search(*it);
		if (pp != nullptr) { //always true
			delete (*pp);
		}
	}
	for (auto it = m_attvalSet->begin(); it != m_attvalSet->end(); it++) {
		std::vector<std::string>** emails = m_rtreeAttValToEmails->search(*it);
		if (emails != nullptr) { // always true
			delete (*emails);
		}
	}
	delete m_rtreeEmailToProfile;
	delete m_rtreeAttValToEmails;
	delete m_emailSet;
	delete m_attvalSet;
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
			if (m_emailSet->find(email) != m_emailSet->end()) {
				return false; // member with email already exists, invalid database
			}
			m_rtreeEmailToProfile->insert(email, new PersonProfile(name, email));
			PersonProfile** ppToAdd = m_rtreeEmailToProfile->search(email);
			m_emailSet->insert(email);

			databaseFile >> attvalCount;
			std::getline(databaseFile, skip);
			// Add all pairs to PersonProfile
			for (int i = 0; i != attvalCount; i++) {
				std::getline(databaseFile, att, ',');
				std::getline(databaseFile, val);
				(*ppToAdd)->AddAttValPair(AttValPair(att, val));

				std::string attvalKey = att + val;
				std::vector<std::string>** emailVec = m_rtreeAttValToEmails->search(attvalKey);
				if (emailVec == nullptr) {
					m_rtreeAttValToEmails->insert(attvalKey, new std::vector<std::string>);
					emailVec = m_rtreeAttValToEmails->search(attvalKey);
					m_attvalSet->insert(attvalKey);
				}
				(*emailVec)->push_back(email);
			}
			std::getline(databaseFile, skip);
			//m_rtreeEmailToProfile->insert(email, ppToAdd);
		}
	}
	return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	std::string relevantAttVal = input.attribute + input.value;
	std::vector<std::string>** matchingMembersVec = m_rtreeAttValToEmails->search(relevantAttVal);
	if (matchingMembersVec != nullptr) {
		return **matchingMembersVec;
	}
	return std::vector<std::string>();
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
	PersonProfile** pp = m_rtreeEmailToProfile->search(email);
	if (pp != nullptr) {
		return *pp;
	}
	//std::cout << " is null, not found by email " << std::endl;
	return nullptr;
}
