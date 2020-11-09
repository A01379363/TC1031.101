/*
Clase que, dada una ip y hostname guarda las conexiones
entrantes y salientes en stack y queue respectivamente.

Enrique Mondelli A01379363
Diego Mejía      A01024228

Fecha de Creación:   14/10/2020
Ultima Modificación: 8/11/2020
 */

#pragma once
#include <stack>
#include <queue>
#include <iostream>
#include "CSVParser.h"
#include "Registro.h"

using namespace std;

class ConexionesComputadora
{
private:
    string IP;
    string name;
    stack<Registro<string>> conexiones_entrantes;
    queue<Registro<string>> conexiones_salientes;
    vector<Registro<string>> registros;

public:
    ~ConexionesComputadora() {}
    ConexionesComputadora() = default;
    ConexionesComputadora(string IP, vector<vector<string>> data) : IP(IP)
    {
        for (size_t i = 1; i < data.size(); i++)
        { // loop que recorre todo el vector con los registros
            Registro<string> r(data[i][0], data[i][1], data[i][2], data[i][3], data[i][4], data[i][5], data[i][6], data[i][7]);
            if (name.empty() && r.ip_fuente == this->IP) // si el nombre esta vacio y encontramos el ip dado
                name = r.hostname_fuente;                // le asigna el hostname fuente que le corresponde al ip fuente

            if (r.ip_fuente == this->IP)
            {                                 // si el ip fuente del registro actual es igual al ip dado por el usuario
                conexiones_salientes.push(r); // agrega el registro al queue de conexiones salientes
                registros.push_back(r);       // agrega el registro a un vector
            }
            else if (r.ip_destino == this->IP)
            {                                 // si el ip destino del registro actual es igual al ip dado por el usuario
                conexiones_entrantes.push(r); // agrega el registro al stack de conexiones entrantes
                registros.push_back(r);       // agrega el registro a un vector
            }
        }
    }

    string get_IP() { return IP; } // metodo para obtener el ip

    void print_conexiones_entrantes() // metodo que imprime todos las conexiones entrantes
    {
        stack<Registro<string>> ce = conexiones_entrantes; // se hace una copia del stack original
        cout << "\nConexiones Entrantes:\n";
        while (!ce.empty()) // loop hasta que la copia del stack este vacia
        {
            ce.top().print_registro(); // imprime el registro de hasta arriba del stack
            ce.pop();                  // elimina el registro de hasta arriba del stack
        }
        cout << endl;
    }

    void print_conexiones_salientes() // metodo que imprime todos las conexiones salientes
    {
        queue<Registro<string>> cs = conexiones_salientes; // se hace una copia del queue original
        cout << "\nConexiones Salientes:\n";
        while (!cs.empty()) // loop hasta que la copia del queue este vacia
        {
            cs.front().print_registro(); // imprime el registro que esta hasta enfrente del queue
            cs.pop();                    // elimina el registro que esta hasta arriba del queue
        }
        cout << endl;
    }

    Registro<string> ultima_conexion_entrante() // metodo que regresa la ultima conexion entrante
    {
        if (conexiones_entrantes.empty()) // si el stack esta vacio
        {
            Registro<string> n;
            return n; // regresa un registro vacio
        }
        else                                   // si no esta vacio
            return conexiones_entrantes.top(); // regresa el registro que esta hasta arriba de la pila
    }

    string get_name() { return name; } // metodo que regresa el nombre
    int get_ce_size() { return conexiones_entrantes.size(); } // metodo que regresa el numero de conexiones entrantes
    int get_cs_size() { return conexiones_salientes.size(); } // metodo que regresa el numero de conexiones salientes
    vector<Registro<string>> get_registros() { return registros; } // metodo que regresa el vectro de registros
    
};