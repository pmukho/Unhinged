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
	RadixTree<PersonProfile*> m_rtreeEmailToPProfile;
	RadixTree<std::vector<std::string>*> m_rtreeAttValToEmails;
	std::set<std::string> m_emailSet;
	std::set<std::string> m_attvalSet;
};

#endif // MEMBERDATABASE_INCLUDED
