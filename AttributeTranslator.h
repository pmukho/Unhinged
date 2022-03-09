// AttributeTranslator.h

#ifndef ATTRIBUTETRANSLATOR_INCLUDED
#define ATTRIBUTETRANSLATOR_INCLUDED

#include <vector>
//#include <unordered_set>
#include <set>
#include <string>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator {
public:
	AttributeTranslator();
	~AttributeTranslator();
	bool Load(std::string filename);
	std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
	//RadixTree<std::vector<AttValPair>>* m_rtreePairToPair;
	RadixTree<std::vector<AttValPair>*> m_rtreePairToPair;
	std::set<std::string> m_sourceAttvalSet;

};

#endif // ATTRIBUTETRANSLATOR_INCLUDED
