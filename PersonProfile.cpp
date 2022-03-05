// PersonProfile.cpp

#include "PersonProfile.h"
#include "provided.h"

PersonProfile::PersonProfile(std::string name, std::string email)
	: m_name(name), m_email(email), m_rtreeAttVal(new RadixTree<std::vector<std::string>>), m_attVec(new std::vector<std::string>)
{}

PersonProfile::~PersonProfile()
{
	delete m_rtreeAttVal;
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
	//return;
	std::vector<std::string>* foundAttVec = m_rtreeAttVal->search(attval.attribute);
	if (foundAttVec != nullptr) { // existing attribute
		foundAttVec->push_back(attval.value);
	}
	else { // new attribute
		std::vector<std::string> toAddVec;
		toAddVec.push_back(attval.value);
		m_rtreeAttVal->insert(attval.attribute, toAddVec);
		m_attVec->push_back(attval.attribute);
	}
}

int PersonProfile::GetNumAttValPairs() const
{
	int countAttValPairs = 0;
	for (int i = 0; i < m_attVec->size(); i++) {
		std::string attOfInterest = (*m_attVec)[i];
		countAttValPairs += m_rtreeAttVal->search(attOfInterest)->size();
	}
	return countAttValPairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	//invalid argument: attribute_num
	if (attribute_num < 0 || attribute_num > GetNumAttValPairs()) {
		return false;
	}

	int stepsTaken = 0;
	for (int i = 0; i < m_attVec->size(); i++) {
		std::string attOfInterest = (*m_attVec)[i];
		std::vector<std::string>* valsForAtt = m_rtreeAttVal->search(attOfInterest);
		for (int j = 0; j < valsForAtt->size(); j++) {
			stepsTaken++;
			if (stepsTaken == attribute_num) {
				attval = AttValPair(attOfInterest, (*valsForAtt)[j]);
				return true;
			}
		}
	}
	//unreachable
	return false;
}