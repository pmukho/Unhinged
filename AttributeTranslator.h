// AttributeTranslator.h

#ifndef ATTRIBUTETRANSLATOR_INCLUDED
#define ATTRIBUTETRANSLATOR_INCLUDED

#include <vector>
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
	//outer tree to search val for given att, inner tree to serach compatible AttValPair given value associated with att
	RadixTree<RadixTree<std::vector<AttValPair*>*>*>* m_rtreeAttSValSPairCompatible;
};

#endif // ATTRIBUTETRANSLATOR_INCLUDED
