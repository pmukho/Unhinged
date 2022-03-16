// MemberDatabase.h

#ifndef MEMBERDATABASE_INCLUDED
#define MEMBERDATABASE_INCLUDED

#include <vector>
#include <set>
#include "PersonProfile.h"
#include "RadixTree.h"

struct AttValPair;

class MemberDatabase {
public:
	MemberDatabase();
	~MemberDatabase();
	bool LoadDatabase(std::string filename);
	std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(std::string email) const;
private:
	RadixTree<PersonProfile*>* m_rtreeEmailToProfile; // maps string email to PersonProfile*
	RadixTree<std::vector<std::string>*>* m_rtreeAttValToEmails; // maps attval string to vector of emails associated with PersonProfile with such AttVal
	std::set<std::string>* m_emailSet; // set of all emails
	std::set<std::string>* m_attvalSet; //set of all attval string
};

#endif // MEMBERDATABASE_INCLUDED
