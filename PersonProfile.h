// PersonProfile.h

#ifndef PERSONPROFILE_INCLUDED
#define PERSONPROFILE_INCLUDED

#include <string>
#include "RadixTree.h"
#include <vector>
#include <set>

struct AttValPair;

class PersonProfile {
public:
	PersonProfile(std::string name, std::string email);
	~PersonProfile();
	std::string GetName() const;
	std::string GetEmail() const;
	void AddAttValPair(const AttValPair& attval);
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
	std::string m_name;
	std::string m_email;
	int m_countAttValPairs;
	//RadixTree<std::vector<std::string>>* m_rtreeAttVal;
	RadixTree<std::set<std::string>>* m_rtreeAttVal;
	//std::set<std::string>* m_attSet;
	std::vector<std::string>* m_attVec;
};

#endif // PERSONPROFILE_INCLUDED
