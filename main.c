#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PONTOS_VETOR 1000

/*Centro Universitario Senac Santo Amaro
Engenharia da Computacao
Algoritmos e Progrmacao I - Profº Fabio Lubacheski

Trabalho 02: kNN pontos mais proximos

Rafael Fortunatti Simoes
Jonathan F. Ramírez S.

*/

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

//A funcao de adicionar um ponto na estrutura, verifica se ja existe e outras operacoes obrigatorias,
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

//função para remover um ponto numa dada posição e reordena o vetor para que não fique um espaço vazio no meio do vetorint vetP_RemPonto(vetPontos *tadPontos, int posToRem)
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

//função para calcular o total de pontos
int vetP_qtPontos(vetPontos *tadPontos)
{
    return tadPontos->valTotElem;
}

//Função para substituir um ponto numa dada posição
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
//Serve como um workaround da incapacidade de C ter constructors primitivos.

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

//Função para leitura do arquivo com os pontos
void vetP_fillFromFile(vetPontos *tadPontos)
{
    int valReceived = 0;
    int i = 0;
    int total = 0;
    //aloca a memória com o tamanho do vetor de pontos
    memset(tadPontos, 0, sizeof(vetPontos));
    //Inicializa o arquivo para leitura
    FILE *fileFrom = fopen("coordenadas.txt", "r");
    //verifica se a abertura do arquivo ocorreu
    if (!fileFrom){
        printf("Não abriu o arquivo\n");
        exit(1);
    }
    //lê o total de pontos do vetor da primaira linha no arquivo
    fscanf(fileFrom, "%d", &total);
    tadPontos->valTotElem = total;
    //loop para inserir os ponto do arquivo no vetoir
    for (i=0;i < total; i++){
        fscanf(fileFrom, "%d", &valReceived);
        tadPontos->arrPontos[i].pointX = valReceived;
        fscanf(fileFrom, "%d", &valReceived);
        tadPontos->arrPontos[i].pointY = valReceived;
    }
    //Fecha o arquivo
    fclose(fileFrom);
}

//função para gravar os pontos num arquivo txt
void vetP_fillToFile(vetPontos *tadPontos)
{
    int valReceived = 0;
    int i = 0;
    int total = 0;
    //Inicializa o arquivo para gravação
    FILE *fileFrom = fopen("coordenadas.txt", "w+");
    //verifica se a abertura do arquivo ocorreu
    if (!fileFrom){
        printf("Não abriu o arquivo\n");
        exit(1);
    }
    //insere o total de pontos do vetor na primaira linha do arquivo
    fprintf(fileFrom, "%d\n", tadPontos->valTotElem);
    //Loop para inserir cada valor de x e y de cada ponto em uma linha
    for (i=0;i < tadPontos->valTotElem; i++){
        fprintf(fileFrom, "%d %d\n", tadPontos->arrPontos[i].pointX,tadPontos->arrPontos[i].pointY);
    }
    //Fecha o arquivo
    fclose(fileFrom);
}

//Função para imprimir os pontos no vetor
void imprimeelementos(vetPontos *tadPontos)
{
    int size = tadPontos->valTotElem;
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%d %d\n", tadPontos->arrPontos[i].pointX, tadPontos->arrPontos[i].pointY);
    }
}

int main()
{
    int menu = 0, ponto= 0, px = 0, py = 0, pos = 0, totalSearch = 0;
    vetPontos meusPontos;
    vetP_Initialize(&meusPontos);
    vetP_fillFromFile(&meusPontos);
    do {
        printf("\n1.- Adicionar ponto no final da lista\n");
        printf("2.- Adicionar ponto em uma posicao especifica\n");
        printf("3.- Remover um ponto\n");
        printf("4.- Total de pontos na lista\n");
        printf("5.- Calcular os pontos mais proximos de um ponto\n");
        printf("6.- Mostrar pontos do vetor\n");
        printf("7.- Sair do programa\n");
        scanf("%d", &menu);
        switch(menu){
                case 1:
                    printf("Insira o valor X e Y do ponto:\nX: ");
                    scanf("%d", &px);
                    printf("Y: ");
                    scanf("%d", &py);
                    vetP_AddPonto(&meusPontos, vetP_qtPontos(&meusPontos) +1, px, py);
                    vetP_fillToFile(&meusPontos);
                    break;
                case 2:
                    printf("Insira a posição do ponto a inserir: ");
                    scanf("%d", &pos);
                    printf("Insira o valor X e Y do ponto:\nX: ");
                    scanf("%d", &px);
                    printf("Y: ");
                    scanf("%d", &py);
                    vetP_AddPonto(&meusPontos, pos, px, py);
                    vetP_fillToFile(&meusPontos);
                    break;
                case 3:
                    printf("Insira a posição do ponto a remover: ");
                    scanf("%d", &pos);
                    vetP_RemPonto(&meusPontos, pos);
                    vetP_fillToFile(&meusPontos);
                    break;
                case 4:
                    printf("Total de pontos: %d\n", vetP_qtPontos(&meusPontos));
                    break;
                case 5:
                    printf("Insira a posição do ponto: ");
                    scanf("%d", &pos);
                    printf("Insira a quantiade de pontos proximo a serem procurados: ");
                    scanf("%d", &totalSearch);
                    vetP_findkNN(&meusPontos, pos,totalSearch);
                    break;
                case 6:
                    imprimeelementos(&meusPontos);
                    break;
                case 7:
                    return 0;
                    break;
                default:
                    printf("Nao e uma opcao de menu valida\n\n\n\n", &menu);

            }
    } while (menu != 0);

    return 0;
}

