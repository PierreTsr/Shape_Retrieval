#ifndef SHAPE_RETRIEVAL__INVERSE_INDEX_H_
#define SHAPE_RETRIEVAL__INVERSE_INDEX_H_

#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

typedef map<int, vector<tuple<int, int>>> InverseIndex;

void writeIndex(InverseIndex &index);

void readIndex(InverseIndex &index);


#endif //SHAPE_RETRIEVAL__INVERSE_INDEX_H_