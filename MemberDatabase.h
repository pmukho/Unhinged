// MemberDatabase.h

#ifndef MEMBERDATABASE_INCLUDED
#define MEMBERDATABASE_INCLUDED

#include <vector>
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
	//RadixTree<PersonProfile>* m_rtreePProfile;
	RadixTree<PersonProfile> m_rtreePProfile;
};

#endif // MEMBERDATABASE_INCLUDED
