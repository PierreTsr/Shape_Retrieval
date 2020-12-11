#include "FeatureGenerator.hpp"

void computeDataset()
{
    double total = 1815;
    for (size_t i = 0; i < 1; i++)
    {   
        //#pragma omp parallel for schedule(dynamic, 4)
        for (size_t j = 0; j < 3; j++)
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

void computeAllHistogram()
{
    double total = 1815;
    for (size_t i = 14; i < 15; i++)
    {   
        #pragma omp parallel for schedule(dynamic, 2)
        for (size_t j = 0; j < 100; j++)
        {
            if (100*1 + j == 762 || 10*i + j > total)
                continue;
            stringstream state;
            state << "Dataset " << 100 * (100*i + j) / total << "% complete" << endl;
            cout << state.str();

            stringstream filePath;
            filePath << DATASET_PATH << "/" << i << "/m" << 100*i + j << "hist_" << 100*i+j << ".xy";
            ofstream histoFile;
            histoFile.open(filePath.str());
            for (size_t k = 0; k < N_VIEWS; k++)
            {
                histoFile << to_string(100*i + j) << " " << k << endl;
                View v = View(100 * i + j, k);
                v.writeHistogram(histoFile);
                histoFile << "===END===" << endl;
            }
            histoFile.close();
        }
    }
}


void loadAllHistograms(map<tuple<int, int>, View> &dataset)
{
    omp_lock_t writelock;
    omp_init_lock(&writelock);
    double total = 1815;
    for (size_t i = 0; i < 1; i++)
    {   
        #pragma omp parallel for schedule(dynamic, 2)
        for (size_t j = 0; j < 100; j++)
        {
            if (100*1 + j == 762 || 10*i + j > total)
                continue;
            stringstream state;
            state << "Dataset " << 100 * (100*i + j) / total << "% complete" << endl;
            cout << state.str();

            stringstream filePath;
            filePath << DATASET_PATH << "/" << i << "/m" << 100*i + j << "hist_" << 100*i+j << ".xy";
            ifstream histoFile;
            histoFile.open(filePath.str());
            int model, view;
            string buf;
            while(histoFile >> model && histoFile >> view)
            {
                histoFile >> buf;
                View v;
                v.model = model;
                v.view = view;
                v.Histo.setFromStream(histoFile);
                omp_set_lock(&writelock);
                dataset[{model, view}] = v;
                omp_unset_lock(&writelock);
            }
            histoFile.close();
        }
    }
}