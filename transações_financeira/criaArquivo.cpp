#include <iostream>
#include <fstream>
using namespace std;

//struct de registro
struct cliente{
    int numero;
    char nome[30];
    float saldo;
};
typedef struct cliente cliente;

int main(){
    cliente clienteVazio = {0, "", 0.0}; // Inicializando uma struct
    ofstream outCredito("credito.dat", ios::out);

    if(!outCredito){
        cerr<< "Arquivo credito.dat nao pode ser aberto." << endl;
        exit(1);
    }else{
        for(int i = 0; i < 100; i++){
            // Renterpret_Cast VAI LER BYTE A BYTE PRA ELE TRANSFERIR O CONTEÚDO DA MEMÓRIA PRO ARQUIVO. ELE IRA FAZER UMA VARREDURA GERAL
            outCredito.write(reinterpret_cast<char *> (&clienteVazio), sizeof(cliente));
        }

    }

    return 0;
}