#ifndef SHAPE_RETRIEVAL__FEATURE_GENERATOR_H_
#define SHAPE_RETRIEVAL__FEATURE_GENERATOR_H_

#include "View.hpp"

using namespace std;

void computeDataset();

void indexDataset(InverseIndex &index);

#endif //SHAPE_RETRIEVAL__FEATURE_GENERATOR_H_

#ifndef N_VIEWS
#define N_VIEWS 102
#endif