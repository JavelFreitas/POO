#include <iostream>
using namespace std;

struct Pessoa{
    int idade;
    string nome;

    Pessoa(int idade = 0, string nome = ""):
        idade(idade), nome(nome){

    }
};
template<class T>
struct Repositorio{
    bool inserir (Pessoa pessoa);
    Pessoa& get(string chave);
    bool exists(string chave);
    void remover(string chave);
    vector<Pessoa> getAll();
};
int main(){

}