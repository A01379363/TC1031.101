/*
Clase que guarda fecha, hora, ip fuente, puerto fuente, 
hostname fuente, ip destino, puerto destino y hostname destino 
de un csv con ese formato.

Enrique Mondelli A01379363
Diego Mejía      A01024228

Fecha de Creación:   5/10/2020
Ultima Modificación: 8/11/2020
*/

#pragma once
#include "CSVParser.h"
#include <iostream>

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

  void print_registro() // metodo que imprime cada atributo del registro
  {
    cout << fecha << ", ";
    cout << hora << ", ";
    cout << ip_fuente << ", ";
    cout << puerto_fuente << ", ";
    cout << hostname_fuente << ", ";
    cout << ip_destino << ", ";
    cout << puerto_destino << ", ";
    cout << hostname_destino << endl;
  }
};