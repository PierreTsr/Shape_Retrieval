#ifndef SHAPE_RETRIEVAL__FEATURE_GENERATOR_H_
#define SHAPE_RETRIEVAL__FEATURE_GENERATOR_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <boost/algorithm/string.hpp>
#include "BagOfFeatures.hpp"

#define N_VIEWS 102

using namespace std;

bool directory_exists(const char *dname);

void computeFeatures(string srcPath);

void computeDataset(string datasetPath);

#endif //SHAPE_RETRIEVAL__FEATURE_GENERATOR_H_