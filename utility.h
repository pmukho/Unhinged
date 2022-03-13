// utility.h

#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include <functional>
#include "provided.h"

class Hash {
public:
	unsigned int operator()(const AttValPair& av) const;
	unsigned int operator()(const EmailCount& ec) const;
};

bool comp(const EmailCount& ec1, const EmailCount& ec2);

#endif // UTILITY_INCLUDED
