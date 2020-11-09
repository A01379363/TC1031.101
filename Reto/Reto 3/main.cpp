/*
Programa que crea un diccionario de conexiones entrantes
y responde las preguntas del reto 3 utilizando diciconarios y conjuntos

Enrique Mondelli A01379363
Diego Mejía      A01024228

Fecha de Creación:   3/11/2020
Ultima Modificación: 9/11/2020
 */

#include "ConexionesComputadora.h"
#include <map>

using namespace std;

int main()
{
    CSVParser<string> team3("nuevo3.csv");
    set<string> computer_names;
    set<string> computer_ips;

    // crea el vector de registros
    team3.parse();
    vector<vector<string>> data = team3.get_data();
    vector<Registro<string>> entries;
    for (size_t i = 0; i < data.size(); i++)
    {
        Registro<string> r(data[i][0], data[i][1], data[i][2], data[i][3], data[i][4], data[i][5], data[i][6], data[i][7]);
        entries.push_back(r);
    }

    //crea el conjunto de dominios/computadoras que no pertenezcan a reto.com
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].hostname_fuente != "-" && entries[i].hostname_fuente.find("reto.com") == string::npos)
            computer_names.insert(entries[i].hostname_fuente);
        
        if (entries[i].hostname_destino != "-" && entries[i].hostname_destino.find("reto.com") == string::npos)
            computer_names.insert(entries[i].hostname_destino);
    }
    
    // imprime los dominios del conjunto 'computer_names'
    cout << "Dominios: \n";
    for (auto itr = computer_names.begin(); itr != computer_names.end(); itr++)
    {
        cout << *itr << endl;
    }
    cout << endl;

    // crea conjunto de todos los ips
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].ip_fuente != "-")
            computer_ips.insert(entries[i].ip_fuente);
        
        if (entries[i].ip_destino != "-")
            computer_ips.insert(entries[i].ip_destino);
    }

    // crea el diccionario de conexiones computadora con todos los ips del conjunto 'computer_ips'
    map<string, ConexionesComputadora> myDict;
    for (auto itr = computer_ips.begin(); itr != computer_ips.end(); itr++)
    {
        ConexionesComputadora cc(*itr, data);
        myDict.insert({*itr, cc});
    }

    // PREGUNTA 2
    cout << "2. ¿Hay algún nombre de dominio que sea anómalo? ¿cuál es su ip?" << endl;
    // vector con los dominios anomalos encontrados con inspeccion visual
    vector<string> sus_sites{"jv38twy2a4emkiz18yo4.net", "x6s57cx25hchyzsyv9oh.com"};
    int count = 0;
    // recorre todos los registros hasta encontrar los ips de los dominios anomalos
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (sus_sites[count] == entries[i].hostname_destino)
        {
            cout << sus_sites[count] << ": " << entries[i].ip_destino << endl;
            count++;
        }

        if (count == 2)
            i = entries.size();

    }
    cout << endl;

    // PREGUNTA 3
    cout << "3. Cantidad de ips del dominio reto.com que tienen al menos una conexión entrante:" << endl;

    // crea el conjunto de con las ips de dominio reto.com
    set<string> destination_names;
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].hostname_destino.find("reto.com") != string::npos)
            destination_names.insert(entries[i].ip_destino);
    }

    //imprime la cantidad de ips en el conjunto
    cout << destination_names.size() << endl << endl;
    
    // PREGUNTA 4
    bool six = false; // variables que podemos crear para responder la pregunta 6
    string six_date;
    string six_protocol;
    string six_hostname;

    // crea el conjunto de conexiones entrantes que no sean server.reto.com y no usen puertos dhcp
    set<string> incoming_ips;
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].puerto_destino != "67" && entries[i].puerto_fuente != "68" && entries[i].hostname_destino.find("server.reto.com") == string::npos)
        {    
            incoming_ips.insert(entries[i].ip_fuente);
            if ((entries[i].ip_destino == "180.48.230.211" || entries[i].ip_destino == "65.174.75.207") && six == false)
            { // obtiene los datos necesarios para la pregunta 6 si las ips se conectan a los dominios anomalos
                six = true;
                six_date = entries[i].fecha;
                six_protocol = entries[i].puerto_destino;
                six_hostname = entries[i].hostname_fuente;
            }
        }

        if (incoming_ips.size() == 150)
            i = entries.size();
    }

    // imprime todos los ips del conjunto 'incoming ips'
    cout << "4. IPs únicas entrantes de computadoras que no sean server.reto.com o el servidor dhcp: \n";
    for (auto itr = incoming_ips.begin(); itr != incoming_ips.end(); itr++)
    {
        cout << *itr << endl;
    }

    // PREGUNTA 6
    cout << "\n6. Se han comunicado con los datos encontrados en la pregunta 1?\n";
    six ? cout << "Si, " << six_hostname << "\n\n": cout << "No\n\n";

    // PREGUNTA 7 (EXTRA)
    cout << "7. (Extra) Fecha y Protocolo de primer comunicación con dominios anómalos: \n";
    cout << six_date << "    " << six_protocol << endl;

    return 0;
}