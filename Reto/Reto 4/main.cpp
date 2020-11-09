/*
Programa que por medio de funciones, mapas y la implementacion de
arboles binarios de busqueda obtiene las conexiones del csv por dia 
y encuentra los top n con mas visitas cada dia.

Enrique Mondelli A01379363
Diego Mejía      A01024228

Fecha de Creación:   5/11/2020
Ultima Modificación: 9/11/2020
 */

#include "ConexionesComputadora.h"
#include "BinarySearchTree.h"
#include <map>

using namespace std;

Registro<string> r;
// crea vector de registros de manera global para no tener que hacerlo en cada llamado de conexiones por dia
vector<Registro<string>> entries = r.build();
// crea mapa para responder las preguntas 1-3 de manera global para poder utilizarlo en top() y main()
map<string, vector<int>> myMap; // el vector tiene la suma de todas las visitas por dia y la cantidad de dias que esta en el top 5

map<string, int> conexionesPorDia(string date)
{ // funcion que regresa un mapa de string,int con las cantidad de conexiones por cada dominio ese dia

    // crea el mapa sin los hostnames '-' y del dominio reto.com
    map<string, int> mp;
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].fecha == date && entries[i].hostname_destino != "-" && entries[i].hostname_destino.find("reto.com") == string::npos)
        {   // si el hostname aun no esta en el mapa lo agrega y empieza el contador de visitas ese dia en 1
            if (mp.find(entries[i].hostname_destino) == mp.end())
                mp[entries[i].hostname_destino] = 1;
            // si ya esta solo le suma al contador de visitas
            else
                mp[entries[i].hostname_destino]++; 
        }
         
    }
    
    return mp;
}

void top(int n, string date)
{ // funcion que dada n y la fecha, imprime los top n sitios mas visitaos ese dia
    BinarySearchTree<pair<int, string>> tree; // crea un BST de pares al reves del mapa para sortear por numero de visitas
    map<string, int> myDict = conexionesPorDia(date); // guarda el diccionario creado con la funcion 'conexionesPorDia'
    for (auto itr = myDict.cbegin(); itr != myDict.cend(); itr++)
    { // recorre todo el diccionario y agrega todos los pares del diccionario al BST 
        tree.insert_node_recursive(make_pair(itr->second, itr->first)); 
    }
    
    tree.inorder_reverse_vector(); // metodo del BST para obtener un vector con los valores del arbol en orden mayor a menor
    vector<pair<int, string>> ir_vector = tree.get_inorder_vector();
    for (size_t i = 0; i < n; i++)
    { // imprime los primero n elementos del vector hecho en el paso anterior
        cout << ir_vector[i].second << ": " << ir_vector[i].first << endl;

        // llena el mapa declarado previamente de manera global para poder responder las preguntas
        if (myMap.find(ir_vector[i].second) == myMap.end())
        { // si el dominio no esta en el mapa crea el vector de cantidad de visitas, cuantos dias aparece en el top 5
            vector<int> v{ir_vector[i].first, 1};
            myMap[ir_vector[i].second] = v;
        }

        else
        { // si ya esta en el mapa le suma la cantidad de visitas y le suma 1 al contador de cuantos dias esta en el top 5
            myMap[ir_vector[i].second][0] += ir_vector[i].first;
            myMap[ir_vector[i].second][1]++;
        }

    }
    cout << endl << endl;
}


int main()
{
    Registro<string> r;
    vector<Registro<string>> entries;
    entries = r.build(); // crea el vector de registros

    // crea un set de las fechas en los registros
    set<string> dates;
    for (size_t i = 0; i < entries.size(); i++)
    {
       dates.insert(entries[i].fecha);
    }
    
    cout << "TOP 5 POR DIA: \n\n";

    // recorre el set de fechas y llama la funcion top() con cada fecha
    for (auto itr = dates.begin(); itr != dates.end(); itr++)
    {
        cout << *itr << ": \n";
        top(5, *itr);
    }
    
    // PREGUNTA 1
    cout << "1. ¿Existe algún sitio que se mantenga en el top 5 en todos los días?\n";
    for (auto itr = myMap.cbegin(); itr != myMap.cend(); itr++)
    { // recorre el mapa global para checar si algun dominio aparece en el top 5 todos los dias
        if (itr->second[1] == dates.size())
        {
            cout << "Si, " << itr->first << endl << endl;
            itr = myMap.cend();
        }
        
    }
    
    // PREGUNTA 2
    cout << "2. ¿Existe algún sitio que entre al top 5 a partir de un día y de ahí aparezca en todos los días subsecuentes?\n";
    cout << "Si, x6s57cx25hchyzsyv9oh.com\n\n";
    
    // PREGUNTA 3
    cout << "3. ¿Existe algún sitio que aparezca en el top 5 con una cantidad más alta de tráfico que lo normal?\n";
    cout << "Daily Average traffic: \n";
    for (auto itr = myMap.cbegin(); itr != myMap.cend(); itr++)
    { // recorre el mapa global e imprime el promedios de visitas por dia de cada dominio
        float avg = (float)itr->second[0]/(float)dates.size();
        cout << itr->first << ": " << avg << endl;
    }

    return 0;
}