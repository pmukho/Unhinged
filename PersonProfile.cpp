// PersonProfile.cpp

#include "PersonProfile.h"
#include "provided.h"

PersonProfile::PersonProfile(std::string name, std::string email)
//	: m_name(name), m_email(email), m_countAttValPairs(0), m_rtreeAttVal(new RadixTree<std::set<std::string>>), m_attvalVec(new std::vector<AttValPair*>)
//	: m_name(name), m_email(email), m_countAttValPairs(0), m_rtreeAttVal(new RadixTree<std::set<std::string>>), m_attvalVec(new std::vector<AttValPair>)
	: m_name(name), m_email(email), m_countAttValPairs(0), m_rtreeAttVal(RadixTree<std::set<std::string>>()), m_attvalVec(std::vector<AttValPair>())
{}

PersonProfile::~PersonProfile()
{
	//delete m_rtreeAttVal;
	//delete m_attvalVec;
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
	//std::set<std::string>* foundAttSet = m_rtreeAttVal->search(attval.attribute);
	std::set<std::string>* foundAttSet = m_rtreeAttVal.search(attval.attribute);

	if (foundAttSet == nullptr) {
		//m_rtreeAttVal->insert(attval.attribute, std::set<std::string>());
		//foundAttSet = m_rtreeAttVal->search(attval.attribute);
		m_rtreeAttVal.insert(attval.attribute, std::set<std::string>());
		foundAttSet = m_rtreeAttVal.search(attval.attribute);
	}
	if (foundAttSet->find(attval.value) == foundAttSet->end()) {
		std::set<std::string>* foundAttSetUpdated = new std::set<std::string>(*foundAttSet);
		foundAttSetUpdated->insert(attval.value);
		//m_rtreeAttVal->insert(attval.attribute, *foundAttSetUpdated);
		//m_attvalVec->push_back(AttValPair(attval));
		m_rtreeAttVal.insert(attval.attribute, *foundAttSetUpdated);
		m_attvalVec.push_back(AttValPair(attval));
		m_countAttValPairs++;
		delete foundAttSetUpdated;
	}
	
}

int PersonProfile::GetNumAttValPairs() const
{
	return m_countAttValPairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	//invalid argument: attribute_num
	if (attribute_num < 0 || attribute_num >= GetNumAttValPairs()) {
		return false;
	}

	//attval = (*m_attvalVec)[attribute_num];
	attval = m_attvalVec[attribute_num];
	return true;
}