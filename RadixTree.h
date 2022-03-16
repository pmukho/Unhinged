// RadixTree.h

#ifndef RADIXTREE_INCLUDED
#define RADIXTREE_INCLUDED

#include <map>
#include <vector>
#include <string>

const int VALID_CHAR_RANGE = 128;

template <typename ValueType>
class RadixTree {
public:
	RadixTree();
	~RadixTree();
	void insert(std::string key, const ValueType& value);
	ValueType* search(std::string key) const;
private:
	//std::map<std::string, ValueType*> m_map;

	struct RTNode {
		ValueType* val; // if leaf node, its not null
		//RTNode* children[VALID_CHAR_RANGE];
		std::vector<RTNode*> children;
		std::string edge[VALID_CHAR_RANGE];
		RTNode() 
		{
			val = nullptr;
			//for (int i = 0; i < VALID_CHAR_RANGE; i++) children[i] = nullptr;
			for (int i = 0; i < VALID_CHAR_RANGE; i++) {
				children.push_back(nullptr);
			}
		}
		~RTNode()
		{
			delete val;
			//delete[] children;
			/*for (int i = 0; i < VALID_CHAR_RANGE; i++) {
				delete children[i];
			}*/
			for (auto it = children.begin(); it != children.end(); it++) {
				delete (*it);
			}
		}
	};

	RTNode* m_root;

	void insertHelper(RTNode* root, std::string, const ValueType& value);
	RTNode* searchHelper(RTNode* root, std::string key) const;
};

//template <typename ValueType>
//RadixTree<ValueType>::RadixTree()
//	: m_map(std::map<std::string, ValueType*>())
//{}

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
//	: m_root(new RTNode)
	: m_root(new typename RadixTree<ValueType>::RTNode)
{}

//template <typename ValueType>
//RadixTree<ValueType>::~RadixTree()
//{
//	for (auto it = m_map.begin(); it != m_map.end(); it++) {
//		delete it->second;
//	}
//	//NOTE: RADIXTREE SHOULD NOT BE RESPONSIBLE FOR DELETING DYNAMICALLY ALLOCATED TYPES
//}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
	delete m_root;
}

//template <typename ValueType>
//void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
//{
//	auto it = m_map.find(key);
//	if (it != m_map.end()) {
//		delete it->second;
//	}
//	ValueType* val = new ValueType(value);
//	m_map[key] = val;
//}

template <typename ValueType>
void RadixTree<ValueType>::insertHelper(RTNode* root, std::string key, const ValueType& value) {
//void RadixTree<ValueType>::insertHelper(typename RadixTree<ValueType>::RTNode* root, std::string key, const ValueType& value) {
	//return;
	// CASE 1: Free Real Estate
	if (key == "") {
		if (root->val != nullptr) {
			delete root->val;
		}
		//root->val = new ValueType(value);
		ValueType* toInsert = new ValueType(value);
		root->val = toInsert;
		return;
	}

	// CASE 2: key forms own unique edge
	int currChar = key[0];
	if (root->children[currChar] == nullptr) {
		root->children[currChar] = new RTNode;
		root->edge[currChar] = key;
		insertHelper(root->children[currChar], "", value);
		return;
	}

	std::string existingEdge = root->edge[currChar];
	int matchLen = 0;
	while (matchLen < existingEdge.length() && matchLen < key.length() && existingEdge[matchLen] == key[matchLen]) {
		matchLen++;
	}

	// CASE 3: part of key matches entire existing edge
	if (matchLen == existingEdge.length()) {
		insertHelper(root->children[currChar], key.substr(matchLen), value);
		return;
	}

	// CASE 4: entire key matches part of existing edge
	if (matchLen == key.length()) {
		RTNode* toAdd = new RTNode;
		toAdd->children[existingEdge[matchLen]] = root->children[currChar];
		toAdd->edge[existingEdge[matchLen]] = existingEdge.substr(matchLen);
		root->children[currChar] = toAdd;
		root->edge[currChar] = key;
		insertHelper(root->children[currChar], "", value);
		return;
	}

	// CASE 5: part of key matches part of existing edge
	if (matchLen < existingEdge.length() && matchLen < key.length()) {
		RTNode* toAdd = new RTNode;
		toAdd->children[existingEdge[matchLen]] = root->children[currChar];
		toAdd->edge[existingEdge[matchLen]] = existingEdge.substr(matchLen);
		root->children[currChar] = toAdd;
		root->edge[currChar] = key.substr(0, matchLen);
		insertHelper(root->children[currChar], key.substr(matchLen), value);
		return;
	}
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
{
	insertHelper(m_root, key, value);
}

//template <typename ValueType>
//ValueType* RadixTree<ValueType>::search(std::string key) const
//{
//	auto it = m_map.find(key);
//	if (it != m_map.end()) {
//		//return const_cast<ValueType*>(it->second);
//		return it->second;
//	}
//	return nullptr;
//}

template <typename ValueType>
typename RadixTree<ValueType>::RTNode* RadixTree<ValueType>::searchHelper(typename RadixTree<ValueType>::RTNode* root, std::string key) const
{
	if (key == "") {
		if (root->val != nullptr) {
			return root;
		}
		return nullptr;
	}

	int currChar = key[0];
	if (root->children[currChar] == nullptr) {
		return nullptr; 
	}
	std::string existingEdge = root->edge[currChar];
	int len;
	if (existingEdge.length() < key.length()) {
		len = existingEdge.length();
	}
	else {
		len = key.length();
	}
	if (existingEdge.substr(0, len) != key.substr(0, len)) {
		return nullptr;
	}
	if (existingEdge.size() == len) {
		return searchHelper(root->children[currChar], key.substr(existingEdge.size()));
	}
	else {
		return nullptr;
	}
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{
	const RTNode* node = searchHelper(m_root, key);
	if (node != nullptr) {
		return node->val;
	}
	return nullptr;
}

#endif // RADIXTREE_INCLUDED
