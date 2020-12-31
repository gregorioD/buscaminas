#include "structs.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;


void mostrarPTO(int opcion, int cantidad_u, PUsuario usuarios){
	system("CLS");
    //borrar
    cout<<"Entrando a mostrarPTO"<<endl;
	int num, x = 0, m=0, x2=0, mayorXusuario, mayorXnivel, p_usuario;
	bool flag1=true, flag2=true;
	char movimiento, rta;

	if (cantidad_u!=0){
            // mejor usuario por nivel y su puntaje
		switch(opcion){
			case 1:
			cout<<"| Nivel |   Usuario   | Puntaje "<<endl;

			mayorXusuario=0;
			mayorXnivel=0;
			p_usuario=-1;

			if(cantidad_u != 0){
				for (int i =0; i<cantidad_u; i++){
					if(usuarios[i].tlfacil !=0){ // solo si tiene alguna partida jugada
						for (int j=0;j<usuarios[i].tlfacil;j++){
							if(usuarios[i].partidasfacil[j].puntaje > mayorXusuario){
								mayorXusuario = usuarios[i].partidasfacil[j].puntaje;
							}
						}
						if(mayorXusuario>mayorXnivel){
							mayorXnivel = mayorXusuario;
							p_usuario = i;
						}
					}
				}
				if (p_usuario != -1) cout<<"| 1     | "<<usuarios[p_usuario].nombre<<" | "<<mayorXnivel<<endl;
				else cout<<"| 1     | "<<"========== | ==="<<endl;
				mayorXusuario=0;
				mayorXnivel=0;
				p_usuario=-1;

				for (int i =0; i<cantidad_u; i++){
					if(usuarios[i].tlmedio !=0){ // solo si tiene alguna partida jugada
						for (int j=0;j<usuarios[i].tlmedio;j++){
							if(usuarios[i].partidasmedio[j].puntaje > mayorXusuario){
								mayorXusuario = usuarios[i].partidasmedio[j].puntaje;
							}
						}
						if(mayorXusuario>mayorXnivel){
							mayorXnivel = mayorXusuario;
							p_usuario = i;
						}
					}
				}
				if (p_usuario != -1) cout<<"| 2     | "<<usuarios[p_usuario].nombre<<" | "<<mayorXnivel<<endl;
				else cout<<"| 2     | "<<"========== | ==="<<endl;
				mayorXusuario=0;
				mayorXnivel=0;
				p_usuario=-1;

				for (int i =0; i<cantidad_u; i++){
					if(usuarios[i].tldificil !=0){ // solo si tiene alguna partida jugada
						for (int j=0;j<usuarios[i].tldificil;j++){
							if(usuarios[i].partidasdificil[j].puntaje > mayorXusuario){
								mayorXusuario = usuarios[i].partidasdificil[j].puntaje;
							}
						}
						if(mayorXusuario>mayorXnivel){
							mayorXnivel = mayorXusuario;
							p_usuario = i;
						}
					}
				}
				if (p_usuario != -1) cout<<"| 3     | "<<usuarios[p_usuario].nombre<<" | "<<mayorXnivel<<endl;
				else cout<<"| 3     | "<<"========== | ==="<<endl;
				mayorXusuario=0;
				mayorXnivel=0;
				p_usuario=-1;
			}else{
				cout<<"| 1     | "<<"========== | ==="<<endl;
				cout<<"| 2     | "<<"========== | ==="<<endl;
				cout<<"| 3     | "<<"========== | ==="<<endl;
			}
			break;

			case 2:
            // Una cantidad definida por el usuario de usuarios con sus porcentajes
			cout<<"Ingrese la cantidad de usuarios a mostrar (un numero entre 1 y "<<cantidad_u<<"): "<<endl;
			cin>>num;
			while (num<1 || num>cantidad_u){
				system("CLS");
				cout<<"El numero ingresado no es valido: Ingrese un valor entre 1 y "<<cantidad_u<<":"<<endl;
				cin>>num;
			}
			
			while (flag1){
				cout<<"   Usuario   | % Ganadas | % Perdidas | % Abandonos"<<endl;
				x = x2;
				while (flag2 && m<32){
					cout<<" "<<usuarios[x].nombre<<" | "<<usuarios[x].ganadas<<"        | ";
					cout<<usuarios[x].perdidas<<"         | "<<usuarios[x].abandonos<<endl;
					x++;
					m++;
					if (x==num) flag2=false;
				}
				cout<<"\n\nUtilice 'j' y 'k' para desplazarse o ingrese 'q' para volver al menu";
				m=0;
				movimiento = getchar();
				if (movimiento == 'j' && x2<num-1){
					x2++;
				}else if (movimiento == 'k' && x2>0){
					x2--;
				}else if (movimiento == 'q'){
					cout<<"Desea salir al menu: s / n"<<endl;
					cin>>rta;
					if(rta=='s') flag1 = false;
				}
				system("CLS");
			}
			break;

			case 3:
            // mejor partida de cada nivel de cada usuario
			int mejpartf, mejpartm, mejpartd;
			
			while (flag1){
				cout<<" Usuario     | Nivel |  Fecha   | Mejor Puntaje"<<endl;
				x = x2;
				while (flag2 && m<10){
					mejpartf = mejorPartida(&(usuarios[x]), 1);
					mejpartm = mejorPartida(&(usuarios[x]), 2);
					mejpartd = mejorPartida(&(usuarios[x]), 3);
					cout<<usuarios[x].nombre<<" | 1     | ";
					if(mejpartf!=-1){
						cout<<usuarios[x].partidasfacil[mejpartf].fecha->dia;
						cout<<"/"<<usuarios[x].partidasfacil[mejpartf].fecha->mes<<"/"<<usuarios[x].partidasfacil[mejpartf].fecha->anyo;
						cout<<" | "<<usuarios[x].partidasfacil[mejpartf].puntaje<<endl;
					}else cout<<"-        | -"<<endl;

					if(mejpartm!=-1){
						cout<<"              | 1     | "<<usuarios[x].partidasmedio[mejpartm].fecha->dia;
						cout<<"/"<<usuarios[x].partidasmedio[mejpartm].fecha->mes<<"/"<<usuarios[x].partidasmedio[mejpartm].fecha->anyo;
						cout<<" | "<<usuarios[x].partidasmedio[mejpartm].puntaje<<endl;
					}else cout<<"-        | -"<<endl;

					if(mejpartf!=-1){
						cout<<"              | 1     | "<<usuarios[x].partidasdificil[mejpartd].fecha->dia;
						cout<<"/"<<usuarios[x].partidasdificil[mejpartd].fecha->mes<<"/"<<usuarios[x].partidasdificil[mejpartd].fecha->anyo;
						cout<<" | "<<usuarios[x].partidasdificil[mejpartd].puntaje<<endl;
					}else cout<<"-        | -"<<endl;

					x++;
					m++;
					if (x==cantidad_u) flag2=false;
				}
				cout<<"\n\nUtilice 'j' y 'k' para desplazarse o ingrese 'q' para volver al menu";
				m=0;
				movimiento = getchar();
				if (movimiento == 'j' && x2<num-1){
					x2++;
				}else if (movimiento == 'k' && x2>0){
					x2--;
				}else if (movimiento == 'q'){
					cout<<"Desea salir al menu: s / n"<<endl;
					cin>>rta;
					if(rta=='s') flag1 = false;
				}
				system("CLS");
			}
		}
	}else cout<<"No hay ningun dato guardado :("<<endl;
}













int main(){



}
