#include <iostream> // fazer ele com get e set e aquela parada com ponteiros
#include <sstream>
using namespace std;

class Pet{
private:
    string nome;
    int energyMax, hungryMax, cleanMax; 
    int energy, hungry, clean;   
    int age {0};
    int diamond {0};
    bool alive {true};

public:
    Pet(string nome = "Momochi", int energyMax = 0, int hungryMax = 0, int cleanMax = 0):
        nome(nome), energyMax(energyMax), hungryMax(hungryMax), cleanMax(cleanMax),
        energy(energyMax), hungry(hungryMax), clean(cleanMax)
    {
    }

    string toString(){
        stringstream ss;
        ss << "N:" << nome << ", " 
           << "E:" << energy << "/" << energyMax << ", "
           << "H:" << hungry << "/" << hungryMax << ", "
           << "C:" << clean  << "/" << cleanMax  << ", "
           << "D:" << diamond << ", A:" << age;
        return ss.str();
    }

    void Energy(int value){
        if(value <= 0){
            this->alive = false;
            energy = 0;
        }else if(value > energyMax){
            energy = energyMax;
        }else
            energy = value;
    }

    void Hunger(int value){
        if(value <= 0){
            this->alive = false;
            hungry = 0;
        }else if(value > hungryMax){
            hungry = hungryMax;
        }else
            hungry = value;
    }

    void Cleanness(int value){
        if(value <= 0){
            this->alive = false;
            clean = 0;
        }else if(value > cleanMax){
            clean = cleanMax;
        }else
            clean = value;
    }


    bool testAlive(){
        if(alive)
            return true;
        cout << "fail: pet esta morto\n" << endl;
        return false;
    }

    void play(){
        if(!testAlive())
            return;
        Energy(energy - 2);
        Hunger(hungry - 1);
        Cleanness(clean - 3);
        this->age = age + 1;
        this->diamond = diamond + 1;
        cout << "O pet se divertiu muito hoje!\n";
    }

    void eat(){
        if(!testAlive())
            return;
        Energy(energy - 1);
        Hunger(hungry + 4);
        Cleanness(clean - 2);
        this->age = age + 1;
        cout << "O pet comeu um morango\n";
    }

    void sleep(){
        if(!testAlive())
            return;
        if(energyMax - energy < 5){
            return;
        }else{
        this->age = energyMax - energy;
        Energy(energyMax);
        Hunger(hungry - 1);
        }
        cout << "O pet hibernou\n";
    }

    void Clean(){
        if(!testAlive()){
            return;
        }
        Energy(energy - 3);
        Hunger(hungry - 1);
        this->age = age + 2;
        Cleanness(cleanMax);
        cout << "O pet canta enquanto toma banho : Na cabeca shampoo lave bem o seu peh\n";
    }


    void Help(){
        cout << "init _energia _fome _limpeza, \n"
             << "show, play, sleep, clean, eat, help\n";
    }

};
struct Controller{
    Pet pet;
    string shell(string line){ 
        stringstream vem(line);
        stringstream vai;
        int en = 0, fo = 0, cl = 0;
        string op;
        vem >> op;
        if(op == "init"){
            cout << "Coloque energia, fome, e limpeza maxima do pet\n";
            cin >> en >> fo >> cl;
            pet = Pet("Momochi", en, fo, cl);
            vai << "Pet criado, bem vindo ao mundo Momochi!\n";
        }else if(op == "show"){
            vai << pet.toString();
        }else if(op == "play"){
            pet.play();
        }else if(op == "sleep"){
            pet.sleep();
        }else if(op == "clean"){
            pet.Clean();
        }else if(op == "eat"){
            pet.eat();    
        }else if(op == "help"){
            pet.Help();
        }


        return vai.str();        


    }
    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                return;
            cout << shell(line);
        }
    }
};

int main(){
    Controller t;
    t.exec();
    return 0;
}