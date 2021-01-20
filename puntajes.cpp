#include "structs.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <windows.h>

using namespace std;

void gotoxy(USHORT x, USHORT y){// Mueve el cursor, necesita windows.h
        COORD cp = {x,y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}

void DibujarCuad(char *str, int ancho, char separador='|'){
        // Imprime una string agrega separadores y determina
        // el tamano del cuadrado con ancho 
        cout<<separador<<' '<<str;
        for (int i=0;i<(ancho-(int)(strlen(str)));i++){
                cout<<' ';}
        // resultado
        // 'sep' str'espacios''fin'
}

void Puntaje(int opcion){
        int an1, an2, an3, an4;
        int num, pos=0, x = 0, linea = 0, maxLineas = 15;// maximo de lineas a mostrar al mismo tiempo
        bool flag1 = true,flag2 = true; // banderas de bucles
        char buffer[100];

        switch(opcion){
                case 1:
                an1=7;an2=11;an3=7;
                // previamente se deben transformar los puntajes a string 
                sprintf(buffer, "%d", 4);
                DibujarCuad("Nivel",an1);DibujarCuad("Usuario",an2);DibujarCuad("Puntaje",an3);
                cout<<endl;

                sprintf(buffer, "%d", 4);
                DibujarCuad("Facil",an1);DibujarCuad("francougo",an2);
                DibujarCuad("23",an3);
                cout<<endl;
                buffer[0] = '\0';

                sprintf(buffer, "%d", 4);
                DibujarCuad("Medio",an1);DibujarCuad("gregoUwU",an2);
                DibujarCuad("45",an3);
                cout<<endl;
                buffer[0] = '\0';

                sprintf(buffer, "%d", 4);
                DibujarCuad("Dificil",an1);DibujarCuad("gustiCKT",an2);
                DibujarCuad("12",an3);
                cout<<endl;
                buffer[0] = '\0';

                break;
                case 2:
                an1 = 11;an2 = 9;an3 = 10;an4 = 11; // anchos de los cuadrados a imprimir

                // validacion
                cout<<"Ingrese la cantidad de usuarios a mostrar (un numero entre 1 y "<<50<<"): "<<endl;
			    while (!(cin>>num) || (num<1 || num>50)){ 
                        cout<<"Caracter incorrecto, ingrese un numero entre 1 y "<<50<<endl;
                        cin.clear();
                        cin.ignore(200, '\n');
                }
                while (flag1){
                        cout<<"while 1"<<endl;
                        DibujarCuad("Usuario", an1);
                        DibujarCuad("% Ganadas", an2);
                        DibujarCuad("% Perdidas", an3);
                        DibujarCuad("% Abandonos", an4);
                        cout<<endl;
                        x = pos;
                        flag2 = true; // para subir luego de llegar al ultimo elemento
                        // Imprimir porcentajes
                        while (flag2 && linea<maxLineas){
                                cout<<x<<' ';
                                DibujarCuad("francougo", an1);

                                sprintf(buffer, "%.1f", 50.5);
                                DibujarCuad(buffer, an2);
                                buffer[0] = '\0';

                                sprintf(buffer, "%.1f", 24.5);
                                DibujarCuad(buffer, an3);
                                buffer[0] = '\0';

                                sprintf(buffer, "%.1f", 25.0);
                                DibujarCuad(buffer, an4);
                                buffer[0] = '\0';

                                cout<<endl;
                                ++x;
                                linea++;
                                if (x==num) flag2 = false;
                        }
                        linea = 0;
                        // movimiento
                        cout<<"Presione 'j' o 'k' para scrolear o 'q' para salir:"<<endl;
                        system("pause");
                        if (GetAsyncKeyState(0x4A)) if ((pos+maxLineas)<num){
                                pos++;
                        }
                        if (GetAsyncKeyState(0x4B)) if (pos>0){
                                pos--;
                        }
                        // salir al menu
                        if (GetAsyncKeyState(0x51)){
                                flag1 = false;
                        }
                }
                break;
                case 3:
                num; pos=0; x = 0; linea = 0; maxLineas = 15;
                an1 = 11;an2 = 7;an3 = 11;an4 = 11; 
                flag1 = true;flag2 = true;
                num = 10;
                char fecha[11];

                while (flag1){
                        DibujarCuad("Usuario", an1);DibujarCuad("Nivel", an2);
                        DibujarCuad("Fecha", an3);DibujarCuad("Mejor Puntaje", an4);
                        cout<<endl;
                        x = pos;
                        flag2 = true;
                        cout<<"x: "<<x<<endl;
                        while(flag2 && linea<(maxLineas/3)){
                                strFecha(fecha, Part);
                                sprintf(buffer, "%d", 999);
                                DibujarCuad("francougo", an1);DibujarCuad("Facil", an2);
                                DibujarCuad(fecha, an3);DibujarCuad("ptj", an4);
                                cout<<"  "<<x;
                                cout<<endl;

                                strFecha(fecha, Part);
                                sprintf(buffer, "%d", 999);
                                DibujarCuad("-", an1);DibujarCuad("Medio", an2);
                                DibujarCuad(fecha, an3);DibujarCuad("ptj", an4);
                                cout<<endl;

                                strFecha(fecha, Part);
                                sprintf(buffer, "%d", 999);
                                DibujarCuad("-", an1);DibujarCuad("Dificil", an2);
                                DibujarCuad(fecha, an3);DibujarCuad("ptj", an4);

                                cout<<endl;
                                ++x;
                                linea++;
                                if (x==num) flag2 = false;
                        }
                        linea = 0;
                        cout<<"Presione 'j' o 'k' para scrolear o 'q' para salir:"<<endl;
                        system("pause");
                        if (GetAsyncKeyState(0x4A)) if ((pos+maxLineas/3)<num){
                                pos++;
                                cout<<"incrementing pos"<<endl;
                        }
                        if (GetAsyncKeyState(0x4B)) if (pos>0){
                                pos--;
                        }
                        // salir al menu
                        if (GetAsyncKeyState(0x51)){
                                flag1 = false;
                                cout<<"exiting"<<endl;
                        }
                }


                
        }
} 
                        
void ordenarRanking(){
}


int mejorXNiv(int dificultad, PDB db){
        int mejPuntaje = 0, indice = -1;
        int qUsuarios = db -> cantidad_usuarios;

        switch(dificultad){
                case 1:

                for (int i=0;i<qUsuarios;i++){
                        if (db -> usuarios[i].partidasfacil[0].puntaje > mejPuntaje){
                                mejPuntaje = db -> usuarios[i].partidasfacil[0].puntaje;
                                indice = i;
                        }
                }
                break;
                case 2:
                for (int i=0;i<qUsuarios;i++){
                        if (db -> usuarios[i].partidasmedio[0].puntaje > mejPuntaje){
                                mejPuntaje = db -> usuarios[i].partidasmedio[0].puntaje;
                                indice = i;
                        }
                }
                break;
                case 3:
                for (int i=0;i<qUsuarios;i++){
                        if (db -> usuarios[i].partidasdificil[0].puntaje > mejPuntaje){
                                mejPuntaje = db -> usuarios[i].partidasdificil[0].puntaje;
                                indice = i;
                        }
                }
                break;
        }

        return indice;
}
                        
void ordenarPartidas(Usuario user, int dificultad){
        // Coloca la partida con el mayor puntaje en el indice 0 de cada arreglo 
        Partida aux;
        int pIndex, usrMax = 0;

        for (int j=0;j<user.tlfacil;j++){
                if (user.partidasfacil[j].puntaje > usrMax){
                        pIndex = j;
                        usrMax = user.partidasfacil[j].puntaje;
                }
        }
        aux = user.partidasfacil[pIndex];
        user.partidasfacil[pIndex] = user.partidasfacil[0];
        user.partidasfacil[0] = aux;

        usrMax = 0;

        for (int j=0;j<user.tlmedio;j++){
                if (user.partidasmedio[j].puntaje > usrMax){
                        pIndex = j;
                        usrMax = user.partidasmedio[j].puntaje;
                }
        }
        aux = user.partidasmedio[pIndex];
        user.partidasmedio[pIndex] = user.partidasmedio[0];
        user.partidasmedio[0] = aux;


        usrMax = 0;
        
        for (int j=0;j<user.tldificil;j++){
                if (user.partidasdificil[j].puntaje > usrMax){
                        pIndex = j;
                        usrMax = user.partidasdificil[j].puntaje;
                }
        }
        aux = user.partidasdificil[pIndex];
        user.partidasdificil[pIndex] = user.partidasdificil[0];
        user.partidasdificil[0] = aux;
}

void strFecha(char fecha[11], Partida part){
        char dia[3],mes[3],anio[5], fch[];
        sprintf(dia, "%d", part.fecha->dia);
        sprintf(mes, "%d", part.fecha->mes);
        sprintf(mes, "%d", part.fecha->anyo);
        fecha[0] = '\0';
        strcat(fecha, dia);strcat(fecha, "/");strcat(fecha, mes);strcat(fecha, "/");strcat(fecha, anyo);
}        

int main(){
        Puntaje(3);
        strcat();
}

