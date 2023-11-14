#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED


///Estructuras
typedef struct
{
    char nombreJugador[40];
    char nacionalidadJugador[20];
    int calidadJugador;
    int edad;
    char piernaHabil[10];
    char posicion[20];;
} jugador;

typedef struct nodoarbol
{
    jugador dato;
    struct nodoarbol* izq;
    struct nodoarbol* der;
} nodoarbol;



///Prototipado
jugador cargar_jugador();
void mostrar_jugador(jugador a);

nodoarbol* inicArbol();
nodoarbol* crear_nodo_arbol(jugador dato);
nodoarbol* buscar(nodoarbol* arbol,char nombre[]);
nodoarbol* insertar_nodo_arbol(nodoarbol* arbol,nodoarbol* nuevo_nodo);
void preorder(nodoarbol* arbol);
void inorder(nodoarbol* arbol);
void postorder(nodoarbol* arbol);


#endif // JUGADOR_H_INCLUDED
