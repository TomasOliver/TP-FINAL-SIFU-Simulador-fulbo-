#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "string.h"
#include "equipo.h"
#include "jugador.h"
#include "listaPPL.h"

const char nombreArchivo[]= {"archivo.bin"};
const char usuAdmin[20] = "admin";
const char contraAdmin[20] = "total";

///Estructuras

typedef struct
{
    char nombreEquipo[50];
    char nacionalidadEquipo[50];
    int calidadEquipo;
    char nombreJugador[40];
    char nacionalidadJugador[20];
    int calidadJugador;
    int edad;
    char piernaHabil[10];
    char posicion[20];
    int puntosEquipo;
    int golesEquipo;
} registroArchivo;

///Prototipado

void menuInicial();
void cargarArchivo();
registroArchivo cargarRegistro();
nodoEquipo* pasar_archivo_a_LDL(nodoEquipo* listaPpl);
void mostrarLDL(nodoEquipo* LDL);
nodoarbol* pasar_archivo_a_arbol(nodoarbol* arbol);
int mostrarJugadoresPorNombreEquipo(nodoEquipo* LDL,char nombreEquipo[]);
void mostrarNombresEquipos(nodoEquipo* LDL);
int sistemaLogin(char usu[],char contra[]);

///FUNCIONES AUXILIARES
void gotoxy(int x, int y);

int main()
{

    //cargarArchivo();

    nodoEquipo* listaEquipos=inicEquipo();

    listaEquipos = pasar_archivo_a_LDL(listaEquipos);

    //mostrarLDL(listaEquipos);


    nodoarbol* arbolJugadores=inicArbol();
    arbolJugadores=pasar_archivo_a_arbol(arbolJugadores);

    // inorder(arbolJugadores);


    int opcion;
    char nombreBuscado[35];
    nodoarbol* nodoBuscado;
    char continuar='s';
    int flag=0;

    char usurio[20];
    char contrasenia[20];
    int credenciales=0;



    do
    {
        //menuInicial();
        printf("MENU\n\n");
        printf("1- Jugar\n");
        printf("2- Ver equipos\n"); //Dentro ver jugadores
        printf("3- Buscar jugador\n");
        printf("0- Salir del programa\n");
        scanf("%i", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ha elegido la opcion 1\n");
            break;
        case 2:
            while(flag==0)
            {
                mostrarNombresEquipos(listaEquipos);
                printf("\nIngrese nombre del equipo cuyo plantel desee ver: \n");
                fflush(stdin);
                gets(nombreBuscado);
                flag=mostrarJugadoresPorNombreEquipo(listaEquipos,nombreBuscado);
            }
            break;
        case 3:
            while(continuar=='s')
            {
                printf("\nIngrese el nombre del jugador buscado: \n");
                fflush(stdin);
                gets(nombreBuscado);

                nodoBuscado=buscar(arbolJugadores,nombreBuscado);

                if(nodoBuscado==NULL)
                {
                    printf("\nError.El jugador no esta registrado.\n");
                }
                else
                {
                    mostrar_jugador(nodoBuscado->dato);
                }
                printf("Desea buscar otro jugador? (s/n)\n");
                fflush(stdin);
                scanf("%c",&continuar);
            }
            break;

        case 4:

            printf("Ingresaste al menu secreto: \n");
            credenciales = sistemaLogin(usurio,contrasenia);

            break;

        case 0:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Error, opcion invalida. Intente nuevamente...\n");
            opcion=-1;
            break;
        }
    }
    while(opcion!=0);


    return 0;
}

///FUNCIONES

void menuInicial()
{
    gotoxy(55,4);
    printf("\n  #####      ###     #######     #     #");
    gotoxy(35,5);
    printf("\n #     #      #      #           #     #");
    gotoxy(35,6);
    printf("\n #            #      #           #     #");
    gotoxy(35,7);
    printf("\n  #####       #      #####       #     #");
    gotoxy(35,8);
    printf("\n       #      #      #           #     #");
    gotoxy(35,9);
    printf("\n #     # ###  #  ### #       ### #     #");
    gotoxy(35,10);
    printf("\n  #####  ### ### ### #       ###  ##### ");
}

void cargarArchivo()
{
    FILE* archi = fopen(nombreArchivo,"wb");
    registroArchivo aux;
    char continuar = 's';

    if(archi)
    {
        while(continuar=='s')
        {
            aux=cargarRegistro();
            fwrite(&aux,sizeof(registroArchivo),1,archi);
            printf("Desea continuar(s/n): \n");
            fflush(stdin);
            scanf("%c",&continuar);
        }
        fclose(archi);
    }
    else
    {
        printf("El archivo no pudo abrirse \n");
    }
}

nodoEquipo* pasar_archivo_a_LDL(nodoEquipo* listaPpl)
{
    FILE* archi=fopen("archivo.bin","rb");
    registroArchivo aux;
    jugador j;
    equipo e;

    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(registroArchivo),1,archi)>0)
        {
            j.calidadJugador=aux.calidadJugador;
            j.edad = aux.edad;
            strcpy(j.nacionalidadJugador, aux.nacionalidadJugador);
            strcpy(j.nombreJugador, aux.nombreJugador);
            strcpy(j.piernaHabil, aux.piernaHabil);
            strcpy(j.posicion, aux.posicion);

            e.calidadEquipo=aux.calidadEquipo;
            strcpy(e.nacionalidadEquipo, aux.nacionalidadEquipo);
            strcpy(e.nombreEquipo,aux.nombreEquipo);
            e.puntosEquipo=aux.puntosEquipo;
            e.golesEquipo=aux.golesEquipo;

            listaPpl = alta(listaPpl,e,j);
        }
        fclose(archi);
    }
    return listaPpl;
}

registroArchivo cargarRegistro()
{
    registroArchivo aux;

    printf("Ingrese nombre del equipo: \n");
    fflush(stdin);
    gets(aux.nombreEquipo);
    printf("Ingrese nacionalidad del equipo: \n");
    fflush(stdin);
    gets(aux.nacionalidadEquipo);
    printf("Ingrese calidad del equipo: \n");
    scanf("%i",&aux.calidadEquipo);
    printf("Ingrese nombre y apellido del jugador: \n");
    fflush(stdin);
    gets(aux.nombreJugador);
    printf("Ingrese nacionalidad del jugador: \n");
    fflush(stdin);
    gets(aux.nacionalidadJugador);
    printf("Ingrese calidad del jugador: \n");
    scanf("%i",&aux.calidadJugador);
    printf("Ingrese edad del jugador: \n");
    scanf("%i",&aux.edad);
    printf("Ingrese pierna habil del jugador: \n");
    fflush(stdin);
    gets(aux.piernaHabil);
    printf("Ingrese posicion del jugador: \n");
    fflush(stdin);
    gets(aux.posicion);

    aux.puntosEquipo=0;

    return aux;
}

void mostrarLDL(nodoEquipo* LDL)
{
    while(LDL!=NULL)
    {
        printf("\n\n-----------Equipo: %s - Calidad equipo:%i - Nacionalidad:%s  ------------\n\n",LDL->dato.nombreEquipo,LDL->dato.calidadEquipo,LDL->dato.nacionalidadEquipo);
        mostrar_lista_jugadores(LDL->listaDeJugadores);
        LDL=LDL->siguiente;
    }
}

nodoarbol* pasar_archivo_a_arbol(nodoarbol* arbol)
{
    FILE* archi=fopen("archivo.bin","rb");
    registroArchivo aux;
    jugador j;

    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(registroArchivo),1,archi)>0)
        {
            j.calidadJugador=aux.calidadJugador;
            j.edad = aux.edad;
            strcpy(j.nacionalidadJugador, aux.nacionalidadJugador);
            strcpy(j.nombreJugador, aux.nombreJugador);
            strcpy(j.piernaHabil, aux.piernaHabil);
            strcpy(j.posicion, aux.posicion);

            arbol = insertar_nodo_arbol(arbol,crear_nodo_arbol(j));
        }
        fclose(archi);
    }
    return arbol;
}

void mostrarNombresEquipos(nodoEquipo* LDL) ///Sacar
{
    int i=1;
    while(LDL!=NULL)
    {
        printf("%i-%s\n",i,LDL->dato.nombreEquipo);
        i++;
        LDL=LDL->siguiente;
    }
}

int mostrarJugadoresPorNombreEquipo(nodoEquipo* LDL,char nombreEquipo[])
{
    int flag=0;
    while(LDL!=NULL)
    {
        if(strcmpi(LDL->dato.nombreEquipo,nombreEquipo)==0)
        {
            mostrar_lista_jugadores(LDL->listaDeJugadores);
            flag=1;
        }
        LDL=LDL->siguiente;
    }

    if(flag==0)
    {
        printf("\nError, el equipo no existe o no esta registrado...\n");
    }

    return flag;
}


int sistemaLogin(char usu[],char contra[])
{

    int credenciales = 0; // 0 invalidas, 1 validas;

    printf("Ingrese su usuario: ");
    fflush(stdin);
    scanf("%s",usu);

    printf("Ingrese la contrasenia: ");
    fflush(stdin);
    scanf("%s",contra);

    if( (strcmp(usu,usuAdmin)== 0) && (strcmp(contra,contraAdmin) == 0) )
    {
        printf("Ingresaste al modo admin, bienvenido: \n");
        credenciales = 1;
    }
    else
    {
        printf("Ingresaste un usuario o contrasenia incorrecta \n");
        credenciales = 0;
    }

    return credenciales;
}


///FUNCIONES AUXILIARES

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
