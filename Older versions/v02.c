#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PONTOS_VETOR 1000

//Estruturas basicas de ponto e vetor de pontos
typedef struct{
    int pointX;
    int pointY;
}tPonto;

typedef struct{
    tPonto arrPontos[MAX_PONTOS_VETOR];
    int valTotElem;
}vetPontos;
//vetPontos (veot de pontos) "herda" tPonto em forma de array.

//Funcoes de manipulacao da estrutura vetPontos.

//A funcao de adicionar um ponto na estrutura, verificar se ja existe e outras operacoes obrigatorias,
//retorna -1 caso nao consiga adicionar ou a posicao do novo ponto caso consiga.
int vetP_AddPonto(vetPontos *tadPontos, int posToAdd, int xToAdd, int yToAdd)
{
    //Caso o array esteja cheio
    if(tadPontos->valTotElem == MAX_PONTOS_VETOR)
        return -1;
    //Caso a posicao seja invalida
    if(posToAdd < 1 || posToAdd > tadPontos->valTotElem + 1)
        return -1;
    //Caso a posicao a ser adicionada seja depois da ultima
    if(posToAdd == tadPontos->valTotElem + 1)
    {
        tadPontos->arrPontos[posToAdd - 1].pointX = xToAdd;
        tadPontos->arrPontos[posToAdd - 1].pointY = yToAdd;
        tadPontos->valTotElem++;
        return posToAdd;
    }
    //Caso a posicao a ser adicionada ja exista
    if(posToAdd <= tadPontos->valTotElem)
    {
        int i;
        for(i = tadPontos->valTotElem - 1; i >= posToAdd - 1; i--)
        {
            tadPontos->arrPontos[i + 1] = tadPontos->arrPontos[i];
        }
        tadPontos->valTotElem++;
        tadPontos->arrPontos[posToAdd - 1].pointX = xToAdd;
        tadPontos->arrPontos[posToAdd - 1].pointY = yToAdd;

        return posToAdd;
    }
    return;
}

int vetP_RemPonto(vetPontos *tadPontos, int posToRem)
{
    //Caso o array esteja vazio
    if(tadPontos->valTotElem == 0)
        return -1;
    //Caso a posicao nao esteja ocupada ou a posicao eh invalida
    if(posToRem > tadPontos->valTotElem || posToRem < 1)
        return -1;
    //A logica de remocao desloca todos os elementos a direita para a esquerda, reocupado a posicao
    //removida e desabilitando o que era a ultima posicao no vetor. Logo, diminuindo o numero de elementos
    //contidos no vetor (valTotElem).
    if(posToRem <= (tadPontos->valTotElem))
    {
        int i;
        for(i = posToRem - 1; i <= tadPontos->valTotElem - 2; i++)
        {
            tadPontos->arrPontos[i] = tadPontos->arrPontos[i+1];
        }
        tadPontos->arrPontos[tadPontos->valTotElem -1].pointX = 0;
        tadPontos->arrPontos[tadPontos->valTotElem -1].pointY = 0;
        tadPontos->valTotElem--;

        return tadPontos->valTotElem;
    }

}

int vetP_qtPontos(vetPontos *tadPontos)
{
    return tadPontos->valTotElem;
}

int vetP_SubPonto(vetPontos *tadPontos, int posSub, int xToAdd, int yToAdd)
{
    if(posSub < 1 || posSub > (tadPontos->valTotElem))
        return -1;
    else{
        tadPontos->arrPontos[posSub - 1].pointX = xToAdd;
        tadPontos->arrPontos[posSub - 1].pointY = yToAdd;
        return posSub;
    }
}

//A funcao vetP_Initialize pega um ponteiro de vetPontos e inicializa. Isto eh,
//determina os todos os valores em 0, tal como o total de elementos.
//Serve mais como um workaround da (in)capacidade de C ter constructors primitivos.

void vetP_Initialize (vetPontos *tadPontos)
{
    tadPontos->valTotElem = 0;
    int i;
    for(i = 0;i < MAX_PONTOS_VETOR; i++)
    {
        tadPontos->arrPontos[i].pointX = 0;
        tadPontos->arrPontos[i].pointY = 0;
    }

}

void vetP_findkNN(vetPontos *tadPontos, int pntOrigem, int kNear)
{
    vetPontos vetP_Near;
    int i, distP = 0, j, distAux;
    int xOrigem, yOrigem;
    xOrigem = tadPontos->arrPontos[pntOrigem - 1].pointX;
    yOrigem = tadPontos->arrPontos[pntOrigem - 1].pointY;
    //Aloco um vetor de vetPontos para guardar e organizar os mais proximos do ponto referencia.
    //O primeiro ponto eh o mais proximo da origem, o ultimo o mais distante.
    vetP_Initialize(&vetP_Near);
    //Essa funcao assume que o programa vez a validacao dos kNear em relacao a estrutura de pontos existente
    //antes de ser evocada.
    //A rotina tera de ser burra: passar por todos os pontos da lista e inserir na ordem desejada, ignorando quaisquer pontos que superem kNear

    for(i = 1; i <= (tadPontos->valTotElem); i++)
    {
        if(i == pntOrigem)
            continue;
        //Calculo a distancia entre um ponto da lista e guardo esta informacao.
        distP = sqrt(pow(tadPontos->arrPontos[i - 1].pointX - xOrigem, 2) + pow(tadPontos->arrPontos[i-1].pointY - yOrigem, 2));
        for(j = 1; j <= (tadPontos->valTotElem); j++)
        {
            distAux = sqrt(pow(vetP_Near.arrPontos[j-1].pointX - xOrigem, 2) + pow(vetP_Near.arrPontos[j-1].pointY - yOrigem, 2));
            if(distP < distAux)
            {
            vetP_AddPonto(&vetP_Near, j, tadPontos->arrPontos[i-1].pointX, tadPontos->arrPontos[i-1].pointY);
            break;
            }
            if(j == vetP_Near.valTotElem)
                vetP_AddPonto(&vetP_Near, j + 1, tadPontos->arrPontos[i-1].pointX, tadPontos->arrPontos[i-1].pointY);
        }
    }

    vetP_Near.valTotElem = kNear;
    imprimeelementos(&vetP_Near);


}

void vetP_fillFromFile(vetPontos *tadPontos)
{
    int valReceived = 0;
    int i = 0;
    int total = 0;
    //vetP_Initialize(&tadPontos);
    memset(tadPontos, 0, sizeof(vetPontos));
    FILE *fileFrom = fopen("coordenadas.txt", "r");
    if (!fileFrom){
        printf("Não abriu o arquivo\n");
        exit(1);
    }
    fscanf(fileFrom, "%d", &total);
    tadPontos->valTotElem = total;
    for (i=0;i < total; i++){
        fscanf(fileFrom, "%d", &valReceived);
        tadPontos->arrPontos[i].pointX = valReceived;
        fscanf(fileFrom, "%d", &valReceived);
        tadPontos->arrPontos[i].pointY = valReceived;
    }
    fclose(fileFrom);
}

void vetP_fillToFile(vetPontos *tadPontos)
{
    int valReceived = 0;
    int i = 0;
    int total = 0;
    //vetP_Initialize(&tadPontos);
    FILE *fileFrom = fopen("coordenadas.txt", "w+");
    if (!fileFrom){
        printf("Não abriu o arquivo\n");
        exit(1);
    }

    fprintf(fileFrom, "%d\n", tadPontos->valTotElem);
    for (i=0;i < tadPontos->valTotElem; i++){
        fprintf(fileFrom, "%d %d\n", tadPontos->arrPontos[i].pointX,tadPontos->arrPontos[i].pointY);
    }
    fclose(fileFrom);
}

void imprimeelementos(vetPontos *tadPontos)
{
    int size = tadPontos->valTotElem;
    int i;
    for(i = 0; i < size; i++)
    {
        printf("\n%d %d", tadPontos->arrPontos[i].pointX, tadPontos->arrPontos[i].pointY);
    }
}

int main()
{
    vetPontos meusPontos;
    vetP_Initialize(&meusPontos);
    vetP_fillFromFile(&meusPontos);
/*
    vetP_AddPonto(&meusPontos, 1, 10, 10);
    vetP_AddPonto(&meusPontos, 2, 32, 2);
    vetP_AddPonto(&meusPontos, 3, 334,545);
    vetP_AddPonto(&meusPontos, 4, 122, 43);
    vetP_AddPonto(&meusPontos, 5, 655, 34);
    vetP_AddPonto(&meusPontos, 6, 5, 36);
    vetP_AddPonto(&meusPontos, 7, 678, 766);
    vetP_AddPonto(&meusPontos, 8, 7, 7);
    vetP_AddPonto(&meusPontos, 9, 8, 8);
    vetP_AddPonto(&meusPontos, 10, 123, 44);
    vetP_AddPonto(&meusPontos, 11, 10, 10);
*/
    imprimeelementos(&meusPontos);
    getchar();
    vetP_fillToFile(&meusPontos);
    imprimeelementos(&meusPontos);
    vetP_findkNN(&meusPontos, 1, 3);




}

