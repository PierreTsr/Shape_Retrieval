#include "InverseIndex.hpp"

void writeIndex(InverseIndex &index)
{
    ofstream file;
    file.open("../data/index.xy");
    for (auto i = index.begin(); i != index.end(); i++)
    {
        file << i->first << endl;
        for (size_t j = 0; j < i->second.size(); j++)
        {
            file << get<0>(i->second[j]) << "," << get<1>(i->second[j])<< ";";
        }
        file << endl;        
    }
    file.close();
}

void readIndex(InverseIndex &index)
{
    ifstream file;
    file.open("../data/index.xy");
    int idx;
    while (file >> idx)
    {
        string line;
        getline(file, line);
        vector<tuple<int,int>> value = {};
        vector<string> tmp;
        boost::split(tmp, line, boost::is_any_of(";"));
        for (size_t i = 0; i < tmp.size() - 1; i++)
        {
            vector<string> tmp2;
            boost::split(tmp2, tmp[i], boost::is_any_of(","));
            assert(tmp2.size()==2);
            value.push_back({atoi(tmp2[0].c_str()), atoi(tmp2[1].c_str())});
            std::cout << idx << " " << tmp2[0] << " " << tmp2[1] << endl;
        }
        index[idx] = value;
    } 
}
