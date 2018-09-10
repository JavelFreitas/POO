#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
class Fone{
public:
  string label; 
  string number;
  
  Fone(string label = "", string number = ""){
    this->label = label;
    this->number = number;
  }

  static bool validar(string n){
    for(int i=0; i< n.size(); i++){
      if(!isdigit(n[i]) && n[i]!='(' && n[i]!=')' && n[i]!='.'){
        return false;
      }
    }
    return true;
  }
  
  string toString(){
    stringstream out;
    out << label << ":" << number; 
    return out.str(); 
  }
  
};
class Contato{
public:
  string nome; 
  vector <Fone> tele;
  
  Contato(string nome = ""){
    this->nome = nome;
  }
    
  string toString(){
    stringstream out;
    int i =0;
    out<<nome<<"=>";
    for(auto cell : tele ){ 
      out <<"["<<i<<":"<< cell.toString()<<"]";
      i++;
    }
    return out.str();
  }

  void adicionar(Fone fone){
    tele.push_back(fone);
  }
  
  bool remover(int indice){
    if(indice < 0 || indice >= (int)tele.size()){
      cout << "Nao eh possivel fazer operacao";
      return false;
    }
    tele.erase(tele.begin() + indice);
    return true;

  }
  
};
struct Controller{
  Contato cont;
  string shell(string frase){

    stringstream in(frase);
    stringstream out;
    string op;
    getline(in, op, ' ');
    if(op == "init"){
      string nome;
      in >> nome;
      cont = Contato(nome);
      out << "Deu certo!";
    }else if(op == "show"){
      out << cont.toString();
    }else if(op == "add"){
      string label;
      string number;
      in >> label >> number;
      if(Fone::validar(number)){
        cont.adicionar(Fone(label,number));
        out << "Sucesso";
      }else{
        out << "Numero invalido";
      }
    }else if(op == "rm"){
      int indice;
      in >> indice;
      if(cont.remover(indice)){
      cout << "Removido com sucesso";  
      }
    }else if(op == "update"){
      string nome;
      in >> nome;
      cont = Contato(nome);
      string fone_serial;
      while(in >> fone_serial){
        stringstream ss(fone_serial);
        string fone, label;
        getline(ss, label, ':');
        getline(ss, fone);
        if(Fone::validar(fone)){
          cont.adicionar(Fone(label, fone));
        }else{
          out << "Nao deu certo";
        }
      }
    }
    return out.str();
  }
  
  void exec(){
    string frase;
    while(true){
      getline(cin, frase);
      if(frase == "end"){
        cout << "Shutting down";
        break;
      }
      cout << "  " << shell(frase) << endl;
    }  
  }
};

int main(){
  Controller t;
  cout << "Digite algo\n";
  t.exec();
  return 0;
}

/*class Fone
+ label: string
+ numero: string
--
+ validate(): bool
+ toString(): string
class Contato
- nome: string
- fones: Fone[]
--
+ addFone(fone: Fone) : boolean
+ rmFone(ind: int) : boolean
--
+ constructor(nome: fone)
+ constructor(nome: string, fones: Fone[])*/