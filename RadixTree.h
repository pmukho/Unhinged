// RadixTree.h

#ifndef RADIXTREE_INCLUDED
#define RADIXTREE_INCLUDED

//#include <map>
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

	struct RTNode {
		ValueType* val; // if leaf node, its not null
		RTNode* children[VALID_CHAR_RANGE];
		std::string edge[VALID_CHAR_RANGE];
		RTNode() 
		{
			val = nullptr;
			for (int i = 0; i < VALID_CHAR_RANGE; i++) children[i] = nullptr;
		}
		~RTNode()
		{
			delete val;
			for (int i = 0; i < VALID_CHAR_RANGE; i++) {
				delete children[i];
			}
		}
	};

	RTNode* m_root;

	void insertHelper(RTNode* root, std::string, const ValueType& value);
	RTNode* searchHelper(RTNode* root, std::string key) const;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
	: m_root(new typename RadixTree<ValueType>::RTNode)
{}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
	delete m_root; // should be noted that if ValueType is already a pointer type this does not free memory
}

template <typename ValueType>
void RadixTree<ValueType>::insertHelper(RTNode* root, std::string key, const ValueType& value) {
	// CASE 1: Nothing matches key, so add copy of value
	if (key.empty()) {
		if (root->val != nullptr) {
			delete root->val;
		}
		root->val = new ValueType(value);
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

template <typename ValueType>
typename RadixTree<ValueType>::RTNode* RadixTree<ValueType>::searchHelper(typename RadixTree<ValueType>::RTNode* root, std::string key) const
{
	if (key == "") { // where it should be
		if (root->val != nullptr) {
			return root;
		}
		return nullptr;
	}

	int currChar = key[0];
	if (root->children[currChar] == nullptr) { // unrecognized edge
		return nullptr;
	}
	std::string existingEdge = root->edge[currChar];
	int len;
	if (existingEdge.length() < key.length()) { // partial of key could match entire edge
		len = existingEdge.length();
	}
	else { // key could match partial of edge or entire edege
		len = key.length();
	}
	if (existingEdge.substr(0, len) != key.substr(0, len)) { // part of key does not match part of edge
		return nullptr;
	}
	if (existingEdge.length() == len) { // edge matches partial of key, shorten key
		return searchHelper(root->children[currChar], key.substr(existingEdge.length()));
	}
	else { // key does not complete edge
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
