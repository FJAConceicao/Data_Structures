#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_VETOR 100000

void merge(int *vetor, int inicio, int meio, int fim){
    int cont1 = inicio, cont2 = meio + 1, contTemp = 0;
    int vetorTemp[TAM_MAX_VETOR] = {};

    while(cont1 <= meio && cont2 <= fim)
	{
        if(vetor[cont1] < vetor[cont2])
		{
            vetorTemp[contTemp] = vetor[cont1];
            cont1++;
        }
		else
		{
            vetorTemp[contTemp] = vetor[cont2];
            cont2++;
        }
        contTemp++;
    }

    while(cont1 <= meio)
	{
        vetorTemp[contTemp] = vetor[cont1];
        contTemp++;
        cont1++;
    }

    while(cont2 <= fim)
	{
        vetorTemp[contTemp] = vetor[cont2];
        contTemp++;
        cont2++;
    }

	int i;
    for(contTemp = inicio, i = 0; contTemp <= fim; contTemp++, i++)
	{
        vetor[contTemp] = vetorTemp[i];
    }
}

void mergeSort(int *vetor, int inicio, int fim)
{
    if((fim - inicio) > 0)
	{
        int meio = (fim+inicio)/2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

int particiona(int *vetor, int inicio, int fim)
{
	int aux;    
	int indiceEsquerda = inicio;
    int indiceDireita = fim;

	int indiceAleatorio = inicio + (rand() % (fim - inicio));
	int pivot = vetor[indiceAleatorio];
	vetor[indiceAleatorio] = vetor[inicio];
	vetor[inicio] = pivot;
    
    while(indiceEsquerda < indiceDireita)
	{
        
		while(vetor[indiceEsquerda] <= pivot)
		{
            indiceEsquerda++;
        }
		while(vetor[indiceDireita] > pivot)
		{
            indiceDireita--;
		}

        if(indiceEsquerda < indiceDireita)
		{
            aux = vetor[indiceEsquerda];
            vetor[indiceEsquerda] = vetor[indiceDireita];
            vetor[indiceDireita] = aux;
        }
    }

    vetor[inicio] = vetor[indiceDireita];
    vetor[indiceDireita] = pivot;

    return indiceDireita;
}

void quickSort(int *vetor, int inicio, int fim) {
    if((fim - inicio) > 1) {
        int pivot = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, pivot - 1);
        quickSort(vetor, pivot + 1, fim);
    }
}

void selectionSort(int *vetor, int numElementosVetor) {
	int i, j, menor, troca;

	for(i = 0; i < (numElementosVetor - 1); i++)
	{
		menor = i;
		for(j = i + 1; j < numElementosVetor; j++)
		{
			if(vetor[j] < vetor[menor])
				menor = j;
		}

		if(vetor[i] != vetor[menor])
		{
			troca = vetor[i];
			vetor[i] = vetor[menor];
			vetor[menor] = troca;
		}
	}
}

void mostraVetor(int *vetor, int inicio, int fim) {
	int i;
    for(i = inicio; i < fim; i++) {
        printf("%d\n", vetor[i]);
    }
}

int main(int argc, char *argv[]) {

    int vetor[TAM_MAX_VETOR];
	int num;
	int numElementos = 0;

    //Inserir números da entrada padrão em um vetor para ser ordenado
	while(!feof(stdin)) {
		if(scanf("%d", &num) == 1) {
			vetor[numElementos] = num;
			numElementos++;
        }
    }

    //Escolher agoritmo de ordenação e realizar a ordenação de acordo com o parametro escolhido
    if(argc > 1) {
        if(strcmp(argv[1], "-m") == 0) {
			printf("Usando Merge Sort ...\n");
			mergeSort(vetor, 0, numElementos);
        } else if (strcmp(argv[1], "-q") == 0) {
			printf("Usando Quick Sort ...\n");
			quickSort(vetor, 0, numElementos);
        }
		mostraVetor(vetor, 1, numElementos + 1);
    } else {
		printf("Usando Selection Sort ...\n");
		selectionSort(vetor, numElementos);
		mostraVetor(vetor, 0, numElementos);
    }

    return 0;
}