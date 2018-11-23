#include <iostream> // Refazer código com herança quando tiver tempo.
#include <vector>  // perguntar onde e como fazer o destrutor de cada classe.
#include <sstream> // matricular materia tem que ser privado?
#include <map>
#include <fstream>
using namespace std;

class Discp;

class Aluno{

    string idAluno;
    vector<Discp> m_discp; //fazer com mapas

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
    //imprimir a pessoa = imprimir todas as matérias, tentar fazer o ostream

};

class Discp{

    string idDiscp;
    vector<Aluno> m_aluno; // tentar utilizar mapas

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
// se a disciplina existe e ainda não está matriculada, colocar aluno na disciplina e vice versa


}




template <typename T>
class Repositorio{
    
    string typeName;
    map<string, T> mapa;

public:

    Repositorio(string nome = ""){
        className = nome;

    }

    
    void add(string key, T t){
        if(!has(key)){
            mapa[key] = t;
        }else{
            cout << nome <<  key + " already exists, try another";
        }
    }

    T get(string key){

    }

    void rm(string key){
        //usa o metodo de desmatricular;
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

    Controller():
        r_aluno("aluno"),

    { // r_alu("aluno") , r_dis("disciplina")
    }

    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op, Alu, Dis;
        in >> op;

        try{

            if(op == "la"){
                
                out << "alunos\n";
                vector<Aluno> va = r_alu.getAll();
                for(auto& alu : va){
                    out << "   " << alu.getIdAluno() << "\n";
                }
                out << "  disciplinas\n";
                vector<Discp> vd = r_dis.getAll();
                for(auto& dis : vd){
                    out << "   " << dis.getIdDiscp() << "\n";
                }


            }else if(op == "nwalu" || op == "nwdis"){

                if(op == "nwalu"){
                    while(in >> Alu){
                        r_alu.add(Alu, Aluno(Alu));
                    }
                }else if(op == "nwdis"){
                    while(in >> Dis){
                        r_dis.add(Dis, Discp(Dis));
                    }
                }

            }else if(op == "mat"){
                in >> Alu; //receber nome do aluno
                while(in >> Dis){ //receber todas as materias que ele vai ser matriculado
                    // enquanto houver materias, ter certeza que elas existem, caso contrario, informar ao aluno que esta materia nao existe
                    // se a materia existir, verificar se o aluno ja nao possue a materia no seu vector
                    // caso ele nao a tiver, adicionar tal materia no vector do aluno, e do void Matricular do aluno adiciona-lo a materia;
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