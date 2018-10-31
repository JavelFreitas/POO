#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#if 0
class Operacao
+ indice: int
+ descricao: string
+ valor: float
+ saldo: float

class Conta
- nextId: int //id da próxima operaçao
- saldo: float
- numero: int
- extrato: Operacao[]
--
+ pushOperation(label: string, value: float, saldo: float) // usado para alterar saldo e extrato
+ debitar(label: string, value: float) : boolean //usado para saque e tarifa
+ creditar(label: string, value: float) : boolean // usado para extorno e depósito
+ getExtratoN(N: int): Operacao[] //retorna as última n operacoes
#endif

class Controller{

public:



    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
    }

    void exec(){
        ifstream archive ("testes2.txt");
        string line;
        if(archive.is_open()){
            while(!archive.eof()){
                getline(archive, line);
                if(line == "manual"){
                    while(line != "end"){
                        getline(cin, line);
                        cout << shell(line) << endl;
                    }
                }else if(line == "end"){
                    break;
                }
                cout << line << endl;
                cout << shell(line) << endl;
            }
            archive.close();
        }else{
            cout << "Cannot open this archive";
        }
    }

};

int main(){
    Controller t;
    t.exec();
    return 0;
}