//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Passenger{
    string id;
    int age;
public:
    Passenger(string id = "", int age = 0)
    {
        this->id = id;
        this->age = age;
    }

    string toString(){
        stringstream out;
        out << this->id << ":" << this->age;
        return out.str(); 
    }

    int getAge(){
        return this->age;
    }

    string getId(){
        return this->id;
    }
    
};

class Topic{
    vector<Passenger*>chairs;
    int chairsPref, chairsNumber;
public:
    Topic(int qtt = 0, int pref = 0):
        chairs(qtt, nullptr)
        
    {
        this->chairsNumber = qtt;
        this->chairsPref = pref;
    }

    ~Topic(){
        for(auto * pass : chairs){
            delete(pass);
        }
    }

    string toString(){
        stringstream out;
        int i = 0;
        out << "[ ";
        for(auto pass : chairs){
            if(pass == nullptr){
                if(i < chairsPref){
                    out << "@ ";
                }else{
                    out << "- ";
                }
            }else{
                out << pass->toString() << " ";
            }
            i++;
        }
        out << "]";
        return out.str();
    }

    void add(Passenger * pass){
        if(pass->getAge()>= 60){
            for(Passenger *& person : chairs){
                if(person == nullptr){
                    person = pass;
                    return;
                }
            }
        }else{
            for(int i = chairsPref; i<chairsNumber; i++){
                if(chairs[i] == nullptr){
                    chairs[i] = pass;
                    return;
                }
            }
            for(int i = 0; i<chairsPref; i++){
                if(chairs[i] == nullptr){
                    chairs[i] = pass;
                    return;
                }
            }
        }
        throw "There are no more seats";
    }
    
    void remove(string idRm){
        for(auto& person : chairs){
            if((person != nullptr) && (person->getId()==idRm)){
                delete(person);
                person = nullptr;
            }
        }
        throw "No one with that name in this Topic";
    }

    bool validate(int chmax, int pref){
        if(chmax>=pref)
            return true;
        return false;
    }

    bool validateAge(int ageIn){
        if(ageIn <= 0){
            return false;
        }
        return true;
    }
};

template <class T>
T read(stringstream& o){
    T t;
    o >> t;
    return t;
}

class Controller{
    Topic top;
public:
    Controller(){}
    void shell(string line){
        stringstream in(line);
        string op;
        in >> op;
        if(op == "init"){
            int chmax, chpref;
            in >> chmax >> chpref;
            if(top.validate(chmax, chpref)){
                top = Topic(chmax, chpref);
            }else{
                throw "There are more preferentials than seats";
            }
        }else if(op == "show"){
            cout << top.toString() << endl;    
        }else if(op == "in"){
            string idIn;
            int ageIn;
            in >> idIn;
            in >> ageIn;
            if(top.validateAge(ageIn)){
                top.add(new Passenger(idIn, ageIn));
            }else{
                throw "Sorry, your age must be incorrect!";
            }
        }else if(op == "rm"){
            string idRm;
            in >> idRm;
            top.remove(idRm);
        }else if(op == "help"){
            throw "show, init _chairs _pref, in _id _age,\nrm _id, help";
        }else{
            throw "This command does not exist";
        }

        throw "Done!";
        
    }

    void exec(){
        string line;
        while (true){
            getline(cin, line);
            if (line == "end"){
                return;
            }
            try{
                shell(line);
            }catch(const char * e){
                cout << e << endl;
            }
        }
    }

};
int main(){
    Controller t;
    t.exec();
    return 0;
}