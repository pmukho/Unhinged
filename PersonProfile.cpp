// PersonProfile.cpp

#include "PersonProfile.h"

PersonProfile::PersonProfile(std::string name, std::string email)
	: m_name(name), m_email(email)
{}

PersonProfile::~PersonProfile()
{}

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
	return;
}

int PersonProfile::GetNumAttValPairs() const
{
	return -999;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	return false;
}