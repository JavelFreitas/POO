#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream> 
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
// Make the repository work with other classes;
struct Controller{
    Repository<Student> rstu;
    void shell(string line){
        stringstream in(line);
        string op, newKey;
        in >> op;
        if(op == "addAlu"){
            string reg, prog, newName;
            in >> reg >> prog;
            getline(in, newName);
            newName = newName.substr(1);
            rstu.add(reg, Student(reg, prog, newName));
        }else if(op == "showAlu"){
            cout << rstu.toString(rstu.getValues());
        }else if(op == "rmAlu"){
            in >> newKey;
            rstu.rm(newKey);
        }else if(op == "getAlu"){
            in >> newKey;
            Student& stu = rstu.getV(newKey);
            cout << stu.toString() << endl;
        }else{
            throw "Command do not exist";
        }
        throw "^Done";
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end"){
                return;
            }else{
                try{
                    shell(line);
                }catch(const char * warning){
                    cout << warning << endl;
                }
            }
        }
    }

};

int main(){
    Controller t;
    t.exec();
    return 0;
}
    // Repository<Teacher> rtea;
    // Repository<Subject> rsub;