// queue::push/pop
#include "Mascota.h"
#include "Evaluador.h"
#include <iostream>
#include <list>
#include <fstream>
using namespace std;

//Escribe los datos del objeto mascota dado en un archivo binario con el nombre dado en la posicion dada
//Nota: Se deben poder agregar varias mascotas en un solo archivo
void escribir(string nombre_archivo, Mascota*mascota, int posicion)
{
    //Abre el archivo de forma binaria en un modo semi lectura y escritura para poder modificarlo
    ofstream out(nombre_archivo.c_str(),ios::in);
    if(!out.is_open()){
        //En caso que el archivo no exista abre uno nuevo
        out.open(nombre_archivo.c_str());
    }
    //Se pocisiona en el primer bite que pertenece al registro especificado
    out.seekp(posicion*40);
    //Escribe las variables en el archivo
    out.write((char*)&mascota->edad,4);
    out.write(mascota->nombre.c_str(),36);//Tamaño del campo nombre es 36 por el nombre mas largo del mundo
    out.close();
}

//Devuelve una mascota previamente escrita (con la funcion escribir()) en un archivo binario con nombre dado en la posicion dada
//Nota: Se deben poder leer varias mascotas de un solo archivo
Mascota* leer(string nombre_archivo, int posicion)
{
    Mascota *m = new Mascota(-1,"");
    //Abre el archivo de forma binaria en un modo lectura
    ifstream in(nombre_archivo.c_str());
    //Se posiciona al inicio del registro
    in.seekg(posicion*40);
    //Variables donde se van a almacenar el registro
    int edad;
    char nombre[36];
    //Lectura del archivo en la posicion indicada y la cantidad indicada
    in.read((char*)&edad,4);
    in.read(nombre,36);
    //Se guarda en el objeto de Mascota
    m->edad = edad;
    m->nombre = nombre;
    return m;
}

//Devuelve un vector que contenga todas las mascotas previamente escritas (con la funcion escribir()) en un archivo binario con nombre dado
//Nota: El vector debe contener las mascotas ordenadas de acuerdo a la posicion en la que se escribieron
vector<Mascota*> leerTodos(string nombre_archivo)
{
    vector<Mascota*>respuesta;
    //Abre el archivo de forma binaria en un modo lectura
    ifstream in(nombre_archivo.c_str());
    //Se posiciona al final del archivo
    in.seekg(0,in.end);
    //Guarda la pocision en que esta ubicado(El final del archivo) calculando la cantidad de registros
    float tam = in.tellg()/40;
    //Se posiciona al inicio del archivo
    in.seekg(0);
    //Variables donde se van a almacenar el registro
    //int* edad = new int(0);
    int edad;
    char nombre [36];
    //se lee cada mascota y si no existe es el fin del archivo
    for(int i = 0; i < tam; i++){
        in.read((char*)&edad,4);
        in.read(nombre,36);
        respuesta.push_back(new Mascota(edad, nombre));
    }
    return respuesta;
}

int main ()
{
    //Funcion evaluadora
    evaluar();
    return 0;
}
