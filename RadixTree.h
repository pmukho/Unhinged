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
	std::map<std::string, ValueType*>* m_map;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
	: m_map(new std::map<std::string, ValueType*>)
{}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
	for (auto it = m_map->begin(); it != m_map->end(); it++) {
		delete it->second;
	}
	m_map->clear();
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
{
	//m_map[key] = value;
	//ValueType val = value;
	(*m_map)[key] = new ValueType(value);
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{
	return (m_map->find(key)->second);
}

#endif // RADIXTREE_INCLUDED
