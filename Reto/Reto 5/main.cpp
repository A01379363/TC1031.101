/*
Programa que crea grafos de dirigidos para representar las
conexiones de los registros en un archivo csv, para mejor entender
las conexiones anomalas que ocurren en la red interna de la empresa.

Enrique Mondelli A01379363
Diego Mejía      A01024228

Fecha de Creación:   25/11/2020
Ultima Modificación: 26/11/2020
*/

#include "CSVParser.h"
#include "graph.h"

using namespace std;

int main()
{
    string A, B, C; 
    int a;
    while (a < 1 || a > 254) // while loop hasta que el usuario ingrese un numero del 1-254
    {
        cout << "Ingresa un numero del 1-254 para generar ip interna: ";
        cin >> a;
    }
    // IPs que vamos a usar para responder las preguntas
    A = "192.168.155." + to_string(a); // ip interna
    B = "65.174.75.207"; // x6s57cx25hchyzsyv9oh.com
    C = "203.50.205.137"; // live.com

    CSVParser<string> equipo3("nuevo3.csv"); // intancia para hacer el parse del csv
    equipo3.parse(); // metodo que hace el parsing
    vector<Registro<string>> entries = equipo3.build_entries_vector(); // metodo que crea un vector de registros

    int i = 0; // int para indices de los nodos que se van agregando en los grafos de la pregunta 1 y 2
    int n = 0; // int para indices de los nodos que se van agregando en los grafos de la pregunta 3 y 4
    int vector_idx = 0; // indice para el vector de indices de A, B y C y vector de graphos vacios
    vector<vector<int>> ABC_idxs(10, {-1,-1,-1}); // vector para indices de A, B y C
    bool A_idx, B_idx, C_idx; // bool para checar si A, B y C ya tienen indice
    vector<Graph<string>> empty(10); // vector de graphos vacios
    map<string, Graph<string>> internal_connections, website_connections; // mapa de grafos de conexiones internas, mapa de grafos de conexiones a sitios web (fecha como llave)
    internal_connections[entries[0].fecha] = empty[vector_idx]; // crea el primer elemento del mapa para las pregunta 1 y 2
    website_connections[entries[0].fecha] = empty[vector_idx]; // crea el primer elemento del mapa para las pregunta 3 y 4
    map<string, int> internal_ip_idx; // mapa para saber los indices de cada nodo de los primeros grafos que utiliza la ip como llave
    map<string, int> website_ip_idx; // mapa para saber los indices de cada nodo de los segundos grafos que utiliza la ip como llave
    string prev_day = entries[0].fecha; // string para saber cuando cambia de dia
    for (size_t j = 0; j < entries.size(); j++) // for loop que recorre el vector de registros
    {
        if (j > 0) // si j es mayor a 0 obtiene la fecha del registro pasado
            prev_day = (entries[j - 1]).fecha;
        
        if (prev_day != entries[j].fecha)
        { // si se detecta un cambio de fecha
            vector_idx++; // subimos el indice de los vectores
            i = n = 0; // reseteamos los indices de los nodos
            A_idx = B_idx = C_idx = false; // reseteamos las variable para checar si A, B y C estan indexados
            internal_ip_idx.clear(); // reseteamos los mapas de indices
            website_ip_idx.clear();
            internal_connections[entries[j].fecha] = empty[vector_idx]; // le damos grafos vacios a los mapas de grafos
            website_connections[entries[j].fecha] = empty[vector_idx];
        }

        if (entries[j].ip_destino.find("192.168.155.") != string::npos && entries[j].ip_fuente.find("192.168.155.") != string::npos)
        { // si el ip fuente y destino son de red interna
            if (entries[j].ip_fuente == A && !A_idx)
            { // asigna el indice de A si es el ip fuente
                ABC_idxs[vector_idx][0] = i;
                A_idx = true;
            }

            if (entries[j].ip_destino == A && !A_idx)
            { // Asigna el indice de A si es el ip destino
                if (internal_ip_idx.find(entries[j].ip_fuente) != internal_ip_idx.end())
                    ABC_idxs[vector_idx][0] = i;
                else
                    ABC_idxs[vector_idx][0] = i+1;
                
                A_idx = true;
            }

            if (internal_ip_idx.find(entries[j].ip_fuente) != internal_ip_idx.end())
            { // si la ip fuente ya esta en nuestro mapa 
                if (internal_ip_idx.find(entries[j].ip_destino) != internal_ip_idx.end()) // si la ip destino ya esta en nuestro mapa
                    internal_connections[entries[j].fecha].add_edge(internal_ip_idx[entries[j].ip_fuente], internal_ip_idx[entries[j].ip_destino]);
                    // solo agrega un edge utilizando los indices del mapa de indices
                else
                { // si no esta la ip destino agrega el nodo del ip destino, el indice y el edge
                    internal_connections[entries[j].fecha].add_node(entries[j].ip_destino);
                    internal_ip_idx[entries[j].ip_destino] = i;
                    i++;
                    internal_connections[entries[j].fecha].add_edge(internal_ip_idx[entries[j].ip_fuente], internal_ip_idx[entries[j].ip_destino]);
                }
            }

            else 
            { // si no esta la ip fuente
                if (internal_ip_idx.find(entries[j].ip_destino) != internal_ip_idx.end())
                { // si ya esta la ip destino, crea el nodo de la ip fuente, el indice y el edge
                    internal_connections[entries[j].fecha].add_node(entries[j].ip_fuente);
                    internal_ip_idx[entries[j].ip_fuente] = i;
                    i++;
                    internal_connections[entries[j].fecha].add_edge(internal_ip_idx[entries[j].ip_fuente], internal_ip_idx[entries[j].ip_destino]);
                }
                else
                { // si no esta la ip destino, crea los dos nodos de ip fuente y destino, los indices y el edge
                    internal_connections[entries[j].fecha].add_node(entries[j].ip_fuente);
                    internal_ip_idx[entries[j].ip_fuente] = i;
                    i++;
                    internal_connections[entries[j].fecha].add_node(entries[j].ip_destino);
                    internal_ip_idx[entries[j].ip_destino] = i;
                    i++;
                    internal_connections[entries[j].fecha].add_edge(internal_ip_idx[entries[j].ip_fuente], internal_ip_idx[entries[j].ip_destino]);
                }
            }
        }

        else if (entries[j].hostname_destino != "-")
        { // si no son de la red interna y no son vacios 
            if (entries[j].ip_destino == B && !B_idx)
            { // asigna el indice a B
                ABC_idxs[vector_idx][1] = n;
                B_idx = true;
            }

            if (entries[j].ip_destino == C && !C_idx)
            { // asigna el indice a C
                ABC_idxs[vector_idx][2] = n;
                C_idx = true;
            }

            if (website_ip_idx.find(entries[j].ip_fuente) != website_ip_idx.end())
            { // si el ip fuente ya esta en nuestro mapa
                if (website_ip_idx.find(entries[j].ip_destino) != website_ip_idx.end()) // si el ip destino ya esta en nuestro mapa
                    website_connections[entries[j].fecha].add_edge(website_ip_idx[entries[j].ip_fuente], website_ip_idx[entries[j].ip_destino]);
                    // solo agrega un edge utilizando los indices del mapa de indices
                else
                { // // si no esta la ip destino agrega el nodo del ip destino, el indice y el edge
                    website_connections[entries[j].fecha].add_node(entries[j].ip_destino);
                    website_ip_idx[entries[j].ip_destino] = n;
                    n++;
                    website_connections[entries[j].fecha].add_edge(website_ip_idx[entries[j].ip_fuente], website_ip_idx[entries[j].ip_destino]);
                }
            }

            else 
            { // si el ip fuente no esta en nuestro mapa
                if (website_ip_idx.find(entries[j].ip_destino) != website_ip_idx.end())
                { // si el ip destino ya esta en nuestro mapa, agrega el nodo del ip fuente, el indice y el edge
                    website_connections[entries[j].fecha].add_node(entries[j].ip_fuente);
                    website_ip_idx[entries[j].ip_fuente] = n;
                    n++;
                    website_connections[entries[j].fecha].add_edge(website_ip_idx[entries[j].ip_fuente], website_ip_idx[entries[j].ip_destino]);
                }
                else
                { // si no esta el ip destino en nuestro mapa, agrega los dos nodos de ip fuente y destino, los nodos y el edge
                    website_connections[entries[j].fecha].add_node(entries[j].ip_fuente);
                    website_ip_idx[entries[j].ip_fuente] = n;
                    n++;
                    website_connections[entries[j].fecha].add_node(entries[j].ip_destino);
                    website_ip_idx[entries[j].ip_destino] = n;
                    n++;
                    website_connections[entries[j].fecha].add_edge(website_ip_idx[entries[j].ip_fuente], website_ip_idx[entries[j].ip_destino]);
                }
            }
        }
    }

    // PREGUNTA 1 y 2
    cout << "\n1. ¿Es A el vértice que más conexiones salientes hacia la red interna tiene?\n2. ¿Existen conexiones de las demás computadoras hacia A?\n";
    
    bool pregunta2 = false; // bool para responder la pregunta 2
    int k = 0; // contador para los indices de los grafos
    for (auto& itr: internal_connections) // recorre el mapa de conexiones internas con grafos por dia
    {
        pair<int, int> max; // first: idx, second: size
        cout << itr.first << ":\n"; // imprime la fecha

        for (size_t i = 0; i < itr.second.get_nodes().size(); i++)
        { // recorre la lista de nodos en el grafo
            vector<int> v = itr.second.get_nodes()[i].get_adj(); // vector de adyacencia de cada nodo
            if (v.size() > max.second) 
            { // si el vector es mas grande que el maximo
                max.first = i; // guarda el indice del nodo con mas conexiones
                max.second = v.size(); // guarda el tamano del vector
            }
            if (find(v.begin(), v.end(), ABC_idxs[k][0]) != v.end()) // si se encuentra el nodo A (dado su indice) en el vector de adyacencia
                pregunta2 = true; // la respuesta de la pregunta 2 es si
            
        }

        max.first == ABC_idxs[k][0] ? cout << "1. Si\n" : cout << "1. No\n"; // imprime la respuesta de la pregunta 1 
        pregunta2 ? cout << "2. Si\n\n" : cout << "2. No\n\n"; // imprime la respuesta de la pregunta 2
        pregunta2 = false; // resetea el bool de la pregunta 2
        k++; // incrementa el contador
    }

    // PREGUNTA 3 y 4
    cout << "3. ¿Cuántas computadoras se han conectado a B por día?\n4. ¿Cuántas computadoras se han conectado a C por día?\n";

    k = 0; // contador para los indices de grafos
    for (auto& itr: website_connections) // recorre el mapa de grafos de conexiones a sitios
    {
        cout << itr.first << ":\n"; // imprime la fecha
        int B_count = 0; // contador de computadoras que se conectan a B
        int C_count = 0; // contador de computadora que se conectan a C

        for (size_t i = 0; i < itr.second.get_nodes().size(); i++)
        { // recorre la lista de nodos en el grafo
            vector<int> v = itr.second.get_nodes()[i].get_adj(); // vector de adyacencia de cada nodo
            if (find(v.begin(), v.end(), ABC_idxs[k][1]) != v.end()) // si se encuentra el nodo B (dado su indice) en el vector de adyacencia
                B_count++; // incrementa el contador de B
            
            if (find(v.begin(), v.end(), ABC_idxs[k][2]) != v.end()) // si se encuentra el nodo C (dado su indice) en el vector de adyacencia
                C_count++; // incrementa el contador de C
        }
        
        cout << "3. " << B_count << endl; // imprime la respuesta de la pregunta 3
        cout << "4. " << C_count << endl << endl; // imprime la respuesta de la pregunta 4
        k++; // incrementa el contador
    }

    return 0;
}