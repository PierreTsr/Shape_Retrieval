#include "FeatureGenerator.hpp"

void computeDataset()
{
    double total = 1815;
    for (size_t i = 0; i < 1; i++)
    {   
        #pragma omp parallel for schedule(dynamic, 4)
        for (size_t j = 0; j < 100; j++)
        {
            if (100*1 + j == 762 || 10*i + j > total)
                continue;
            stringstream state;
            state << "Dataset " << 100 * (100*i + j) / total << "% complete" << endl;
            cout << state.str();
            for (size_t k = 0; k < N_VIEWS; k++)
            {
                View v = View(100 * i + j, k);
                v.writeHistogram();
            }
        }
    }
}

void indexDataset(InverseIndex &index)
{
    double total = 1815;
    for (size_t i = 0; i < 1; i++)
    {   
        #pragma omp parallel for schedule(dynamic, 4)
        for (size_t j = 0; j < 100; j++)
        {
            if (100*1 + j == 762 || 10*i + j > total)
                continue;
            stringstream state;
            state << "Dataset " << 100 * (100*i + j) / total << "% complete" << endl;
            cout << state.str();
            for (size_t k = 0; k < N_VIEWS; k++)
            {
                View v = View();
                v.setID(100*i+j, k);
                v.indexize(index);
            }
        }
    }
}