#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Phone{
    string label;
    string number;
public:
    Phone(string label = "", string number = ""){
        this->label = label;
        this->number = number;
    }
    bool validate(){
        for(int i=0; i< this->number.size(); i++){
            if(!isdigit(this->number[i]) && this->number[i]!='(' && this->number[i]!=')' && this->number[i]!='.'){
                return false;
            }
        }
        return true;
    }

    string getNumber(){
        return this->number;
    }

    string toString(){
        stringstream info;
        info << this->label << ":" << this-> number;
        return info.str();
    }
};

class Contact{
    string name;
    vector<Phone*>list;
public:
    Contact(string name = "Empty"){
        this->name = name;
    }

    ~Contact(){
        for(auto& person : list){
            delete(person);
        }
    }

    void add(Phone * newPhone){
        if(newPhone->validate()){
            list.push_back(newPhone);
        }else{
            delete(newPhone);
            cout << "This number ~" << newPhone->getNumber() << "~ is invalid, please verify\n";
            return;
        }
    }

    void remove(int index){
        if((index < 0) ||( index >list.size()))
            throw "Did not found index";
        list.erase(next(begin(list),+ index));
    }
    void update(){

    }

    string toString(){
        stringstream show;
        int i = 0;
        show << this->name << "=>";
        for(auto& phone : list){
            if(phone != nullptr){
                show << "[" << i << ":" << phone->toString() << "]";
            }
            i++;
        }
        return show.str();
    }
};

class Controller{
    Contact cont;
public:
    
    Controller(){}

    void shell(string line){
        // else if(op == ""){

        // }
        stringstream in(line);
        string op, newName;
        in >> op;
        if(op == "init"){
            in >> newName;
            cont = Contact(newName);
        }else if(op == "show"){
            cout << cont.toString() << endl;
        }else if(op == "add"){
            string newLabel;
            string newNumber;
            in >> newLabel >> newNumber;
            cont.add(new Phone(newLabel, newNumber));
        }else if(op == "rm"){
            int index;
            in >> index;
            cont.remove(index);
        }else if(op == "update"){
            string newUser, newPhone, newLabel, newNumber;
            in >> newUser;
            cont = Contact(newUser);
            while(in >> newPhone){
                stringstream ss(newPhone);
                getline(ss, newLabel, ':');
                getline(ss, newNumber);
                cont.add(new Phone(newLabel, newNumber));
            }
        }else if(op == "help"){
            throw "init _user, add _name _number, rm _index, show, end\nupdate _new_user (_new_number:_new_phone)(As many as you want)\n";
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
    Controller control;
    control.exec();
    return 0;
}