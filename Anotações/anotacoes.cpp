#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class Note{

    string title;
    string text;

public:

    Note(string title = "", string text = ""){
        this->title = title;
        this->text = text;
    }

    string toString(){
        stringstream out;
        out << title << " : " << text;
        return out.str();
    }
};

class User{
    
    string username;
    string password;
    map<string, Note> notes;

public:

    User(string name = "", string pass = ""):
        username(name), password(pass)
    {}


    void addNote(string title, string text){
        if(!existsNote(title))
            throw "This note already exists";
        notes[title] = Note(title, text);
    }

    bool rmNote(string title){

    }

    bool changePass(string oldPass, string newPass){

    }

    string toString(){

    }

    bool existsNote(string title){
        return notes.find(title) != notes.end();
    }
};

class GerLogin{

    User * current;
    System * sis;

public:
    
    GerLogin(System * sis){
        this->sis = sis;
        this->current = nullptr;
    }

    User& getUser(){
        if(isNotOn())
            throw "Ninguem logado";
        return *current;
    }

    void login(){
        
    }

    void logout(){

    }

    bool isNotOn(){
        if(current == nullptr)
            return false;
        return true;
    }

};

class System{
    
    map<string, User> users;

public:

    bool addUser(User user){

    }

    User& getUser(){

    }

    string toString(){

    }

    bool exists(){

    }
    

};

class Controller{
    
    System sis;
    GerLogin gerlog;

public:

    Controller():
        gerlog(&sis)
    {

    }

    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op, newUser, newPass;
        
        in >> op;
        
        try{
            if(op == "addUser"){
                in >> newUser >> newPass;
            }
        }catch(const char * warning){
            cout << warning << endl;
        }
        return out.str();

    }

    void exec(){

        ifstream file("teste.txt");
        string line;
        if(file.is_open()){
            while(!file.eof()){
                getline(file, line);
                if(line == "manual"){
                    while(getline(cin, line)){
                        if(line == "end")
                            return;
                        cout << "  " << shell(line) << endl;
                    }
                }else if(line == "end")
                    return;
                cout << line << endl;
                cout << "  " << shell(line) << endl;
            }
            file.close();
        }else{
            cout << "Cannot open file";
        }
    }

};


int main(){
    
    Controller control;
    control.exec();
    return 0;

}