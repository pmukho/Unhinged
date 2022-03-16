// PersonProfile.cpp

#include "PersonProfile.h"
#include "provided.h"

PersonProfile::PersonProfile(std::string name, std::string email)
	: m_name(name), m_email(email), m_countAttValPairs(0), m_rtreeAttVal(new RadixTree<std::set<std::string>*>), m_attvalVec(new std::vector<AttValPair*>)
{}

PersonProfile::~PersonProfile()
{
	for (auto it = m_attvalVec->begin(); it != m_attvalVec->end(); it++) {
		std::set<std::string>** attSet = m_rtreeAttVal->search((*it)->attribute);
		if (attSet != nullptr) { // always true
			delete (*attSet);
			*attSet = nullptr; // to avoid delete the same thing twice
		}
		delete (*it);
	}
	delete m_rtreeAttVal;
	delete m_attvalVec;
}

std::string PersonProfile::GetName() const
{
	return m_name;
}

std::string PersonProfile::GetEmail() const
{
	return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{	
	std::set<std::string>** foundAttSet = m_rtreeAttVal->search(attval.attribute);
	if (foundAttSet == nullptr) {
		m_rtreeAttVal->insert(attval.attribute, new std::set<std::string>);
		foundAttSet = m_rtreeAttVal->search(attval.attribute);
	}
	if ((*foundAttSet)->find(attval.value) == (*foundAttSet)->end()) {
		(*foundAttSet)->insert(attval.value);
		m_attvalVec->push_back(new AttValPair(attval));
		m_countAttValPairs++;
	}
}

int PersonProfile::GetNumAttValPairs() const
{
	return m_countAttValPairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	if (attribute_num < 0 || attribute_num >= GetNumAttValPairs()) {
		return false;
	}
	attval = *(*m_attvalVec)[attribute_num];
	return true;
}