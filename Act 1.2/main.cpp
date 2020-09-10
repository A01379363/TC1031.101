#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Sorter.h"

using namespace std;

template <typename T>
int busqSecuencial(T val, vector<T> &v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] == val)
            return i;
    }

    return -1;
}

template <typename T>
int busqBinaria(T val, int first, int last, vector<T> &v)
{
    if (last < first)
        return -1;
    else
    {
        int mid = (first + last) / 2;
        if (v[mid] == val)
            return mid;

        else if (v[mid] > val)
            return busqBinaria(val, first, mid - 1, v);

        else
            return busqBinaria(val, mid + 1, last, v);
    }
}

template <typename T>
void fill_random(vector<T> &arr, int N)
{
    for (size_t i = 0; i < N; i++)
        arr.push_back((T)rand() % 1000 + 1);
}

int main()
{
    char alg, print;
    int n, num_busquedas, val;
    InsertionSort<int> insertion;
    BubbleSort<int> bubble;
    QuickSort<int> quick;
    vector<int> v, vcopy;

    cout << "Ingrese el numero de elementos en el vector: ";
    cin >> n;

    srand(time(0));
    fill_random(v, n);

    cout << "Ingrese el numero de busquedas que quiere realizar: ";
    cin >> num_busquedas;

    for (size_t i = 0; i < num_busquedas; i++)
    {
        vcopy = v;
        cout << "Ingrese el numero que desea buscar en el arreglo: ";
        cin >> val;

        cout << "El numero '" << val << "' fue encontrado en el indice: " << busqSecuencial(val, vcopy) << endl;
        cout << "Utilizando busqueda secuencial en el arreglo desordenado" << endl
             << endl;

        while (true)
        {
            cout << "Que algoritmo de ordenamiento desea usar para poder utilizar la busqueda binaria?" << endl;
            cout << "Ingrese 'i' para el metodo Insercion" << endl;
            cout << "Ingrese 'b' para el metodo Burbuja" << endl;
            cout << "Ingrese 'q' para el metodo Quick" << endl;
            cin >> alg;

            if (alg == 'i')
            {
                cout << "Ordenando con metodo Insercion..." << endl;
                insertion.sort(vcopy);
                break;
            }

            else if (alg == 'b')
            {
                cout << "Ordenando con metodo Burbuja..." << endl;
                bubble.sort(vcopy);
                break;
            }

            else if (alg == 'q')
            {
                cout << "Ordenando con metodo Quick..." << endl;
                quick.sort(vcopy);
                break;
            }

            else
                cout << "Input invalido, intente de nuevo" << endl;
        }

        cout << "El numero '" << val << "' fue encontrado en el indice: " << busqBinaria(val, 0, vcopy.size() - 1, vcopy) << endl;
        cout << "Utilizando busqueda binaria en el arreglo ordenado" << endl
             << endl;
    }

    while (true)
    {
        cout << "Desea imprimir el arreglo? (s/n): ";
        cin >> print;

        if (print == 's')
        {
            cout << "Arreglo Desordenado: " << endl;
            for (size_t i = 0; i < v.size(); i++)
                cout << v[i] << ", ";

            cout << endl;

            cout << "Arreglo Ordenado: " << endl;
            for (size_t i = 0; i < vcopy.size(); i++)
                cout << vcopy[i] << ", ";

            cout << endl;
            break;
        }
        else if (print == 'n')
            break;

        else
            cout << "Input Invalido, intente de nuevo" << endl;
        }

    return 0;
}
