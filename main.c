#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

const char ARCHIVO[12] = "listas.bin";

typedef struct
{
    char nombre[30];
    char password[15];
    int edad;
    int ganadas;
    int empatadas;
    int perdidas;

} JUGADOR;

typedef struct
{
    JUGADOR jug;
    struct NODO *siguiente;
} NODO;

/**4.Hacer una función que intercale en orden los elementos de dos listas ordenadas  generando  una  nueva  lista.
Se  deben  redireccionar  los punteros, no se deben crear nuevos nodos**/

///Prototipos
void inicLista(NODO ** lista);
void cargarJugador();
void crearNodo(NODO **nuevo, JUGADOR jug);
void agregarPrincipioLista(NODO **lista, NODO *nuevo);
void mostrarPersona(JUGADOR jug);
void recorrerYmostrar(NODO * lista);
void archivoToLista(NODO **lista);
void agregarFinalLista(NODO **lista, NODO *nuevo);

int main()
{
    NODO * lista;

    ///Llamadas
    inicLista(&lista);
    cargarJugador();
    archivoToLista(&lista);
    recorrerYmostrar(lista);


    return 0;
}

void inicLista(NODO ** lista)
{
    (*lista) = NULL;
}

void cargarJugador()
{
    JUGADOR jug;
    char control;

    FILE *file = fopen(ARCHIVO,"ab");

    if (file != NULL)
    {
        do
        {
            printf("Nombre: ");
            fflush(stdin);
            gets(jug.nombre);
            printf("Password: ");
            fflush(stdin);
            gets(jug.password);
            printf("Edad: ");
            fflush(stdin);
            scanf("%d",&jug.edad);
            jug.ganadas = 0;
            jug.empatadas = 0;
            jug.perdidas = 0;

            fwrite(&jug,sizeof(JUGADOR),1,file);

            printf("Cargar otro jugador (s/n)");
            fflush(stdin);
            control = getch();
            system("cls");
        }
        while(control == 's');
        fclose(file);
    }
}

void archivoToLista(NODO **lista)
{
    JUGADOR jug;
    NODO * nuevo;

    FILE *file = fopen(ARCHIVO,"rb");

    if (file != NULL)
    {
        while(fread(&jug,sizeof(JUGADOR),1,file)>0)
        {
            nuevo = (NODO *)malloc(sizeof(NODO));
            crearNodo(&nuevo,jug);
            ///agregarPrincipioLista(lista,nuevo);
            ///agregarFinalLista(lista,nuevo);

            agregarEnOrden(lista,nuevo);
        }
        fclose(file);
    }
}

void crearNodo(NODO **nuevo, JUGADOR jug)
{
    (*nuevo)->jug = jug;
    (*nuevo)->siguiente = NULL;
}

void agregarPrincipioLista(NODO **lista, NODO *nuevo)
{
    if((*lista) == NULL)
    {
        (*lista) = nuevo;
    }
    else
    {
        nuevo->siguiente = (*lista);
        (*lista) = nuevo;
    }
}

void buscarUltimo(NODO * lista, NODO **ultimo)
{
    (*ultimo) = lista;
    while((*ultimo)->siguiente!=NULL)
    {
        (*ultimo) = (*ultimo)->siguiente;
    }
}

void agregarFinalLista(NODO **lista, NODO *nuevo)
{
    NODO * ultimo;
    if((*lista) == NULL)
    {
        (*lista) = nuevo;
    }
    else
    {
        buscarUltimo((*lista),&ultimo);
        ultimo->siguiente = nuevo;
    }
}

void agregarEnOrden(NODO **lista, NODO *nuevo)
{
    if((*lista) == NULL)
    {

        (*lista) = nuevo;

    }
    else
    {

        if(nuevo->jug.edad < (*lista)->jug.edad)
        {
            agregarPrincipioLista(lista,nuevo);
        }
        else
        {
            NODO*ante = (*lista);
            NODO*aux = (*lista);

            while(aux!=NULL && nuevo->jug.edad > aux->jug.edad)
            {
                ante = aux;
                aux = aux->siguiente;
            }
            ante->siguiente = nuevo;
            nuevo->siguiente = aux;
        }
    }
}


void mostrarJugador(JUGADOR jug)
{
    printf("\nNickname: %s\n",jug.nombre);
    printf("Password: %s\n",jug.password);
    printf("Edad: %d\n", jug.edad);
    printf("Ganadas: %d\n", jug.ganadas);
    printf("Empatadas: %d\n", jug.empatadas);
    printf("Perdidas: %d\n", jug.perdidas);
}

void recorrerYmostrar(NODO * lista)
{
    while(lista != NULL)
    {
        mostrarJugador(lista->jug);
        lista = (NODO *)lista->siguiente;
    }
}
