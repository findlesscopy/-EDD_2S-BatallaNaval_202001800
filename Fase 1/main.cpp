#include <iostream>
#include <cstdlib>

using namespace std;

int opcion;

int main(){

    do{
        cout << "--------=====Menu=====--------"<<endl;
        cout << "| 1. Carga masiva            |"<<endl;
        cout << "| 2. Registrar Usuario       |"<<endl;
        cout << "| 3. Login                   |"<<endl;
        cout << "| 4. Reportes                |"<<endl;
        cout << "| 5. Salir del Juego         |"<<endl;
        cout << "--------==============--------"<<endl;
        cin >> opcion;
        switch(opcion){
            case 1 : 
                cout <<"Carga masiva"<<endl;
                system("pause");
                break;
            case 2 :
                cout <<"Registro de usuario"<<endl;
                system("pause");
                break;
            case 3 :
                cout <<"Login"<<endl;
                system("pause");
                break;
            case 4 :
                cout << "Reportes"<<endl;
                system("pause");
                break;
            default :
                cout << "Opcion no valida"<<endl;
                system("pause");
                break;
        }
        system("cls");
    }while (opcion<=4);
    return 0;
}