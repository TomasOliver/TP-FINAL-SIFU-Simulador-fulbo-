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
    int calidadEquipo;
    char nombreJugador[40];
    char nacionalidadJugador[20];
    int calidadJugador;
    int edad;
    char piernaHabil[10];
    char posicion[20];
    int puntosEquipo;
    int golesEquipo;
    int estadoJugador; //1 activo - 2 inactivo
    int estadoEquipo; //1 activo - 2 inactivo
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
} registroArchivo;

///Prototipado

void cargarArchivo();
registroArchivo cargarRegistro();
jugador pasarJugador(registroArchivo aux);
equipo pasarEquipo(registroArchivo aux);
nodoEquipo* pasar_archivo_a_LDL(nodoEquipo* listaPpl);
void mostrarLDL(nodoEquipo* LDL);
void mostrarNombresEquipos(nodoEquipo* LDL);
nodoarbol* pasar_archivo_a_arbol(nodoarbol* arbol);
int mostrarJugadoresPorNombreEquipo(nodoEquipo* LDL,char nombreEquipo[]);
void mostrarNombresEquipos(nodoEquipo* LDL);
int sistemaLogin(char usu[],char contra[]);
nodoTorneo * pasarListaPPLATabla(nodoEquipo * listaEquipos);

void menuInicial();
void menuPrincipal();
void subMenuJugar(nodoEquipo* listaEquipos);
void subMenuVerEquipos(nodoEquipo* listaEquipos);
void subMenuBuscarJugador(nodoarbol* arbolJugadores);
void subSubMenuSimularPartido(nodoEquipo* listaEquipos);
void subMenuAdministrador(nodoEquipo* listaPpl,nodoarbol* arbolJugadores);
void subSubmenuJugadores(nodoEquipo* listaPpl,nodoarbol* arbolJugadores);

//auxiliares
void cuadroPantalla();

///MAIN
int main()
{


    //cargarArchivo();

    nodoEquipo* listaEquipos=inicEquipo();

    listaEquipos = pasar_archivo_a_LDL(listaEquipos);

    //mostrarLDL(listaEquipos);


    nodoarbol* arbolJugadores=inicArbol();
    arbolJugadores=pasar_archivo_a_arbol(arbolJugadores);

    //inorder(arbolJugadores);


    int opcion,guardado;

    system("title=S.I.F.U (Simulador de Fulbo)");

    limitarCompilador();

///MENU

    menuInicial();
    cuadroPantalla();
    gotoxy(30,24);
    color(7);
    system("pause");

    do
    {
        system("cls");

        menuPrincipal();
        cuadroPantalla();
        fflush(stdin);
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

        case 912:
            subMenuAdministrador(listaEquipos,arbolJugadores);
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

    gotoxy(30,3);
    color(176);
    printf("     _____   _____   _____   _    _     \n");
    gotoxy(30,4);
    color(176);
    printf("    / ____| |_   _| |  ___| | |  | |    \n");
    gotoxy(30,5);
    color(176);
    printf("   | (___     | |   | |_    | |  | |    \n");
    gotoxy(30,6);
    color(176);
    printf("    \\___ \\    | |   |  _|   | |  | |    \n");
    gotoxy(30,7);
    color(176);
    printf("    ____) |  _| |_  | |     | |__| |    \n");
    gotoxy(30,8);
    color(176);
    printf("   |_____/  |_____| |_|      \\____/     \n");
    gotoxy(30,9);
    color(176);
    printf("                                        \n");
    color(7);
    printf("\n\n");
    gotoxy(39,11);
    printf("\x4 SIMULADOR DE FULBO \x4");
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
    j.estadoJugador = aux.estadoJugador;

    return j;
}

equipo pasarEquipo(registroArchivo aux)
{
    equipo e;
    e.calidadEquipo=aux.calidadEquipo;
    strcpy(e.nombreEquipo,aux.nombreEquipo);
    e.puntosEquipo = aux.puntosEquipo;
    e.golesEquipo = aux.golesEquipo;
    e.estadoEquipo = aux.estadoEquipo;
    e.partidosEmpatados=aux.partidosEmpatados;
    e.partidosGanados=aux.partidosGanados;
    e.partidosPerdidos=aux.partidosPerdidos;
    e.partidosJugados=aux.partidosJugados;

    return e;
}

registroArchivo cargarRegistro()
{
    registroArchivo aux;

    printf("Ingrese nombre del equipo: \n");
    fflush(stdin);
    gets(aux.nombreEquipo);
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
    aux.golesEquipo=0;
    aux.estadoJugador=1; //1 activo - 2 de baja
    aux.estadoEquipo=1; //1 activo - 2 de baja
    aux.partidosJugados=0;
    aux.partidosGanados=0;
    aux.partidosEmpatados=0;
    aux.partidosPerdidos=0;

    return aux;
}

void mostrarLDL(nodoEquipo* LDL)
{
    while(LDL!=NULL)
    {
        if(LDL->dato.estadoEquipo==1)
        {
            printf("\n\n-----------Equipo: %s - Calidad equipo:%i - Estado equipo:%s  ------------\n\n",LDL->dato.nombreEquipo,LDL->dato.calidadEquipo,"Alta");
        }
        else
        {
            printf("\n\n-----------Equipo: %s - Calidad equipo:%i - Estado equipo:%s  ------------\n\n",LDL->dato.nombreEquipo,LDL->dato.calidadEquipo,"De baja");
        }
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
        system("cls");
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
        for(int i=1; i<99; i++)
        {
            gotoxy(i,3);
            printf("-");
        }

        cuadroPantalla();
        gotoxy(42,2);
        printf("MENU JUGAR");
        gotoxy(5,5);
        printf("1- Simular Liga\n");
        gotoxy(5,6);
        printf("2- Simular Partido\n");
        gotoxy(5,7);
        printf("0- Volver al menu anterior\n");
        gotoxy(2,24);
        scanf("%i", &opcionPartido);

        switch(opcionPartido)
        {
        case 1:

            break;
        case 2:
            while(continuar=='s')
            {
                subSubMenuSimularPartido(listaEquipos);
                printf("\n Desea hacer otro amistoso? (s/n)\n");
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

    //contarPuntosYGoles(&equipoA->dato, &equipoB->dato, partidoX);

    //printf("\nPuntos y goles del Equipo A: %i %i",equipoA->dato.puntosEquipo, equipoA->dato.golesEquipo);
    //printf("\nPuntos y goles del Equipo B: %i %i",equipoB->dato.puntosEquipo, equipoB->dato.golesEquipo);

    printf("\n\n");

    gotoxy(2,26);
    system("pause");

}

void subMenuAdministrador(nodoEquipo* listaPpl,nodoarbol* arbolJugadores)
{
    int opcionAdmin;
    char usurio[20];
    char contrasenia[20];
    int credenciales=0;
    int seguir = 0;
    system("cls");
    printf("Ingresaste al menu secreto: \n");
    credenciales = sistemaLogin(usurio,contrasenia);

    if(credenciales == 1)
    {
        do
        {
            system("cls");
            printf("MENU ADMIN\n");
            printf("\n1- Sub menu jugadores");
            printf("\n2- Sub menu equipos");
            printf("\n0- Volver al menu anterior\n");
            scanf("%i",&opcionAdmin);
            switch(opcionAdmin)
            {
            case 1:
                system("cls");
                subSubmenuJugadores(listaPpl,arbolJugadores);
                break;
            case 2:
                system("cls");
                printf("Ingresaste a la opcion 2\n");
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
}

void subSubmenuJugadores(nodoEquipo* listaPpl,nodoarbol* arbolJugadores)
{
    int opcionJugadores=0;
    char nombre[30];
    do
    {
        system("cls");
        printf("MENU JUGADORES\n");
        printf("1- Dar de alta un jugador\n");
        printf("2- Dar de baja un jugador\n");
        printf("3- Modificar datos de un jugador\n");
        printf("4- Consultar un jugador\n");
        printf("0- Volver al menu anterior\n");
        scanf("%i",&opcionJugadores);
        switch(opcionJugadores)
        {
        case 1:
            system("cls");
            printf("Ingrese el nombre del jugador que desea dar de alta: \n");
            fflush(stdin);
            gets(nombre);
            altaJugador(arbolJugadores,listaPpl,nombre);
            system("pause");
            break;
        case 2:
            system("cls");
            printf("Ingrese el nombre del jugador que desea dar de baja: \n");
            fflush(stdin);
            gets(nombre);
            bajaJugador(arbolJugadores,listaPpl,nombre);
            system("pause");
            break;
        case 3:
            system("cls");
            printf("Ingrese el nombre del jugador cuyos datos desea modificar: \n");
            fflush(stdin);
            gets(nombre);
            modificarJugador(listaPpl,arbolJugadores,nombre);
            system("pause");
            break;
        case 4:
            system("cls");
            /*
            printf("Ingrese el nombre del jugador cuyos datos desea consultar: \n");
            fflush(stdin);
            gets(nombre);
            system("cls");
            mostrarJugadorLDL(listaPpl,nombre);
            */
            subMenuBuscarJugador(arbolJugadores); ///Es mejor basicamente
            break;
        case 0:
            system("cls");
            break;
        default:
            system("cls");
            printf("Error, opcion invalida. Intente nuevamente...");
            opcionJugadores=-1;
            break;
        }
    }
    while(opcionJugadores!=0);
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

void cuadroPantalla()
{
    // ESQUINAS //
    gotoxy(0,0);
    printf("*");
    gotoxy(0,25);
    printf("*");
    gotoxy(99,0);
    printf("*");
    gotoxy(99,25);
    printf("*");

    // Linea Superior //
    for(int i=1; i<99; i++)
    {
        gotoxy(i,0);
        printf("-");
    }

    // Linea Derecha //
    for(int l=1; l<25; l++)
    {
        gotoxy(99,l);
        printf("|");
    }
    // Linea Inferior//
    for(int j=1; j<99; j++)
    {
        gotoxy(j,25);
        printf("-");
    }
    for(int j=1; j<99; j++)
    {
        gotoxy(j,22);
        printf("-");
    }
    // Linea Izquierda //

    for(int k=1; k<25; k++)
    {
        gotoxy(0,k);
        printf("|");
    }
}

void menuPrincipal()
{
    for(int i=1; i<99; i++)
    {
        gotoxy(i,3);
        printf("-");
    }

    gotoxy(40,2);
    printf("MENU PRINCIPAL\n\n");
    gotoxy(5,5);
    printf("1- Jugar\n");
    gotoxy(5,6);
    printf("2- Ver equipos\n");//Dentro ver jugadores
    gotoxy(5,7);
    printf("3- Buscar jugador\n");
    gotoxy(5,8);
    printf("0- Salir del programa\n");
}
