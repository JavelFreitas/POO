#include <iostream>
#include <vector>
#include <sstream>
#include <clocale>
#include <algorithm>

using namespace std;

class Client{
    string id;
    string fone;
public:
    Client(string id = "", string fone = "")
    {
        this->id = id;
        this->fone = fone;
    }
    string toString(){
        stringstream ss;
        ss << this->id << ":" << this-> fone;
        return ss.str();
    }
    string getID(){
        return id;
    }
};

class Cinema{
    vector<Client*>chairs;

public:

    Cinema(int qtt = 0):
        chairs(qtt, nullptr)
    {
    }

    ~Cinema(){
        for(Client* cli : chairs){
            delete(cli);
        }
    }

    void add(Client * cli,int idc){
        int qtt = chairs.size();

        if(idc >= qtt || idc < 0){
            throw "Chair does not exist!";
        }else if(chairs[idc] != nullptr){
            throw "This chair is occupy";
        }
        for(int i=0; i< qtt; i++){
            if((chairs[i] != nullptr) && (chairs[i]->getID() == cli->getID()))
                throw "This Client is already at the cinema";
        }
        chairs[idc] = cli;
        return;
    }

    void remove(string name){
        for (Client *& cli : chairs){
            if((cli != nullptr) && (cli->getID() == name)){
                delete(cli);
                cli = nullptr;
            }
        }
    }
    string toString(){
        stringstream os;
        os << "[";
        for(auto client : chairs){
            if(client == nullptr){
                os << "- ";
            }else{
                os << client->toString() << " ";
            }
        }
        os << "]";
        return os.str();
    }

//    friend ostream& operator<<(ostream& os, Cinema cine);
};

// template <class T>
// ostream& operator<<(ostream& outs, T& thing){
//     outs << thing.toString();
//     return outs;
// }

template <class T>
T read(stringstream& ss){
    T t;
    ss >> t;
    return t;
}

class Controller{
public:
    Controller(){}
    Cinema cine;


    void shell(string ops){
        stringstream ss(ops);
        string op;
        ss >> op;
        if(op == "init"){
            cine = Cinema(read<int>(ss));
        }else if(op == "show"){
            cout << cine.toString() << endl;
        }else if(op == "add"){
            string name, number;
            int idc;
            ss >> name >> number >> idc;
            cine.add(new Client(name, number), idc);
        }else if(op == "rm"){
            string name;
            ss >> name;
            cine.remove(name);
        }else{
            throw "This command do not exist";
        }
            throw "Done";
    }
    void exec(){
        string ops;
        while(true){
            getline(cin, ops);
            if(ops == "end"){
                return;
            }
            try{
                shell(ops);
            }catch(const char * e){
                cout << e << endl;
            }

        }
    }
};

int main(){
    setlocale(LC_ALL, "Portuguese");
    Controller remote;
    remote.exec();
    return 0;
}