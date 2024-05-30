#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct cliente{
    int numero;
    char nome[30];
    float saldo;
};
typedef struct cliente cliente;

enum Escolhas{CRIAR = 1, TELA, ARQUIVOTEXTO, ATUALIZAR, NOVO, APAGAR, FIM};

Escolhas enterChoice(){
    int menuChoice;
    cout<< "\nMenu:" << endl
        << "1 - cria registros vazios no arquivo\n"
        << "2 - lista os dados na tela\n"
        << "3 - armazena os dados no arquivo texto \"print.txt\"\n"
        << "4 - atualiza uma conta que ja contenha informacoes\n"
        << "5 - insere informacoes em uma nova conta\n"
        << "6 - apaga informacoes de uma conta\n"
        << "7 - fim do programa\n"
        << "Opcao: ";
    cin >> menuChoice;
    return (Escolhas) menuChoice;
}

void outputLine(ostream &output, const cliente &c){
    output << setiosflags(ios::left)
            << setw(10) << c.numero
            << setw(30) << c.nome
            << setw(10) << setprecision(2) << resetiosflags(ios::left)
            << setiosflags(ios::fixed | ios::showpoint) <<c.saldo << '\n';
}

void deleteRecord(fstream &f){
    int conta;
    cliente c, clienteVazio = {0, "", 0.0};
    conta = getAccount("Conta a ser apagada");
    f.seekg((conta - 1) * sizeof(cliente));
    f.read((char *) &c, sizeof(cliente));
    if(c.numero !=0){
       f.seekp((conta -1) * sizeof(cliente));
       f.write(reinterpret_cast<const char *>(&clienteVazio),sizeof(cliente));
       cout << "Conta #" <<conta << " apagada" <<endl;
    }else{
    cerr << "Conta #" << conta << "Ja esta apagada." << endl;
    }

int getAccount(string msg){
    int conta;
    do{
        cout << msg << " (1-100): ";
        cin >> conta;
    }while (conta < 1 || conta > 100);
    return conta;
}

void newRecord(fstream &f){
    int conta;
    cliente c;

    conta = getAccount("Numero da conta nova")
    f.seekg((conta-1)*sizeof(cliente)); // lendo o registro e pulando os espaços necessários 
    f.read((char*) &c, sizeof(cliente)); //Leitura de um arquivo binário byte a byte
    if(c.numero ==0) {
        cout << "Entre nome, saldo \n";
        cin >>c.nome >> c.saldo;
        c.numero = conta;
        f.seekp((conta-1) * sizeof(cliente));
        f.write(reinterpret_cast<char *> (&clienteVazio), sizeof(cliente));
    }else{
        cerr<<"Conta #" << conta << "apagada." << endl;
    }else{
        cerr<<"Conta #" << conta<< "ja esta apagada " << endl;
    }
}

void create(fstream &f){
     cliente clienteVazio = {0, "", 0.0};
     f.seekp(0);
     for(int i = 0; i<100; i++){
        f.write(reinterpret_cast<const char *> (&clienteVazio), sizeof(cliente));
     }
}

void screen(fstream &f) { // Lê a informação em arquivo e exibe na tela
     cliente c;
     cout << setiosflags(ios::left)
            << setw(10) << "Conta"
            << setw(30) << "Nome"
            << resetiosflags(ios::left) << setw(10) << "Saldo"<< endl;
     f.seekg(0);
     f.read((char*) &c, sizeof(cliente));
     while(!f.oef()){
           if(c.numero ! = 0){
           outputLine(cout, c);
           }
           f.read((char *) &c, sizeof(cliente)); // Lendo a próxima linha
     }
}

void textFile(fstream &f){// criando um arquivo que armazena as linhas de texto
     cliente c; // ele vai receber os arquivos linha a linha
     ofstream outPrintFile("print.txt", ios::out); // vai gerar os arquivos de texto
     if(!outPrintFile){
        cerr<< "Arquivo print.txt nao pode ser aberto." << endl;
        exit(1);
     }
        outPrintFile << setiosflags(ios::left)
            << setw(10) << "Conta"
            << setw(30) << "Nome"
            << resetiosflags(ios::left) << setw(10) << "Saldo"<< endl;

    f.seekg(0);
    f.read((char *) &c, sizeof(cliente));
    while(!f.eof()){
          if(c.numero !=0){
          outputLine(outPrintFile, c);
    }
    f.read((char *) &c, sizeof(cliente));
    
    }
     outPrintFile.close()
};

void updateRecord(fstream &f) { // Atualizando o saldo
int conta;
cliente c;
float transacao;

conta = getAccount("Conta a ser atualizada");
f.seekg((conta-1) * sizeof(cliente));
f.read((char *) &c, sizeof(cliente));

if(c.numero !=0){
   outputLine(cout, c); 
   cout << "\nEntre deposito(+) ou retirada (-): ";
   cin >> transacao;
   c.saldo += transacao.
   outputLine(cout, c);
   f.seekp((conta -1) *sizeof(cliente));
   f.write(reinterpret_cast<const char *>(&c), sizeof(cliente));
   
}else{
   cerr << "Conta #" << conta << "nao possui informacao" << endl;
}

}

int main(){
    Escolhas opcao;
    fstream inOutCredito("credito.dat", ios::in | ios::out);

    if(!inOutCredito){
        cerr << "Arquivo credito.dat nao pode ser aberto." << endl;
        exit (1);
    }

    while((opcao = enterChoice()) != FIM){
        switch(opcao){
            case CRIAR:
                create(inOutCredito);
                break;
            case TELA:
                screen(inOutCredito);
                break;
            case ARQUIVOTEXTO:
                textFile(inOutCredito);
                break;
            case ATUALIZAR:
                updateRecord(inOutCredito);
                break;
            case NOVO:
                newRecord(inOutCredito);
                break;
            case APAGAR:
                deleteRecord(inOutCredito);
                break;
            default:
                cerr << "Opcao incorreta\n";
                break;
        }
        inOutCredito.clear(); // Manda os Bits para os estados iniciais do arquivo

    }
    return 0;
}