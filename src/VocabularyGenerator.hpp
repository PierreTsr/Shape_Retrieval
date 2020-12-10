#ifndef SHAPE_RETRIEVAL__VOCABULARY_GENERATOR_H_
#define SHAPE_RETRIEVAL__VOCABULARY_GENERATOR_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <dirent.h>
#include <random>
#include <sys/stat.h>
#include <boost/algorithm/string.hpp>
#include "Vocabulary.hpp"
#include "BagOfFeatures.hpp"

#define DATASET_PATH "/home/pierre/Documents/INF574/psb_v1/benchmark/db"

void buildVocabulary(Vocabulary &vocab, size_t nSamples, size_t vocabSize, size_t nViews);

void collectSamples(MatrixXd &samples, size_t vocabSize, size_t nViews);

void saveVocabulary(Vocabulary& vocab);

#endif //SHAPE_RETRIEVAL__VOCABULARY_GENERATOR_H_