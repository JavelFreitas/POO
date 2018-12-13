#include <iostream> //Adicionar LC_ALL "Portuguese"
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

class Emb{ 
public:
    virtual string getId() = 0;
    virtual string toString() = 0;
    virtual ~Emb(){};
};

class Pass: public Emb {
    string id;
public:
    Pass(string id = ""):
        id(id){}

    virtual ~Pass(){}

    virtual string getId(){
        return id;
    }
    virtual string toString(){
        return id;
    }
};

class Carga : public Emb {
    string id;
    float peso;
public:

    Carga(string newId = "", float newPeso = 0.0):
    id(newId), peso(newPeso){}

    ~Carga(){}
    
    float getPeso(){
        return peso;
    }

    virtual string getId(){
        return id;
    }

    virtual string toString(){
        return id + ":" + to_string(peso);
    }
};

class Vagao{ //contratos
public:
    virtual bool embarcar(Emb * emb) = 0;
    virtual ~Vagao(){};
    virtual bool desembar(string idPass) = 0;
    virtual bool exists(string idPass) = 0;
    virtual string toString() = 0;
};

class VagaoCarga : public Vagao {
    float capacidade;
    map<string, Carga*> elementos;
public:
    VagaoCarga(float cap = 0.0){
        capacidade = cap;
    }

    ~VagaoCarga(){
        for(auto &elemento : elementos){
            delete elemento.second;
        }
    }

    virtual bool embarcar(Emb * emb){
        if(Carga * newCarga = dynamic_cast<Carga*>(emb)){
            if(newCarga->getPeso() <= capacidade){
                elementos[newCarga->getId()] = newCarga;
                capacidade -= newCarga->getPeso();
                return true;
            }
        }
        return false;
        
    }
    
    virtual bool desembar(string idCarga){
        if(exists(idCarga)){
            auto it = elementos.find(idCarga);
            capacidade += it->second->getPeso();
            delete it->second;
            elementos.erase(it);
            return true;
        }
        return false;
    }

    virtual string toString(){
        stringstream ss;
        ss << "( ";
        for(auto & couple : elementos){
            ss << couple.second->toString() << " ";
        }
        ss << "_" << capacidade << " )";
        return ss.str();
    }

    virtual bool exists(string idCarga){
        return elementos.find(idCarga) != elementos.end();
    }

};

class VagaoPessoas : public Vagao {
    vector<Pass*> passageiros;
public:
    VagaoPessoas(int capacidade):
        passageiros(capacidade, nullptr)
    {}

    ~VagaoPessoas(){
        for(size_t i = 0; i < passageiros.size(); i++){
            if(passageiros[i] != nullptr)
                delete passageiros[i];
        }
    }

    virtual bool embarcar(Emb * emb){
        if(Pass * pass = dynamic_cast<Pass*>(emb)){
            for(size_t i = 0; i < passageiros.size(); i++){
                if(passageiros[i] == nullptr){
                    passageiros[i] = pass;
                    return true;
                }
            }
        }
        return false;
    }
    virtual bool desembar(string idPass){
        for(auto *& passageiro : passageiros){
            if((passageiro != nullptr) && (passageiro->getId()) == idPass){
                passageiro = nullptr;
                delete passageiro;
                return true;
            }
        }
        return false;
    }

    virtual bool exists(string idPass){
        for(auto *&passageiro : passageiros){
            if((passageiro != nullptr) && (passageiro->getId() == idPass)){
                return true;
            }
        }
        return false;
    }

    virtual string toString(){
        stringstream ss;
        ss << "[ ";
        for(auto * pass : passageiros){
            if(pass == nullptr)
                ss << "- ";
            else
                ss << pass->toString() << " ";
        }
        ss << "]";
        return ss.str();
    }
};

class Trem{
    vector<Vagao*> vagoes;
    int forca;
public:
    Trem(int forca = 0){
        this->forca = forca;
    }
    ~Trem(){
        for(auto * vagao : vagoes)
            delete vagao;
    }
    bool addVagao(Vagao * vagao){
        if((int) vagoes.size() < forca){
            vagoes.push_back(vagao);
            return true;
        }
        return false;
    }

    bool embarcar(Emb * emb){
        for(auto * vagao : vagoes){
            if(vagao->embarcar(emb))
                return true;
        }
        return false;
    }

    bool desembar(string idPass){
        for(auto * vagao : vagoes){
            if(vagao->desembar(idPass))
                return true;
        }
        return false;
    }

    string toString(){
        stringstream ss;
        ss << "Trem: ";
        for(auto * vagao : vagoes)
            ss << vagao->toString() << " ";
        return ss.str();
    }

    bool exists(string idEmb){
        for(auto * vagao : vagoes){
            if(vagao->exists(idEmb)){
                return true;
            }
        }
        return false;
    }
};

template<class T>
T read(stringstream& ss){
    T t;
    ss >> t;
    return t;
}

class Controller{
    Trem trem;
public:
    Controller(){}

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "init"){
            trem = Trem(read<int>(ss));
        }else if(op == "nwvp"){
            Vagao * vagao = new VagaoPessoas(read<int>(ss));
            if(!trem.addVagao(vagao)){
                delete vagao;
                throw "Nao eh possivel criar vagao";
            }
        }else if(op == "addp"){
            Pass * pass = new Pass(read<string>(ss));
            if(!trem.embarcar(pass)){
                delete pass;
                throw "Nao eh possivel adicionar pessoa";
            }
        }else if(op == "desemb"){
            string newId;
            ss >> newId;
            if(!trem.desembar(newId)){
                throw "Passageiro nao embarcado";
            }
        }else if(op == "nwvc"){
            Vagao * vagao = new VagaoCarga(read<float>(ss));
            if(!trem.addVagao(vagao)){
                delete vagao;
                throw "Nao eh possivel criar vagao";
            }
        }else if(op == "addc"){
            string newId;
            ss >> newId;
            Carga * carga = new Carga(newId, read<float>(ss));
            if(trem.exists(newId)){
                throw "Ja esta no trem";
            }else if(!trem.embarcar(carga)){
                delete carga;
                throw "Esta lotado";
            }
        }else if(op == "show"){
            cout << trem.toString() << endl;
        }else
            cout << "fail: comando invalido" << endl;
    }

    void exec(){
        string line;
        while(true){
            try{
                getline(cin, line);
                cout << "$" << line << endl;
                if(line == "end")
                    return;
                shell(line);
            }catch(const char * e){
                cout << "   Erro: " << e << endl;
            }
        }
    }
};

int main(){
    Controller cont;
    cont.exec();
    return 0;
}