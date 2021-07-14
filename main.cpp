/******************************************************************************
    AUTORES:
        1.-Franco Cares Venegas
        2.-Lukas Medina Rozas
    PROFESOR:
        - Fabian Jesus Gonzales Berger
    SECCION: 301
    LINK A VIDEO EN YOUTUBE:
        https://www.youtube.com/watch?v=StlG9xUj9Fw

*******************************************************************************/
#include <iostream>
#include <fstream> //lectura y escritura de archivos
#include <sstream>

using namespace std;


struct nodo {
  int fecha;
  int codigo_hospital;
  int numero_de_camas;
  struct nodo *sgte;
};

typedef struct nodo *tipo_lista;

string nombre_archivo = "camas_ocupadas_csv.txt";


void leeProcesa(string nombre_archivo, tipo_lista & todos_los_datos);
void imprimir_lista_sinPerderDatos (tipo_lista & lista);
void nuevaListaSinDuplicados(tipo_lista todos_los_datos, tipo_lista & los_datos_sin_duplicados);
void seleccionar(tipo_lista todos_los_datos, int codigo_hospital, tipo_lista & datos_de_un_hospital);
void estadistico(tipo_lista los_datos);
int contar(tipo_lista los_datos_sin_duplicar, int anho, int mes, int dia);
void eliminarHospital(tipo_lista & los_datos_sin_duplicar, int codigo_hospital);


int main()
{
    tipo_lista todos_los_datos=NULL;
    tipo_lista los_datos_sin_duplicar= NULL;
    tipo_lista datosUnHospital=NULL;
    int codigo_hospital=0,anho,mes,dia;//Opmenu=0;
    char Opmenu;
    // construccion del menu
     do{
       cout<<endl;
        cout<<"Catastro Camas UCI"<<endl;
        cout<<endl;
        cout << "Ingrese una opcion para continuar.." << endl;
        cout << "a.- Crear Lista desde archivo" << endl;
        cout << "b.- Crear Lista sin duplicados" << endl;
        cout << "c.- Crear Lista desde un hospital" << endl;
        cout << "d.- Mostrar estadísticas de número de camas por Hospital" << endl;
        cout << "e.- Cantidad de camas ocupadas por fecha especificada" << endl;
        cout << "f.- Eliminar registros de camas de un hospital" << endl;
        cout << "g.- Salir" << endl;
        cin>>Opmenu;
        switch(Opmenu){
            case 'a': 
            leeProcesa(nombre_archivo, todos_los_datos);
            imprimir_lista_sinPerderDatos(todos_los_datos);
            break;
            case 'b': 
            nuevaListaSinDuplicados(todos_los_datos, los_datos_sin_duplicar);
            imprimir_lista_sinPerderDatos(los_datos_sin_duplicar);
            cout<<"Lista sin duplicados."<<endl<<endl;
            break;
            case 'c':
            cout<<"Ingrese codigo de hospital: ";
            cin>>codigo_hospital;
            seleccionar(los_datos_sin_duplicar,codigo_hospital, datosUnHospital);
            imprimir_lista_sinPerderDatos(datosUnHospital);
            break;
            case 'd':
            estadistico(los_datos_sin_duplicar);
            break;
            case 'e':
            cout<<"ingrese anho: ";
            cin>>anho;
            cout<<"ingrese mes: ";
            cin>>mes;
            cout<<"ingrese dia: ";
            cin>>dia;
            cout<<contar(los_datos_sin_duplicar,anho,mes,dia);
            break;
            case 'f':
            cout<<"Ingrese codigo de hospital a eliminar: ";
            cin>>codigo_hospital;
            eliminarHospital(los_datos_sin_duplicar,codigo_hospital);
            imprimir_lista_sinPerderDatos(los_datos_sin_duplicar);
            cout<<"Se borraron los hospitales con codigo: "<<codigo_hospital<<endl;

            
            break;
            case 'g':
            cout<<"Apagando Consola..."<<endl;
            break;
            default: cout<<"opcion incorrecta"<<endl<<endl;
            

        } 
    }while(Opmenu!='g');
    // llamadas desde el menu a las funciones
}





void leeProcesa(string nombre_archivo, tipo_lista & todos_los_datos){
  ifstream archivo;
  archivo.open (nombre_archivo.c_str (), ios::in);
  int contador=0;
  if(archivo.is_open()){
    string linea;
    while(getline(archivo,linea,'\n')){
      stringstream ss (linea);
      string temp;
      contador++;
      tipo_lista tempo;
      tipo_lista nuevo = new(struct nodo);
      //agregar dato al final del nodo 
      if (todos_los_datos == NULL)
      {
        todos_los_datos = nuevo;
      }
      else
      {
        tempo = todos_los_datos;
          while (tempo->sgte!=NULL)
            {
              tempo =  tempo->sgte;
            }
            tempo->sgte = nuevo;
      }
      //con este for separo las columnas para guardarlo en cada nodo
      for(int columna=0;getline(ss,temp,';');columna++){
        if(columna==0){
          nuevo->fecha= atoi(temp.c_str());
          //cout<<nuevo->fecha<<endl;
        }
        if(columna==1){
          nuevo->codigo_hospital= atoi(temp.c_str());
          //cout<<nuevo->codigo_hospital<<endl;
        }
        if(columna==2){
          nuevo->numero_de_camas= atoi(temp.c_str());
          //cout<<nuevo->numero_de_camas<<endl;
        }
      }
      nuevo->sgte=NULL;

    }
     cout <<"Se han procesado "<< contador << " registros"<<endl;
  }else {
        cout << "Error en la apertura del archivo "+nombre_archivo;
    }
  archivo.close();//cerramos el archivo

}


//para verificar si estan los datos cargados en los nodos
void imprimir_lista_sinPerderDatos (tipo_lista & lista)
{
  // con variable auxiliar
  tipo_lista q;			// otra variable, para copiar la lista
  q = lista;			// hago que q sea una copia de lista
  while (q->sgte != NULL)   
    {
      cout<<"------------------------"<<endl;
      cout << "Fecha: "<<q->fecha <<endl;
      cout<< "Codigo Hospital: "<<q->codigo_hospital<<endl;
      cout<< "Camas: "<<q->numero_de_camas<<endl;
      cout<<"------------------------"<<endl;
      q = q->sgte;
    }
}




void nuevaListaSinDuplicados(tipo_lista todos_los_datos, tipo_lista &los_datos_sin_duplicados){
  tipo_lista aux;
  aux=todos_los_datos;
  int fechaU = aux->fecha;
  int codigoHospital = aux->codigo_hospital;
  int numeroCama = aux->numero_de_camas;

  tipo_lista q = new (struct nodo); 
  q->fecha=fechaU;
  q->codigo_hospital= codigoHospital;
  q->numero_de_camas = numeroCama;
  q->sgte =los_datos_sin_duplicados;
  los_datos_sin_duplicados=q;

  aux=aux->sgte; 

  while(aux != NULL)
  {  
     int fechaU = aux->fecha;
     int codigoHospital = aux->codigo_hospital;
     int numeroCama = aux->numero_de_camas;

    if(los_datos_sin_duplicados->numero_de_camas != numeroCama)
    {

      tipo_lista q = new (struct nodo);
      q->fecha=fechaU;
      q->codigo_hospital= codigoHospital;
      q->numero_de_camas = numeroCama;
      q->sgte = los_datos_sin_duplicados;
      los_datos_sin_duplicados=q;
                
      aux=aux->sgte;
    }else{
       aux=aux->sgte;
    }

    }
}

void seleccionar(tipo_lista todos_los_datos, int codigo_hospital, tipo_lista & datos_de_un_hospital){

  //hago que auxp sea una copia de la lista todosLosDatos
  tipo_lista auxp = todos_los_datos; 
  tipo_lista auxq= datos_de_un_hospital;

  while(auxp!=NULL){
    if(auxp->codigo_hospital==codigo_hospital){
      auxq=new(nodo);//creo el nuevo nodo 
      auxq->fecha= auxp->fecha;
      //guardo el mismo dato que tengo en auxp numeroCamas en auxq numero de camas 
      auxq->numero_de_camas= auxp->numero_de_camas;
      auxq->codigo_hospital=codigo_hospital;
      auxq->sgte=datos_de_un_hospital;
      datos_de_un_hospital=auxq;

    }
    //si auxp != NULL pase al sgte nodo
    auxp=auxp->sgte;
  }
}


void estadistico(tipo_lista los_datos){


  for(int i=10;i<21;i++){
    tipo_lista aux;
    int contador=0;
    //hago que aux sea una copia de la lista losDatos
    aux=los_datos;
    while(aux!=NULL){
      //si i=codigoDelHospital habra un contador 
      if(i==aux->codigo_hospital){

        contador++;

      }
      aux=aux->sgte;
    }
    cout<<"Hospital "<<i<<" tiene en total: "<<contador<<" camas(s) distintas"<<endl;

  }
}

int contar(tipo_lista los_datos_sin_duplicar, int anho, int mes, int dia)
{
  tipo_lista aux=los_datos_sin_duplicar;
  int contador=0,fechaHastaMes,fechaHastaDia;
  fechaHastaMes = anho*100+mes;//202100+3
  fechaHastaDia = fechaHastaMes*100+dia;//20211200+12
  while(aux!=NULL){
    if(aux->fecha==fechaHastaDia){
      contador++;
    }
    aux= aux->sgte;
  }
  return contador;
}


void eliminarHospital(tipo_lista & los_datos_sin_duplicar, int codigo_hospital){
  tipo_lista aux,aEliminar;
  aux=los_datos_sin_duplicar;

  while(aux!=NULL){
    if(aux->codigo_hospital==codigo_hospital){
      aEliminar=los_datos_sin_duplicar;
      los_datos_sin_duplicar=los_datos_sin_duplicar->sgte;
      aux=aux->sgte;
      delete(aEliminar);
    }else if(aux->sgte!=NULL&&aux->sgte->codigo_hospital==codigo_hospital){
      aEliminar=aux->sgte;
      aux->sgte=aux->sgte->sgte;
      delete(aEliminar);
    }else{
      aux=aux->sgte;
    }

  }


}
