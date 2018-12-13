#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <locale.h>
using namespace std;
#if 0
verificar
    deposito nao pode ser negativo
    nao pode sacar mais do que se tem no saldo 
depositar
    coloca dinheiro na conta
sacar   
    você tira dinheiro da conta
tarifa
    o estado tira dinheiro da sua conta
extornar
    retorna um valor anterior á conta, escolhe um índice, pega o valor dele e retorna pra conta
extrato
    mostra todas as operações
extratoN _n
    escolhe a quantidade de operações(sempre as ultimas) a serem mostradas

#endif
class Operacao{
public:
    
    int indice;
    string descricao;
    float valor;
    float saldo;

};

class Conta{

    int nextId; //id da próxima operaçao
    float saldo; 
    int numero;
    vector<Operacao> extrato;

public:

    Conta(int saldo = 0){
        this->saldo = saldo;
    }

    void pushOperation(string label, float value, float saldo){

    } // usado para alterar saldo e extrato

    bool debitar(string label , float value){

    } //usado para saque e tarifa

    bool creditar(string label, float value){

    } // usado para extorno e depósito

    vector<Operacao> getExtratoN(int N){

    } //retorna as última n operacoes
};

class Controller{
    Conta cont;
public:

    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        int newSaldo;
        in >> op;
        if(op == "init"){
            in >> newSaldo;
            cont = Conta(newSaldo);
        }




        else{
            throw "Comando não valido!";
        }
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end"){
                return;
            }
            try{
                shell(line);
            }catch(const char * warning){
                cout << warning << endl;
            }
        }
    }

};

int main(){
    setlocale(LC_ALL, "Portuguese");
    Controller t;
    t.exec();
    return 0;
}