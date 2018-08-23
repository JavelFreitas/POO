#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

struct Carro{
    int pessoas;
    int pessoasMax;
    float litros;
    float litrosMax;
    float km;

    Carro(){
        pessoas = 0;
        pessoasMax = 2;
        litros = 10;
        litrosMax = 10;
        km = 0;
    }
    
    void mostrar(){
        cout <<"# Pessoas: " << pessoas <<endl
        <<"# Combustivel: " << litros <<endl
        <<"# Km: " << km <<endl;
    }

    bool embarcar(){
        if(pessoas<pessoasMax){
            pessoas++;
            cout << "Um entrou\n";
            return true;
        }
        cout << "Limite atingido!\n";
        return false;
    }
    
    bool sair(){
        if(pessoas==0){
            cout << "Nao eh possivel fazer acao!\n";
            return false;
        }
        pessoas--;
        cout << "Um saiu\n";
        return true;
    }

    void abastecer(int quant){
        litros += quant;
        if(litros>litrosMax){
            litros = litrosMax;
            cout << "Limite maximo atingido\n";
        }else{
            cout << "Feito\n";
        }
    }

    bool dirigir(int quant){
        if((pessoas>0) && (litros>0) && (quant<=litros*10)){
            km += quant;
            litros -= ceil(quant/10);
            cout << "Feito\n";
            return true;
        }
        cout << "Nao eh possivel fazer acao, reveja rota e passageiros.\n";
        return false;
    }
    void ajuda(){
        cout<< "Comandos:\n" 
        << "Show : s\n"
        << "In : i\n"
        << "Out : o\n"
        << "Drive : d\n"
        << "Fill : f\n"
        << "Help : help\n"; 
    }
};

int main(){
    Carro tesla;
    string opcao;
    int quant;

    while(1){
        cin >> opcao;
        if(opcao=="s"){    tesla.mostrar();   }
        else if(opcao=="i"){
            tesla.embarcar();
        }else if(opcao=="o"){
            tesla.sair();
        }else if(opcao=="f"){
            cin >> quant;
            tesla.abastecer(quant);
        }else if(opcao=="d"){
            cin >> quant;
            tesla.dirigir(quant);
        }else if(opcao=="help"){
            tesla.ajuda();
        }

    }
    //Fazer alteracoes e colocar ponteiros
    return 0;
}