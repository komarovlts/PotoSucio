#include "Funciones.h"

Lista crearLista(){ // Inicializar lista.
	// Se crea una lista enlazada con longitud cero que apunta a NULL.
	Lista baraja;
	baraja.inicio = NULL;
	baraja.longitud = 0;
	return baraja;
}

Carta* crearCarta(char numero[], char pinta[], int num, int posicion){ // Inicializar nodo.
	// Entradas: string: numero, string pinta, entero numero, entero posición.
	// Generará un "Nodo" carta con valores predeterminados e ingresados en la función.
	Carta * carta = (Carta*)malloc(sizeof(Carta)); // Se le asigna memoria a carta.
	strcpy(carta->numero, numero); // String con el número (A,2,3,4,5,6,7,8,9,10,J,Q,K) de la Carta.
	strcpy(carta->pinta, pinta); // String con la pinta (Corazón(C), Trébol(T), Pica(P) y Diamante(D)) de la Carta.
	carta->num = num; // Identificación del número correspondiente a la carta.
	carta->e = 1; //  Valor predeterminado.
	carta->posicion = posicion; // Identificador de la posición de la carta en la lista.
	return carta;
	//Salidas: "Nodo": carta.
}

Carta* obtenerElemento(Lista lista, int n){ // Obtener carta en la posición n. (1 = posición 1)
	int pos; // Contador de posición.
	n--; // Para ajustar el funcionamiento de la función para que la posición 0 de la lista sea considerada como indice 1 y no 0.
	Carta* cartaVacia = crearCarta("0","0",20,0);
	if(n >= lista.longitud || n < 0){
		cartaVacia->e = 0;
		return cartaVacia;
	}
	if(lista.inicio == NULL){
		cartaVacia->e = 0;
		return cartaVacia;
	}
	else{
		Carta* aux = lista.inicio;
		pos = 0;
		while(pos < n && aux->sgte){
			aux = aux->sgte;
			pos++;
		}
		if(pos != n){
			cartaVacia->e = 0;
			return cartaVacia;
		}
		else{
			Carta* carta = crearCarta(aux->numero, aux->pinta, aux->num, aux->posicion);
			return carta;
		}
	}
	cartaVacia->e = 0;
	return cartaVacia;
}

Lista insertarCarta(Lista lista, Carta* carta){
	int i;
	carta->sgte = NULL;
	if(carta->num != 20 || carta->e != 0){
		if(lista.inicio == NULL){
			lista.inicio = carta;
			lista.longitud = 1;
			return lista;
		}
		else{
			Carta * aux = lista.inicio;
			for (i = 0; i < lista.longitud - 1; i++){
				aux = aux->sgte;
			}
			aux -> sgte = carta;
			lista.longitud++;
			return lista;
		}
	}
}

Lista eliminarElemento(Lista lista, int n){ // Elimina el elemento en la posición n. (1 = posición 1)
    Carta* aux;
    Carta* anterior;
    int pos = 1;
    aux = lista.inicio;
    if(n > lista.longitud || n < 1){
    	printf("Elemento fuera de la Lista\n"); // Quitar.
    }
    else{
        if(n == 1){
            aux = lista.inicio;
            lista.inicio = lista.inicio->sgte;
            free(aux);
            lista.longitud--;
            }
        else if(n == lista.longitud){
            while(pos < lista.longitud){
                if(pos == (lista.longitud-1)){
                    anterior = aux;
                }
                pos++;
                aux = aux->sgte;
            }
            free(aux);
            anterior->sgte = NULL;
            lista.longitud--;
        }
        else{
           while(pos <= lista.longitud){
                if(pos == (n-1)){
                    anterior = aux;
                }
                if(pos == n){
                    free(aux);
                }
                if(pos == (n+1)){
                    anterior->sgte = aux;
                }
                pos++;
                aux= aux->sgte;
            }
         	lista.longitud--;
        }
    }
    return lista;
}

Lista limpiarLista(Lista baraja, int i){ //  Eliminar n elementos de una lista.
	// Si se busca vaciar la lista, n debe ser la longitud de la lista.
	int n;
	n = 0;
	while(n < i){
		baraja = eliminarElemento(baraja, 1);
		n++;
	}
	return baraja;
}

Lista barajaOrdenada(){
	char* pinta[4]={"C]", "T]", "P]", "D]"};
	char* numeros[13] = {"[A","[2","[3","[4","[5","[6","[7","[8","[9","[10","[J","[Q","[K"};
	Lista baraja = crearLista();
	int i,j,k,n;
	k = 1;
	n = 1;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 13; j++){
			if(k == 14){
				k = 1;
			}
				Carta * nuevaCarta = crearCarta(numeros[j], pinta[i],k,n);
				baraja = insertarCarta(baraja, nuevaCarta);
				k++; n++;
		}
	}
	Carta * primerJoker = crearCarta("[J","K]",14,53);// Se inserta un Joker.
	baraja = insertarCarta(baraja, primerJoker);

	Carta * segundoJoker = crearCarta("[J","K]",14,54);// Se inserta un segundo Joker.
	segundoJoker->e = 2; // Identificador para no tomar en cuenta esta carta.
	baraja = insertarCarta(baraja, segundoJoker);

	return baraja;
}

Lista revolverBaraja(Lista baraja){
	Lista barajaRevuelta = crearLista();
	int rnum, c, n;
	n = 1;
	while(barajaRevuelta.longitud != 53 && baraja.longitud!= 1){
		rnum = rand() % baraja.longitud;
		if((rnum+1) == baraja.longitud){
			rnum--;
		}
		if(rnum == 0){
			rnum++;
		}
		Carta* cartaObtenida = obtenerElemento(baraja, rnum);
		if (cartaObtenida->e == 0){
			c++;
		}
		if (cartaObtenida->e == 2){
			c++;
		}
		else{
			cartaObtenida->posicion = n;
			barajaRevuelta = insertarCarta(barajaRevuelta, cartaObtenida);
			baraja = eliminarElemento(baraja, rnum);
			n++;
		}
	}
	return barajaRevuelta;
}

void imprimirCarta(Carta* carta){
	printf("%s%s",carta->numero,carta->pinta);
}

void imprimirBaraja(Lista baraja){ // Sólo para uso del Desarrollador.
	int contador = 0;
	Carta * aux = baraja.inicio;
	while(aux->sgte != NULL){
		if(contador == 15 || contador == 30 || contador == 45){
			printf("\n");
		}
		if(contador != 15 || contador != 30 || contador != 45){
			imprimirCarta(aux);
			aux = aux ->sgte;
			contador++;
		}
	}
	imprimirCarta(aux);
	printf("\n");
}

void imprimirMano(Lista mano){
	int contador = 0;
	Carta * aux = mano.inicio;
	if(mano.inicio == NULL){
		printf("Sin cartas en Mano\n");
	}
	else{
		while(aux->sgte != NULL){
				imprimirCarta(aux);
				//printf("Esta es la posicion de la carta: %d\n", aux->posicion); // Pruebas de desarrollador.
				aux = aux ->sgte;
				contador++;
		}
	imprimirCarta(aux);
	//printf("Esta es la posicion de la carta: %d\n", aux->posicion); // Pruebas de desarrollador.
	printf("\n");
	}
}

void imprimirPares(Lista mano){
	int contador = 0;
	Carta * aux = mano.inicio;
	if(mano.inicio == NULL){
		printf("No tiene pares\n");
	}
	else{
		while(aux->sgte != NULL){
				imprimirCarta(aux);
				//printf("Esta es la posicion de la carta: %d\n", aux->posicion); // Pruebas de desarrollador.
				aux = aux ->sgte;
				contador++;
		}
	imprimirCarta(aux);
	//printf("Esta es la posicion de la carta: %d\n", aux->posicion); // Pruebas de desarrollador.
	printf("\n");
	}
}

Lista crearMano(Lista barajaRevuelta){
	int c,n;
	Lista mano = crearLista();
	c = 1;
	n = 0;
	while(mano.longitud != 12){
		Carta* carta = obtenerElemento(barajaRevuelta, c);
		if(carta->e == 0){
			n++;
		}
		else{
			mano = insertarCarta(mano, carta);
			c++;
		}
	}
	return mano;
}

Lista copiarLista(Lista lista){
	int i = 0;
	Lista nuevaLista = crearLista();
	Carta* aux;
	aux = lista.inicio;
	while(i < lista.longitud){
		Carta* carta = crearCarta(aux->numero, aux->pinta, aux->num, aux->posicion);
		nuevaLista = insertarCarta(nuevaLista, carta);
		aux = aux->sgte;
		i++;
	}
	return nuevaLista;
}

Lista revolverMano(Lista mano){ // Basada en revolver baraja.
	Lista manoRevuelta = crearLista();
	int rnum, c, n, auxlongitud;
	auxlongitud = mano.longitud;
	n = 1;
	while(manoRevuelta.longitud != auxlongitud && mano.longitud != 0){
		rnum = rand() % mano.longitud;
		if(rnum == 0){
			rnum++;
		}
		Carta* cartaObtenida = obtenerElemento(mano, rnum);
		if (cartaObtenida->e == 0){
			c++;
		}
		if (cartaObtenida->e == 2){
			c++;
		}
		else{
			cartaObtenida->posicion = n;
			manoRevuelta = insertarCarta(manoRevuelta, cartaObtenida);
			mano = eliminarElemento(mano, rnum);
			n++;
		}
	}
	return manoRevuelta;
}

Lista quitarPares(Lista pares, Lista mano){
	int i,j,n;
	Lista auxmano = copiarLista(mano);
	Lista auxpares = copiarLista(pares);
	for (i = 1; i <= auxmano.longitud; i++){
		for (j = 1; j <= auxpares.longitud; j++){
			Carta* cartaR = obtenerElemento(auxmano, i);
			Carta* cartaC = obtenerElemento(auxpares, j);
			if(cartaR->e != 0 || cartaC->e != 0){
				if(cartaR->posicion == cartaC->posicion){
					auxmano = eliminarElemento(auxmano, i);
					auxpares = eliminarElemento(auxpares, j);
					i--;
					j--;
				}
			}
		}
	}
	return auxmano;
}

Lista buscarPares(Lista mano){
	int i,j,n;
	Lista aux = copiarLista(mano);
	Lista pares = crearLista();
	for (i = 0; i <= aux.longitud; i++){
		for (j = 0; j <= aux.longitud; j++){
			if(i != j){
				Carta* cartaR = obtenerElemento(aux, i);
				Carta* cartaC = obtenerElemento(aux, j);
				if(cartaR->e != 0 || cartaC->e != 0){
					if(cartaR->num == cartaC->num){
						pares = insertarCarta(pares, cartaR);
						pares = insertarCarta(pares, cartaC);
						aux = eliminarElemento(aux, i);
						aux = eliminarElemento(aux, (j-1));
						i--;
						j--;
					}
				}
			}
		}
	}
	return pares;
}

// Turnos/Jugadores.

void inicializar(){
    inicio = NULL;
    longitud = 0;
}

Jugador* crearJugador(int id){

	Jugador* jugador = (Jugador*)malloc(sizeof(Jugador));
	jugador->id = id;
	return jugador;
}

void insertarJugador(Jugador* jugador){
	int i;
	jugador->sgte = NULL;
	if(inicio == NULL){
		inicio = jugador;
		longitud = 1;
	}
	else{
		Jugador* aux = inicio;
		for (i = 0; i < longitud - 1; i++){
			aux = aux->sgte;
		}
		aux -> sgte = jugador;
		longitud++;
	}
}

void imprimirJugador(Jugador* jugador){
	printf("%d\n", jugador->id);
}

void imprimirJugadores(){
	int contador = 0;
	Jugador* aux = inicio;
	if(inicio == NULL){
		printf("No existen jugadores.\n");
	}
	else{
		while(aux->sgte != NULL){
			imprimirJugador(aux);
			aux = aux ->sgte;
			contador++;
	  }
  imprimirJugador(aux);
  printf("\n");
  }
}

void eliminarJugador(int n){ // Elimina el elemento en la posición n. (1 = posición 1)
    Jugador* aux;
    Jugador* anterior;
    int pos = 1;
    aux = inicio;
    if(n > longitud || n < 1){
    	printf("\n");
    }
    else{
        if(n == 1){
            aux = inicio;
            inicio = inicio->sgte;
            free(aux);
            longitud--;
			}
			else if(n == longitud){
				while(pos < longitud){
                if(pos == (longitud-1)){
                    anterior = aux;
                }
                pos++;
                aux = aux->sgte;
            }
            free(aux);
            anterior->sgte = NULL;
            longitud--;
        }
        else{
           while(pos <= longitud){
                if(pos == (n-1)){
                    anterior = aux;
                }
                if(pos == n){
                    free(aux);
                }
                if(pos == (n+1)){
                    anterior->sgte = aux;
                }
                pos++;
                aux= aux->sgte;
            }
         	longitud--;
        }
    }
}

int buscarJugador(int b){
    Jugador* actual;
    int p = 1;
    int encontrado = 0;
    actual = inicio;
    while (p <= longitud){
        if(actual->id == b){
            encontrado = actual->id;
            return encontrado;
        }
        p++;
        actual = actual->sgte;
    }
    if (encontrado == 0){
      	return encontrado;
    }
}

Jugador* crearCPU(){
	int i,j,k,rnum;
	printf("Ingrese contra que CPU quiere enfrentarse: \n");
	scanf("%d", &k);
	if(k == 1){
		Jugador* CPU1 = crearJugador(1);
		return CPU1;
	}
	if(k == 2){
		Jugador* CPU2 = crearJugador(2);
		return CPU2;
	}
	if(k == 3){
		Jugador* CPU3 = crearJugador(3);
	return CPU3;
	}
	else{
		printf("\n");
		printf("Lo lamento, opción no válida, vuelva a intentarlo.\n");
		printf("\n");
		crearCPU();
	}
}
//Acciones de las CPUs en la Partida Normal, no imprimen por pantalla.
Lista accionCPU1N(Lista ManoCP1, Lista mano){ // Siempre seguido de un eliminarElement(mano, 1)
	Carta* carta = obtenerElemento(mano, 1);
	ManoCP1 = insertarCarta(ManoCP1, carta);
	return ManoCP1;
}

Lista accionCPU2N(Lista ManoCP2, Lista mano){// Siempre seguido de un eliminarElemento(mano, mano.longitud)
	Carta* carta = obtenerElemento(mano, mano.longitud);
	ManoCP2 = insertarCarta(ManoCP2, carta);
	return ManoCP2;
}

Lista accionCPU3N(Lista ManoCP3, Lista mano, int rnum){// Declarar un número random antes de esta función.
	/*int rnum;				incluir este código antes de llamar esta función.
	rnum = rand() % 2;*/
	if(rnum == 0){
		Carta* carta = obtenerElemento(mano, 1);
		ManoCP3 = insertarCarta(ManoCP3, carta);
	}
	if(rnum == 1){
		Carta* carta = obtenerElemento(mano, mano.longitud);
		ManoCP3 = insertarCarta(ManoCP3, carta);
	}
	return ManoCP3;
	/*if(rnum == 0){  incluir este código después de llamar esta función.
		mano = eliminarElemento(mano, 1);
	}
	if(rnum == 1){
		mano = eliminarElemento(mano, mano.longitud);
	}*/
}
//Acciones de las CPUs en la Partida Superuser, imprimen por pantalla.
Lista accionCPU1(Lista ManoCP1, Lista mano){ // Siempre seguido de un eliminarElement(mano, 1)
	Carta* carta = obtenerElemento(mano, 1);
	printf("   Carta robada por CPU1:  ");
	imprimirCarta(carta);
	printf("\n\n");
	ManoCP1 = insertarCarta(ManoCP1, carta);
	return ManoCP1;
}

Lista accionCPU2(Lista ManoCP2, Lista mano){// Siempre seguido de un eliminarElemento(mano, mano.longitud)
	Carta* carta = obtenerElemento(mano, mano.longitud);
	printf("   Carta robada por CPU2:  ");
	imprimirCarta(carta);
	printf("\n\n");
	ManoCP2 = insertarCarta(ManoCP2, carta);
	return ManoCP2;
}

Lista accionCPU3(Lista ManoCP3, Lista mano, int rnum){// Declarar un número random antes.
	/*int rnum;				incluir este código antes de llamar esta función.
	rnum = rand() % 2;*/
	if(rnum == 0){
		Carta* carta = obtenerElemento(mano, 1);
		printf("   Carta robada por CPU3:  ");
		imprimirCarta(carta);
		printf("\n\n");
		ManoCP3 = insertarCarta(ManoCP3, carta);
	}
	if(rnum == 1){
		Carta* carta = obtenerElemento(mano, mano.longitud);
		printf("   Carta robada por CPU3:  ");
		imprimirCarta(carta);
		printf("\n\n");
		ManoCP3 = insertarCarta(ManoCP3, carta);
	}
	return ManoCP3;
	/*if(rnum == 0){  incluir este código después de llamar esta función.
		mano = eliminarElemento(mano, 1);
	}
	if(rnum == 1){
		mano = eliminarElemento(mano, mano.longitud);
	}*/
}

int eleccionUsuario(int longitudManoCPU){// Se le solicita al usuario elegir la posicion de la carta del enemigo.
	int eleccionU;
	printf("El jugador siguiente tiene %d cartas\n", longitudManoCPU);
	printf("Que carta desea sacar? \n");
	scanf("%d", &eleccionU);
	printf("\n");
	if(eleccionU > longitudManoCPU || eleccionU < 1){
		printf("Lo lamento, opcion no valida, vuelva a intentarlo.\n");
		eleccionU = eleccionUsuario(longitudManoCPU);
		return eleccionU;
	}
	else{
		return eleccionU;
	}
}

Lista accionUsuario(Lista ManoP1){ // Devolverá la baraja tal y como estaba o revuelta según la decisión del usuario.
	char r;
	printf("\nDesea revolver su mano? \n      (S/n) \n");
	scanf("%c", &r);
	r = getchar(); // Recibir un carácter.
	printf("\n");

	if(r == 'S' || r == 's'){
		ManoP1 = revolverMano(ManoP1);
		return ManoP1;
	}
	if(r == 'N' || r == 'n'){
		return ManoP1;
	}
	else{
		printf("Opcion no valida, vuelva a intentarlo.\n");
		ManoP1 = accionUsuario(ManoP1);
		return ManoP1;
	}
}
// Ayudante! no te asustes! parece mucho, pero sólo es repetición de secuencias de código.
void partidaNormal(int j, char* usuario){ // Partida Normal, sólo muestra la mano del Jugador 1 (usuario).
	// Mayor cantidad de comentarios explicativos, Partida Superuser es un copy/paste de esta función,
	// pero con muestra de información en pantalla.
	int i = 1; // contador
	int k,a,b,c,d,eleccionU;
	// a,b,c,d son constantes para determinar las CPUs.
	// eleccionU es una constante que indica la elección del usuario al momento de elegir una carta de una mano enemiga.
	Lista baraja = barajaOrdenada();
	Lista barajaRevuelta = revolverBaraja(baraja);
	if(j == 1){ // Dos jugadores jugarán.
		//Asignación de CPUs.
		a = inicio->sgte->id;
		//Inicialización de Jugador 1.
		Lista ManoP1 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP1.longitud);
		printf("Mano de %s: \n", usuario);
		imprimirMano(ManoP1);
		printf("\n");
		//Inicialización de Jugador 2.
		Lista ManoP2 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP2.longitud);
		printf("CPU%d \n", a);
		//imprimirMano(ManoP2);
		printf("\n");
		// Etapa 1
		// Busqueda y extracción de pares.
		// Busqueda de pares.
		Lista ParesP1 = buscarPares(ManoP1);
		// Extracción de pares.
		ManoP1 = quitarPares(ParesP1, ManoP1);
		ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
		printf("Mano de %s: \n", usuario);
		imprimirMano(ManoP1);
		printf("\n");
		// Busqueda de pares.
		Lista ParesP2 = buscarPares(ManoP2);
		// Extracción de pares.
		ManoP2 = quitarPares(ParesP2, ManoP2);
		ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
		printf("CPU%d \n", a);
		//imprimirMano(ManoP2);
		printf("\n");
		// Fin de Etapa 1 e inicio de Etapa 2.
		while(barajaRevuelta.longitud != 0){
			if(barajaRevuelta.longitud != 0){
				Carta* carta1 = obtenerElemento(barajaRevuelta, 1);
				ManoP1 = insertarCarta(ManoP1, carta1);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP1 = buscarPares(ManoP1);
				ManoP1 = quitarPares(ParesP1, ManoP1);
				ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
				printf("Mano de %s: \n", usuario);
				imprimirMano(ManoP1);
				printf("\n");
			}
			if(barajaRevuelta.longitud != 0){
				Carta* carta2 = obtenerElemento(barajaRevuelta, 1);
				ManoP2 = insertarCarta(ManoP2, carta2);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP2 = buscarPares(ManoP2);
				ManoP2 = quitarPares(ParesP2, ManoP2);
				ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				printf("CPU%d \n", a);
				//imprimirMano(ManoP2);
				printf("\n");
			}
		}
		// Fin de Etapa 2.
		while(longitud != 0){
			// Busqueda de pares.
			printf("CPU%d  \n\n", a);
			ParesP2 = buscarPares(ManoP2);
			// Extracción de pares.
			ManoP2 = quitarPares(ParesP2, ManoP2);
			ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
			if(ManoP2.longitud == 0){
				eliminarJugador(2);
				printf("CPU%d ha salido de la partida.\n", a);
			}
			if(ManoP2.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", a);
				ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
				return;
			}
			if(ManoP2.longitud != 0){
				ManoP1 = accionUsuario(ManoP1);
				if(a == 1){
					ManoP2 = accionCPU1N(ManoP2, ManoP1);
					ManoP1 = eliminarElemento(ManoP1, 1);
				}
				if(a == 2){
					ManoP2 = accionCPU2N(ManoP2, ManoP1);
					ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
				}
				if(a == 3){
					int rnum;
					rnum = rand() % 2;
					ManoP2 = accionCPU3N(ManoP2, ManoP1, rnum);
					if(rnum == 0){
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(rnum == 1){
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
				}
				printf("CPU%d  \n\n", a);
				// Busqueda de pares.
				ParesP2 = buscarPares(ManoP2);
				// Extracción de pares.
				ManoP2 = quitarPares(ParesP2, ManoP2);
				ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				if(ManoP2.longitud == 0){
					eliminarJugador(2);
					printf("CPU%d ha salido de la partida.\n", a);
				}
				if(ManoP2.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", a);
					ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
					return;
				}
			}

			printf("Mano de %s:  \n", usuario);
			// Busqueda de pares.
			ParesP1 = buscarPares(ManoP1);
			// Extracción de pares.
			ManoP1 = quitarPares(ParesP1, ManoP1);
			ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
			imprimirMano(ManoP1);
			printf("\n");
			if(ManoP1.longitud == 0){
				eliminarJugador(1);
				printf("%s ha salido de la partida.\n", usuario);
			}
			if(ManoP1.longitud != 0 && longitud == 1){
				printf("%s ha perdido.\n", usuario);
				ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
				return;
			}
			if(ManoP1.longitud != 0){
				eleccionU = eleccionUsuario(ManoP2.longitud);
				Carta* carta1 = obtenerElemento(ManoP2, eleccionU);
				ManoP1 = insertarCarta(ManoP1, carta1);
				ManoP2 = eliminarElemento(ManoP2, eleccionU);
				// Busqueda de pares.
				printf("Mano de %s:  ", usuario);
				ParesP1 = buscarPares(ManoP1);
				// Extracción de pares.
				ManoP1 = quitarPares(ParesP1, ManoP1);
				ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
				imprimirMano(ManoP1);
				printf("\n\n");
				if(ManoP1.longitud == 0){
					eliminarJugador(1);
					printf("%s ha salido de la partida.\n", usuario);
				}
				if(ManoP1.longitud != 0 && longitud == 1){
					printf("%s ha perdido.\n", usuario);
					ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
					return;
				}
			}
		}
	}
	if(j == 2){ // Tres jugadores jugarán.
		a = inicio->sgte->id;
		b = inicio->sgte->sgte->id;
		//Inicialización de Jugador 1.
		Lista ManoP1 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP1.longitud);
		printf("Mano de %s: \n", usuario);
		imprimirMano(ManoP1);
		printf("\n");
		//Inicialización de Jugador 2.
		Lista ManoP2 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP2.longitud);
		printf("CPU%d \n", a);
		printf("\n");
		//Inicialización de Jugador 3.
		Lista ManoP3 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP3.longitud);
		printf("CPU%d \n", b);
		printf("\n");
		// Etapa 1
		// Busqueda y extracción de pares.
		// Busqueda de pares.
		Lista ParesP1 = buscarPares(ManoP1);
		// Extracción de pares.
		ManoP1 = quitarPares(ParesP1, ManoP1);
		ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
		printf("Mano de %s: \n", usuario);
		imprimirMano(ManoP1);
		printf("\n");
		// Busqueda de pares.
		Lista ParesP2 = buscarPares(ManoP2);
		// Extracción de pares.
		ManoP2 = quitarPares(ParesP2, ManoP2);
		ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
		printf("CPU%d \n", a);
		printf("\n");
		// Busqueda de pares.
		Lista ParesP3 = buscarPares(ManoP3);
		// Extracción de pares.
		ManoP3 = quitarPares(ParesP3, ManoP3);
		ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
		printf("CPU%d \n", b);
		printf("\n");
		// Fin de Etapa 1 e inicio de Etapa 2.
		while(barajaRevuelta.longitud != 0){
			if(barajaRevuelta.longitud != 0){
				Carta* carta1 = obtenerElemento(barajaRevuelta, 1);
				ManoP1 = insertarCarta(ManoP1, carta1);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP1 = buscarPares(ManoP1);
				ManoP1 = quitarPares(ParesP1, ManoP1);
				ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
				printf("Mano de %s: \n", usuario);
				imprimirMano(ManoP1);
				printf("\n");
			}
			if(barajaRevuelta.longitud != 0){
				Carta* carta2 = obtenerElemento(barajaRevuelta, 1);
				ManoP2 = insertarCarta(ManoP2, carta2);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP2 = buscarPares(ManoP2);
				ManoP2 = quitarPares(ParesP2, ManoP2);
				ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				printf("CPU%d \n", a);
				//imprimirMano(ManoP2);
				printf("\n");
			}
			if(barajaRevuelta.longitud != 0){
				Carta* carta3 = obtenerElemento(barajaRevuelta, 1);
				ManoP3 = insertarCarta(ManoP3, carta3);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP3 = buscarPares(ManoP3);
				ManoP3 = quitarPares(ParesP3, ManoP3);
				ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
				printf("CPU%d \n", b);
				//imprimirMano(ManoP3);
				printf("\n");
			}
		}
		// Fin de Etapa 2.
		// Inicio de Etapa 3.
		while(longitud != 0){ // 2 | 3->1->2->3
			// Jugador 3 (CPU).
			// Busqueda de pares.
			ParesP3 = buscarPares(ManoP3);
			// Extracción de pares.
			ManoP3 = quitarPares(ParesP3, ManoP3);
			ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
			printf("CPU%d  \n\n", b);
			if(ManoP3.longitud == 0){
				eliminarJugador(3);
				printf("CPU%d ha salido de la partida.\n", b);
			}
			if(ManoP3.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", b);
				ManoP3 = eliminarElemento(ManoP3, 1); // Eliminar última carta.
				return;
			}
			if(ManoP3.longitud != 0){ //Quitar carta al contrincante.
				if(ManoP1.longitud != 0){ //3->1
					ManoP1 = accionUsuario(ManoP1);
					if(b == 1){
						ManoP3 = accionCPU1N(ManoP3, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(b == 2){
						ManoP3 = accionCPU2N(ManoP3, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
					if(b == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP3 = accionCPU3N(ManoP3, ManoP1, rnum);
						if(rnum == 0){
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
						if(rnum == 1){
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
				}
				if(ManoP1.longitud == 0 && ManoP2.longitud != 0){ // 3->2
					// Determinar acción de CPU.
					if(b == 1){
						ManoP3 = accionCPU1N(ManoP3, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, 1);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(b == 2){
						ManoP3 = accionCPU2N(ManoP3, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(b == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP3 = accionCPU3N(ManoP3, ManoP2, rnum);
						if(rnum == 0){
							ManoP2 = eliminarElemento(ManoP2, 1);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
						if(rnum == 1){
							ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
					}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
				}
				if(ManoP3.longitud == 0){
					eliminarJugador(3);
					printf("CPU%d ha salido de la partida.\n", b);
				}
				if(ManoP3.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", b);
					ManoP3 = eliminarElemento(ManoP3, 1); // Eliminar última carta.
					return;
				}
			}
			// Jugador 1.
			// Busqueda de pares.
			ParesP1 = buscarPares(ManoP1);
			// Extracción de pares.
			ManoP1 = quitarPares(ParesP1, ManoP1);
			ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
			printf("Mano de %s:  ", usuario);
			imprimirMano(ManoP1);
			printf("\n");
			if(ManoP1.longitud == 0){
				eliminarJugador(1);
				printf("%s ha salido de la partida.\n", usuario);
			}
			if(ManoP1.longitud != 0 && longitud == 1){
				printf("%s ha perdido.\n", usuario);
				ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
				return;
			}
			if(ManoP1.longitud != 0){
				if(ManoP2.longitud != 0){ // 1->2
					eleccionU = eleccionUsuario(ManoP2.longitud);
					Carta* carta1 = obtenerElemento(ManoP2, eleccionU);
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP2 = eliminarElemento(ManoP2, eleccionU);
					if(a == 2){
						ManoP2 = revolverMano(ManoP2);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("Mano de %s:  ", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP2.longitud == 0 && ManoP3.longitud != 0) { // 1->3
					eleccionU = eleccionUsuario(ManoP3.longitud);
					Carta* carta1 = obtenerElemento(ManoP3, eleccionU);
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP3 = eliminarElemento(ManoP3, eleccionU);
					if(b == 2){ // Si es CPU2, luego de que le quiten la carta, revuelve su mano.
						ManoP3 = revolverMano(ManoP3);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("Mano de %s:  ", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP1.longitud == 0){
					eliminarJugador(1);
					printf("%s ha salido de la partida.\n", usuario);
				}
				if(ManoP1.longitud != 0 && longitud == 1){
					printf("%s ha perdido.\n", usuario);
					ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
					return;
				}
			}
			// Jugador 2 (CPU).
			// Busqueda de pares.
			ParesP2 = buscarPares(ManoP2);
			// Extracción de pares.
			ManoP2 = quitarPares(ParesP2, ManoP2);
			ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
			printf("CPU%d  \n\n", a);
			if(ManoP2.longitud == 0){
				eliminarJugador(2);
				printf("CPU%d ha salido de la partida.\n", a);
			}
			if(ManoP2.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", a);
				ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
				return;
			}
			if(ManoP2.longitud != 0){
				if(ManoP3.longitud != 0){ // 2->3
					if(a == 1){
						ManoP2 = accionCPU1N(ManoP2, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, 1);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(a == 2){
						ManoP2 = accionCPU2N(ManoP2, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3N(ManoP2, ManoP3, rnum);
						if(rnum == 0){
							ManoP3 = eliminarElemento(ManoP3, 1);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
						if(rnum == 1){
							ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				}
				if (ManoP3.longitud == 0 && ManoP1.longitud != 0) { // 2->1
					ManoP1 = accionUsuario(ManoP1);
					if(a == 1){
						ManoP2 = accionCPU1N(ManoP2, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(a == 2){
						ManoP2 = accionCPU2N(ManoP2, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3N(ManoP2, ManoP1, rnum);
						if(rnum == 0){
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
						if(rnum == 1){
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				}
				if(ManoP2.longitud == 0){
					eliminarJugador(2);
					printf("CPU%d ha salido de la partida.\n", a);
				}
				if(ManoP2.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", a);
					ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
					return;
				}
			}
		}
	}
	if(j == 3){ // Cuatro jugadores jugarán.
		//Asignación de CPUs.
		a = inicio->sgte->id;
		b = inicio->sgte->sgte->id;
		c = inicio->sgte->sgte->sgte->id;
		//Inicialización de Jugador 1.
		Lista ManoP1 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP1.longitud);
		printf("Mano de %s: \n", usuario);
		imprimirMano(ManoP1);
		printf("\n");
		//Inicialización de Jugador 2.
		Lista ManoP2 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP2.longitud);
		printf("CPU%d \n", a);
		printf("\n");
		//Inicialización de Jugador 3.
		Lista ManoP3 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP3.longitud);
		printf("CPU%d \n", b);
		printf("\n");
		//Inicialización de Jugador 4.
		Lista ManoP4 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP4.longitud);
		printf("CPU%d \n", c);
		printf("\n");
		// Etapa 1
		// Busqueda y extracción de pares.
		// Busqueda de pares.
		Lista ParesP1 = buscarPares(ManoP1);
		// Extracción de pares.
		ManoP1 = quitarPares(ParesP1, ManoP1);
		ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
		printf("Mano de %s: \n", usuario);
		imprimirMano(ManoP1);
		printf("\n");
		// Busqueda de pares.
		Lista ParesP2 = buscarPares(ManoP2);
		// Extracción de pares.
		ManoP2 = quitarPares(ParesP2, ManoP2);
		ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
		printf("CPU%d \n", a);
		printf("\n");
		// Busqueda de pares.
		Lista ParesP3 = buscarPares(ManoP3);
		// Extracción de pares.
		ManoP3 = quitarPares(ParesP3, ManoP3);
		ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
		printf("CPU%d \n", b);
		printf("\n");
		// Busqueda de pares.
		Lista ParesP4 = buscarPares(ManoP4);
		// Extracción de pares.
		ManoP4 = quitarPares(ParesP4, ManoP4);
		ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
		printf("CPU%d \n", c);
		printf("\n");
		// Fin de Etapa 1 e inicio de Etapa 2.
		while(barajaRevuelta.longitud != 0){
			if(barajaRevuelta.longitud != 0){
				Carta* carta1 = obtenerElemento(barajaRevuelta, 1);
				ManoP1 = insertarCarta(ManoP1, carta1);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP1 = buscarPares(ManoP1);
				ManoP1 = quitarPares(ParesP1, ManoP1);
				ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
				printf("Mano de %s: \n", usuario);
				imprimirMano(ManoP1);
				printf("\n");
			}
			if(barajaRevuelta.longitud != 0){
				Carta* carta2 = obtenerElemento(barajaRevuelta, 1);
				ManoP2 = insertarCarta(ManoP2, carta2);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP2 = buscarPares(ManoP2);
				ManoP2 = quitarPares(ParesP2, ManoP2);
				ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				printf("CPU%d \n\n", a);
			}
			if(barajaRevuelta.longitud != 0){
				Carta* carta3 = obtenerElemento(barajaRevuelta, 1);
				ManoP3 = insertarCarta(ManoP3, carta3);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP3 = buscarPares(ManoP3);
				ManoP3 = quitarPares(ParesP3, ManoP3);
				ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
				printf("CPU%d \n\n", b);
			}
			if(barajaRevuelta.longitud != 0){
				Carta* carta4 = obtenerElemento(barajaRevuelta, 1);
				ManoP4 = insertarCarta(ManoP4, carta4);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP4 = buscarPares(ManoP4);
				ManoP4 = quitarPares(ParesP4, ManoP4);
				ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
				printf("CPU%d \n\n", c);
			}
		}
		// Fin de Etapa 2.
		// Inicio Etapa 3.
		while(longitud != 0){ // 1 | 2->3->4->1
			//Jugador 2 (CPU).
			// Busqueda de pares.
			ParesP2 = buscarPares(ManoP2);
			// Extracción de pares.
			ManoP2 = quitarPares(ParesP2, ManoP2);
			ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
			printf("CPU%d  \n\n", a);
			if(ManoP2.longitud == 0){
				eliminarJugador(2);
				printf("CPU%d ha salido de la partida.\n", a);
			}
			if(ManoP2.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", a);
				return;
			}
			if(ManoP2.longitud != 0){ //Quitar carta al contrincante.
				if(ManoP3.longitud != 0){ // 2->3
					if(a == 1){
						ManoP2 = accionCPU1N(ManoP2, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, 1);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(a == 2){
						ManoP2 = accionCPU2N(ManoP2, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3N(ManoP2, ManoP3, rnum);
						if(rnum == 0){
							ManoP3 = eliminarElemento(ManoP3, 1);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
						if(rnum == 1){
							ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				}
				if(ManoP3.longitud == 0 && ManoP4.longitud != 0){ // 2->4
					if(a == 1){
						ManoP2 = accionCPU1N(ManoP2, ManoP4);
						ManoP4 = eliminarElemento(ManoP4, 1);
						if(c == 2){
							ManoP4 = revolverMano(ManoP4);
						}
					}
					if(a == 2){
						ManoP2 = accionCPU2N(ManoP2, ManoP4);
						ManoP4 = eliminarElemento(ManoP4, ManoP4.longitud);
						if(c == 2){
							ManoP4 = revolverMano(ManoP4);
						}
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3N(ManoP2, ManoP4, rnum);
						if(rnum == 0){
							ManoP4 = eliminarElemento(ManoP4, 1);
							if(c == 2){
								ManoP4 = revolverMano(ManoP4);
							}
						}
						if(rnum == 1){
							ManoP4 = eliminarElemento(ManoP4, ManoP4.longitud);
							if(c == 2){
								ManoP4 = revolverMano(ManoP4);
							}
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				}
				if(ManoP4.longitud == 0 && ManoP1.longitud != 0){ // 2->1
					ManoP1 = accionUsuario(ManoP1);
					if(a == 1){
						ManoP2 = accionCPU1N(ManoP2, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(a == 2){
						ManoP2 = accionCPU2N(ManoP2, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3N(ManoP2, ManoP1, rnum);
						if(rnum == 0){
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
						if(rnum == 1){
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				}
				if(ManoP2.longitud == 0){
					eliminarJugador(2);
					printf("CPU%d ha salido de la partida.\n", a);
				}
				if(ManoP2.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", a);
					return;
				}
			}
			// Jugador 3 (CPU).
			// Busqueda de pares.
			ParesP3 = buscarPares(ManoP3);
			// Extracción de pares.
			ManoP3 = quitarPares(ParesP3, ManoP3);
			ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
			printf("CPU%d  \n\n", b);
			if(ManoP3.longitud == 0){
				eliminarJugador(3);
				printf("CPU%d ha salido de la partida.\n", b);
			}
			if(ManoP3.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", b);
				return;
			}
			if(ManoP3.longitud != 0){ //Quitar carta al contrincante.
				if(ManoP4.longitud != 0){ //3->4
					if(b == 1){
						ManoP3 = accionCPU1N(ManoP3, ManoP4);
						ManoP4 = eliminarElemento(ManoP4, 1);
						if(c == 2){
							ManoP4 = revolverMano(ManoP4);
						}
					}
					if(b == 2){
						ManoP3 = accionCPU2N(ManoP3, ManoP4);
						ManoP4 = eliminarElemento(ManoP4, ManoP4.longitud);
						if(c == 2){
							ManoP4 = revolverMano(ManoP4);
						}
					}
					if(b == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP3 = accionCPU3N(ManoP3, ManoP4, rnum);
						if(rnum == 0){
							ManoP4 = eliminarElemento(ManoP4, 1);
							if(c == 2){
								ManoP4 = revolverMano(ManoP4);
							}
						}
						if(rnum == 1){
							ManoP4 = eliminarElemento(ManoP4, ManoP4.longitud);
							if(c == 2){
								ManoP4 = revolverMano(ManoP4);
							}
						}
					}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
				}
				if(ManoP4.longitud == 0 && ManoP1.longitud != 0){ // 3->1
					ManoP1 = accionUsuario(ManoP1);
					if(b == 1){
						ManoP3 = accionCPU1N(ManoP3, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(b == 2){
						ManoP3 = accionCPU2N(ManoP3, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
					if(b == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP3 = accionCPU3N(ManoP3, ManoP1, rnum);
						if(rnum == 0){
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
						if(rnum == 1){
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
				}
				if(ManoP1.longitud == 0 && ManoP2.longitud != 0){ // 3->2
					if(b == 1){
						ManoP3 = accionCPU1N(ManoP3, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, 1);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(b == 2){
						ManoP3 = accionCPU2N(ManoP3, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(b == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP3 = accionCPU3N(ManoP3, ManoP2, rnum);
						if(rnum == 0){
							ManoP2 = eliminarElemento(ManoP2, 1);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
						if(rnum == 1){
							ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
					}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
				}
				if(ManoP3.longitud == 0){
					eliminarJugador(3);
					printf("CPU%d ha salido de la partida.\n", b);
				}
				if(ManoP3.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", b);
					return;
				}
			}
			// Jugador 4 (CPU).
			// Busqueda de pares.
			ParesP4 = buscarPares(ManoP4);
			// Extracción de pares.
			ManoP4 = quitarPares(ParesP4, ManoP4);
			ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
			printf("CPU%d  \n\n", c);
			if(ManoP4.longitud == 0){
				eliminarJugador(4);
				printf("CPU%d ha salido de la partida.\n", c);
			}
			if(ManoP4.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", c);
				return;
			}
			if(ManoP4.longitud != 0){ //Quitar carta al contrincante.
				if(ManoP1.longitud != 0){ // 4->1
					ManoP1 = accionUsuario(ManoP1);
					if(c == 1){
						ManoP4 = accionCPU1N(ManoP4, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(c == 2){
						ManoP4 = accionCPU2N(ManoP4, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
					if(c == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP4 = accionCPU3N(ManoP4, ManoP1, rnum);
						if(rnum == 0){
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
						if(rnum == 1){
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					}
					// Busqueda de pares.
					ParesP4 = buscarPares(ManoP4);
					// Extracción de pares.
					ManoP4 = quitarPares(ParesP4, ManoP4);
					ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
				}
				if(ManoP1.longitud == 0 && ManoP2.longitud != 0){ //4->2
					if(c == 1){
						ManoP4 = accionCPU1N(ManoP4, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, 1);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(c == 2){
						ManoP4 = accionCPU2N(ManoP4, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(c == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP4 = accionCPU3N(ManoP4, ManoP2, rnum);
						if(rnum == 0){
							ManoP2 = eliminarElemento(ManoP2, 1);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
						if(rnum == 1){
							ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
					}
					// Busqueda de pares.
					ParesP4 = buscarPares(ManoP4);
					// Extracción de pares.
					ManoP4 = quitarPares(ParesP4, ManoP4);
					ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
				}
				if(ManoP2.longitud == 0 && ManoP3.longitud != 0){ //4->3
					if(c == 1){
						ManoP4 = accionCPU1N(ManoP4, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, 1);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(c == 2){
						ManoP4 = accionCPU2N(ManoP4, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(c == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP4 = accionCPU3N(ManoP4, ManoP3, rnum);
						if(rnum == 0){
							ManoP3 = eliminarElemento(ManoP3, 1);
							if(b == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
						if(rnum == 1){
							ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
							if(b == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
					}
					// Busqueda de pares.
					ParesP4 = buscarPares(ManoP4);
					// Extracción de pares.
					ManoP4 = quitarPares(ParesP4, ManoP4);
					ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
				}
				if(ManoP4.longitud == 0){
					eliminarJugador(4);
					printf("CPU%d ha salido de la partida.\n", c);
				}
				if(ManoP4.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", c);
					return;
				}
			}
			// Jugador 1 (CPU).
			// Busqueda de pares.
			ParesP1 = buscarPares(ManoP1);
			// Extracción de pares.
			ManoP1 = quitarPares(ParesP1, ManoP1);
			ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
			printf("Mano de %s: \n", usuario);
			imprimirMano(ManoP1);
			printf("\n");
			if(ManoP1.longitud == 0){
				eliminarJugador(1);
				printf("%s ha salido de la partida.\n", usuario);
			}
			if(ManoP1.longitud != 0 && longitud == 1){
				printf("%s ha perdido.\n", usuario);
				return;
			}
			if(ManoP1.longitud != 0){ //Quitar carta al contrincante.
				if(ManoP2.longitud != 0){
					eleccionU = eleccionUsuario(ManoP2.longitud);
					Carta* carta1 = obtenerElemento(ManoP2, eleccionU);
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP2 = eliminarElemento(ManoP2, eleccionU);
					if(a == 2){
						ManoP2 = revolverMano(ManoP2);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("Mano de %s: \n", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP2.longitud == 0 && ManoP3.longitud != 0){
					eleccionU = eleccionUsuario(ManoP3.longitud);
					Carta* carta1 = obtenerElemento(ManoP3, eleccionU);
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP3 = eliminarElemento(ManoP3, eleccionU);
					if(b == 2){
						ManoP3 = revolverMano(ManoP3);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("Mano de %s: \n", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP2.longitud == 0 && ManoP3.longitud != 0){
					eleccionU = eleccionUsuario(ManoP4.longitud);
					Carta* carta1 = obtenerElemento(ManoP4, eleccionU);
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP4 = eliminarElemento(ManoP4, eleccionU);
					if(c == 2){
						ManoP4 = revolverMano(ManoP4);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("Mano de %s: \n", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP1.longitud == 0){
					eliminarJugador(1);
					printf("%s ha salido de la partida.\n", usuario);
				}
				if(ManoP1.longitud != 0 && longitud == 1){
					printf("%s ha perdido.\n", usuario);
					return;
				}
			}
		}
	}
}
// Ambas partidas funcionan igual, sólo se diferencian en lo que muestran por pantalla.
void partidaSuperuser(int j, char* usuario){ // Partida Especial, muestra las manos y las cartas obtenidas de todos los jugadores.
	int i = 1; // contador
	int k,a,b,c,d,eleccionU; // a,b,c son identificadores de las CPU.
	Lista baraja = barajaOrdenada();
	Lista barajaRevuelta = revolverBaraja(baraja);
	if(j == 1){ // Dos jugadores jugarán.
		//Asignación de CPUs.
		a = inicio->sgte->id; // Valor dentro de Lista de Jugadores.
		// Etapa 1
		printf("\n\n\nInicio etapa 1\n\n\n");
		//Inicialización de Jugador 1.
		Lista ManoP1 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP1.longitud);
		// Turno Jugador 1.
		printf("Turno de %s\n", usuario);
		printf("   Mano de %s:  ", usuario);
		imprimirMano(ManoP1);
		printf("\n");
		//Inicialización de Jugador 2.
		Lista ManoP2 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP2.longitud);
		printf("Turno de CPU%d\n  ", a);
		printf("   Mano de CPU%d:  ", a);
		imprimirMano(ManoP2);
		printf("\n\n");
		// Busqueda y extracción de pares.
		// Busqueda de pares.
		Lista ParesP1 = buscarPares(ManoP1);
		// Extracción de pares.
		ManoP1 = quitarPares(ParesP1, ManoP1);
		printf("Turno de %s\n", usuario);
		printf("   Pares de %s:  ", usuario);
		imprimirPares(ParesP1);
		printf("\n");
		ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
		printf("   Mano de %s:  ", usuario);
		imprimirMano(ManoP1);
		printf("\n\n");
		// Busqueda de pares.
		Lista ParesP2 = buscarPares(ManoP2);
		// Extracción de pares.
		ManoP2 = quitarPares(ParesP2, ManoP2);
		printf("Turno de CPU%d\n  ", a);
		printf("   Pares de CPU%d:  ", a);
		imprimirPares(ParesP2);
		printf("\n");
		ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
		printf("   Mano de CPU%d:  ", a);
		imprimirMano(ManoP2);
		printf("\n\n");
		// Fin de Etapa 1 e inicio de Etapa 2.
		printf("\nFin etapa 1\n\n\n");
		printf("\n\n\nInicio etapa 2\n\n\n\n\n");
		while(barajaRevuelta.longitud != 0){
			if(barajaRevuelta.longitud != 0){
				printf("Turno de %s\n", usuario);
				Carta* carta1 = obtenerElemento(barajaRevuelta, 1);
				printf("   Carta robada por %s:  ", usuario);
				imprimirCarta(carta1);
				printf("\n\n");
				ManoP1 = insertarCarta(ManoP1, carta1);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP1 = buscarPares(ManoP1);
				printf("   Pares de %s:  ", usuario);
				imprimirPares(ParesP1);
				printf("\n");
				ManoP1 = quitarPares(ParesP1, ManoP1);
				ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
				printf("   Mano de %s:  ", usuario);
				imprimirMano(ManoP1);
				printf("\n\n");
			}
			if(barajaRevuelta.longitud != 0){
				printf("Turno de CPU%d\n  ", a);
				Carta* carta2 = obtenerElemento(barajaRevuelta, 1);
				printf("   Carta robada por CPU%d:  ", a);
				imprimirCarta(carta2);
				printf("\n\n");
				ManoP2 = insertarCarta(ManoP2, carta2);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP2 = buscarPares(ManoP2);
				printf("   Pares de CPU%d:  ", a);
				imprimirPares(ParesP2);
				printf("\n");
				ManoP2 = quitarPares(ParesP2, ManoP2);
				ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				printf("   Mano de CPU%d:  ", a);
				imprimirMano(ManoP2);
				printf("\n\n");
			}
		}
		// Fin de Etapa 2.
		printf("\n\n\nFin etapa 2\n\n\n\n");

		printf("\n\n\nInicio etapa 3\n\n\n\n\n");
		while(longitud != 0){ // 1 | 2->1->2->1
			//
			printf("Turno de CPU%d\n  ", a);
			// Busqueda de pares.
			ParesP2 = buscarPares(ManoP2);
			// Extracción de pares.
			ManoP2 = quitarPares(ParesP2, ManoP2);
			printf("   Pares de CPU%d:  ", a);
			imprimirPares(ParesP2);
			printf("\n");
			ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
			printf("   Mano de CPU%d:  ", a);
			imprimirMano(ManoP2);
			printf("\n");
			if(ManoP2.longitud == 0){
				eliminarJugador(2);
				printf("CPU%d ha salido de la partida.\n", a);
			}
			if(ManoP2.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", a);
				ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
				return;
			}
			if(ManoP2.longitud != 0){
				ManoP1 = accionUsuario(ManoP1);
				if(a == 1){
					ManoP2 = accionCPU1(ManoP2, ManoP1);
					ManoP1 = eliminarElemento(ManoP1, 1);
				}
				if(a == 2){
					ManoP2 = accionCPU2(ManoP2, ManoP1);
					ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
				}
				if(a == 3){
					int rnum;
					rnum = rand() % 2;
					ManoP2 = accionCPU3(ManoP2, ManoP1, rnum);
					if(rnum == 0){
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(rnum == 1){
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
				}
				// Busqueda de pares.
				ParesP2 = buscarPares(ManoP2);
				// Extracción de pares.
				ManoP2 = quitarPares(ParesP2, ManoP2);
				printf("   Pares de CPU%d:  ", a);
				imprimirPares(ParesP2);
				printf("\n");
				ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				printf("   Mano de CPU%d:  ", a);
				imprimirMano(ManoP2);
				printf("\n");
				if(ManoP2.longitud == 0){
					eliminarJugador(2);
					printf("CPU%d ha salido de la partida.\n", a);
				}
				if(ManoP2.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", a);
					ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
					return;
				}
			}

			printf("Turno de %s\n", usuario);
			// Busqueda de pares.
			ParesP1 = buscarPares(ManoP1);
			// Extracción de pares.
			ManoP1 = quitarPares(ParesP1, ManoP1);
			printf("   Pares de %s:  ", usuario);
			imprimirPares(ParesP1);
			printf("\n");
			ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
			printf("   Mano de %s:  ", usuario);
			imprimirMano(ManoP1);
			printf("\n");
			if(ManoP1.longitud == 0){
				eliminarJugador(1);
				printf("%s ha salido de la partida.\n", usuario);
			}
			if(ManoP1.longitud != 0 && longitud == 1){
				printf("%s ha perdido.\n", usuario);
				ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
				return;
			}
			if(ManoP1.longitud != 0){
				eleccionU = eleccionUsuario(ManoP2.longitud);
				Carta* carta1 = obtenerElemento(ManoP2, eleccionU);
				printf("   Carta robada por %s:  ", usuario);
				imprimirCarta(carta1);
				printf("\n\n");
				ManoP1 = insertarCarta(ManoP1, carta1);
				ManoP2 = eliminarElemento(ManoP2, eleccionU);
				if(a == 2){
					ManoP2 = revolverMano(ManoP2);
				}
				// Busqueda de pares.
				ParesP1 = buscarPares(ManoP1);
				// Extracción de pares.
				ManoP1 = quitarPares(ParesP1, ManoP1);
				printf("   Pares de %s:  ", usuario);
				imprimirPares(ParesP1);
				printf("\n");
				ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
				printf("   Mano de %s:  ", usuario);
				imprimirMano(ManoP1);
				printf("\n\n");
				if(ManoP1.longitud == 0){
					eliminarJugador(1);
					printf("%s ha salido de la partida.\n", usuario);
				}
				if(ManoP1.longitud != 0 && longitud == 1){
					printf("%s ha perdido.\n", usuario);
					ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
					return;
				}
			}
		}
	}
	if(j == 2){ // Tres jugadores jugarán.
		//Asignación de CPUs.
		a = inicio->sgte->id;
		b = inicio->sgte->sgte->id;
		// Etapa 1
		printf("\n\n\nInicio etapa 1\n\n\n");
		//Inicialización de Jugador 1.
		Lista ManoP1 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP1.longitud);
		printf("Turno de %s\n", usuario);
		printf("   Mano de %s:  ", usuario);
		imprimirMano(ManoP1);
		printf("\n");
		//Inicialización de Jugador 2.
		Lista ManoP2 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP2.longitud);
		printf("Turno de CPU%d\n  ", a);
		printf("   Mano de CPU%d:  ", a);
		imprimirMano(ManoP2);
		printf("\n");
		//Inicialización de Jugador 3.
		Lista ManoP3 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP3.longitud);
		printf("Turno de CPU%d\n  ", b);
		printf("   Mano de CPU%d:  ", b);
		imprimirMano(ManoP3);
		printf("\n\n");
		// Busqueda y extracción de pares.
		// Busqueda de pares.
		Lista ParesP1 = buscarPares(ManoP1);
		// Extracción de pares.
		ManoP1 = quitarPares(ParesP1, ManoP1);
		printf("Turno de %s\n", usuario);
		printf("   Pares de %s:  ", usuario);
		imprimirPares(ParesP1);
		printf("\n");
		ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
		printf("   Mano de %s:  ", usuario);
		imprimirMano(ManoP1);
		printf("\n\n");
		// Busqueda de pares.
		Lista ParesP2 = buscarPares(ManoP2);
		// Extracción de pares.
		ManoP2 = quitarPares(ParesP2, ManoP2);
		printf("Turno de CPU%d\n  ", a);
		printf("   Pares de CPU%d:  ", a);
		imprimirPares(ParesP2);
		printf("\n");
		ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
		printf("   Mano de CPU%d:  ", a);
		imprimirMano(ManoP2);
		printf("\n\n");
		// Busqueda de pares.
		Lista ParesP3 = buscarPares(ManoP3);
		// Extracción de pares.
		ManoP3 = quitarPares(ParesP3, ManoP3);
		printf("Turno de CPU%d\n  ", b);
		printf("   Pares de CPU%d:  ", b);
		imprimirPares(ParesP3);
		printf("\n");
		ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
		printf("   Mano de CPU%d:  ", b);
		imprimirMano(ManoP3);
		printf("\n\n");
		// Fin de Etapa 1 e inicio de Etapa 2.
		printf("\nFin etapa 1\n\n\n");
		printf("\n\n\nInicio etapa 2\n\n\n\n\n");
		while(barajaRevuelta.longitud != 0){
			if(barajaRevuelta.longitud != 0){
				printf("Turno de %s\n", usuario);
				Carta* carta1 = obtenerElemento(barajaRevuelta, 1);
				printf("   Carta robada por %s:  ", usuario);
				imprimirCarta(carta1);
				printf("\n\n");
				ManoP1 = insertarCarta(ManoP1, carta1);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP1 = buscarPares(ManoP1);
				printf("   Pares de %s:  ", usuario);
				imprimirPares(ParesP1);
				printf("\n");
				ManoP1 = quitarPares(ParesP1, ManoP1);
				ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
				printf("   Mano de %s:  ", usuario);
				imprimirMano(ManoP1);
				printf("\n\n");
			}
			if(barajaRevuelta.longitud != 0){
				printf("Turno de CPU%d\n  ", a);
				Carta* carta2 = obtenerElemento(barajaRevuelta, 1);
				printf("   Carta robada por CPU%d:  ", a);
				imprimirCarta(carta2);
				printf("\n\n");
				ManoP2 = insertarCarta(ManoP2, carta2);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP2 = buscarPares(ManoP2);
				printf("   Pares de CPU%d:  ", a);
				imprimirPares(ParesP2);
				printf("\n");
				ManoP2 = quitarPares(ParesP2, ManoP2);
				ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				printf("   Mano de CPU%d:  ", a);
				imprimirMano(ManoP2);
				printf("\n\n");
			}
			if(barajaRevuelta.longitud != 0){
				printf("Turno de CPU%d\n  ", b);
				Carta* carta3 = obtenerElemento(barajaRevuelta, 1);
				printf("   Carta robada por CPU%d:  ", b);
				imprimirCarta(carta3);
				printf("\n\n");
				ManoP3 = insertarCarta(ManoP3, carta3);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP3 = buscarPares(ManoP3);
				printf("   Pares de CPU%d:  ", b);
				imprimirPares(ParesP3);
				printf("\n");
				ManoP3 = quitarPares(ParesP3, ManoP3);
				ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
				printf("   Mano de CPU%d:   ", b);
				imprimirMano(ManoP3);
				printf("\n\n");
			}
		}
		// Fin de Etapa 2.
		printf("\n\n\nFin etapa 2\n\n\n\n");

		printf("\n\n\nInicio etapa 3\n\n\n\n\n");
		while(longitud != 0){ // 2 | 3->1->2->3

			printf("Turno de CPU%d\n  ", b);
			// Busqueda de pares.
			ParesP3 = buscarPares(ManoP3);
			// Extracción de pares.
			ManoP3 = quitarPares(ParesP3, ManoP3);
			printf("   Pares de CPU%d:  ", b);
			imprimirPares(ParesP3);
			printf("\n");
			ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
			printf("   Mano de CPU%d:  ", b);
			imprimirMano(ManoP3);
			printf("\n");
			if(ManoP3.longitud == 0){
				eliminarJugador(3);
				printf("CPU%d ha salido de la partida.\n", b);
			}
			if(ManoP3.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", b);
				ManoP3 = eliminarElemento(ManoP3, 1); // Eliminar última carta.
				return;
			}
			if(ManoP3.longitud != 0){ //Quitar carta al contrincante.
				if(ManoP1.longitud != 0){
					ManoP1 = accionUsuario(ManoP1);
					if(b == 1){
							ManoP3 = accionCPU1(ManoP3, ManoP1);
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
					if(b == 2){
							ManoP3 = accionCPU2(ManoP3, ManoP1);
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					if(b == 3){
							int rnum;
							rnum = rand() % 2;
							ManoP3 = accionCPU3(ManoP3, ManoP1, rnum);
							if(rnum == 0){
								ManoP1 = eliminarElemento(ManoP1, 1);
							}
							if(rnum == 1){
								ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
							}
						}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					printf("   Pares de CPU%d:  ", b);
					imprimirPares(ParesP3);
					printf("\n");
					ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
					printf("   Mano de CPU%d:  ", b);
					imprimirMano(ManoP3);
					printf("\n");
				}
				if(ManoP1.longitud == 0 && ManoP2.longitud != 0){
					if(b == 1){
							ManoP3 = accionCPU1(ManoP3, ManoP2);
							ManoP2 = eliminarElemento(ManoP2, 1);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
					if(b == 2){
							ManoP3 = accionCPU2(ManoP3, ManoP2);
							ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
					if(b == 3){
							int rnum;
							rnum = rand() % 2;
							ManoP3 = accionCPU3(ManoP3, ManoP2, rnum);
							if(rnum == 0){
								ManoP2 = eliminarElemento(ManoP2, 1);
								if(a == 2){
									ManoP2 = revolverMano(ManoP2);
								}
							}
							if(rnum == 1){
								ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
								if(a == 2){
									ManoP2 = revolverMano(ManoP2);
								}
							}
						}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					printf("   Pares de CPU%d:  ", b);
					imprimirPares(ParesP3);
					printf("\n");
					ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
					printf("   Mano de CPU%d:  ", b);
					imprimirMano(ManoP3);
					printf("\n");
				}
				if(ManoP3.longitud == 0){
					eliminarJugador(3);
					printf("CPU%d ha salido de la partida.\n", b);
				}
				if(ManoP3.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", b);
					ManoP3 = eliminarElemento(ManoP3, 1); // Eliminar última carta.
					return;
				}
			}


			printf("Turno de %s\n", usuario);
			// Busqueda de pares.
			ParesP1 = buscarPares(ManoP1);
			// Extracción de pares.
			ManoP1 = quitarPares(ParesP1, ManoP1);
			printf("   Pares de %s:  ", usuario);
			imprimirPares(ParesP1);
			printf("\n");
			ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
			printf("   Mano de %s:  ", usuario);
			imprimirMano(ManoP1);
			printf("\n");
			if(ManoP1.longitud == 0){
				eliminarJugador(1);
				printf("%s ha salido de la partida.\n", usuario);
			}
			if(ManoP1.longitud != 0 && longitud == 1){
				printf("%s ha perdido.\n", usuario);
				ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
				return;
			}
			if(ManoP1.longitud != 0){
				if(ManoP2.longitud != 0){
					eleccionU = eleccionUsuario(ManoP2.longitud);
					Carta* carta1 = obtenerElemento(ManoP2, eleccionU);
					printf("   Carta robada por %s:  ", usuario);
					imprimirCarta(carta1);
					printf("\n\n");
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP2 = eliminarElemento(ManoP2, eleccionU);
					if(a == 2){
						ManoP2 = revolverMano(ManoP2);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					printf("   Pares de %s:  ", usuario);
					imprimirPares(ParesP1);
					printf("\n");
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("   Mano de %s:  ", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP2.longitud == 0 && ManoP3.longitud != 0){
					eleccionU = eleccionUsuario(ManoP3.longitud);
					Carta* carta1 = obtenerElemento(ManoP3, eleccionU);
					printf("   Carta robada por %s:  ", usuario);
					imprimirCarta(carta1);
					printf("\n\n");
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP3 = eliminarElemento(ManoP3, eleccionU);
					if(b == 2){
						ManoP3 = revolverMano(ManoP3);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					printf("   Pares de %s:  ", usuario);
					imprimirPares(ParesP1);
					printf("\n");
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("   Mano de %s:  ", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP1.longitud == 0){
					eliminarJugador(1);
					printf("%s ha salido de la partida.\n", usuario);
				}
				if(ManoP1.longitud != 0 && longitud == 1){
					printf("%s ha perdido.\n", usuario);
					ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
					return;
				}
			}

			printf("Turno de CPU%d\n  ", a);
			// Busqueda de pares.
			ParesP2 = buscarPares(ManoP2);
			// Extracción de pares.
			ManoP2 = quitarPares(ParesP2, ManoP2);
			printf("   Pares de CPU%d:  ", a);
			imprimirPares(ParesP2);
			printf("\n");
			ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
			printf("   Mano de CPU%d:  ", a);
			imprimirMano(ManoP2);
			printf("\n");
			if(ManoP2.longitud == 0){
				eliminarJugador(2);
				printf("CPU%d ha salido de la partida.\n", a);
			}
			if(ManoP2.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", a);
				ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
				return;
			}
			if(ManoP2.longitud != 0){
				if(ManoP3.longitud != 0){
					if(a == 1){
						ManoP2 = accionCPU1(ManoP2, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, 1);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(a == 2){
						ManoP2 = accionCPU2(ManoP2, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3(ManoP2, ManoP3, rnum);
						if(rnum == 0){
							ManoP3 = eliminarElemento(ManoP3, 1);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
						if(rnum == 1){
							ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					printf("   Pares de CPU%d:  ", a);
					imprimirPares(ParesP2);
					printf("\n");
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
					printf("   Mano de CPU%d:  ", a);
					imprimirMano(ManoP2);
					printf("\n");
				}
				if(ManoP3.longitud == 0 && ManoP1.longitud != 0){
					ManoP1 = accionUsuario(ManoP1);
					if(a == 1){
						ManoP2 = accionCPU1(ManoP2, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(a == 2){
						ManoP2 = accionCPU2(ManoP2, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3(ManoP2, ManoP1, rnum);
						if(rnum == 0){
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
						if(rnum == 1){
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					printf("   Pares de CPU%d:  ", a);
					imprimirPares(ParesP2);
					printf("\n");
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
					printf("   Mano de CPU%d:  ", a);
					imprimirMano(ManoP2);
					printf("\n");
				}
				if(ManoP2.longitud == 0){
					eliminarJugador(2);
					printf("CPU%d ha salido de la partida.\n", a);
				}
				if(ManoP2.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", a);
					ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
					return;
				}
			}
		}
	}
	if(j == 3){ // Cuatro jugadores jugarán.
		//Asignación de CPUs.
		a = inicio->sgte->id;
		b = inicio->sgte->sgte->id;
		c = inicio->sgte->sgte->sgte->id;
		// Etapa 1
		printf("\n\n\nInicio etapa 1\n\n\n");
		//Inicialización de Jugador 1.
		Lista ManoP1 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP1.longitud);
		printf("Turno de %s\n", usuario);
		printf("   Mano de %s:  ", usuario);
		imprimirMano(ManoP1);
		printf("\n");
		//Inicialización de Jugador 2.
		Lista ManoP2 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP2.longitud);
		printf("Turno de CPU%d\n  ", a);
		printf("   Mano de CPU%d:  ", a);
		imprimirMano(ManoP2);
		printf("\n");
		//Inicialización de Jugador 3.
		Lista ManoP3 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP3.longitud);
		printf("Turno de CPU%d\n  ", b);
		printf("   Mano de CPU%d:  ", b);
		imprimirMano(ManoP3);
		printf("\n");
		//Inicialización de Jugador 4.
		Lista ManoP4 = crearMano(barajaRevuelta);
		barajaRevuelta = limpiarLista(barajaRevuelta, ManoP4.longitud);
		printf("Turno de CPU%d\n  ", c);
		printf("   Mano de CPU%d:  ", c);
		imprimirMano(ManoP4);
		printf("\n\n");
		// Busqueda y extracción de pares.
		// Busqueda de pares.
		Lista ParesP1 = buscarPares(ManoP1);
		// Extracción de pares.
		ManoP1 = quitarPares(ParesP1, ManoP1);
		printf("Turno de %s\n", usuario);
		printf("   Pares de %s:  ", usuario);
		imprimirPares(ParesP1);
		printf("\n");
		ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
		printf("   Mano de %s:  ", usuario);
		imprimirMano(ManoP1);
		printf("\n\n");
		// Busqueda de pares.
		Lista ParesP2 = buscarPares(ManoP2);
		// Extracción de pares.
		ManoP2 = quitarPares(ParesP2, ManoP2);
		printf("Turno de CPU%d\n  ", a);
		printf("   Pares de CPU%d:  ", a);
		imprimirPares(ParesP2);
		printf("\n");
		ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
		printf("   Mano de CPU%d:  ", a);
		imprimirMano(ManoP2);
		printf("\n\n");
		// Busqueda de pares.
		Lista ParesP3 = buscarPares(ManoP3);
		// Extracción de pares.
		ManoP3 = quitarPares(ParesP3, ManoP3);
		printf("Turno de CPU%d\n  ", b);
		printf("   Pares de CPU%d:  ", b);
		imprimirPares(ParesP3);
		printf("\n");
		ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
		printf("   Mano de CPU%d:  ", b);
		imprimirMano(ManoP3);
		printf("\n\n");
		// Busqueda de pares.
		Lista ParesP4 = buscarPares(ManoP4);
		// Extracción de pares.
		ManoP4 = quitarPares(ParesP4, ManoP4);
		printf("Turno de CPU%d\n  ", c);
		printf("   Pares de CPU%d:  ", c);
		imprimirPares(ParesP4);
		printf("\n");
		ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
		printf("   Mano de CPU%d:  ", c);
		imprimirMano(ManoP4);
		printf("\n\n");
		// Fin de Etapa 1 e inicio de Etapa 2.
		printf("\nFin etapa 1\n\n\n");
		printf("\n\n\nInicio etapa 2\n\n\n\n\n");
		while(barajaRevuelta.longitud != 0){
			if(barajaRevuelta.longitud != 0){
				printf("Turno de %s\n", usuario);
				Carta* carta1 = obtenerElemento(barajaRevuelta, 1);
				printf("   Carta robada por %s:  ", usuario);
				imprimirCarta(carta1);
				printf("\n\n");
				ManoP1 = insertarCarta(ManoP1, carta1);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP1 = buscarPares(ManoP1);
				printf("   Pares de %s:  ", usuario);
				imprimirPares(ParesP1);
				printf("\n");
				ManoP1 = quitarPares(ParesP1, ManoP1);
				ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
				printf("   Mano de %s:  ", usuario);
				imprimirMano(ManoP1);
				printf("\n\n");
			}
			if(barajaRevuelta.longitud != 0){
				printf("Turno de CPU%d\n  ", a);
				Carta* carta2 = obtenerElemento(barajaRevuelta, 1);
				printf("   Carta robada por CPU%d:  ", a);
				imprimirCarta(carta2);
				printf("\n\n");
				ManoP2 = insertarCarta(ManoP2, carta2);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP2 = buscarPares(ManoP2);
				printf("   Pares de CPU%d:  ", a);
				imprimirPares(ParesP2);
				printf("\n");
				ManoP2 = quitarPares(ParesP2, ManoP2);
				ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
				printf("   Mano de CPU%d:  ", a);
				imprimirMano(ManoP2);
				printf("\n\n");
			}
			if(barajaRevuelta.longitud != 0){
				printf("Turno de CPU%d\n  ", b);
				Carta* carta3 = obtenerElemento(barajaRevuelta, 1);
				printf("   Carta robada por CPU%d:  ", b);
				imprimirCarta(carta3);
				printf("\n\n");
				ManoP3 = insertarCarta(ManoP3, carta3);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP3 = buscarPares(ManoP3);
				printf("   Pares de CPU%d:  ", b);
				imprimirPares(ParesP3);
				printf("\n");
				ManoP3 = quitarPares(ParesP3, ManoP3);
				ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
				printf("   Mano de CPU%d:   ", b);
				imprimirMano(ManoP3);
				printf("\n\n");
			}
			if(barajaRevuelta.longitud != 0){
				printf("Turno de CPU%d\n  ", c);
				Carta* carta4 = obtenerElemento(barajaRevuelta, 1);
				printf("   Carta robada por CPU%d:  ", c);
				imprimirCarta(carta4);
				printf("\n\n");
				ManoP4 = insertarCarta(ManoP4, carta4);
				barajaRevuelta = eliminarElemento(barajaRevuelta, 1);

				ParesP4 = buscarPares(ManoP4);
				printf("   Pares de CPU%d:  ", c);
				imprimirPares(ParesP4);
				printf("\n");
				ManoP4 = quitarPares(ParesP4, ManoP4);
				ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
				printf("   Mano de CPU%d:   ", c);
				imprimirMano(ManoP4);
				printf("\n\n");
			}
		}
		// Fin de Etapa 2.
		printf("\n\n\nFin etapa 2\n\n\n\n");

		printf("\n\n\nInicio etapa 3\n\n\n\n\n");

		while(longitud != 0){ // 1 | 2->3->4->1

			printf("Turno de CPU%d\n  ", a);
			// Busqueda de pares.
			ParesP2 = buscarPares(ManoP2);
			// Extracción de pares.
			ManoP2 = quitarPares(ParesP2, ManoP2);
			printf("   Pares de CPU%d:  ", a);
			imprimirPares(ParesP2);
			printf("\n");
			ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
			printf("   Mano de CPU%d:  ", a);
			imprimirMano(ManoP2);
			printf("\n");
			if(ManoP2.longitud == 0){
				eliminarJugador(2);
				printf("CPU%d ha salido de la partida.\n", a);
			}
			if(ManoP2.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", a);
				ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
				return;
			}
			if(ManoP2.longitud != 0){
				if(ManoP3.longitud != 0){ // 2->3
					if(a == 1){
						ManoP2 = accionCPU1(ManoP2, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, 1);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(a == 2){
						ManoP2 = accionCPU2(ManoP2, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3(ManoP2, ManoP3, rnum);
						if(rnum == 0){
							ManoP3 = eliminarElemento(ManoP3, 1);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
						if(rnum == 1){
							ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					printf("   Pares de CPU%d:  ", a);
					imprimirPares(ParesP2);
					printf("\n");
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
					printf("   Mano de CPU%d:  ", a);
					imprimirMano(ManoP2);
					printf("\n");
				}
				if(ManoP3.longitud == 0 && ManoP4.longitud != 0){ // 2->4
					if(a == 1){
						ManoP2 = accionCPU1(ManoP2, ManoP4);
						ManoP4 = eliminarElemento(ManoP4, 1);
						if(c == 2){
							ManoP3 = revolverMano(ManoP4);
						}
					}
					if(a == 2){
						ManoP2 = accionCPU2(ManoP2, ManoP4);
						ManoP4 = eliminarElemento(ManoP4, ManoP4.longitud);
						if(c == 2){
							ManoP4 = revolverMano(ManoP4);
						}
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3(ManoP2, ManoP4, rnum);
						if(rnum == 0){
							ManoP4 = eliminarElemento(ManoP4, 1);
							if(c == 2){
								ManoP4 = revolverMano(ManoP4);
							}
						}
						if(rnum == 1){
							ManoP4 = eliminarElemento(ManoP4, ManoP4.longitud);
							if(c == 2){
								ManoP4 = revolverMano(ManoP4);
							}
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					printf("   Pares de CPU%d:  ", a);
					imprimirPares(ParesP2);
					printf("\n");
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
					printf("   Mano de CPU%d:  ", a);
					imprimirMano(ManoP2);
					printf("\n");
				}
				if(ManoP4.longitud == 0 && ManoP1.longitud != 0){ // 2->1
					ManoP1 = accionUsuario(ManoP1);
					if(a == 1){
						ManoP2 = accionCPU1(ManoP2, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(a == 2){
						ManoP2 = accionCPU2(ManoP2, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
					if(a == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP2 = accionCPU3(ManoP2, ManoP1, rnum);
						if(rnum == 0){
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
						if(rnum == 1){
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					}
					// Busqueda de pares.
					ParesP2 = buscarPares(ManoP2);
					// Extracción de pares.
					ManoP2 = quitarPares(ParesP2, ManoP2);
					printf("   Pares de CPU%d:  ", a);
					imprimirPares(ParesP2);
					printf("\n");
					ParesP2 = limpiarLista(ParesP2, ParesP2.longitud);
					printf("   Mano de CPU%d:  ", a);
					imprimirMano(ManoP2);
					printf("\n");
				}
				if(ManoP2.longitud == 0){
					eliminarJugador(2);
					printf("CPU%d ha salido de la partida.\n", a);
				}
				if(ManoP2.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", a);
					ManoP2 = eliminarElemento(ManoP2, 1); // Eliminar última carta.
					return;
				}
			}

			printf("Turno de CPU%d\n  ", b);
			// Busqueda de pares.
			ParesP3 = buscarPares(ManoP3);
			// Extracción de pares.
			ManoP3 = quitarPares(ParesP3, ManoP3);
			printf("   Pares de CPU%d:  ", b);
			imprimirPares(ParesP3);
			printf("\n");
			ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
			printf("   Mano de CPU%d:  ", b);
			imprimirMano(ManoP3);
			printf("\n");
			if(ManoP3.longitud == 0){
				eliminarJugador(3);
				printf("CPU%d ha salido de la partida.\n", b);
			}
			if(ManoP3.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", b);
				ManoP3 = eliminarElemento(ManoP3, 1); // Eliminar última carta.
				return;
			}
			if(ManoP3.longitud != 0){ //Quitar carta al contrincante.
				if(ManoP4.longitud != 0){ //3->4
					if(b == 1){
						ManoP3 = accionCPU1(ManoP3, ManoP4);
						ManoP4 = eliminarElemento(ManoP4, 1);
						if(c == 2){
							ManoP4 = revolverMano(ManoP4);
						}
					}
					if(b == 2){
						ManoP3 = accionCPU2(ManoP3, ManoP4);
						ManoP4 = eliminarElemento(ManoP4, ManoP4.longitud);
						if(c == 2){
							ManoP4 = revolverMano(ManoP4);
						}
					}
					if(b == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP3 = accionCPU3(ManoP3, ManoP4, rnum);
						if(rnum == 0){
							ManoP4 = eliminarElemento(ManoP4, 1);
							if(c == 2){
								ManoP4 = revolverMano(ManoP4);
							}
						}
						if(rnum == 1){
							ManoP4 = eliminarElemento(ManoP4, ManoP4.longitud);
							if(c == 2){
								ManoP4 = revolverMano(ManoP4);
							}
						}
					}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					printf("   Pares de CPU%d:  ", b);
					imprimirPares(ParesP3);
					printf("\n");
					ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
					printf("   Mano de CPU%d:  ", b);
					imprimirMano(ManoP3);
					printf("\n");
				}
				if(ManoP4.longitud == 0 && ManoP1.longitud != 0){ //3->1
					ManoP1 = accionUsuario(ManoP1);
					if(b == 1){
						ManoP3 = accionCPU1(ManoP3, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(b == 2){
						ManoP3 = accionCPU2(ManoP3, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
					if(b == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP3 = accionCPU3(ManoP3, ManoP1, rnum);
						if(rnum == 0){
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
						if(rnum == 1){
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					printf("   Pares de CPU%d:  ", b);
					imprimirPares(ParesP3);
					printf("\n");
					ParesP3 = limpiarLista(ParesP2, ParesP2.longitud);
					printf("   Mano de CPU%d:  ", b);
					imprimirMano(ManoP3);
					printf("\n");
				}
				if(ManoP1.longitud == 0 && ManoP2.longitud != 0){ //3->2
					if(b == 1){
						ManoP3 = accionCPU1(ManoP3, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, 1);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(b == 2){
						ManoP3 = accionCPU2(ManoP3, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(b == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP3 = accionCPU3(ManoP3, ManoP2, rnum);
						if(rnum == 0){
							ManoP2 = eliminarElemento(ManoP2, 1);
							if(a == 2){
								ManoP4 = revolverMano(ManoP2);
							}
						}
						if(rnum == 1){
							ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
					}
					// Busqueda de pares.
					ParesP3 = buscarPares(ManoP3);
					// Extracción de pares.
					ManoP3 = quitarPares(ParesP3, ManoP3);
					printf("   Pares de CPU%d:  ", b);
					imprimirPares(ParesP3);
					printf("\n");
					ParesP3 = limpiarLista(ParesP3, ParesP3.longitud);
					printf("   Mano de CPU%d:  ", b);
					imprimirMano(ManoP3);
					printf("\n");
				}
				if(ManoP3.longitud == 0){
					eliminarJugador(3);
					printf("CPU%d ha salido de la partida.\n", b);
				}
				if(ManoP3.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", b);
					ManoP3 = eliminarElemento(ManoP3, 1); // Eliminar última carta.
					return;
				}
			}

			printf("Turno de CPU%d\n  ", c);
			// Busqueda de pares.
			ParesP4 = buscarPares(ManoP4);
			// Extracción de pares.
			ManoP4 = quitarPares(ParesP4, ManoP4);
			printf("   Pares de CPU%d:  ", c);
			imprimirPares(ParesP4);
			printf("\n");
			ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
			printf("   Mano de CPU%d:  ", c);
			imprimirMano(ManoP4);
			printf("\n");
			if(ManoP4.longitud == 0){
				eliminarJugador(4);
				printf("CPU%d ha salido de la partida.\n", c);
			}
			if(ManoP4.longitud != 0 && longitud == 1){
				printf("CPU%d ha perdido.\n", c);
				ManoP4 = eliminarElemento(ManoP4, 1); // Eliminar última carta.
				return;
			}
			if(ManoP4.longitud != 0){ //Quitar carta al contrincante.
				if(ManoP4.longitud != 0){ //4->1
					ManoP1 = accionUsuario(ManoP1);
					if(c == 1){
						ManoP4 = accionCPU1(ManoP4, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, 1);
					}
					if(c == 2){
						ManoP4 = accionCPU2(ManoP4, ManoP1);
						ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
					}
					if(c == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP4 = accionCPU3(ManoP4, ManoP1, rnum);
						if(rnum == 0){
							ManoP1 = eliminarElemento(ManoP1, 1);
						}
						if(rnum == 1){
							ManoP1 = eliminarElemento(ManoP1, ManoP1.longitud);
						}
					}
					// Busqueda de pares.
					ParesP4 = buscarPares(ManoP4);
					// Extracción de pares.
					ManoP4 = quitarPares(ParesP4, ManoP4);
					printf("   Pares de CPU%d:  ", c);
					imprimirPares(ParesP4);
					printf("\n");
					ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
					printf("   Mano de CPU%d:  ", c);
					imprimirMano(ManoP4);
					printf("\n");
				}
				if(ManoP4.longitud == 0 && ManoP1.longitud != 0){ //4->2
					if(c == 1){
						ManoP4 = accionCPU1(ManoP4, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, 1);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(c == 2){
						ManoP4 = accionCPU2(ManoP4, ManoP2);
						ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
						if(a == 2){
							ManoP2 = revolverMano(ManoP2);
						}
					}
					if(c == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP4 = accionCPU3(ManoP4, ManoP2, rnum);
						if(rnum == 0){
							ManoP2 = eliminarElemento(ManoP2, 1);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
						if(rnum == 1){
							ManoP2 = eliminarElemento(ManoP2, ManoP2.longitud);
							if(a == 2){
								ManoP2 = revolverMano(ManoP2);
							}
						}
					}
					// Busqueda de pares.
					ParesP4 = buscarPares(ManoP4);
					// Extracción de pares.
					ManoP4 = quitarPares(ParesP4, ManoP4);
					printf("   Pares de CPU%d:  ", c);
					imprimirPares(ParesP4);
					printf("\n");
					ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
					printf("   Mano de CPU%d:  ", c);
					imprimirMano(ManoP4);
					printf("\n");
				}
				if(ManoP4.longitud == 0 && ManoP1.longitud != 0){ //4->3
					if(c == 1){
						ManoP4 = accionCPU1(ManoP4, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, 1);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(c == 2){
						ManoP4 = accionCPU2(ManoP4, ManoP3);
						ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
						if(b == 2){
							ManoP3 = revolverMano(ManoP3);
						}
					}
					if(c == 3){
						int rnum;
						rnum = rand() % 2;
						ManoP4 = accionCPU3(ManoP4, ManoP3, rnum);
						if(rnum == 0){
							ManoP3 = eliminarElemento(ManoP3, 1);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
						if(rnum == 1){
							ManoP3 = eliminarElemento(ManoP3, ManoP3.longitud);
							if(b == 2){
								ManoP3 = revolverMano(ManoP3);
							}
						}
					}
					// Busqueda de pares.
					ParesP4 = buscarPares(ManoP4);
					// Extracción de pares.
					ManoP4 = quitarPares(ParesP4, ManoP4);
					printf("   Pares de CPU%d:  ", c);
					imprimirPares(ParesP4);
					printf("\n");
					ParesP4 = limpiarLista(ParesP4, ParesP4.longitud);
					printf("   Mano de CPU%d:  ", c);
					imprimirMano(ManoP4);
					printf("\n");
				}
				if(ManoP4.longitud == 0){
					eliminarJugador(4);
					printf("CPU%d ha salido de la partida.\n", c);
				}
				if(ManoP4.longitud != 0 && longitud == 1){
					printf("CPU%d ha perdido.\n", c);
					ManoP4 = eliminarElemento(ManoP4, 1); // Eliminar última carta.
					return;
				}
			}


			printf("Turno de %s\n", usuario);
			// Busqueda de pares.
			ParesP1 = buscarPares(ManoP1);
			// Extracción de pares.
			ManoP1 = quitarPares(ParesP1, ManoP1);
			printf("   Pares de %s:  ", usuario);
			imprimirPares(ParesP1);
			printf("\n");
			ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
			printf("   Mano de %s:  ", usuario);
			imprimirMano(ManoP1);
			printf("\n");
			if(ManoP1.longitud == 0){
				eliminarJugador(1);
				printf("%s ha salido de la partida.\n", usuario);
			}
			if(ManoP1.longitud != 0 && longitud == 1){
				printf("%s ha perdido.\n", usuario);
				ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
				return;
			}
			if(ManoP1.longitud != 0){ //Quitar carta al contrincante.
				if(ManoP2.longitud != 0){ //1->2
					eleccionU = eleccionUsuario(ManoP2.longitud);
					Carta* carta1 = obtenerElemento(ManoP2, eleccionU);
					printf("   Carta robada por %s:  ", usuario);
					imprimirCarta(carta1);
					printf("\n\n");
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP2 = eliminarElemento(ManoP2, eleccionU);
					if(a == 2){
						ManoP2 = revolverMano(ManoP2);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					printf("   Pares de %s:  ", usuario);
					imprimirPares(ParesP1);
					printf("\n");
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("   Mano de %s:  ", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP2.longitud == 0 && ManoP3.longitud != 0){//1->3
					eleccionU = eleccionUsuario(ManoP3.longitud);
					Carta* carta1 = obtenerElemento(ManoP3, eleccionU);
					printf("   Carta robada por %s:  ", usuario);
					imprimirCarta(carta1);
					printf("\n\n");
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP3 = eliminarElemento(ManoP3, eleccionU);
					if(b == 2){
						ManoP3 = revolverMano(ManoP3);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					printf("   Pares de %s:  ", usuario);
					imprimirPares(ParesP1);
					printf("\n");
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("   Mano de %s:  ", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP3.longitud == 0 && ManoP4.longitud != 0){//1->4
					eleccionU = eleccionUsuario(ManoP4.longitud);
					Carta* carta1 = obtenerElemento(ManoP4, eleccionU);
					printf("   Carta robada por %s:  ", usuario);
					imprimirCarta(carta1);
					printf("\n\n");
					ManoP1 = insertarCarta(ManoP1, carta1);
					ManoP4 = eliminarElemento(ManoP4, eleccionU);
					if(c == 2){
						ManoP4 = revolverMano(ManoP4);
					}
					// Busqueda de pares.
					ParesP1 = buscarPares(ManoP1);
					// Extracción de pares.
					ManoP1 = quitarPares(ParesP1, ManoP1);
					printf("   Pares de %s:  ", usuario);
					imprimirPares(ParesP1);
					printf("\n");
					ParesP1 = limpiarLista(ParesP1, ParesP1.longitud);
					printf("   Mano de %s:  ", usuario);
					imprimirMano(ManoP1);
					printf("\n\n");
				}
				if(ManoP1.longitud == 0){
					eliminarJugador(1);
					printf("%s ha salido de la partida.\n", usuario);
				}
				if(ManoP1.longitud != 0 && longitud == 1){
					printf("%s ha perdido.\n", usuario);
					ManoP1 = eliminarElemento(ManoP1, 1); // Eliminar última carta.
					return;
				}
			}
		}
	}
}

void generarPartida(int n, char* usuario){
	int i,a,b,c,j,rnum;
	// rnum random number, constante designada para ser un número aleatoreo.
	// i constantes utilizada como contador
	// a,b,c constantes que determinarán el id de las CPUs.
	// j indicará el número de jugadores.
	// n indica el tipo de jugada que se llevará acabo.
	printf("1.- Jugador V/S CPU \n");
	printf("2.- Jugador V/S 2 CPU \n");
	printf("3.- Jugador V/S 3 CPU \n");
	printf("Elija una opción: ");
	scanf("%d", &j);
	printf("\n");
	if(j == 1 || j == 2 || j == 3){// Se pueden elegir hasta 3 CPUs.
		if(j == 1){ // Creará dos jugadores.
			Jugador* P1 = crearJugador(0); // Creará un Jugador con id 0 que representará el jugador Humano.
			Jugador* CPU1 = crearCPU(); // Creará una CPU.
			insertarJugador(P1);
			insertarJugador(CPU1);
			if(n == 0){
				partidaSuperuser(j, usuario);
			}
			if(n == 1){
				partidaNormal(j, usuario);
			}
		}
		if(j == 2){
			a = 0;
			b = 0;
			c = 0;
			Jugador* P1 = crearJugador(0);
			insertarJugador(P1);
			while(i != 2){
				rnum = rand() % 4;
				if(rnum == 1 && a != 1){
					Jugador* CPU1 = crearJugador(1);
					a = 1;
					insertarJugador(CPU1);
					i++;
				}
				if(rnum == 2 && b != 2){
					Jugador* CPU2 = crearJugador(2);
					b = 2;
					insertarJugador(CPU2);
					i++;
				}
				if(rnum == 3 && c != 3){
					Jugador* CPU3 = crearJugador(3);
					c = 3;
					insertarJugador(CPU3);
					i++;
				}
			}
			if(n == 0){
				partidaSuperuser(j, usuario);
			}
			if(n == 1){
				partidaNormal(j, usuario);
			}
		}
		if(j == 3){
			Jugador* P1 = crearJugador(0);
			insertarJugador(P1);
			a = 0;
			b = 0;
			c = 0;
			while(i != 3){
				rnum = rand() % 4;
				if(rnum == 1 && a != 1){
					Jugador* CPU1 = crearJugador(1);
					a = 1;
					insertarJugador(CPU1);
					i++;
				}
				if(rnum == 2 && b != 2){
					Jugador* CPU2 = crearJugador(2);
					b = 2;
					insertarJugador(CPU2);
					i++;
				}
				if(rnum == 3 && c != 3){
					Jugador* CPU3 = crearJugador(3);
					c = 3;
					insertarJugador(CPU3);
					i++;
				}
			}
			if(n == 0){
				partidaSuperuser(j, usuario);
			}
			if(n == 1){
				partidaNormal(j, usuario);
			}
		}
	}
	else{
		printf("\n");
		printf("Lo lamento, opción no válida, vuelva a intentarlo.\n");
		printf("\n");
		generarPartida(n, usuario);
	}
}

void iniciarMenu(){
	int r/*,i,p*/; // En el enunciado sólo se especifíca en mayúsculas.
	char usuario[30];	// por lo que se dejará comentado el código para que funcione con variaciones.
	char superuser[] = "JANICE";
	/*char superuser1[] = "Janice";
	char superuser2[] = "janice";*/

	printf("Bienvenido!\n");
	printf("Ingrese su nombre de usuario: ");
	fflush(stdin);
	scanf("%s",usuario);
	printf("\n");

   r = strncmp(superuser, usuario, 6);
   /*i = strncmp(superuser1, usuario, 6);
   p = strncmp(superuser2, usuario, 6);*/

	if(r == 0 /*|| i == 0 || p == 0*/){
    	printf("Partida Superuser activada\n");
    	generarPartida( 0, usuario);
    }
    else{
    	printf("Partida Normal\n");
    	generarPartida( 1, usuario);
    }
}
