// AttributeTranslator.cpp

#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>

AttributeTranslator::AttributeTranslator()
//	: m_rtreeAttSValSPairCompatible(new RadixTree<RadixTree<std::vector<AttValPair>>>)
	: m_rtreePairToPair(new RadixTree<std::vector<std::string>>)
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

			//RadixTree<std::vector<AttValPair>>* attSBranch = m_rtreeAttSValSPairCompatible->search(attSRead);
			//if (attSBranch == nullptr) { // unknown attribute, start new attSBranch
			//	m_rtreeAttSValSPairCompatible->insert(attSRead, RadixTree<std::vector<AttValPair>>());
			//	attSBranch = m_rtreeAttSValSPairCompatible->search(attSRead);
			//}
			////on attSBranch now
			//std::vector<AttValPair>* valSBranch = attSBranch->search(valSRead);
			//if (valSBranch == nullptr) { // unknown val, start new valSBranch
			//	attSBranch->insert(valSRead, std::vector<AttValPair>());
			//	valSBranch = attSBranch->search(valSRead);
			//}
			////on valSBranch now
			//auto it = valSBranch->cbegin();
			//for (; it != valSBranch->end(); it++) {
			//	if ((*it).attribute == attCRead && (*it).value == valCRead) {
			//		break;
			//	}
			//}
			//if (it == valSBranch->end()) {
			//	valSBranch->push_back(AttValPair(attCRead, valCRead));
			//	attSBranch->insert(valSRead, *valSBranch);
			//	m_rtreeAttSValSPairCompatible->insert(attSRead, *attSBranch);
			//}

			std::string sourcePair(attSRead + "," + valSRead);
			std::string compatiblePair(attCRead + "," + valCRead);
			std::vector<std::string>* sourceBr = m_rtreePairToPair->search(sourcePair);
			if (sourceBr == nullptr) {
				m_rtreePairToPair->insert(attSRead, std::vector<std::string>());
				sourceBr = m_rtreePairToPair->search(attSRead);
			}
			auto it = sourceBr->cbegin();
			for (; it != sourceBr->end(); it++) {
				if ((*it) == compatiblePair) {
					break;
				}
			}
			if (it == sourceBr->end()) {
				sourceBr->push_back(compatiblePair);
			}
			
			for (int i = 0; i != sourceBr->size(); i++) {
				std::cout << (*sourceBr)[i] << std::endl;
			}
		}
	}
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	std::vector<AttValPair> vecToReturn;

	std::string toSearch = source.attribute + source.value;
	std::vector<std::string>* vecCompatible = m_rtreePairToPair->search(toSearch);
	if (vecCompatible != nullptr) {
		for (int i = 0; i < vecCompatible->size(); i++) {
			std::string pairOfInterest = (*vecCompatible)[i];
			int splitIndex = pairOfInterest.find(',');
			std::string attC = pairOfInterest.substr(0, splitIndex);
			std::string valC = pairOfInterest.substr(splitIndex);
			vecToReturn.push_back(AttValPair(attC, valC));
		}
	}
	
	return vecToReturn;
}

