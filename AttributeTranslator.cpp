// AttributeTranslator.cpp

#include "AttributeTranslator.h"
#include <fstream>

AttributeTranslator::AttributeTranslator()
	: m_rtreeAttValPair(new RadixTree<AttValPair>)
{}

AttributeTranslator::~AttributeTranslator()
{
	delete m_rtreeAttValPair;
}

bool AttributeTranslator::Load(std::string filename)
{
	std::ifstream translatorFile(filename);
	if (!translatorFile) {
		return false;
	}

	if (translatorFile.is_open()) {
		std::string attS, valS, attC, valC, skip;
		while (translatorFile.good()) {
			std::getline(translatorFile, attS, ',');
			std::getline(translatorFile, valS, ','); 
			std::getline(translatorFile, attC, ',');
			std::getline(translatorFile, valC);
		}
	}
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	std::vector<AttValPair> v;
	return v;
}

