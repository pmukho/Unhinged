// PersonProfile.cpp

#include "PersonProfile.h"
#include "provided.h"

PersonProfile::PersonProfile(std::string name, std::string email)
	: m_name(name), m_email(email), m_rtreeAttVal(new RadixTree<std::vector<std::string>>)
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
	if (m_rtreeAttVal->search(attval.attribute) != nullptr) {

	}
}

int PersonProfile::GetNumAttValPairs() const
{
	return -999;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	return false;
}