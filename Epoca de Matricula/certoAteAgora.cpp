#include <iostream> // Refazer código com herança quando tiver tempo
#include <vector>
#include <sstream>
#include <map>
#include <fstream>
using namespace std;

class Discp;

class Aluno{

    string idAluno;
    vector<Discp> m_discp;

public:

    Aluno(string idAluno = ""): //Construtor
        idAluno(idAluno)
    {}

    void matricular(Discp discp);

    void desmatricular(string idAlu){ // Desmatricula aluno

    }

    vector<Discp> getDisciplinas(){ // Retorna todas as disciplinas do aluno

    }

    string getIdAluno(){
        return this->idAluno;
    }

    friend class Discp; // Concede permissão à classe Discp

};

class Discp{

    string idDiscp;
    vector<Aluno> m_aluno;

public:

    Discp(string idDiscp = ""):
        idDiscp(idDiscp)
    {}

    void matricular(Aluno aluno){ 

    }

    void desmatricular(string idAluno){

    }

    vector<Aluno> getAlunos(){

    }

    string getIdDiscp(){
        return this->idDiscp;
    }

};


void Aluno::matricular(Discp discp){ // Realiza matricula do aluno aqui por causa do foward declaration

}




template <typename T>
class Repositorio{
    
    string className;
    map<string, T> mapa;

public:

    Repositorio(string nome = ""){
        if(is_same<T, Aluno>::value){
            this->className = "aluno";
        }else if(is_same<T, Discp>::value){
            this->className = "disciplina";
        }

    }

    
    void add(string key, T t){
        if(!has(key)){
            mapa[key] = t;
        }else{
            cout << "Key " + key + " already exists, try another";
        }
    }

    T get(string key){

    }

    void rm(string key){

    }

    bool has(string key){
        return mapa.find(key) != mapa.end();
    }

    vector<string> keys(){
        vector<string> vs;
        for(auto& par : mapa){
            vs.push_back(par.first);
        }
        return vs;
    }

    vector<T> getAll(){
        vector<T> vt;
        for(auto& par : mapa){
            vt.push_back(par.second);
        }
        return vt;
    }

};


class Controller{
    
    Repositorio<Aluno> r_alu;
    Repositorio<Discp> r_dis;

public:

    Controller(){
        Repositorio<Aluno> r_alu;
        Repositorio<Discp> r_dis;
    }

    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op, newAlu;
        in >> op;

        try{
            if(op == "la"){
                out << "alunos\n";
                vector<Aluno> va = r_alu.getAll();
                for(auto& alu : va){
                    out << "   " << alu.getIdAluno() << "\n";
                }
            }else if(op == "nwalu"){
                while(in >> newAlu){
                    r_alu.add(newAlu, Aluno(newAlu));
                }
            }
            
            else{
                out << "Command do not exists";
            }

        }catch(const char * warning){
            cout << warning;
        }catch(string waitWhat){
            cout << waitWhat;
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