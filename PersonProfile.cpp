// PersonProfile.cpp

#include "PersonProfile.h"
#include "provided.h"

PersonProfile::PersonProfile(std::string name, std::string email)
//: m_name(name), m_email(email), m_countAttValPairs(0), m_rtreeAttVal(new RadixTree<std::set<std::string>>), m_attVec(new std::vector<std::string>)
	: m_name(name), m_email(email), m_countAttValPairs(0), m_rtreeAttVal(new RadixTree<std::set<std::string>>), m_attvalVec(new std::vector<AttValPair*>)
{}

PersonProfile::~PersonProfile()
{
	delete m_rtreeAttVal;
	//m_attVec->clear();
	for (auto it = m_attvalVec->begin(); it != m_attvalVec->end(); it++) {
		delete (*it);
	}
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
	std::set<std::string>* foundAttSet = m_rtreeAttVal->search(attval.attribute);
	if (foundAttSet != nullptr) { // existing attribute
		if (foundAttSet->insert(attval.value).second == false) { // existing attribute-value pair, fail to insert
			return;
		}
	}
	else {
		std::set<std::string> toAddSet;
		toAddSet.insert(attval.value);
		m_rtreeAttVal->insert(attval.attribute, toAddSet);
		//m_attVec->push_back(attval.attribute);
	}
	m_attvalVec->push_back(new AttValPair(attval.attribute, attval.value));
	m_countAttValPairs++;
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

	//int stepsTaken = 0;
	//for (int i = 0; i < m_attVec->size(); i++) {
	//	std::string attOfInterest = (*m_attVec)[i];
	//	std::set<std::string>* valsForAtt = m_rtreeAttVal->search(attOfInterest);
	//	for (auto it = valsForAtt->cbegin(); it != valsForAtt->end(); it++) {
	//		if (stepsTaken == attribute_num) {
	//			attval = AttValPair(attOfInterest, *it);
	//			return true;
	//		}
	//		stepsTaken++;
	//	}
	//}
	////unreachable
	//return false;
	attval.attribute = (*m_attvalVec)[attribute_num]->attribute;
	attval.value = (*m_attvalVec)[attribute_num]->value;
	return true;
}