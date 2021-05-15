#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

template <typename T>
class No
{
    public:
        T valorNo;
        No<T> *proximo;

        No(T valor)
        {
            valor = valor;
            proximo = NULL;
        }
};

template <typename T>
class Fila
{
    private:
        int totalElementos;
        No<T>* pontInicio;
        No<T>* pontFim;

    public:
        Fila()
        {
            totalElementos = 0;
            pontInicio = NULL;
            pontFim = NULL;
        }
        int tamanho()
        {
            return totalElementos;
        }
        bool estaVazia()
        {
            return totalElementos <= 0;
        }
        T inicio()
        {
            return pontInicio->valorNo;
        }
        void adicionar(T valor)
        {
            No<T>* no = new No<T>(valor);

            if(totalElementos == 0)
            {
                no->proximo = NULL;
                pontInicio = no;
                pontFim = pontInicio;
            }
            else
            {
                pontFim->proximo = no;
                pontFim = no;
            }

            totalElementos++;
        }

        void remover()
        {
            if(totalElementos == 0)
                return;

            No<T>* no = pontInicio;
            pontInicio = pontInicio->proximo;
            delete no;
            totalElementos--;
        }
};

int main()
{    
    int numeroDeEquipes, quantElementosDaEquipe, elementoDaEquipe, numeroCenario = 1;
    string comando;

    while(true)
    {
        cin >> numeroDeEquipes;
        if(numeroDeEquipes == 0)
            break;

        map<int,Fila<int>*> mapDeElementoComEquipe;
        Fila<Fila<int>*> filasDeEquipes;

        while(numeroDeEquipes > 0)
        {
            cin >> quantElementosDaEquipe;
            Fila<int>* filaDeEquipe = new Fila<int>();

            int cont = 0;
            while(cont < quantElementosDaEquipe)
            {
                cin >> elementoDaEquipe;
                mapDeElementoComEquipe[elementoDaEquipe] = filaDeEquipe;
                ++cont;
            }
            --numeroDeEquipes;
        }

        cout << "Scenario #" << numeroCenario << endl;
        ++numeroCenario;

        while(true)
        {
            cin >> comando;
            if(comando == "STOP")
                break;

            if(comando == "ENQUEUE")
            {
                cin >> elementoDaEquipe;
                mapDeElementoComEquipe[elementoDaEquipe]->adicionar(elementoDaEquipe);
                
                if(mapDeElementoComEquipe[elementoDaEquipe]->tamanho() == 1)
                    filasDeEquipes.adicionar(mapDeElementoComEquipe[elementoDaEquipe]);
            }
            else if(comando == "DEQUEUE")
            {
                while(filasDeEquipes.inicio()->estaVazia())
                    filasDeEquipes.remover();

                cout << filasDeEquipes.inicio()->inicio() << endl;
                filasDeEquipes.inicio()->remover();
            }
        }
        cout << endl;
    }
    cout << endl;
    
    return 0;
}