#include <iostream>

#include <string.h>

using namespace std;

int conjunto[50100];
int rank_[50100];

int encontraConjunto(int valor)
{
   if (conjunto[valor] < 0)
   {  
      return valor;
   }
   else
   {
      return conjunto[valor] = encontraConjunto(conjunto[valor]);
   }
}

void uneConjuntos(int representElemA, int representElemB)
{
   representElemA = encontraConjunto(representElemA);
   representElemB = encontraConjunto(representElemB);

   if(representElemA != representElemB)
   {
      if (rank_[representElemA] < rank_[representElemB])
      {
         int temp = representElemA;
         representElemA = representElemB;
         representElemB = temp;
      }
      
      conjunto[representElemB] = representElemA;

      if (rank_[representElemA] == rank_[representElemB])
         rank_[representElemA]++;
   }
}

int main() {
   
   int n, m, numeroCaso = 0;
   
   while (true)
   {
      cin >> n >> m;

      if (n == 0 && m == 0)
      {
         break;
      }

      memset(conjunto, -1, sizeof(conjunto));
      memset(rank_, 0, sizeof(rank_));
      
      int contador = 1;
      while (contador <= m)
      {
         int AlunoI, AlunoJ;
         cin >> AlunoI >> AlunoJ;
         uneConjuntos(AlunoI, AlunoJ);
         contador++;
      }
      
      int religioesDiferentes = 0, numeroAluno = 1;
      while (numeroAluno <= n)
      {
         if (conjunto[numeroAluno] < 0)
         {
            religioesDiferentes++;
         }

         numeroAluno++;
      }

      numeroCaso++;
      cout << "Case " << numeroCaso << ": " << religioesDiferentes << endl;
   }

   return 0;
}