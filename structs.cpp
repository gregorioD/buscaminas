#include "structs.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

void crearBaseDeDatos(PDB database){
	database -> cantidad_usuarios = 0;
	database -> usuarios = new Usuario[100];
}
void crearUsuario(PUsuario user){
	char name[11], pwrd[13], c;
	int i = 0;
	bool correcto = false;
	puts("Ingrese su nuevo nombre: ");
	while(c = getchar() != '\n'){
		if (i<10) name[i++] = c;
	}
	i = 0;
	cout<<"Su nombre es: ";
	puts(name);
	puts("Ingrese su contrasenia: ");
	while(!correcto){
		while(c = getchar() != '\n'){
			if (i<12) pwrd[i++] = c;
		}
		if (strlen(pwrd)>=8) correcto = true;
		else cout<<"Contrasenia invalida, por favor intente otra vez."<<endl;
	}
	cout<<"Su contrasenia es: ";
	puts(pwrd);
	for (int i = 0; i<11; i++){
		user -> nombre[i] = name[i];
	}
	for (int i = 0; i<13; i++){
		user -> contrasena[i] = pwrd[i];
	}
	user -> partidas = new Partida[30];
	user -> perdidas = 0;
	user -> ganadas = 0;
	user -> abandonos = 0;
}
void GuardarPartida (PPartida match, int dif, int score, char tipo){
	// Cambie la funcion para aprovechar que pasaste todo a punteros,
	// ahora lo que hace es generar una fecha nueva con cada nueva partida
	// y despues le asigna al puntero de fecha de la partida el valor de memoria
	// de la nueva fecha uwu
	Pfecha date;
	obtenerFecha(date);
	match -> fecha = date;
	match -> dificultad = dif;
	match -> puntaje = score;
	match -> tipo = tipo;
}
void obtenerFecha (Pfecha date){
	// no se como funciona time xd, asi que si podes fijate eso de los meses y anyo
	time_t fechaact;
	time(&fechaact);
	date -> dia = (((fechaact / 60)/60)/24);
	//date -> mes = ((((fechaact / 60)/60)/24)/30);
	
	
}

void partidaAUsuario(PPartida match, PUsuario usr){
		if (match -> tipo == 'G') usr -> gan++;
		else if (match -> tipo == 'P') usr -> perd++;
		else usr -> ab++;

		int total = usr -> gan + usr -> perd + usr -> ab;

		usr -> ganadas = usr -> gan * 100.0 / total;	
		usr -> perdidas = usr -> perd * 100.0 / total;
		usr -> abandonos = usr -> ab * 100.0 / total;
}










