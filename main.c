#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "equipo.h"
#include "jugador.h"
#include "listaPPL.h"
#include "partido.h"
#include "gotoxy.h"
#include "torneo.h"

const char nombreArchivo[]= {"archivo.bin"};
const char usuAdmin[20] = "admin";
const char contraAdmin[20] = "admin";

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
jugador pasarJugador(registroArchivo aux);
equipo pasarEquipo(registroArchivo aux);
nodoEquipo* pasar_archivo_a_LDL(nodoEquipo* listaPpl);
void mostrarLDL(nodoEquipo* LDL);
nodoarbol* pasar_archivo_a_arbol(nodoarbol* arbol);
int mostrarJugadoresPorNombreEquipo(nodoEquipo* LDL,char nombreEquipo[]);
void mostrarNombresEquipos(nodoEquipo* LDL);
int sistemaLogin(char usu[],char contra[]);
nodoTorneo * pasarListaPPLATabla(nodoEquipo * listaEquipos);

void subMenuJugar(nodoEquipo* listaEquipos);
void subMenuVerEquipos(nodoEquipo* listaEquipos);
void subMenuBuscarJugador(nodoarbol* arbolJugadores);
void subSubMenuSimularPartido(nodoEquipo* listaEquipos);

///MAIN
int main()
{

    //cargarArchivo();

    nodoEquipo* listaEquipos=inicEquipo();

    listaEquipos = pasar_archivo_a_LDL(listaEquipos);

    //mostrarLDL(listaEquipos);


    nodoarbol* arbolJugadores=inicArbol();
    arbolJugadores=pasar_archivo_a_arbol(arbolJugadores);

    // inorder(arbolJugadores);


    int opcion,opcionAdmin,guardado;
    char continuarPartido = 's';

    char usurio[20];
    char contrasenia[20];
    int credenciales=0;
    int seguir = 0;

    system("title=S.I.F.U (Simulador de Fulbo)");

///MENU
    modificarJugador(listaEquipos,arbolJugadores,"Enzo Perez");
    //menuInicial();

    do
    {
        //system("cls");

        printf("MENU\n\n");
        printf("1- Jugar\n");
        printf("2- Ver equipos\n");//Dentro ver jugadores
        printf("3- Buscar jugador\n");
        printf("0- Salir del programa\n");

        scanf("%i", &opcion);

        switch (opcion)
        {
        case 1:
            subMenuJugar(listaEquipos);
            break;
        case 2:
            subMenuVerEquipos(listaEquipos);
            break;
        case 3:
            subMenuBuscarJugador(arbolJugadores);
            break;

        case 4:
            system("cls");
            printf("\n\nIngresaste al menu secreto: \n");
            credenciales = sistemaLogin(usurio,contrasenia);

            if(credenciales == 1)
            {
                do
                {
                    printf("\n\nMENU ADMIN\n");
                    printf("\n1- Listados");
                    printf("\n2- Alta");
                    printf("\n3- Baja");
                    printf("\n4- Modificacion");
                    printf("\n0- Volver al menu anterior\n");
                    scanf("%i",&opcionAdmin);
                    switch(opcionAdmin)
                    {
                    case 1:
                        system("cls");
                        printf("Ingresaste a la opcion 1\n");
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        printf("Ingresaste a la opcion 2\n");
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        printf("Ingresaste a la opcion 3\n");
                        system("pause");
                        break;
                    case 4:
                        system("cls");
                        printf("Ingresaste a la opcion 4\n");
                        system("pause");
                        break;
                    case 0:
                        system("cls");
                        break;
                    default:
                        system("cls");
                        printf("Error, opcion invalida. Intente nuevamente...");
                        opcionAdmin=-1;
                        break;
                    }
                }
                while(opcionAdmin!=0);
            }

            break;

        case 0:
            printf("Desea guardar los datos modificados en partida? \n1- si / 2- no \n");
            scanf("%i",&guardado);

            printf("\nSaliendo del programa...\n");
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
    system("cls");
    system("COLOR 0");

    gotoxy(40,5);
    color(176);
    printf("     _____   _____   _____   _    _     \n");
    gotoxy(40,6);
    color(176);
    printf("    / ____| |_   _| |  ___| | |  | |    \n");
    gotoxy(40,7);
    color(176);
    printf("   | (___     | |   | |_    | |  | |    \n");
    gotoxy(40,8);
    color(176);
    printf("    \\___ \\    | |   |  _|   | |  | |    \n");
    gotoxy(40,9);
    color(176);
    printf("    ____) |  _| |_  | |     | |__| |    \n");
    gotoxy(40,10);
    color(176);
    printf("   |_____/  |_____| |_|      \\____/     \n");
    gotoxy(40,11);
    color(176);
    printf("                                        \n");
    color(7);
    printf("\n\n");
    gotoxy(49,13);
    printf("\x4 SIMULADOR DE FULBO \x4");
    color(7);
    gotoxy(40,15);
    system("pause");
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
            j=pasarJugador(aux);

            e=pasarEquipo(aux);

            listaPpl = alta(listaPpl,e,j);
        }
        fclose(archi);
    }
    return listaPpl;
}

jugador pasarJugador(registroArchivo aux)
{
    jugador j;

    j.calidadJugador=aux.calidadJugador;
    j.edad = aux.edad;
    strcpy(j.nacionalidadJugador, aux.nacionalidadJugador);
    strcpy(j.nombreJugador, aux.nombreJugador);
    strcpy(j.piernaHabil, aux.piernaHabil);
    strcpy(j.posicion, aux.posicion);
    j.estadoJugador = 1;

    return j;
}

equipo pasarEquipo(registroArchivo aux)
{
    equipo e;

    e.calidadEquipo=aux.calidadEquipo;
    strcpy(e.nacionalidadEquipo, aux.nacionalidadEquipo);
    strcpy(e.nombreEquipo,aux.nombreEquipo);
    e.puntosEquipo = 0;
    e.golesEquipo = 0;
    e.estadoEquipo = 1;

    return e;
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
            j=pasarJugador(aux);

            arbol = insertar_nodo_arbol(arbol,crear_nodo_arbol(j));
        }
        fclose(archi);
    }
    return arbol;
}

void mostrarNombresEquipos(nodoEquipo* LDL) ///Sacar
{
    while(LDL!=NULL)
    {
        printf("-%s\n",LDL->dato.nombreEquipo);
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
            system("cls");
            mostrar_lista_jugadores(LDL->listaDeJugadores);
            flag=1;
        }
        LDL=LDL->siguiente;
    }

    if(flag==0)
    {
        system("cls");
        printf("Error, el equipo no existe o no esta registrado. Intente nuevamente...\n");
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
        printf("\nIngresaste al modo admin, bienvenido: \n");
        credenciales = 1;
    }
    else
    {
        printf("Ingresaste un usuario o contrasenia incorrecta \n");
        credenciales = 0;
    }

    return credenciales;
}

void subMenuVerEquipos(nodoEquipo* listaEquipos)
{
    char nombreBuscado[35];
    char contEquipos;
    int flag=0;
    do
    {
        system("cls");
        flag=0;
        while(flag==0)
        {
            mostrarNombresEquipos(listaEquipos);
            printf("\nIngrese nombre del equipo cuyo plantel desee ver: \n");
            fflush(stdin);
            gets(nombreBuscado);
            flag=mostrarJugadoresPorNombreEquipo(listaEquipos,nombreBuscado);
        }
        printf("\nDesea ver otro equipo? (s/n)\n");
        fflush(stdin);
        scanf("%c",&contEquipos);
    }
    while(contEquipos=='s');
    system("cls");
}

void subMenuBuscarJugador(nodoarbol* arbolJugadores)
{
    char continuar = 's';
    char nombreBuscado[35];
    nodoarbol* nodoBuscado;

    while(continuar=='s')
    {
        system("cls");
        printf("Ingrese el nombre y apellido del jugador buscado: \n");
        fflush(stdin);
        gets(nombreBuscado);

        nodoBuscado=buscar(arbolJugadores,nombreBuscado);

        if(nodoBuscado==NULL)
        {
            printf("\nError.El jugador no esta registrado.\n");
        }
        else
        {
            system("cls");
            mostrar_jugador(nodoBuscado->dato);
        }
        printf("Desea buscar otro jugador? (s/n)\n");
        fflush(stdin);
        scanf("%c",&continuar);
    }
    system("cls");
}

void subMenuJugar(nodoEquipo* listaEquipos)
{
    int opcionPartido;
    char continuar='s';

    system("cls");

    do
    {
        printf("1- Simular Liga\n");
        printf("2- Simular Partido\n");
        printf("0- Volver al menu anterior\n");
        scanf("%i", &opcionPartido);

        switch(opcionPartido)
        {
        case 1:

            break;
        case 2:
            while(continuar=='s')
            {
                subSubMenuSimularPartido(listaEquipos);
                printf("\nDesea hacer otro amistoso? (s/n)\n");
                fflush(stdin);
                scanf("%c",&continuar);
                system("cls");
            }
            break;
        case 0:
            system("cls");
            break;
        default:
            system("cls");
            printf("Opcion invalida. Ingrese nuevamente...\n");
        }
    }
    while(opcionPartido!=0);
}

void subSubMenuSimularPartido(nodoEquipo* listaEquipos)
{
    char nombreEquipoA[20];
    char nombreEquipoB[20];
    int flag=0;

    system("cls");

    mostrarNombresEquipos(listaEquipos);

    while(flag==0)
    {
        printf("\nIngrese el nombre del primer equipo\n");
        fflush(stdin);
        gets(nombreEquipoA);

        printf("\nIngrese el nombre del segundo equipo\n");
        fflush(stdin);
        gets(nombreEquipoB);


        if(existeEquipo(listaEquipos,nombreEquipoA) && existeEquipo(listaEquipos,nombreEquipoB))
        {
            flag=1;
        }
        else if(existeEquipo(listaEquipos,nombreEquipoA)!=1 && existeEquipo(listaEquipos,nombreEquipoB)!=1)
        {
            printf("Error. Los equipos ingresados no son validos. Intente nuevamente...\n");
        }
        else if(existeEquipo(listaEquipos,nombreEquipoA)!=1)
        {
            printf("Error. El equipo ingresado %s no es valido. Intente nuevamente...\n",nombreEquipoA);
        }
        else
        {
            printf("Error. El equipo ingresado %s no es valido. Intente nuevamente...\n",nombreEquipoB);
        }

    }
    system("cls");

    partido partidoX;

    nodoEquipo* equipoA = buscar_equipo(listaEquipos,nombreEquipoA);
    nodoEquipo* equipoB = buscar_equipo(listaEquipos,nombreEquipoB);

    simularPartido(equipoA->dato, equipoB->dato, &partidoX, 2);
    resumenPartido(equipoA->dato, equipoB->dato, partidoX);

    contarPuntosYGoles(&equipoA->dato, &equipoB->dato, partidoX);

    printf("\nPuntos y goles del Equipo A: %i %i",equipoA->dato.puntosEquipo, equipoA->dato.golesEquipo);
    printf("\nPuntos y goles del Equipo B: %i %i",equipoB->dato.puntosEquipo, equipoB->dato.golesEquipo);

    printf("\n\n");

    system("pause");

}

/*
void subMenuJugarTorneo(nodoEquipo * listaEquipos)
{
    nodoTorneo * tabla = inicListaTorneo();
    tabla = pasarListaPPLATabla(listaEquipos,tabla);

    printf("\nTorneo SIFU:");
    mostrarTabla(tabla);

    char continuarFecha = 's';
    int contarFecha = 0;
    while(continuarFecha = 's')
    {
        simularPartido(arr)
    }


}

nodoTorneo * pasarListaPPLATabla(nodoEquipo * listaEquipos, nodoTorneo * tabla)
{
    nodoTorneo * auxTabla;

    while(listaEquipos!=NULL)
    {
        auxTabla =crearNodoTorneo(listaEquipos->dato);
        tabla = agregarEnOrdenNombre(tabla,auxTabla);
        listaEquipos= listaEquipos->siguiente;
    }
    return tabla;
}
*/
