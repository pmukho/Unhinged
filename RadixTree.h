// RadixTree.h

#ifndef RADIXTREE_INCLUDED
#define RADIXTREE_INCLUDED

#include <map>
#include <string>

template <typename ValueType>
class RadixTree {
public:
	RadixTree();
	~RadixTree();
	void insert(std::string key, const ValueType& value);
	ValueType* search(std::string key) const;
private:
	std::map<std::string, ValueType*> m_map;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
	: m_map(std::map<std::string, ValueType*>())
{}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
	for (auto it = m_map.begin(); it != m_map.end(); it++) {
		delete it->second;
	}

	//NOTE: RADIXTREE SHOULD NOT BE RESPONSIBLE FOR DELETING DYNAMICALLY ALLOCATED TYPES
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
{
	auto it = m_map.find(key);
	if (it != m_map.end()) {
		delete it->second;
	}
	ValueType* val = new ValueType(value);
	m_map[key] = val;
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{
	auto it = m_map.find(key);
	if (it != m_map.end()) {
		//return const_cast<ValueType*>(it->second);
		return it->second;
	}
	return nullptr;
}

#endif // RADIXTREE_INCLUDED
