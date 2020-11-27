#include "structs.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cstdio>

using namespace std;
// Para guardar datos de partidas:
// se guarda una partida(inicializa), se ejecuta partidaAUsuario para cargar los datos y
// se ejecuta guardarDB para escribir los datos modificados al archivo (los usuarios se crean
// dentro de la base de datos por lo que no es necesario cargarlos en la misma)

void crearBaseDeDatos(PDB database){
	database -> cantidad_usuarios = 0;
}

// inicializa a un usuario con el nombre y contrasenia que el usuario ingrese
void crearUsuario(PDB database){
	int cont = 0, QUsuarios = database -> cantidad_usuarios;
	Usuario user = database -> usuarios[database -> cantidad_usuarios];
	PUsuario Puser = &user;
	char nombre[11], n[11], contrasena[13];
	bool correcto = false, tamanoCorrecto = false, esAlNum = true, esUnic = true;
	if (QUsuarios < 100){
		cin.ignore(1000, '\n');
		cout<<"Ingrese su nombre: ";
		gets(nombre);
		while(!correcto){
			if(strlen(nombre)>7 && strlen(nombre) <11){
				tamanoCorrecto = true;
			}
			while(esAlNum && cont<strlen(nombre)){
				if(!isalnum(nombre[cont])) esAlNum = false;
				else cont++;
			}
			cont = 0;
			if(QUsuarios > 0){
				while(esUnic && cont < QUsuarios){
					strcpy(n, database -> usuarios[cont].nombre);
					if(strcmp(nombre, n)==0) esUnic = false;
					else cont++;
				}
				cont = 0;
			}
			if (tamanoCorrecto && esAlNum && esUnic){
				correcto = true;
			}
		}
		cout <<"Su nombre es: "<<nombre;
		correcto = false;
		tamanoCorrecto = false;
		esAlNum = true;
		cin.ignore(1000, '\n');
		cout<<"Ingrese su contrasena: ";
		gets(contrasena);
		while (!correcto){
			if (strlen(contrasena) > 0 && strlen(contrasena)<13){
				tamanoCorrecto = true;
			}
			while(esAlNum && cont<strlen(contrasena)){
				if(!isalnum(contrasena[cont])) esAlNum = false;
				else cont++;
			}
			if (esAlNum && tamanoCorrecto){
				correcto = true;
				cout<<"Su contrasena es: "<<contrasena<<endl;
			}
		}
		strcpy((Puser -> nombre), nombre);
		strcpy((Puser -> contrasena), contrasena);
		Puser -> perdidas = 0;
		Puser -> ganadas = 0;
		Puser -> abandonos = 0;
		Puser -> tlfacil = 0;
		Puser -> tlmedio = 0;
		Puser -> tldificil = 0;
		database -> cantidad_usuarios++;
		}
}

void GuardarPartida (PPartida match, int dif, int score, char tipo){
	// Cambie la funcion para aprovechar que pasaste todo a punteros,
	// ahora lo que hace es generar una fecha nueva con cada nueva partida
	// y despues le asigna al puntero de fecha de la partida el valor de memoria
	// de la nueva fecha uwu
	Fecha date;
	Pfecha punterodate = &date;
	obtenerFecha(punterodate);
	match -> fecha = punterodate;
	match -> dificultad = dif;
	match -> puntaje = score;
	match -> tipo = tipo;
}

void obtenerFecha(Pfecha date){
	
	int dig0, dig1, dig2, dig3, mes, anio, dia;
	char fecha[25], nombreMes[3];
	time_t current_time;
	current_time=time(NULL);
	ctime(&current_time);
	strcpy(fecha, ctime(&current_time));
	dig0 = (int)fecha[8] - 48;
	dig1 = (int)fecha[9] -48;
	dia = dig0 * 10 + dig1;
	date -> dia = dia;
	for (int i = 0; i<3; i++){
		nombreMes[i] = fecha[i+4];
	}
	mes = QueMesEs(nombreMes);
	date -> mes = mes;
	dig0 = (int)fecha[20] - 48;
	dig1 = (int)fecha[21] -48;
	dig2 = (int)fecha[22] -48;
	dig3 = (int)fecha[23] -48;
	anio = dig0 * 1000 + dig1 * 100 + dig2 * 10 + dig3;
	date -> anyo = anio;
}
	
int QueMesEs(char mes[3]){
	int rdo = -1;
	if (mes[0]=='D'){
		rdo = 12;
	}else{
		if (mes[0]=='N'){
			rdo = 11;
		}else{
			if (mes[0]=='O'){
				rdo = 10;
			}else{
				if (mes[0]=='S'){
					rdo = 9;
				}else{
					if (mes[0]=='F'){
						rdo = 2;
					}else{
						if(mes[0]=='A'){
							if (mes[1]=='p') rdo = 4;
							else rdo = 8;
						}else{
							if(mes[0]=='M'){
								if(mes[2]=='r') rdo = 3;
								else rdo = 5;
							}else{
								if(mes[0]=='J'){
									if(mes[1]=='a') rdo = 1;
									else{
										if (mes[2]=='n') rdo = 6;
										else rdo = 7;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return  rdo;
}

// toma una partida y le guarda los datos al usuario ingresado
void partidaAUsuario(PPartida match, PUsuario usr){
		if (match -> tipo == 'G') usr -> gan++;
		else if (match -> tipo == 'P') usr -> perd++;
		else usr -> ab++;
		int total = (usr -> gan) + (usr -> perd) + (usr -> ab);
		usr -> ganadas = usr -> gan * 100.0 / total;	
		usr -> perdidas = usr -> perd * 100.0 / total;
		usr -> abandonos = usr -> ab * 100.0 / total;
		

		// guardado de partida
		int menor_punt = 10000000, pos=-1;
		if (match -> dificultad ==1){
			if (usr->tlfacil==10) {
				for (int i=0;i<10;i++){
					if (usr->partidasfacil[i].puntaje < menor_punt){
						menor_punt = usr->partidasfacil[i].puntaje;
						pos = i;
					}
				}
				if (match->puntaje>menor_punt) usr->partidasfacil[pos] = *match;
			}else{
				usr->partidasfacil[usr->tlfacil] = *match;
				usr->tlfacil++;
			}
		}
		else if (match -> dificultad ==2){
			if (usr->tlmedio ==10){
				for (int j=0;j<10;j++){
					if (usr->partidasmedio[j].puntaje < menor_punt){
						menor_punt = usr->partidasmedio[j].puntaje;
						pos = j;
					}
				}
				if (match->puntaje>menor_punt) usr->partidasmedio[pos] = *match;
			}else{
				usr->partidasmedio[usr->tlmedio] = *match;
				usr->tlmedio++;
			}
		}
		else{
			if (usr->tldificil==10){
				for (int k=0;k<10;k++){
					if (usr->partidasdificil[k].puntaje < menor_punt){
						menor_punt = usr->partidasdificil[k].puntaje;
						pos = k;
					}
				}
				if (match->puntaje>menor_punt) usr->partidasdificil[pos] = *match;
			}else{
				usr->partidasdificil[usr->tldificil] = *match;
				usr->tldificil++;
			}
		}
}

// guarda la base de datos ingresada en el archivo
void guardarDB(PDB database){
	ofstream archivo;
	archivo.open("usuarios.bin",ios::binary);
	if(!archivo.fail()){
		archivo.write((char*) database, sizeof(*database));
		archivo.close();
		cout<<"Progreso guardado"<<endl;
	}else{
		cout<<"Error al abrir el archivo. guardarDB"<<endl;
	}

}

// busca un usuario por su nombre y contrasenia
Usuario AbrirUsuario (PDB database, bool &sale){
	Usuario user;
	int QU = database -> cantidad_usuarios, cont = 0, i = 0, longitud;
	char nombre[11], n[11], pwrd[13], p[13];
	bool encontrado = false, coincide = false;
	while(cont<3 && (!ecnontrado || !coincide)){
		while(!encontrado){
			cin.ignore(1000, '\n');
			cout<<"Ingrese nombre de usuario: ";
			gets(nombre);
			while(!encontrado && cont < QU){
				strcpy(n, (database->usuarios[cont].nombre));
				if (strcmp(nombre, n)==0) encontrado = true;
				else cont++;
			}
			cont = 0;
			if(!encontrado) cout<<"Usuario inexistente."<<endl;
		}
		while(!coincide){
			strcpy(p, (database -> usuarios[cont].contrasena));
			cin.ignore(1000, '\n');
			cout<<"Ingrese su contrasena: ";
			gets(pwrd);
			if (strcmp(pwrd, p)==0) coincide = true;
			else cout<<"Contrasena incorrecta, por favor, intente de nuevo."<<endl;
		}	
		if (encontrado && coincide) user = database -> usuarios[cont];
		else cont++;
	}
	if (cont==3) sale = true;
	else sale = false;
	
	return user;
}

//se ejecuta al comienzo del programa
// intenta leer un archivo, lo crea si no existe y lee o crea una base de datos para cargar
// en memoria
DB AbrirBaseDeDatos(){
	DB database;
	PDB aux;
	ifstream archivo;
	archivo.open("usuarios.bin",ios::binary);
	if(!archivo.fail()){
		// cambie esta parte para que si no logra leer la base de datos devuelva una nueva

		archivo.read((char*) &database, sizeof(database));
		if (archivo.eof()){
			crearBaseDeDatos(aux);
			database = *aux;
		}
		
		archivo.close();
		
	}else{
		// se toma en cuenta que si fail=1 es porque el archivo no existe y se crea uno
		crearBaseDeDatos(aux);
		ofstream arch;
		arch.open("usuarios.bin", ios::binary);
		arch.write((char*) aux, sizeof(*aux));
		database = *aux;
		//puts("Error al abrir el archivo.(Abrir base de datos)");
	}
	return database;
}

//calcula puntos con el tiempo
int calculoPTO(int tiempo){
	int ret;
	if (tiempo<=0) ret = 1000000;
	else ret=60000/tiempo;
	
}






















