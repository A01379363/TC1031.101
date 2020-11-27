/*
Clase para hacer parsing a un archivo csv
y guardar los datos en un vector 

Enrique Mondelli A01379363
Diego Mejía      A01024228

Fecha de Creación:   5/10/2020
Ultima Modificación: 25/11/2020
*/

#pragma once
#include <bits/stdc++.h>
#include "Registro.h"
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

    vector<Registro<T>> build_entries_vector()
    {
        vector<Registro<T>> registros;
        for (size_t i = 0; i < file_data.size(); i++)
        {
            Registro<string> r(file_data[i][0], file_data[i][1], file_data[i][2], file_data[i][3], file_data[i][4], file_data[i][5], file_data[i][6], file_data[i][7]);
            registros.push_back(r);
        }
        
        return registros;
    }

    int get_size() { return size; }
};
