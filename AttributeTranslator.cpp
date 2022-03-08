// AttributeTranslator.cpp

#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>

AttributeTranslator::AttributeTranslator()
//	: m_rtreeAttSValSPairCompatible(new RadixTree<RadixTree<std::vector<AttValPair>>>)
//	: m_rtreePairToPair(new RadixTree<std::vector<std::string>>)
	: m_rtreePairToPair(new RadixTree<std::vector<AttValPair>>)
{}

AttributeTranslator::~AttributeTranslator()
{
	//delete m_rtreeAttSValSPairCompatible;
	delete m_rtreePairToPair;
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
			std::vector<AttValPair>* sourceBr = m_rtreePairToPair->search(sourcePair);
			if (sourceBr == nullptr) {
				m_rtreePairToPair->insert(sourcePair, std::vector<AttValPair>());
				sourceBr = m_rtreePairToPair->search(sourcePair);
			}
			auto it = sourceBr->cbegin();
			for (; it != sourceBr->end(); it++) {
				if ((*it) == compatiblePair) {
					break;
				}
			}
			if (it == sourceBr->end()) {
				//sourceBr->push_back(compatiblePair);
				std::vector<AttValPair>* sourceBrUpdated = new std::vector<AttValPair>(*sourceBr);
				sourceBrUpdated->push_back(compatiblePair);
				m_rtreePairToPair->insert(sourcePair, *sourceBrUpdated);
				delete sourceBrUpdated;
			}
		}
	}
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	std::vector<AttValPair> vecToReturn;

	/*std::string toSearch = source.attribute + source.value;
	std::vector<std::string>* vecCompatible = m_rtreePairToPair->search(toSearch);
	if (vecCompatible != nullptr) {
		for (int i = 0; i < vecCompatible->size(); i++) {
			std::string pairOfInterest = (*vecCompatible)[i];
			int splitIndex = pairOfInterest.find(',');
			std::string attC = pairOfInterest.substr(0, splitIndex);
			std::string valC = pairOfInterest.substr(splitIndex);
			vecToReturn.push_back(AttValPair(attC, valC));
		}
	}*/

	std::string toSearch = source.attribute + source.value;
	std::vector<AttValPair>* vecCompatible = m_rtreePairToPair->search(toSearch);
	if (vecCompatible != nullptr) {
		vecToReturn = *vecCompatible;
	}
	
	return vecToReturn;
}

