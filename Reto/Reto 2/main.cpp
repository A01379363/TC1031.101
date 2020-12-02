/*
Main para reponder las preguntas del reto utilizando la
nueva clase creada ConecionesComputadora

Enrique Mondelli A01379363
Diego Mejía      A01024228

Fecha de Creación:   5/10/2020
Ultima Modificación: 16/10/2020
*/

#include "ConexionesComputadora.h"
#include <iostream>

using namespace std;

int main()
{
    int num = 0;
    while (num > 150 || num < 1) // loop para recibir el numero de ip que se quiere utilizar
    {
        cout << "Ingrese un numero del 1 al 150: ";
        cin >> num;                                           // guarda el numero dado en la variable num
        if (num > 150 || num < 1)                             // si es mayor a 150 o menor a 1
            cout << "Fuera del rango, intente de nuevo.\n\n"; // que ingrese otro numero
    }
    cout << endl;
    // crea la instancia de conexiones computadora con el ip interno obtenido en la parte pasada del reto pero con el numero dado por el usuario convertido a string
    ConexionesComputadora cc("192.168.155." + to_string(num));

    //Pregunta 1
    cout << "¿Qué dirección ip estas usando?\n";
    cout << cc.get_IP() << endl
         << endl; // imprime el ip

    cc.print_conexiones_entrantes(); // imprime las conexiones entrantes
    cc.print_conexiones_salientes(); // imprime las conexiones salientes

    //Pregunta 2
    cout << "¿Cuál fue la ip de la última conexión que recibió esta computadora?\n";
    if (cc.ultima_conexion_entrante().ip_fuente == "") // si no hay conexiones entrantes
        cout << "Esta computadora no recibió conexiones\n\n"; // imprime que no se recibio conexiones

    else
    { // si hay conexiones entrantes
        string ip;
        string ipf = cc.ultima_conexion_entrante().ip_fuente;
        string ipd = cc.ultima_conexion_entrante().ip_destino;
        vector<string> ipf_sep; // vector donde se guardan los digitos del ip fuente
        vector<string> ipd_sep; // vector donde se guardan los digitos del ip destino
        cout << ipf << endl; // imprime el ip fuente de la ultima conexion entrante
        stringstream s(ipf); // string stream para ip fuente
        while (s.good())
        { // agrega todos los numeros del ip fuente al vector excluyendo los puntos
            getline(s, ip, '.');
            ipf_sep.push_back(ip); 
        }
        stringstream ss(ipd); // string stream para ip destino
        while (ss.good())
        { // agrega todos los numeros del ip destino al vector excluyendo los puntos
            getline(ss, ip, '.');
            ipd_sep.push_back(ip);
        }
        ipf_sep.pop_back(); // quita los ultimos digitos del ip fuente
        ipd_sep.pop_back(); // quita los ultimos digitos del ip destino
        cout << "¿Es interna o externa?\n";
        ipf_sep == ipd_sep ? cout << "Interna\n\n" : cout << "Externa\n\n";
        // si el ip fuente es igual al ip destino es interna, si no es externa
    }

    //Pregunta 3
    cout << "¿Cuántas conexiones entrantes tiene esta computadora?\n";
    cout << cc.get_ce_size() << endl
         << endl; // imprime el numero de conexiones entrantes

    //Pregunta 4
    cout << "¿Cuántas conexiones salientes tiene esta computadora?\n";
    cout << cc.get_cs_size() << endl
         << endl; // imprime el numero de conexiones salientes

    //Pregunta Extra
    cout << "¿Tiene esta computadora 3 conexiones seguidas a un mismo sitio web?\n";
    bool check = false; // bool para checar si si hay 3 seguidos
    if (cc.get_registros().size() != 0)
    {
        for (size_t i = 0; i < cc.get_registros().size() - 2; i++)
        { // loop que recorre el vector de registros
            if (cc.get_registros()[i].hostname_destino == cc.get_registros()[i + 1].hostname_destino && cc.get_registros()[i].hostname_destino == cc.get_registros()[i + 2].hostname_destino)
            { // si el hostanme destino es igual en 3 registros seguidos
                check = true; // check se vuelve true
                i = cc.get_registros().size() - 2; // para que se acabe el for sin usar break
            }
        }
    }
    check ? cout << "Si\n\n" : cout << "No\n\n";
    // si check es true imprime si, si no imprime no

    return 0;
}