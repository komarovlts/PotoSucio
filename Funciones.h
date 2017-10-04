#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _FUNCIONES_H
#define _FUNCIONES_H

typedef struct Carta{ // Nodo
	char numero[4];
	char pinta[2];
	int e; // Indicador de carta vacía o no vacía.
	int num; // Indicador del número de la carta (para una mejor comparación).
	int posicion;
	struct Carta * sgte;
}Carta;

typedef struct ListaCartas{ // Lista con Cartas; Baraja, Manos, Pozo.
	Carta* inicio;
	int longitud;
}Lista;

Lista crearLista();

Carta* crearCarta(char numero[], char pinta[], int num, int posicion);

Carta* obtenerElemento(Lista lista, int n);

Lista insertarCarta(Lista lista, Carta* carta);

Lista eliminarElemento(Lista lista, int n);

Lista limpiarLista(Lista baraja, int i);

Lista barajaOrdenada();

Lista revolverBaraja(Lista baraja);

void imprimirCarta(Carta* carta);

void imprimirBaraja(Lista baraja);

void imprimirMano(Lista mano);

void imprimirPares(Lista mano);

Lista crearMano(Lista barajaRevuelta);

Lista copiarLista(Lista lista);

Lista revolverMano(Lista mano);

Lista quitarPares(Lista pares, Lista mano);

Lista buscarPares(Lista mano);

// Turnos/Jugadores.

typedef struct Jugador{ // Nodo
    int id; // identificación del jugador, va desde el 1 al 4, según la cantidad de jugadores.
    struct Jugador *sgte;
}Jugador;

Jugador* inicio;
int longitud;
int posicion;


void inicializar();

Jugador* crearJugador(int id);

void insertarJugador(Jugador* jugador);

void imprimirJugador(Jugador* jugador);

void imprimirJugadores();

void eliminarJugador(int n);

int buscarJugador(int b);

Jugador* crearCPU();

Lista accionCPU1N(Lista ManoCP1, Lista mano);

Lista accionCPU2N(Lista ManoCP2, Lista mano);

Lista accionCPU3N(Lista ManoCP3, Lista mano, int rnum);

Lista accionCPU1(Lista ManoCP1, Lista mano);

Lista accionCPU2(Lista ManoCP2, Lista mano);

Lista accionCPU3(Lista ManoCP3, Lista mano, int rnum);

int eleccionUsuario(int longitudManoCPU);

Lista accionUsuario(Lista ManoP1);

void partidaNormal(int j, char* usuario);

void partidaSuperuser(int j, char* usuario);

void generarPartida(int n, char* usuario);

void iniciarMenu();

#endif
