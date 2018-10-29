#include <iostream> // fazer outras operações, onde usar try e catch;
#include <sstream>
using namespace std;

struct Calculadora{
    int bateria;
    int batmax;

    Calculadora(){
        this->bateria = 5;
        this->batmax = 0;
    }

    void gastarBateria(){
        if(this->bateria<=0){
            cout << "fail: bateria insuficiente";
            return;
        }
        this->bateria-=1;
    }

    int somar(int a, int b){
        gastarBateria();
        return a+b;
    }

    int subtrair(int a, int b){
        gastarBateria();
        return a-b;
    }

    int dividir(int a, int b){
        gastarBateria();
        if(b<1){
            cout << "fail: nao eh possivel fazer divisao";
            return 0;
        }
        return a/b;
    }

    void charge(int carga){
        if((bateria+carga)>batmax){
            bateria = batmax;
            cout << "Excedeu o limite, esta totalmente carregada";
        }else{
            bateria += carga;
        }
        return;
    }

    string toString(){
        return "bateria = " + to_string(this->bateria);
    }

};

struct Controller{
    Calculadora calc;
    void shell(string line){
        stringstream entrada(line);
        string op;
        int a, b;
        entrada >> op;
        if(op == "sum"){
            entrada >> a >> b;
            cout << calc.somar(a, b) << endl;
        }else if(op == "sub"){
            entrada >> a >> b;
            cout << calc.subtrair(a, b) << endl;
        }else if(op == "div"){
            entrada >> a >> b;
            cout << calc.dividir(a, b) << endl;
        }else if(op == "show"){
            cout << calc.toString() << endl;
        }else if(op == "charge"){
            entrada >> a;
            calc.charge(a);
        }else if(op == "help"){
            cout << "sum _a _b , sub _a _b , div _a _b" << endl 
                 << "show , charge , help "<< endl;
        }else{
            cout << "nao eh uma opcao" << endl;
        }

    }
    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end"){
                break;
            }
            shell(line);
        }
    }
};

int main(){
    Controller t;
    t.exec();
    return 0;
} // testando o git