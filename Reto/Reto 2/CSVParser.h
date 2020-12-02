#pragma once
#include <bits/stdc++.h>
using namespace std;

template <class T>
class CSVParser
{
private:
    string file_name;
    vector<vector<T>> file_data;
    int size;

public:
    ~CSVParser() {}
    CSVParser() = default;
    CSVParser(string file_name) : file_name(file_name) {}

    void parse()
    {
        fstream file;
        int size = 0;
        string word, temp;
        file.open(file_name, ios::in);

        while (getline(file, temp))
            size++;

        this->size = size;
        file.clear();
        file.seekg(0);
        string line;
        vector<vector<T>> data(size);
        for (size_t i = 0; i < size; i++)
        {
            getline(file, line);
            stringstream s(line);
            while (s.good())
            {
                getline(s, word, ',');
                data[i].push_back(word);
            }
        }

        file_data = data;
    }

    vector<vector<T>> get_data() { return file_data; }
    int get_size() { return size; }
};
