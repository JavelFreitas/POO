#include <iostream>
#include <sstream>
using namespace std;

class Car{
private:
    int passengersMax{2}, fuelMax{10},
        fuel{0}, passengers{0}, km{0};
public:
    Car(){}

    string toString(){
        cout << "P: " << passengers << endl
             << "F: " << fuel       << endl
             << "Km: "<< km        << endl;
    }

    /*int getFuel(){
        return fuel;
    }
    void setFuel(int value){
        this->fuel += value;
    }
    int getPassenger(){
        return passengers;
    }
    void setPassenger(int value){
        this->passengers += value;
    }
    void setKm(int value){
        this->km += value;
    }*/
    //tentar fazer o set things usar o target pra encurtar o código
    
    void embark(){
        if(passengers + 1 > passengersMax)
            throw "Limit exceeded";
        passengers += 1;
    }

    void exit(){
        if(passengers - 1 < 0)
            throw "The car is empty";
        passengers -= 1;
    }

    void supply(){
        int fill;
        cout << "Please insert quantity" << endl;
        cin >> fill;
        if(fuel + fill > fuelMax){
            fuel = fuelMax;
            throw "You crossed the fuel limit";
        }
        fuel += fill;
        cout << "Good to go!";
    }

    void travel(){
        int drove;
        cout << "Please insert amount you want to drive" << endl;
        cin >> drove;
        if(passengers>0){
            if(drove<=(fuel*10)){
                fuel -= (drove/10);
                km += drove;
            }else{
                throw "Not enough fuel, please refuel or recalculate the route";
            }
        }else{
            throw "Car is empty, get in the car to start driving";
        }
    }


};

class Controller{
    Car c;
public:
    void shell(string line){
        stringstream in(line);
        string op;
        in >> op;
        if(op == "init"){
            Car();
            throw "Success, you've created a car";
        }else if(op == "show"){
            c.toString();
        }else if(op == "in"){
            c.embark();
        }else if(op == "out"){
            c.exit();
        }else if(op == "fuel"){
            c.supply();
        }else if(op == "drive"){
            c.travel();
        }else if(op == "help"){
            cout << "init, show, in, out, \n"
                 << "fuel _qtt, drive _qtt\n"
                 << "help, end " << endl;
        }
        
    }
    void exec(){
        string op;
        while(true){
            getline(cin, op);
            if(op == "end")
                return;
            try{
                shell(op);
            }catch(const char* warning){
                cout << warning << endl;
            }
        }
    }
};
int main(){
    Controller t;
    t.exec();        
    return 0;
}