/*Este programa lee un archivo .csv y crea vectores con la informacion del archivo
para poder responder preguntas sobre dicha informacion*/
// Enrique Mondelli A01379363
// Diego Mejia      A01024228
// Creado: 22/09/2020
// Modificado: 26/09/2020

#include "CSVParser.h"
#include "Sorter.h"
#include "Search.h"
#include "Registro.h"

template <class T> // funcion generica para comparar ints o strings
bool compare(T &a, T &b)
{
    return a < b;
}

int main()
{
    CSVParser<string> equipo3("equipo3_.csv");        // Crea la instancia con el file_name
    equipo3.parse();                                  // crea el vector de 2 dimensiones para guardar los datos del csv
    vector<vector<string>> data = equipo3.get_data(); // guarda el vector de la instancia CSVParser
    vector<Registro<string>> registros;
    for (size_t i = 1; i < data.size(); i++)
    {
        Registro<string> r(data[i][0], data[i][1], data[i][2], data[i][3], data[i][4], data[i][5], data[i][6], data[i][7]);
        registros.push_back(r);
    }

    //Pregunta 1
    cout
        << "¿Cuántos registros tiene tu archivo? " << equipo3.get_size() << endl;

    //Pregunta 2
    int day1 = 0, day2, count = 0;
    string sday2;
    stringstream s(registros[0].fecha.substr(0, 2)), ss; //obtiene el dia del primer registro
    s >> day1;                                           // converte el string del dia a int
    day2 = day1 + 1;                                     // segundo dia es +1 que el primer dia
    ss << day2;                                          // convierte int a string del dia 2
    ss >> sday2;
    for (size_t i = 1; i < registros.size(); i++) // recorre cada registro de fecha
    {
        string day = registros[i].fecha.substr(0, 2); //obtiene solo el dia de la fecha
        if (day == sday2)                             // si el dia es igual al segundo dia sube el counter
            count++;
        else if (count > 0 && day != sday2) // cuando se pasa del segundo dia acaba el loop
            break;
    }

    cout << "¿Cuántos récords hay del segundo día registrado? " << count << endl;
    cout << "¿Qué día es este? " << sday2 + data[1][0].substr(2) << endl;

    // Pregunta 3 y 5
    QuickSort<string> quick;         //crea instancia de quicksort
    vector<string> source_host_name; // crea vector para guardar host name fuente
    for (size_t i = 1; i < registros.size(); i++)
        source_host_name.push_back(registros[i].hostname_fuente); // agrega todos los host name fuente

    quick.sort(source_host_name, &compare); // ordena el vector con metodo quicksort

    cout << "¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?\n";
    Search<string> search(source_host_name); //crea instancia de busqueda para el vector host name fuente
    // vector para buscar esos nombres en el vector host name fuente
    vector<string> name = {"jeffrey", "betty", "katherine", "scott", "benjamin", "samuel", "raymond", "server"};
    for (size_t i = 0; i < name.size(); i++)
    {
        if (i == name.size() - 1)
            cout << "¿Alguna computadora se llama server.reto.com?" << endl;
        cout << name[i];
        if (search.binary(name[i] + ".reto.com", 0, source_host_name.size() - 1, &compare) != -1)
            cout << ": Si\n"; // Si encuentra el nombre el el vector imprime 'si'
        else
            cout << ": No\n"; // Si no, imprime 'no'
    }

    //Pregunta 4
    cout << "¿Cuál es la dirección de la red interna de la compañía?" << endl;
    string ip;
    vector<string> ip_sep;
    int i = 0;
    while (registros[i].ip_fuente == "-" && registros[i].hostname_fuente != "server.reto.com")
    {
        // si el ip fuente es nulo y el hostname fuente no es server.reto.com, entonces agrega los digitos del ip a un vector
        stringstream s2(registros[i].ip_destino);
        while (s2.good())
        {
            getline(s2, ip, '.');
            ip_sep.push_back(ip);
        }
        i++;
    }

    for (int i = 0; i < ip_sep.size() - 1; i++)
        cout << ip_sep[i] << ".";

    cout << "0" << endl;

    //Pregunta 6
    vector<string> destination_host_name; // crea el vector para guardar hostname destino
    for (size_t i = 1; i < registros.size(); i++)
        destination_host_name.push_back(registros[i].hostname_destino); // agrega todos los hostname destino

    quick.sort(destination_host_name, &compare); // ordena el vector con metodo quicksort

    cout << "¿Qué servicio de mail utilizan (algunas ideas: Gmail, Hotmail, Outlook, Protonmail)?\n";
    Search<string> search2(destination_host_name);                       //crea instancia de busqueda para el vector host name destino
    vector<string> mail = {"gmail", "hotmail", "outlook", "protonmail"}; // vector para buscar esos servicios de mail en el vector hostname destino

    for (size_t i = 0; i < mail.size(); i++)
    {
        cout << mail[i];
        if (search2.binary(mail[i] + ".com", 0, destination_host_name.size() - 1, &compare) != -1)
            cout << ": Si\n"; // Si encuentra el nombre en el vector imprime 'si'
        else
            cout << ": No\n"; // Si no, imprime 'no'
    }

    // Pregunta 7
    vector<int> destination_port; // vector para guardar puertos destino
    QuickSort<int> quick1;        // crea instancia de quicksort para ints
    for (size_t i = 1; i < registros.size(); i++)
    {
        if (registros[i].puerto_destino != "-") //agrega todos los puertos destino menos los que sean '-'
        {
            stringstream s1(registros[i].puerto_destino);
            int port = 0;
            s1 >> port; // convierte el puerto de string a int
            destination_port.push_back(port);
        }
    }

    quick1.sort(destination_port, &compare);   // ordena el vector de puertos destino
    vector<int> destination_port_set;          // crea vector donde se guardaran los puertos destino sin repeticiones
    Search<int> search3(destination_port_set); // crea instancia de busqueda para el vector sin repeticiones
    for (size_t i = 0; i < destination_port.size(); i++)
    { // si no se encuentra el puerto en el vector sin repeticiones, se agrega el puerto al vector
        if (search3.binary(destination_port[i], 0, search3.get_vector().size() - 1, &compare) == -1)
            search3.push(destination_port[i]);
    }

    destination_port_set = search3.get_vector(); // actualizar vector de puerto destino sin repeticiones

    cout << "¿Qué puertos abajo del 1000 se están usando?\n";
    for (size_t i = 0; i < destination_port_set.size(); i++)
    { // imprime el vector de puertos destino sin repeticiones
        cout << destination_port_set[i];
        if (i == destination_port_set.size() - 1)
            cout << endl;
        else
            cout << ", ";
    }

    return 0;
}