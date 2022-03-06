// AttributeTranslator.cpp

#include "AttributeTranslator.h"

AttributeTranslator::AttributeTranslator()
	: m_rtreeAttValPair(new RadixTree<AttValPair>)
{}

AttributeTranslator::~AttributeTranslator()
{
	delete m_rtreeAttValPair;
}

bool AttributeTranslator::Load(std::string filename)
{
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	std::vector<AttValPair> v;
	return v;
}

