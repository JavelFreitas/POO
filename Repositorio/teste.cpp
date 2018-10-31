#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <fstream> 
using namespace std;

class Student{
    string name, program, registration;
public:

    Student(string registration = "", string program = "", string name = ""){
        this->registration = registration;
        this->program = program;
        this->name = name;
    }

    string toString(){
        stringstream out;
        out << registration << ":" << program << ":" << name;
        return out.str();
    }

};

class Teacher{
    string name;
    string registration;
public:

    Teacher(string registration = "", string name = ""){
        this->registration = registration;
        this->name = name;
    }

    string toString(){
        stringstream out;
        out << registration << ":" << name;
        return out.str();
    }
};

class Subject{
    string id, name;
public:

    Subject(string id = "", string name = ""){
        this->id = id;
        this->name = name;
    }

    string toString(){
        stringstream out;
        out << id << ":" << name;
        return out.str();
    }
    
};

template<class T>
struct Repository{
    map<string, T> all;

    void add(string key, T thing){
        if(!exist(key)){
            all[key] = thing;
        }else{
            throw "Key already exists, try another";
        }
    }

    bool exist(string key){
        return all.find(key) != all.end();
    }

    void rm(string key){
        if(!exist(key)){
            throw "Key does not exist";
        }else{
            all.erase(key);
        }
    }

    vector<T> getValues(){
        vector<T> vt;
        for(auto& par : all){
            vt.push_back(par.second);
        }
        return vt;
    }

    vector<string> getKeys(){
        vector<string> vt;
        for(auto& par : all){
            vt.push_back(par.first);
        }
        return vt;
    }

    T& getV(string key){
        auto it = all.find(key);
        if (it != all.end()){
            return it->second;
        }
        throw "Key not found";
    }

    string toString(vector<T> vet){
        stringstream out;
        for(auto& thing : vet){
            out << thing.toString() << "\n";
        }
        return out.str();
    }

};

class Controller{

    Repository<Student> rstu;
    Repository<Teacher> rtea;
    Repository<Subject> rsub;

public:

//This code can still be shortened

    string shell(string line){
        try{    
            stringstream in(line);
            stringstream out;
            string op, newKey;
            in >> op;
            if(op == "addAlu" || op == "addPro" || op == "addDis" ){
                string newReg, newProg, newName;
                if(op == "addAlu"){
                    in >> newReg >> newProg;
                    getline(in, newName);
                    newName = newName.substr(1);
                    rstu.add(newReg, Student(newReg, newProg, newName));
                }else if(op == "addPro"){
                    in >> newReg;
                    getline(in, newName);
                    newName = newName.substr(1);
                    rtea.add(newReg, Teacher(newReg, newName));
                }else{
                    in >> newReg;
                    getline(in, newName);
                    newName = newName.substr(1);
                    rsub.add(newReg, Subject(newReg, newName));
                }
            }else if(op == "showAlu" || op == "showPro" || op == "showDis"){
                if(op == "showAlu")
                    cout << rstu.toString(rstu.getValues());
                else if(op == "showPro")
                    cout << rtea.toString(rtea.getValues());
                else
                    cout << rsub.toString(rsub.getValues());
            }else if(op == "rmAlu"|| op == "rmPro" || op == "rmDis"){
                in >> newKey;
                if(op == "rmAlu"){
                    rstu.rm(newKey);
                }else if(op == "rmPro"){
                    rtea.rm(newKey);
                }else{
                    rsub.rm(newKey);
                }
            }else if(op == "getAlu"|| op == "getPro" || op == "getDis"){
                in >> newKey;
                if(op == "getAlu"){
                    Student& stu = rstu.getV(newKey);
                    cout << stu.toString() << endl; 
                }else if(op == "getPro"){
                    Teacher& tea = rtea.getV(newKey);
                    cout << tea.toString() << endl;
                }else{
                    Subject& sub = rsub.getV(newKey);
                    cout << sub.toString() << endl;
                }
            }else{
                throw "Command do not exist";
            }
            throw "^Done";
        }catch(const char * warning){
            cout << warning << endl;
        }
    }

    void tester(){
        ifstream archive ("teste.txt");
        string line;
        if(archive.is_open()){
            while(!archive.eof()){
                getline(archive, line);
                if(line == "manual"){
                    while(line != "end"){
                        getline(cin, line);
                        cout << " " << shell(line) << endl;
                    }
                }else if(line == "end"){
                    break;
                }
                cout << line << endl;
                cout << " " << shell(line) << endl;
            }
            archive.close();
        }else{
            cout << "Cannot open this archive\n";
        }
    }
};

int main(){
    Controller t;
    t.tester();
    return 0;
}
