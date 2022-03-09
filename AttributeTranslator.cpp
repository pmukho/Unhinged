// AttributeTranslator.cpp

#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>

AttributeTranslator::AttributeTranslator()
	: m_rtreePairToPair(new RadixTree<std::vector<AttValPair>*>), m_sourceAttvalSet(new std::set<std::string>)
{}

AttributeTranslator::~AttributeTranslator()
{
	for (auto it = m_sourceAttvalSet->begin(); it != m_sourceAttvalSet->end(); it++) {
		std::vector<AttValPair>** compatibleVec = m_rtreePairToPair->search(*it);
		if (compatibleVec != nullptr) { // always true
			delete (*compatibleVec);
		}
	}
	delete m_rtreePairToPair;
	delete m_sourceAttvalSet;
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

			std::string sourcePair(attSRead + valSRead);
			AttValPair compatiblePair(attCRead, valCRead);
			std::vector<AttValPair>** compatibleVec = m_rtreePairToPair->search(sourcePair);
			if (compatibleVec == nullptr) {
				m_rtreePairToPair->insert(sourcePair, new std::vector<AttValPair>);
				compatibleVec = m_rtreePairToPair->search(sourcePair);
				m_sourceAttvalSet->insert(sourcePair);
			}
			(*compatibleVec)->push_back(compatiblePair);
		}
	}
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	std::string sourcePair = source.attribute + source.value;
	if (m_sourceAttvalSet->find(sourcePair) != m_sourceAttvalSet->end()) {
		return **m_rtreePairToPair->search(sourcePair);
	}
	return std::vector<AttValPair>();
}

