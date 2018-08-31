// caso do onibus estar cheio, criar destrutor do passageiro
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Pass{
	string nome;
	int idade;

	Pass(string nome = "", int idade = 0):
		nome(nome),
		idade(idade)
	{
	}

	string toString(){
		stringstream ss;
		ss << nome << ":" << idade;
		return ss.str();
	}
};

struct Topic{
	int pref;
	vector<Pass *> lugares;

	Topic(int pref = 0, int lotacao = 0):
		pref(pref),
		lugares(lotacao, nullptr)
	{		
	}

	string toString(){
		stringstream saida;
		saida << "[";
		for(int i = 0; i < (int)lugares.size(); i++){
			saida << (i < pref ? '@' : '-');
			saida << (lugares[i] != nullptr ? lugares[i]->toString() : "");
			saida << " ";
		}
		saida << "]";
		return saida.str();
	}

	int find(string nome){
	    cout << "Dentro do find";
		for(int i=0; i < (int)lugares.size(); i++){
			if(lugares[i]->nome == nome){
				return 1;
			}
		}
		return 0;
	}

	bool getin(string nome, int idade){
        if(find(nome) == 1){
			return 0;
		}
		if(idade<60){
			for(int i = pref; i < (int)lugares.size() ; i++){
				if(lugares[i] == nullptr){
					lugares[i] = new Pass(nome, idade);
					return 1;
				}		
			}
		}else{
			for(int i = 0; i < pref ; i++){
				if(lugares[i] == nullptr){
					lugares[i] = new Pass(nome, idade);
					return 1;
				}
			}
		}
		for(int i = 0; i < (int)lugares.size() ; i++){
			if(lugares[i] == nullptr){
				lugares[i] = new Pass(nome, idade);
				return 1;
			}
		}
		return 0;
	// for (Pessoa * p : passageiros)
	// if (p == nullptr)
	// p = new 
	}
};

int main(){
	Topic top;
	int qtd = 0, pref = 0, idade = 0;
	string frase, nome;
	while(true){
        cin >> frase;
		if(frase == "show"){
			cout << top.toString();
		}else if(frase == "ini"){
			cin >> qtd >> pref;
			top = Topic(pref, qtd);
			cout << "Topic criada com " << qtd <<" cadeiras sendo " << pref << " preferenciais!\n";
		}else if(frase == "in"){
			cout << "Insira nome e idade ";
			cin >> nome >> idade;
			// O erro ta aqui
			if(top.getin(nome, idade) == 1){
			    cout << "Cadastrado";
		    }else{
		    cout << "Nao foi possivel realizar a operacao";
		    }
			
		}

	}

	return 0;
}

/* Implementar o controller depois que resolver o segmentation fault
struct Controller{
    Topic top;

    string shell(string frase){
        stringstream in(frase);
        stringstream out;
        string op;
        in >> op;
        if(op == "show"){
            cout << Topic.toString();
        }else if(op == "init"){
            Topic.initiate();
        }else if(op == "in"){
            Topic.adicionar();
        }else if(op == "out"){
            Topic.remover();
        }
        return out.str();
    };

    void exec(){
        string frase;
        while(true){
            getline(cin, frase);
            if(frase == "end") 
                return;
            cout << frase << endl;
            cout << "  " << shell(frase) << endl;
        }
    }
};      //int main
setlocale(LC_ALL, "Portuguese");
    Controller t;
    t.exec();
*/
