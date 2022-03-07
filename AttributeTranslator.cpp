// AttributeTranslator.cpp

#include "AttributeTranslator.h"
#include <fstream>

AttributeTranslator::AttributeTranslator()
	//: m_rtreeAttSValSPairCompatible(new RadixTree<RadixTree<std::vector<AttValPair*>>>)
	: m_rtreeAttSValSPairCompatible(new RadixTree<RadixTree<std::unordered_set<AttValPair>>>)
{}

AttributeTranslator::~AttributeTranslator()
{
	delete m_rtreeAttSValSPairCompatible;
}

bool AttributeTranslator::Load(std::string filename)
{
	std::ifstream translatorFile(filename);
	if (!translatorFile) {
		return false;
	}

	if (translatorFile.is_open()) {
		std::string attSRead, valSRead, attCRead, valCRead, skip;
		while (translatorFile.good()) {
			std::getline(translatorFile, attSRead, ',');
			std::getline(translatorFile, valSRead, ','); 
			std::getline(translatorFile, attCRead, ',');
			std::getline(translatorFile, valCRead);

			//RadixTree<std::vector<AttValPair*>>* attSBranch = m_rtreeAttSValSPairCompatible->search(attSRead);
			RadixTree<std::unordered_set<AttValPair>>* attSBranch = m_rtreeAttSValSPairCompatible->search(attSRead);
			if (attSBranch == nullptr) { // unknown attribute, start new attSBranch
				//m_rtreeAttSValSPairCompatible->insert(attSRead, RadixTree<std::vector<AttValPair*>>());
				m_rtreeAttSValSPairCompatible->insert(attSRead, RadixTree<std::unordered_set<AttValPair>>());
				attSBranch = m_rtreeAttSValSPairCompatible->search(attSRead);
			}
			//on attSBranch now
			//std::vector<AttValPair*>* valSBranch = attSBranch->search(valSRead);
			std::unordered_set<AttValPair>* valSBranch = attSBranch->search(valSRead);
			if (valSBranch == nullptr) { // unknown val, start new valSBranch
				//attSBranch->insert(valSRead, std::vector<AttValPair*>());
				attSBranch->insert(valSRead, std::unordered_set<AttValPair>());
				valSBranch = attSBranch->search(valSRead);
			}
			//on valSBranch now
			valSBranch->insert(AttValPair(attCRead, valCRead));
			//need to update both trees
			//attSBranch->insert(valSRead, *valSBranch);
			//m_rtreeAttSValSPairCompatible->insert(attSRead, *attSBranch);
		}
	}
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	std::vector<AttValPair> v;
	RadixTree<std::unordered_set<AttValPair>>* attSBranch = m_rtreeAttSValSPairCompatible->search(source.attribute);
	if (attSBranch != nullptr) {
		std::unordered_set<AttValPair>* valSBranch = attSBranch->search(source.value);
		if (valSBranch != nullptr) {
			v = std::vector<AttValPair>(valSBranch->begin(), valSBranch->end());
		}
	}
	return v;
}

