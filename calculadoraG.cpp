#include <iostream>
using namespace std;

struct Calculadora{

    // Atributos
    int bateria;
    int limiteBateria;

    // Métodos
    void carregar(int carga){
        bateria += carga;
        if (bateria > limiteBateria)
            bateria = limiteBateria;
    }

    bool gastarCarga(){
        if (bateria > 0){
            bateria -= 1;
            return true;
        }
        cout << "ERRO: bateria fraca...";
        return false;
    }

    float somar(float a, float b){
        if (gastarCarga()){
            return a + b;
        }
    }

    float multiplicar(float a, float b){
        if(gastarCarga()){
            return a * b;
        }
    }

    float dividir(float a, float b){
        if(gastarCarga()){
            if(b!=0){
                return a / b;
            }
            cout << "Divisao por 0 nao permitida";
        }
    }

};

int main(){

    Calculadora c = {3, 5};
    string op;
    while (true){
        cin >> op;
        float a, b;
        cin >> a >> b;
        if (op == "soma"){
            float resp = c.somar(a, b);
            cout << resp << endl;
        } else if(op == "multiplicar"){

        } else if(op == "dividir"){
            
        } else if(op == "carregar"){
            
        }
    }

    return 0;
}