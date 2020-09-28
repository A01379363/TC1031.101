#pragma once
#include <bits/stdc++.h>
#include "CSVParser.h"

using namespace std;

template <class T>
class Registro
{
public:
    T fecha;
    T hora;
    T ip_fuente;
    T puerto_fuente;
    T hostname_fuente;
    T ip_destino;
    T puerto_destino;
    T hostname_destino;
    ~Registro() {}
    Registro() = default;
    Registro(T fecha, T hora, T ip_fuente, T puerto_fuente, T hostname_fuente, T ip_destino, T puerto_destino, T hostname_destino)
        : fecha(fecha), hora(hora), ip_fuente(ip_fuente), puerto_fuente(puerto_fuente), hostname_fuente(hostname_fuente),
          ip_destino(ip_destino), puerto_destino(puerto_destino), hostname_destino(hostname_destino) {}
};