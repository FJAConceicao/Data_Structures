#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int chave;
	int altura;
	struct no *esq;
	struct no *dir;
} tno;

int maior(int num1, int num2){
    if(num1 > num2)
        return num1;
    else
        return num2;
}

int calculaAltura(tno *no){
    if(no == NULL)
        return 0;
    
    int alturaEsq = calculaAltura(no->esq);
    int alturaDir = calculaAltura(no->dir);
    
    int alturaNo = maior(alturaEsq, alturaDir) + 1;

    return alturaNo;
}

int fatorDeBalanceamento(tno *no){
	if(no == NULL)
        return 0;
    int resultado = calculaAltura(no->esq) - calculaAltura(no->dir);
    return resultado;
}

tno* rotacaoParaDireita(tno* raiz){
	tno* noAuxiliarEsquerda = raiz->esq;
	tno* noAuxiliarDireita = noAuxiliarEsquerda->dir;

	noAuxiliarEsquerda->dir = raiz;
	raiz->esq = noAuxiliarDireita;

	raiz->altura = maior(calculaAltura(raiz->esq), calculaAltura(raiz->dir)) + 1;
	noAuxiliarEsquerda->altura = maior(calculaAltura(noAuxiliarEsquerda->esq), calculaAltura(noAuxiliarEsquerda->dir)) + 1;

	return noAuxiliarEsquerda;
}

tno* rotacaoParaEsquerda(tno* raiz){
	tno* noAuxiliarDireita = raiz->dir;
	tno* noAuxiliarEsquerda = noAuxiliarDireita->esq;

	noAuxiliarDireita->esq = raiz;
	raiz->dir = noAuxiliarEsquerda;

	raiz->altura = maior(calculaAltura(raiz->esq), calculaAltura(raiz->dir)) + 1;
	noAuxiliarDireita->altura = maior(calculaAltura(noAuxiliarDireita->esq), calculaAltura(noAuxiliarDireita->dir)) + 1;

    return noAuxiliarDireita;
}

tno* insereAVL(tno* ptraiz, int valor){

	if(ptraiz == NULL) {
		ptraiz = (struct no*) malloc(sizeof(tno));
        ptraiz->chave = valor;
        ptraiz->esq = NULL;
        ptraiz->dir = NULL;
        ptraiz->altura = 1;
        return ptraiz;
	} else {
		if (valor < ptraiz->chave)
            ptraiz->esq = insereAVL(ptraiz->esq, valor);
		else
            ptraiz->dir = insereAVL(ptraiz->dir, valor);
	}

	ptraiz->altura = maior(calculaAltura(ptraiz->esq), calculaAltura(ptraiz->dir)) + 1;

	int fatorBalanceamento = fatorDeBalanceamento(ptraiz);

	if((fatorBalanceamento > 1) && (valor < ptraiz->esq->chave))
        return rotacaoParaDireita(ptraiz);

    if((fatorBalanceamento > 1) && (valor > ptraiz->esq->chave)){
		ptraiz->esq = rotacaoParaEsquerda(ptraiz->esq);
		return rotacaoParaDireita(ptraiz);
	}

	if((fatorBalanceamento < -1) && (valor > ptraiz->dir->chave))
        return rotacaoParaEsquerda(ptraiz);

	if((fatorBalanceamento < -1) && (valor < ptraiz->dir->chave)){
		ptraiz->dir = rotacaoParaDireita(ptraiz->dir);
		return rotacaoParaEsquerda(ptraiz);
	}

	return ptraiz;
}

void imprimirEmPreOrdem(tno* ptraiz)
{
	if (ptraiz == NULL)
        return;
	else
    {
        printf("%d\n", ptraiz->chave);
		imprimirEmPreOrdem(ptraiz->esq);
		imprimirEmPreOrdem(ptraiz->dir);
	}
}

int main() {

    tno *ptraiz = NULL;
    int num = 0;

    while(!feof(stdin)) {
        if(scanf("%d", &num) == 1) {
            ptraiz = insereAVL(ptraiz, num);
        }
    }

    imprimirEmPreOrdem(ptraiz);
}