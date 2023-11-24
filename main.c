#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "equipo.h"
#include "jugador.h"
#include "listaPPL.h"
#include "partido.h"
#include "gotoxy.h"
#include "torneo.h"

///Constantes
const char nombreArchivo[]= {"archivo.bin"}; ///datos de equipos y jugadores
const char nombreArchivoTorneo[]= {"archivoTorneo.bin"}; ///Datos del torneo
const char nombreArchivoOriginal[]= {"archivoOriginal.bin"}; ///datos de equipos y jugadores base
const char nombreArchivoTorneoOriginal[]= {"archivoTorneoOriginal.bin"}; ///Datos del torneo base
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
void cargarArchivoTorneo();
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
nodoTorneo* pasarListaPPLATabla(nodoEquipo* listaEquipos, nodoTorneo* tabla);
void simularFecha(fecha torneo[],int validos,nodoEquipo* listaPpl,int fechasJugadas,nodoTorneo* tabla);
int pasarArchivoTorneoToTorneo(fecha torneo[],int dimension);
void pasarTorneoToArchivoTorneo(fecha torneo[],int validos);
void mostrarNombresEquipos(nodoEquipo* LDL);
void pasarListaPplToArchivo(nodoEquipo* listaPpl);
registroArchivo pasarEquipoToRegistro(equipo e);
registroArchivo pasarJugadorToRegistro(jugador j);
int validarGuardado(int opcionGuardado);
void reiniciarArchivoRegistros();
void reiniciarArchivoTorneo();
int compararArchivosTorneo();
void verificarPartidaGuardada();


void menuInicial();
void menuPrincipal();
void subMenuJugar(nodoEquipo* listaEquipos,fecha torneo[],int validosTorneo);
void subMenuVerEquipos(nodoEquipo* listaEquipos);
void subMenuBuscarJugador(nodoarbol* arbolJugadores);
void subMenuGuardado(fecha torneo[],int validosTorneo,nodoEquipo* listaEquipos);
void subMenuAdministrador(nodoEquipo* listaPpl,nodoarbol* arbolJugadores);
void subSubMenuSimularPartido(nodoEquipo* listaEquipos);
void subSubMenuJugadores(nodoEquipo* listaPpl,nodoarbol* arbolJugadores);
void subSubMenuSimularTorneo(nodoEquipo* listaPpl,fecha torneo[],int validosTorneo);
void subSubMenuEquipos(nodoEquipo* listaPpl);

///auxiliares
void cuadroPantalla();

///MAIN
int main()
{
    //cargarArchivo();
    //cargarArchivoTorneo();

    verificarPartidaGuardada();

    nodoEquipo* listaEquipos=inicEquipo();

    listaEquipos = pasar_archivo_a_LDL(listaEquipos);

    fecha torneo[10];

    int validosTorneo=pasarArchivoTorneoToTorneo(torneo,10);

    //mostrarTorneo(torneo,validosTorneo);


    //simularFecha(torneo,validosTorneo,listaEquipos,0);


    //mostrarLDL(listaEquipos);
    //system("pause");


    nodoarbol* arbolJugadores=inicArbol();
    arbolJugadores=pasar_archivo_a_arbol(arbolJugadores);

    //inorder(arbolJugadores);


    int opcion;

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
            subMenuJugar(listaEquipos,torneo,validosTorneo);
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
            subMenuGuardado(torneo,validosTorneo,listaEquipos);
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
        printf("\nError,el archivo no pudo abrirse \n");
    }
}

void cargarArchivoTorneo()
{
    FILE* archi = fopen(nombreArchivoTorneo,"wb");
    fecha torneo[10];
    if(archi)
    {
        cargarTorneo(torneo,10);
        fwrite(torneo,sizeof(fecha),10,archi);
        fclose(archi);
    }
    else
    {
        printf("\nError, el archivo no puedo abrirse \n");
    }
}

int pasarArchivoTorneoToTorneo(fecha torneo[],int dimension)
{
    FILE* archi=fopen(nombreArchivoTorneo,"rb");
    fecha aux;
    int i=0;
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(fecha),1,archi)>0 && i<dimension)
        {
            torneo[i]=aux;
            i++;
        }
        fclose(archi);
    }
    return i;
}

nodoEquipo* pasar_archivo_a_LDL(nodoEquipo* listaPpl)
{
    FILE* archi=fopen(nombreArchivo,"rb");
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

void mostrarNombresEquipos(nodoEquipo* LDL)
{
    gotoxy(15,2);
    printf("EQUIPOS");
    int y = 4;

    while(LDL!=NULL)
    {
        gotoxy(5,y);
        printf("-%s - Calidad: %i\n",LDL->dato.nombreEquipo,LDL->dato.calidadEquipo);

        y++;
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

    gotoxy(5,4);
    printf("Ingrese su usuario: ");
    fflush(stdin);
    gotoxy(5,5);
    scanf("%s",usu);

    gotoxy(5,7);
    printf("Ingrese la contrasenia: ");
    gotoxy(5,8);
    fflush(stdin);
    scanf("%s",contra);

    if( (strcmp(usu,usuAdmin)== 0) && (strcmp(contra,contraAdmin) == 0) )
    {
        system("cls");
        gotoxy(5,3);
        printf("\nIngresaste al modo admin, bienvenido: \n");
        credenciales = 1;
    }
    else
    {
        gotoxy(5,6);
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
            cuadroPantalla();
            mostrarNombresEquipos(listaEquipos);
            gotoxy(5,11);
            printf("Ingrese nombre del equipo cuyo plantel desee ver: \n");
            fflush(stdin);
            gotoxy(5,12);
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
        cuadroPantalla();
        gotoxy(5,3);
        printf("Ingrese el nombre y apellido del jugador buscado: \n");
        fflush(stdin);
        gotoxy(5,4);
        gets(nombreBuscado);

        nodoBuscado=buscar(arbolJugadores,nombreBuscado);

        if(nodoBuscado==NULL)
        {
            gotoxy(5,6);
            printf("Error.El jugador no esta registrado.\n");
        }
        else
        {
            system("cls");
            mostrar_jugador(nodoBuscado->dato);
        }
        gotoxy(5,11);
        printf("Desea buscar otro jugador? (s/n)");
        fflush(stdin);
        gotoxy(5,12);
        scanf("%c",&continuar);
    }
    system("cls");
}

void subMenuJugar(nodoEquipo* listaEquipos,fecha torneo[],int validosTorneo)
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
        printf("1- Jugar Liga\n");
        gotoxy(5,6);
        printf("2- Simular Partido\n");
        gotoxy(5,7);
        printf("0- Volver al menu anterior\n");
        gotoxy(2,24);
        scanf("%i", &opcionPartido);

        switch(opcionPartido)
        {
        case 1:
            subSubMenuSimularTorneo(listaEquipos,torneo,validosTorneo);
            break;
        case 2:
            while(continuar=='s')
            {
                subSubMenuSimularPartido(listaEquipos);
                printf("Desea hacer otro amistoso? (s/n)\n");
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

void subSubMenuSimularTorneo(nodoEquipo* listaPpl,fecha torneo[],int validosTorneo)
{
    int opcionTorneo;
    int fechasJugadas;
    nodoTorneo* tabla=inicListaTorneo();
    tabla=pasarListaPPLATabla(listaPpl,tabla);

    do
    {
        system("cls");

        for(int i=1; i<99; i++)
        {
            gotoxy(i,3);
            printf("-");
        }

        cuadroPantalla();
        gotoxy(42,2);
        printf("MENU TORNEO\n");
        gotoxy(5,5);
        printf("1-Simular Torneo\n");
        gotoxy(5,6);
        printf("2-Ver Fechas y cruces\n");
        gotoxy(5,7);
        printf("3-Ver tabla del torneo\n");
        gotoxy(5,8);
        printf("0-Volver al menu anterior\n");

        gotoxy(2,24);
        scanf("%i", &opcionTorneo);
        system("cls");

        switch(opcionTorneo)
        {
        case 1:
            fechasJugadas=torneo[0].fechasJugadas;

            simularFecha(torneo,validosTorneo,listaPpl,fechasJugadas,tabla);
            break;
        case 2:
            mostrarTorneo(torneo,validosTorneo);
            system("pause");
            break;
        case 3:
            tabla=borrarTodaLaLista(tabla);
            tabla=pasarListaPPLATabla(listaPpl,tabla);
            tablaPuntos(tabla);
            gotoxy(1,23);
            system("pause");
            break;
        case 0:
            system("cls");
            break;
        default:
            system("cls");
            printf("Opcion invalida. Ingrese nuevamente...\n");
        }
    }
    while(opcionTorneo!=0);

}

void subSubMenuSimularPartido(nodoEquipo* listaEquipos)
{
    char nombreEquipoA[20];
    char nombreEquipoB[20];
    int flag=0;

    system("cls");


    while(flag==0)
    {
        cuadroPantalla();
        mostrarNombresEquipos(listaEquipos);

        gotoxy(5,12);
        printf("Ingrese el nombre del primer equipo\n");
        fflush(stdin);
        gotoxy(5,13);
        gets(nombreEquipoA);

        gotoxy(5,15);
        printf("Ingrese el nombre del segundo equipo\n");
        fflush(stdin);
        gotoxy(5,16);
        gets(nombreEquipoB);


        if(existeEquipo(listaEquipos,nombreEquipoA) && existeEquipo(listaEquipos,nombreEquipoB))
        {
            if(strcmpi(nombreEquipoA,nombreEquipoB)!=0)
            {
                flag=1;
            }
            else
            {
                gotoxy(5,18);
                printf("Error. Un equipo no puede jugar contra si mismo. Intente nuevamente...\n");
                gotoxy(5,19);
                system("pause");
                system("cls");
            }
        }
        else if(existeEquipo(listaEquipos,nombreEquipoA)!=1 && existeEquipo(listaEquipos,nombreEquipoB)!=1)
        {
            gotoxy(5,18);
            printf("Error. Los equipos ingresados no son validos. Intente nuevamente...\n");
            gotoxy(5,19);
            system("pause");
            system("cls");
        }
        else if(existeEquipo(listaEquipos,nombreEquipoA)!=1)
        {
            gotoxy(5,18);
            printf("Error. El equipo ingresado %s no es valido. Intente nuevamente...\n",nombreEquipoA);
            gotoxy(5,19);
            system("pause");
            system("cls");
        }
        else
        {
            gotoxy(5,18);
            printf("Error. El equipo ingresado %s no es valido. Intente nuevamente...\n",nombreEquipoB);
            gotoxy(5,19);
            system("pause");
            system("cls");
        }

    }
    system("cls");

    partido partidoX;

    nodoEquipo* equipoA = buscar_equipo(listaEquipos,nombreEquipoA);
    nodoEquipo* equipoB = buscar_equipo(listaEquipos,nombreEquipoB);

    simularPartido(equipoA->dato, equipoB->dato, &partidoX, 2);
    resumenPartido(equipoA->dato, equipoB->dato, partidoX);

    printf("\n\n");

    gotoxy(2,26);
    system("pause");
    system("cls");

}

void subMenuAdministrador(nodoEquipo* listaPpl,nodoarbol* arbolJugadores)
{
    int opcionAdmin;
    char usurio[20];
    char contrasenia[20];
    int credenciales=0;

    system("cls");

    cuadroPantalla();
    gotoxy(5,2);
    printf("Ingresaste al menu secreto: \n");
    credenciales = sistemaLogin(usurio,contrasenia);

    if(credenciales == 1)
    {
        do
        {
            system("cls");
            cuadroPantalla();

            for(int i=1; i<99; i++)
            {
                gotoxy(i,3);
                printf("-");
            }
            gotoxy(42,2);
            printf("MENU ADMIN\n");
            gotoxy(5,5);
            printf("1- Menu jugadores");
            gotoxy(5,6);
            printf("2- Menu equipos");
            gotoxy(5,7);
            printf("0- Volver al menu anterior\n");
            gotoxy(5,24);
            scanf("%i",&opcionAdmin);
            switch(opcionAdmin)
            {
            case 1:
                system("cls");
                subSubMenuJugadores(listaPpl,arbolJugadores);
                break;
            case 2:
                system("cls");
                subSubMenuEquipos(listaPpl);
                break;
            case 0:
                system("cls");
                break;
            default:
                system("cls");
                gotoxy(5,5);
                printf("Error, opcion invalida. Intente nuevamente...");
                opcionAdmin=-1;
                break;
            }
        }
        while(opcionAdmin!=0);
    }
}

void subSubMenuJugadores(nodoEquipo* listaPpl,nodoarbol* arbolJugadores)
{
    int opcionJugadores=0;
    char nombre[30];
    do
    {
        system("cls");

        cuadroPantalla();

        for(int i=1; i<99; i++)
        {
            gotoxy(i,3);
            printf("-");
        }

        gotoxy(42,2);
        printf("MENU JUGADORES\n");
        gotoxy(5,5);
        printf("1- Dar de alta un jugador\n");
        gotoxy(5,6);
        printf("2- Dar de baja un jugador\n");
        gotoxy(5,7);
        printf("3- Modificar datos de un jugador\n");
        gotoxy(5,8);
        printf("4- Consultar un jugador\n");
        gotoxy(5,9);
        printf("0- Volver al menu anterior\n");
        gotoxy(5,24);
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

            subMenuBuscarJugador(arbolJugadores); ///Es mejor basicamente
            break;
        case 0:
            system("cls");
            break;
        default:
            system("cls");
            gotoxy(5,5);
            printf("Error, opcion invalida. Intente nuevamente...");
            opcionJugadores=-1;
            break;
        }
    }
    while(opcionJugadores!=0);
}

void subSubMenuEquipos(nodoEquipo* listaPpl)
{
    int opcionEquipos=0;
    char nombre[30];
    do
    {
        system("cls");

        cuadroPantalla();

        for(int i=1; i<99; i++)
        {
            gotoxy(i,3);
            printf("-");
        }

        gotoxy(42,2);
        printf("MENU EQUIPO\n");
        gotoxy(5,5);
        printf("1- Dar de alta un equipo\n");
        gotoxy(5,6);
        printf("2- Dar de baja un equipo\n");
        gotoxy(5,7);
        printf("3- Modificar datos de un equipo\n");
        gotoxy(5,8);
        printf("4- Consultar un equipo\n");
        gotoxy(5,9);
        printf("0- Volver al menu anterior\n");
        gotoxy(5,24);
        scanf("%i",&opcionEquipos);
        switch(opcionEquipos)
        {
        case 1:
            system("cls");
            printf("Ingrese el nombre del equipo que desea dar de alta: \n");
            fflush(stdin);
            gets(nombre);
            altaEquipo(listaPpl,nombre);
            system("pause");
            break;
        case 2:
            system("cls");
            printf("Ingrese el nombre del equipo que desea dar de baja: \n");
            fflush(stdin);
            gets(nombre);
            bajaEquipo(listaPpl,nombre);
            system("pause");
            break;
        case 3:
            system("cls");
            printf("Ingrese el nombre del equipo cuyos datos desea modificar: \n");
            fflush(stdin);
            gets(nombre);
            modificarEquipo(listaPpl,nombre);
            system("pause");
            break;
        case 4:
            system("cls");
            //subMenuBuscarJugador(arbolJugadores);
            ///HACER ESTA FUNCION
            break;
        case 0:
            system("cls");
            break;
        default:
            system("cls");
            gotoxy(5,5);
            printf("Error, opcion invalida. Intente nuevamente...");
            opcionEquipos=-1;
            break;
        }
    }
    while(opcionEquipos!=0);
}

void simularFecha(fecha torneo[],int validos,nodoEquipo* listaPpl,int fechasJugadas,nodoTorneo* tabla)
{
    char continuar='s';
    int i=fechasJugadas;
    cruce partido1;
    cruce partido2;
    cruce partido3;
    partido aux1,aux2,aux3;

    while (continuar=='s' && i<validos)
    {
        printf("Fecha %i: \n\n",i+1);

        partido1=torneo[i].partido1;
        partido2=torneo[i].partido2;
        partido3=torneo[i].partido3;

        printf("%s vs %s\n\n",partido1.equipoA,partido1.equipoB);
        printf("%s vs %s\n\n",partido2.equipoA,partido2.equipoB);
        printf("%s vs %s\n\n",partido3.equipoA,partido3.equipoB);

        system("pause");
        system("cls");

        //Partido1
        nodoEquipo* nodoEquipoA=buscar_equipo(listaPpl,partido1.equipoA);
        nodoEquipo* nodoEquipoB=buscar_equipo(listaPpl,partido1.equipoB);

        simularPartido(nodoEquipoA->dato,nodoEquipoB->dato,&aux1,1);
        contarPuntosYGoles(&nodoEquipoA->dato,&nodoEquipoB->dato,aux1);


        mostrar_equipo(nodoEquipoA->dato); //Desp reemplazar esto por la tabla abajo
        mostrar_equipo(nodoEquipoB->dato); //Desp reemplazar esto por la tabla abajo
        system("pause");
        system("cls");

        //Partido2
        nodoEquipo* nodoEquipoC=buscar_equipo(listaPpl,partido2.equipoA);
        nodoEquipo* nodoEquipoD=buscar_equipo(listaPpl,partido2.equipoB);

        simularPartido(nodoEquipoC->dato,nodoEquipoD->dato,&aux2,1);
        contarPuntosYGoles(&nodoEquipoC->dato,&nodoEquipoD->dato,aux2);

        mostrar_equipo(nodoEquipoC->dato);  //Desp reemplazar esto por la tabla abajo
        mostrar_equipo(nodoEquipoD->dato);  //Desp reemplazar esto por la tabla abajo
        system("pause");
        system("cls");

        //Partido3
        nodoEquipo* nodoEquipoE=buscar_equipo(listaPpl,partido3.equipoA);
        nodoEquipo* nodoEquipoF=buscar_equipo(listaPpl,partido3.equipoB);


        simularPartido(nodoEquipoE->dato,nodoEquipoF->dato,&aux3,1);
        contarPuntosYGoles(&nodoEquipoE->dato,&nodoEquipoF->dato,aux3);

        mostrar_equipo(nodoEquipoE->dato);  //Desp reemplazar esto por la tabla abajo
        mostrar_equipo(nodoEquipoF->dato);  //Desp reemplazar esto por la tabla abajo

        system("pause");
        system("cls");

        tabla=borrarTodaLaLista(tabla);
        tabla=pasarListaPPLATabla(listaPpl,tabla);

        tablaPuntos(tabla);

        i++;

        printf("\n\n\nDesea simular otra fecha? (s/n)\n");
        fflush(stdin);
        scanf("%c",&continuar);
        system("cls");
    }
    if(i==10)
    {
        tabla=borrarTodaLaLista(tabla);
        tabla=pasarListaPPLATabla(listaPpl,tabla);
        multiplesExplosiones(20,tabla->datoEquipo.nombreEquipo);
    }

    guardarFechasJugadasEnTorneo(torneo,validos,i);
}

void pasarTorneoToArchivoTorneo(fecha torneo[],int validos)
{
    FILE* archi=fopen(nombreArchivoTorneo,"wb");
    if(archi!=NULL)
    {
        fwrite(torneo,sizeof(fecha),validos,archi);
        fclose(archi);
    }
}

void pasarListaPplToArchivo(nodoEquipo* listaPpl)
{
    FILE* archi=fopen(nombreArchivo,"wb");
    registroArchivo aux;

    if(archi!=NULL)
    {
        while(listaPpl!=NULL)
        {
            aux=pasarEquipoToRegistro(listaPpl->dato);
            while(listaPpl->listaDeJugadores!=NULL)
            {
                aux=pasarJugadorToRegistro(listaPpl->listaDeJugadores->dato);
                listaPpl->listaDeJugadores=listaPpl->listaDeJugadores->siguiente;
                fwrite(&aux,sizeof(registroArchivo),1,archi);
            }
            listaPpl=listaPpl->siguiente;
        }
        fclose(archi);
    }
}

registroArchivo pasarJugadorToRegistro(jugador j)
{
    registroArchivo aux;

    aux.calidadJugador=j.calidadJugador;
    aux.edad=j.edad;
    strcpy(aux.nacionalidadJugador,j.nacionalidadJugador);
    strcpy(aux.nombreJugador,j.nombreJugador);
    strcpy(aux.piernaHabil,j.piernaHabil);
    strcpy(aux.posicion,j.posicion);
    aux.estadoJugador=j.estadoJugador;

    return aux;
}

registroArchivo pasarEquipoToRegistro(equipo e)
{
    registroArchivo aux;

    aux.calidadEquipo=e.calidadEquipo;
    strcpy(aux.nombreEquipo,e.nombreEquipo);
    aux.puntosEquipo=e.puntosEquipo;
    aux.golesEquipo=e.golesEquipo;
    aux.estadoEquipo=e.estadoEquipo;
    aux.partidosEmpatados=e.partidosEmpatados;
    aux.partidosGanados=e.partidosGanados;
    aux.partidosPerdidos=e.partidosPerdidos;
    aux.partidosJugados=e.partidosJugados;

    return aux;
}


int validarGuardado(int opcionGuardado)
{
    while(opcionGuardado!=1 && opcionGuardado!=2)
    {
        printf("\nError.Opcion invalida. Intente nuevamente...\n");
        fflush(stdin);
        scanf("%i",&opcionGuardado);
    }
    return opcionGuardado;
}

void subMenuGuardado(fecha torneo[],int validosTorneo,nodoEquipo* listaEquipos)
{
    int guardado;

    system("cls");

    printf("Desea guardar los datos modificados en partida? \n1- si / 2- no \n");
    fflush(stdin);
    scanf("%i",&guardado);
    guardado=validarGuardado(guardado);

    system("cls");

    if(guardado==1)
    {
        pasarTorneoToArchivoTorneo(torneo,validosTorneo);
        pasarListaPplToArchivo(listaEquipos);
        printf("Los datos han sido guardados con exito.\n");
    }

    printf("Saliendo del programa...\n");
}

void reiniciarArchivoRegistros()
{
    FILE* archi=fopen(nombreArchivo,"wb");
    FILE* archi2=fopen(nombreArchivoOriginal,"rb");
    registroArchivo aux;

    if(archi!=NULL && archi2!=NULL)
    {
        while(fread(&aux,sizeof(registroArchivo),1,archi2)>0)
        {
            fwrite(&aux,sizeof(registroArchivo),1,archi);
        }
        fclose(archi);
        fclose(archi2);
    }
}

int compararArchivosTorneo()
{
    FILE* archi=fopen(nombreArchivoTorneo,"rb");
    FILE* archi2=fopen(nombreArchivoTorneoOriginal,"rb");
    fecha aux;
    fecha aux2;
    int flag=1;

    if(archi!=NULL && archi2!=NULL)
    {
        while(fread(&aux,sizeof(fecha),1,archi2)>0 && fread(&aux2,sizeof(fecha),1,archi)>0 && flag==1)
        {
            if(aux.fechasJugadas!=aux2.fechasJugadas)
            {
                flag=0;
            }
        }
        fclose(archi);
        fclose(archi2);

    }
    return flag;
}


void reiniciarArchivoTorneo()
{
    FILE* archi=fopen(nombreArchivoTorneo,"wb");
    FILE* archi2=fopen(nombreArchivoTorneoOriginal,"rb");
    fecha aux;

    if(archi!=NULL && archi2!=NULL)
    {
        while(fread(&aux,sizeof(fecha),1,archi2)>0)
        {
            fwrite(&aux,sizeof(fecha),1,archi);
        }
        fclose(archi);
        fclose(archi2);
    }
}

void verificarPartidaGuardada()
{
    if(compararArchivosTorneo()==0)
    {
        int opcionNuevoTorneo;
        system("cls");
        printf("Hay una partida guardada. Desea continuar?\n");
        printf("1-Si\n");
        printf("2-No\n");
        fflush(stdin);
        scanf("%i",&opcionNuevoTorneo);
        opcionNuevoTorneo=validarGuardado(opcionNuevoTorneo);
        if(opcionNuevoTorneo==2)
        {
            reiniciarArchivoRegistros();
            reiniciarArchivoTorneo();
        }
    }
}



nodoTorneo* pasarListaPPLATabla(nodoEquipo* listaEquipos, nodoTorneo* tabla)
{
    nodoTorneo * auxTabla;

    while(listaEquipos!=NULL)
    {
        auxTabla =crearNodoTorneo(listaEquipos->dato);
        tabla = agregarEnOrdenPuntos(tabla,auxTabla);
        listaEquipos= listaEquipos->siguiente;
    }
    return tabla;
}


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

