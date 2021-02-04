#include <cstring>
#include <iostream>

using namespace std;

int main(){
        char cadena[6];
        cin>>ws;
        fgets(cadena, 6, stdin);
        
        for (int i=0;i<6;i++){
                if (cadena[i]=='\n') cadena[i]='\0';
        }
        cin.clear();
        cout<<cadena<<"nari"<<endl;
}

