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
	RadixTree<AttValPair>* m_rtreeAttValPair;
};

#endif // ATTRIBUTETRANSLATOR_INCLUDED
