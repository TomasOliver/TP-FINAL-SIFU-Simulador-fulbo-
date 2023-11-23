#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "listaPPL.h"

nodoEquipo* inicEquipo()
{
    return NULL;
}

nodoEquipo* alta(nodoEquipo* listaPpl, equipo e, jugador j)
{
    nodoJugador* nuevo_nodo=crear_nodo_jugador(j);

    nodoEquipo* posEquipo = buscar_equipo(listaPpl, e.nombreEquipo);

    if(posEquipo == NULL)
    {
        listaPpl = agregar_equipo(listaPpl, e);
        posEquipo = buscar_nodo_final_equipo(listaPpl);
    }

    posEquipo->listaDeJugadores = agregar_final(posEquipo->listaDeJugadores, nuevo_nodo);


    return listaPpl;
}

nodoEquipo* buscar_equipo(nodoEquipo* listaPpl,char nombreEquipo[])
{
    nodoEquipo* nodoBuscado = NULL;
    nodoEquipo* seg = listaPpl;

    while(seg !=NULL && nodoBuscado == NULL)
    {
        if(strcmpi(seg->dato.nombreEquipo, nombreEquipo) == 0)
        {
            nodoBuscado = seg;
        }
        seg = seg->siguiente;
    }

    return nodoBuscado;
}

nodoEquipo* crear_nodo_equipo(equipo e)
{
    nodoEquipo* aux = (nodoEquipo*) malloc(sizeof(nodoEquipo)); //Reservo memoria para el NODO
    aux->dato = e;
    aux->siguiente = NULL;
    aux->listaDeJugadores = iniclista_jugador();
    return aux; //Retorno el nodo
}

nodoEquipo* agregar_equipo(nodoEquipo* listaPpl, equipo e)
{
    nodoEquipo* nuevoNodoEquipo = crear_nodo_equipo(e);

    listaPpl = agregar_final_equipo(listaPpl, nuevoNodoEquipo);

    return listaPpl;
}


nodoEquipo* agregar_final_equipo(nodoEquipo* lista,nodoEquipo* nuevo_nodo)
{
    nodoEquipo* seg=lista;

    if(lista==NULL)
    {
        lista=nuevo_nodo;
    }
    else
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevo_nodo;
    }
    return lista;
}

nodoEquipo* buscar_nodo_final_equipo(nodoEquipo* lista)
{
    nodoEquipo* seg=lista;

    while(seg->siguiente!=NULL)
    {
        seg=seg->siguiente;
    }

    return seg;
}

int existeEquipo(nodoEquipo* listaPpl,char nombreEquipo[])
{
    int flag=0;
    nodoEquipo* seg = listaPpl;

    while(seg !=NULL && flag == 0)
    {
        if(strcmpi(seg->dato.nombreEquipo, nombreEquipo) == 0)
        {
            flag=1;
        }
        seg = seg->siguiente;
    }

    return flag;
}

void AgregarJugador(nodoEquipo* listaPpl,nodoarbol* arbolJugadores,jugador j)
{
    if(existeJugador(arbolJugadores,j.nombreJugador)==1)
    {
        printf("\nError. El jugador ya se encuentra registrado...\n");
    }
    else
    {
        int flag=0;
        char nombreEquipo[30];
        equipo e;
        mostrarNombresEquipos(listaPpl);

        while(flag==0)
        {
            printf("Ingrese el nombre del equipo donde desea registrar al jugador: \n");
            fflush(stdin);
            gets(nombreEquipo);

            if(existeEquipo(listaPpl,nombreEquipo)==0)
            {
                printf("\nError. El equipo no existe o no esta registrado. Intente nuevamente...\n");
            }
            else
            {
                flag=1;
                e=retornarEquipo(listaPpl,nombreEquipo);
            }
        }

        nodoarbol* nuevoNodo=crear_nodo_arbol(j); //Lo agrego en la LDL
        insertar_nodo_arbol(arbolJugadores,nuevoNodo); //Lo agrego en el arbol

        alta(listaPpl,e,j); //Para cargarlo en la LISTA DE LISTAS
    }
}

equipo retornarEquipo(nodoEquipo* listaPpl,char nombreEquipo[])
{
    equipo e;
    while(listaPpl!=NULL)
    {
        if(strcmp(nombreEquipo,listaPpl->dato.nombreEquipo)==0)
        {
            e=listaPpl->dato;
        }
        listaPpl=listaPpl->siguiente;
    }
    return e;
}

void altaJugador(nodoarbol* arbol,nodoEquipo* listaPpl,char nombreJugador[])
{
    if(existeJugador(arbol,nombreJugador)==1)
    {
        nodoarbol* nodoJugadorArbol=buscar(arbol,nombreJugador);
        nodoJugador* nodoJugadorLDL=buscarJugadorEnLDL(listaPpl,nombreJugador);

        if(nodoJugadorArbol->dato.estadoJugador==0)
        {
            nodoJugadorArbol->dato.estadoJugador=1; //Lo modifico en el arbol

            nodoJugadorLDL->dato.estadoJugador=1; //Lo modifico en la LDL

            printf("\nEl jugador ha sido dado de alta correctamente.\n");
        }
        else
        {
            printf("\nError. El jugador ya se encuentra dado de alta\n");
        }
    }
    else
    {
        printf("\nError. El juegador no existe o no se encuentra registrado...\n");
    }
}

void bajaJugador(nodoarbol* arbol,nodoEquipo* listaPpl,char nombreJugador[])
{

    if(existeJugador(arbol,nombreJugador)==1)
    {
        nodoarbol* nodoJugadorArbol=buscar(arbol,nombreJugador);
        nodoJugador* nodoJugadorLDL=buscarJugadorEnLDL(listaPpl,nombreJugador);

        if(nodoJugadorArbol->dato.estadoJugador==1)
        {

            nodoJugadorArbol->dato.estadoJugador=0; //Lo modifico en el arbol

            nodoJugadorLDL->dato.estadoJugador=0; //Lo modifico en la LDL

            printf("\nEl jugador ha sido dado de baja correctamente.\n");
        }
        else
        {
            printf("\nError. El jugador ya se encuentra dado de baja\n");
        }
    }
    else
    {
        printf("Error. El juegador no existe o no se encuentra registrado...\n");
    }
}

nodoJugador* buscarJugadorEnLDL(nodoEquipo* listaPpl,char nombreJugador[])
{
    nodoJugador* nodoBuscado=NULL;

    while(listaPpl!=NULL && nodoBuscado==NULL)
    {
        nodoBuscado=buscar_nodo_jugador_lista(listaPpl->listaDeJugadores,nombreJugador);
        listaPpl=listaPpl->siguiente;
    }

    return nodoBuscado;
}

void modificarJugador(nodoEquipo* listaPpl,nodoarbol* arbolJugadores,char nombreBuscado[])
{
    if(existeJugador(arbolJugadores,nombreBuscado)==1)
    {
        nodoarbol* jugadorBuscadoArbol=buscar(arbolJugadores,nombreBuscado);
        nodoJugador* JugadorBuscadoLDL=buscarJugadorEnLDL(listaPpl,nombreBuscado);
        jugador aux;
        jugador aux2;
        int opcion;


        printf("Que dato desea modificar?\n");
        printf("1-Nombre y Apellido\n");
        printf("2-Nacionalidad\n");
        printf("3-Calidad\n");
        printf("4-Edad\n");
        printf("5-Pierna habil\n");
        printf("6-Posicion\n");
        printf("7-Estado del Jugador\n");
        printf("0-Ninguno\n");
        scanf("%i",&opcion);
        switch(opcion)
        {
        case 1: ///No se puede utilizar, el nombre es el criterio de ordenamiento del arbol, y si lo cambiamos no se vera reflejado en el arbol cuando busquemos el jugador. Decidimos borrar el nodo y reinsertarlo
            system("cls");
            printf("Ingrese el nuevo nombre y apellido del jugador: \n");
            fflush(stdin);
            gets(aux.nombreJugador);
            aux=validarNombreJugador(arbolJugadores,aux);

            strcpy(JugadorBuscadoLDL->dato.nombreJugador,aux.nombreJugador);  ///Lo modifico en la LDL

            aux2=jugadorBuscadoArbol->dato; ///Copio el dato en un auxiliar
            strcpy(aux2.nombreJugador,aux.nombreJugador);
            nodoarbol* nuevoNodo=crear_nodo_arbol(aux2);

            arbolJugadores=borrarNodoArbol(arbolJugadores,nombreBuscado);

            arbolJugadores=insertar_nodo_arbol(arbolJugadores,nuevoNodo); ///Lo modifico en el arbol
            break;
        case 2:
            system("cls");
            printf("Ingrese nueva nacionalidad del jugador: \n");
            fflush(stdin);
            gets(aux.nacionalidadJugador);

            strcpy(jugadorBuscadoArbol->dato.nacionalidadJugador,aux.nacionalidadJugador); ///Lo modifico en el arbol
            strcpy(JugadorBuscadoLDL->dato.nacionalidadJugador,aux.nacionalidadJugador);  ///Lo modifico en la LDL
            break;
        case 3:
            system("cls");
            printf("Ingrese nueva calidad del jugador (entre 1 y 5): \n");
            scanf("%i",&aux.calidadJugador);
            aux=validarCalidadJugador(aux);

            jugadorBuscadoArbol->dato.calidadJugador=aux.calidadJugador; ///Lo modifico en el arbol
            JugadorBuscadoLDL->dato.calidadJugador=aux.calidadJugador; ///Lo modifico en la LDL
            break;
        case 4:
            system("cls");
            printf("Ingrese edad del jugador (entre 18 y 40): \n");
            scanf("%i",&aux.edad);
            aux=validarEdadJugador(aux);

            jugadorBuscadoArbol->dato.edad=aux.edad; ///Lo modifico en el arbol
            JugadorBuscadoLDL->dato.edad=aux.edad; ///Lo modifico en la LDL
            break;
        case 5:
            system("cls");
            printf("Ingrese pierna habil del jugador(Izquierda/Derecha): \n");
            fflush(stdin);
            gets(aux.piernaHabil);
            aux=validarPiernaHabilJugador(aux);

            strcpy(jugadorBuscadoArbol->dato.piernaHabil,aux.piernaHabil); ///Lo modifico en el arbol
            strcpy(JugadorBuscadoLDL->dato.piernaHabil,aux.piernaHabil); ///Lo modifico en la LDL
            break;
        case 6:
            system("cls");
            printf("Ingrese posicion del jugador (arquero/defensor/mediocampista/delantero): \n");
            fflush(stdin);
            gets(aux.posicion);
            aux=validarPosicionJugador(aux);

            strcpy(jugadorBuscadoArbol->dato.posicion,aux.posicion); ///Lo modifico en el arbol
            strcpy(JugadorBuscadoLDL->dato.posicion,aux.posicion); ///Lo modifico en la LDL
            break;
        case 7:
            system("cls");
            if(jugadorBuscadoArbol->dato.estadoJugador==1)
            {
                bajaJugador(arbolJugadores,listaPpl,nombreBuscado);
            }
            else
            {
                altaJugador(arbolJugadores,listaPpl,nombreBuscado);
            }
            break;
        case 0:
            system("cls");
            break;

        }
    }
    else
    {
        printf("\nError. El jugador no existe o no se encuentra registrado...\n");
    }
}

jugador validarNombreJugador(nodoarbol* arbolJugadores,jugador j)
{
    while(existeJugador(arbolJugadores,j.nombreJugador)==1)
    {
        printf("Error. El nombre ya esta registrado. Intente con otro nombre...\n");
        fflush(stdin);
        gets(j.nombreJugador);
    }
    return j;
}

void altaEquipo(nodoEquipo* listaPpl,nodoarbol* arbolJugadores,char nombreEquipo[])
{
    if(existeEquipo(listaPpl,nombreEquipo)==1)
    {
        nodoEquipo* nodoEquipoBuscado=buscarEquipoEnLDL(listaPpl,nombreEquipo);
        if(nodoEquipoBuscado->dato.estadoEquipo==0)
        {
            nodoEquipoBuscado->dato.estadoEquipo=1;
        }
        else
        {
            printf("\nError. El equipo ya se encuentra dado de alta\n");
        }
    }
    else
    {
        printf("\nError. El equipo no existe o no se encuentra registrado...\n");
    }
}

void bajaEquipo(nodoEquipo* listaPpl,nodoarbol* arbolJugadores,char nombreEquipo[])
{
    if(existeEquipo(listaPpl,nombreEquipo)==1)
    {
        nodoEquipo* nodoEquipoBuscado=buscarEquipoEnLDL(listaPpl,nombreEquipo);
        if(nodoEquipoBuscado->dato.estadoEquipo==1)
        {
            nodoEquipoBuscado->dato.estadoEquipo=0;
        }
        else
        {
            printf("\nError. El equipo ya se encuentra dado de baja\n");
        }
    }
    else
    {
        printf("\nError. El equipo no existe o no se encuentra registrado...\n");
    }
}

nodoEquipo* buscarEquipoEnLDL(nodoEquipo* listaPpl,char nombreEquipo[])
{
    nodoEquipo* nodoBuscado=NULL;

    while(listaPpl!=NULL && nodoBuscado==NULL)
    {
        if(strcmp(nombreEquipo,listaPpl->dato.nombreEquipo)==0)
        {
            nodoBuscado=listaPpl;
        }
        listaPpl=listaPpl->siguiente;
    }

    return nodoBuscado;
}

void mostrarJugadorLDL(nodoEquipo* listaPpl,char nombreJugador[])
{
    while(listaPpl!=NULL)
    {
        buscarYmostrarJugador(listaPpl->listaDeJugadores,nombreJugador);
        listaPpl=listaPpl->siguiente;
    }
}




