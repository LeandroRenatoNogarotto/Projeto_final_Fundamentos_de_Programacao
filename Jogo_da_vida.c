#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#define LIMPA "cls"
#else
#include <unistd.h>
#define LIMPA "clear"
#endif
#define ORG 'X'
#define VAZ '.'
#define TAM 101
#define FALSE 0
#define TRUE 1
typedef struct
{
    char nomeJogo[TAM]; /* o nome do jogo deve ser relativo ao padrao
    de inicializacao. Por exemplo, JogoSapo ou JogoBloco*/
    int nCiclos;        // Define quanto cada jogo vai rodar (ciclos)
    int nL, nC;         // dimensoes do tabuleirouleiro linhas x colunas
    char **m;           // Atenção! Essa matriz terá que ser alocada dinamicamente
    // para que a futabuleiro.nCao que inicializa possa futabuleiro.nCionar
} Tab;

void limpaMatriz(Tab tabuleiro);
void inicBlinker(Tab tabuleiro);
void inicBloco(Tab tabuleiro);
void inicSapo(Tab tabuleiro);
void inicGlider(Tab tabuleiro);
void inicLWSS(Tab tabuleiro);
void desalocaMatriz(Tab tabuleiro);
void imprimeMatriz(Tab tabuleiro);
char **alocaMatriz(Tab tabuleiro);
void copiaMatriz(char **mAnt, Tab tabuleiro);
int verifica(Tab tabuleiro, int i, int j);
int contaVivos(char **mAnt, Tab tabuleiro, int i, int j);
void atualizaMat(char **mAnt, Tab tabuleiro);
void menuInicJogo(Tab tabuleiro);
void jogaJogoVida(Tab tabuleiro);
void inicInvasorUm(Tab tabuleiro);
void inicInvasorDois(Tab tabuleiro);
void inicInvasorTerceiro(Tab tabuleiro);
void inicInvasorQuarto(Tab tabuleiro);
void inicInvasorQuinto(Tab tabuleiro);
void inicInvasorSexto(Tab tabuleiro);
void inicInvasorSete(Tab tabuleiro);

int main() // função priTab.nCipal do jogo
{
    Tab tabuleiro;
    int decisao = TRUE;
    printf("Digite o numero de linhas, de colunas (entre 15 e 100) e de ciclos:\n"); // entrada de dados para definir caracteristicas do jogo
    scanf("%d %d %d", &tabuleiro.nL, &tabuleiro.nC, &tabuleiro.nCiclos);
    if( tabuleiro.nL < 15 || tabuleiro.nC < 15)
    {
        printf("\nVOCE EH UMA MULA! tinha que ser menor que 15!\n");
        return 0;
    }
    tabuleiro.m = alocaMatriz(tabuleiro); // aloca espaços na memoria de acordo com a escolha do usuário
    while (decisao == TRUE)
    {
        menuInicJogo(tabuleiro);                                 // inicia o jogo
        jogaJogoVida(tabuleiro);                                 // inicia o jogo
        printf("\n\nDeseja jogar novamente?\n(1)sim\n(0)nao\n"); // verifica se o jogador deseja repetir o processo
        scanf("%d", &decisao);
    }
    desalocaMatriz(tabuleiro); // desaloca os espaços armazenados na memoria
    return 0;                  // etabuleiro.nCerra o programa
}

char **alocaMatriz(Tab tabuleiro) // função responsavel por alocar espações da memoria (recebe parametros da main que são fornecidos pelo usuario)
{
    int i, j;
    char **m;
    m = (char **)malloc(tabuleiro.nC * sizeof(char *)); // aloca coluna
    for (i = 0; i < tabuleiro.nL; i++)
        m[i] = (char *)malloc(tabuleiro.nL * sizeof(char)); // aloca linhas

    if (m == NULL) // sem espaço na memoria
    {
        printf("não foi possivel alocar memoria para rodar o programa, FECHANDO...");
        Sleep(150);
        exit(1);
    }

    for (i = 0; i < tabuleiro.nL; i++)
        if (m[i] == NULL) // sem espaço na memoria
        {
            printf("não foi possivel alocar memoria para rodar o programa, FECHANDO...");
            Sleep(150);
            exit(1);
        }

    for (i = 0; i < tabuleiro.nL; i++)
    {
        for (j = 0; j < tabuleiro.nC; j++)
        {
            m[i][j] = VAZ;
        }
    }
    return m; // aloca por retorno
}

void menuInicJogo(Tab tabuleiro) // função responsavel por mostrar o menu de escolhas do jogo e captar sua respectiva escolha
{
    srand(time(NULL));
    int opcao,i = 0;
    printf("(1)Bloco\n(2)Blinker\n(3)Sapo\n(4)Glider\n(5)LWSS\nEntre com a opcao: ");
    scanf("%d", &opcao); // capta a escolha do usuario
    switch (opcao)       // switch de captação
    {
    case 1:
        inicBloco(tabuleiro);
        strcpy(tabuleiro.nomeJogo,"BLOCO.");
        break;
    case 2:
        inicBlinker(tabuleiro);
        strcpy(tabuleiro.nomeJogo,"BLINKER.");
        break;
    case 3:
        inicSapo(tabuleiro);
        strcpy(tabuleiro.nomeJogo,"SAPO.");
        break;
    case 4:
        inicGlider(tabuleiro);
        strcpy(tabuleiro.nomeJogo,"GLIDER.");
        break;
    case 5:
        inicLWSS(tabuleiro);
        strcpy(tabuleiro.nomeJogo,"LWSS.");
        break;
    }
    printf("\n");
    while(tabuleiro.nomeJogo[i] != '.')
    {
        printf("%c",tabuleiro.nomeJogo[i]);
        i++;
    }
    printf("\n");
    imprimeMatriz(tabuleiro);
    printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo...");
    while (getchar() != '\n')
        ;
    getchar();
}

void inicBloco(Tab tabuleiro) // função responsável por gerar o padrão de jogo "bloco"
{
    char padrao[2][2] = {{ORG, ORG}, {ORG, ORG}};                 // definição do elemento bloco na matriz
    int i, j, xInic = tabuleiro.nL / 2, yInic = tabuleiro.nC / 2; // cordenadas iniciais (será iniciado no meio da matriz)

    limpaMatriz(tabuleiro);

    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preetabuleiro.nChe padrão na matriz
}

void inicBlinker(Tab tabuleiro) // função responsável por gerar o padrão de jogo Blinker
{
    char padrao[1][3] = {{ORG, ORG, ORG}};                        // definição do elemento Blinker na matriz
    int i, j, xInic = tabuleiro.nL / 2, yInic = tabuleiro.nC / 2; // cordenadas iniciais (será iniciado no meio da matriz)
    limpaMatriz(tabuleiro);
    for (i = 0; i < 1; i++)
        for (j = 0; j < 3; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preetabuleiro.nChe padrão na matriz
}

void inicSapo(Tab tabuleiro) // função responsavel por gerar o padrão de jogo Sapo
{
    char padrao[2][4] = {{VAZ, ORG, ORG, ORG}, {ORG, ORG, ORG, VAZ}}; // definição do elemento Sapo na matriz
    int i, j, xInic = tabuleiro.nL / 2, yInic = tabuleiro.nC / 2;     // cordenadas iniciais (será iniciado no meio da matriz)
    limpaMatriz(tabuleiro);
    for (i = 0; i < 2; i++)
        for (j = 0; j < 4; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preetabuleiro.nChe padrão na matriz
}

void inicGlider(Tab tabuleiro) // função responsavel por gerar o padrão de jogo Glider
{
    char padrao[3][3] = {{ORG, ORG, ORG}, {ORG, VAZ, VAZ}, {VAZ, ORG, VAZ}}; // definição do elemento Glider na matriz
    int i, j, xInic, yInic;

    limpaMatriz(tabuleiro);
    xInic = tabuleiro.nL - 4; // cordenadas iniciais (canto inferior direito com quatro posições deslocadas em direção ao centro)
    yInic = tabuleiro.nC - 4;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preetabuleiro.nChe padrão na matriz
}

void inicLWSS(Tab tabuleiro) // função responsavel por gerar o padrão de jogo LWSS
{
    char padrao[4][5] = {{VAZ, ORG, VAZ, VAZ, ORG}, {ORG, VAZ, VAZ, VAZ, VAZ}, {ORG, VAZ, VAZ, VAZ, ORG}, {ORG, ORG, ORG, ORG, VAZ}}; // definição do elemento LWSS na matriz
    int i, j, xInic, yInic;
    limpaMatriz(tabuleiro);
    xInic = tabuleiro.nL - 5; // posição inicial do padrão
    yInic = tabuleiro.nC - 6;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 5; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preetabuleiro.nChe padrão na matriz
}

void limpaMatriz(Tab tabuleiro) // pretabuleiro.nChe matriz com pontos
{
    int i, j;
    for (i = 0; i < tabuleiro.nL; i++)
        for (j = 0; j < tabuleiro.nC; j++)
            tabuleiro.m[i][j] = VAZ; // faz com que a matriz seja preeTab.nCida com pontos (VAZIO)
}

void imprimeMatriz(Tab tabuleiro) // plota padrão na matriz
{
    int i, j;
    for (i = 0; i < tabuleiro.nL; i++)
    {
        for (j = 0; j < tabuleiro.nC; j++)
        {
            printf("%c ", tabuleiro.m[i][j]); // plota padrão da matriz na tela
        }
        printf("\n");
    }
}

void jogaJogoVida(Tab tabuleiro) // função responsavel por comandar o jogo
{
    char **mAnt;
    int c = 0;
    int n = 0;
    printf("\n");
    system(LIMPA);
    mAnt = alocaMatriz(tabuleiro);           // aloca espaço para matriz que vai guardar informações de espaço
    for (c = 1; c <= tabuleiro.nCiclos; c++) // repete o processo de atualização de tela por determinadas veze definidas pelo usario
    {

        if (c % 2 == 0)
        {
            n = rand() % 30;
        }
        if (n == 1)
        {
            inicInvasorUm(tabuleiro);
        }
        else if (n == 2)
        {
            inicInvasorDois(tabuleiro);
        }
        else if (n == 3)
        {
            inicInvasorTerceiro(tabuleiro);
        }
        else if (n == 4)
        {
            inicInvasorQuarto(tabuleiro);
        }
        else if (n == 5)
        {
            inicInvasorQuinto(tabuleiro);
        }
        else if (n == 6)
        {
            inicInvasorSexto(tabuleiro);
        }
        else if (n == 7)
        {
            inicInvasorSete(tabuleiro);
        }
        printf("\n");
        copiaMatriz(mAnt, tabuleiro);
        atualizaMat(mAnt, tabuleiro);
        system(LIMPA);
        imprimeMatriz(tabuleiro);
        Sleep(250);
    }
    desalocaMatriz(tabuleiro);
}

void copiaMatriz(char **mAnt, Tab tabuleiro) // unção responsável por preservar dados da matriz em outras matriz identica para que a matriz original possa ser modificada
{
    int i, j;
    for (i = 0; i < tabuleiro.nL; i++)
    {
        for (j = 0; j < tabuleiro.nC; j++)
        {
            mAnt[i][j] = tabuleiro.m[i][j]; // copia a matriz atual para a antiga (backup de dados)
        }
    }
}

void atualizaMat(char **mAnt, Tab tabuleiro) // muda o padrão da imagem de acorod com as regras do jogo
{
    int i, j, contador = 0;
    for (i = 0; i < tabuleiro.nL; i++)
    {
        for (j = 0; j < tabuleiro.nC; j++)
        {
            contador = contaVivos(mAnt, tabuleiro, i, j); // verificação de espaços ao redor da entidade
            if (mAnt[i][j] == ORG)                        // verifica casos de individuos vivos e sua redondeza
            {
                contador--;
                if (contador < 2)            // caso tenha menos de 2 organismo em torno
                    tabuleiro.m[i][j] = VAZ; // o organismo morre
                else if (contador > 3)       // caso tenha mais de 3 organismo em torno
                    tabuleiro.m[i][j] = VAZ; // o organismo morre
                else                         // caso contrario
                    tabuleiro.m[i][j] = ORG; // um organismo nasce
            }

            else // verifica casos de locais sem org e sua redondeza
            {
                if (contador == 3)           // caso exista 3 org vivos em volta de um local sem org
                    tabuleiro.m[i][j] = ORG; // nasce um org nesse local
            }

            contador = 0; // contador é zerado para que outra posião seja verificada
        }
    }
}

int contaVivos(char **mAnt, Tab tabuleiro, int i, int j) // função responsavel por contar entidades
{
    int cont = 0, i2, j2;
    for (i2 = i - 1; i2 <= i + 1; i2++)
    {
        for (j2 = j - 1; j2 <= j + 1; j2++)
        {
            if (verifica(tabuleiro, i2, j2) == TRUE)
            {
                if (mAnt[i2][j2] == ORG) // caso tenha algum organismo em torno do ponto analisado
                {
                    cont++; //é acrescentado um ao contador de vivos
                }
            }
        }
    }
    return cont;
}

int verifica(Tab tabuleiro, int i, int j) // verifica bordas
{
    if (i >= 0 && i < tabuleiro.nL && j >= 0 && j < tabuleiro.nC) // verifica se não esta nas bordas
        return TRUE;
    return FALSE;
}

void desalocaMatriz(Tab tabuleiro) // desaloca espaços que foram alocados posteriormente

{
    int i = 0;
    for (i = 0; i < tabuleiro.nL; i++)
    {
        free(tabuleiro.m[i]);
    }
    free(tabuleiro.m);
}

void inicInvasorUm(Tab tabuleiro) // função responsavel por gerar o padrão de jogo invasor
{

    char padrao[3][3] =
    {
        {VAZ, ORG, ORG},
        {ORG, VAZ, VAZ},
        {VAZ, ORG, VAZ},
    }; // definição do elemento Glider na matriz
    int i, j, xInic, yInic;

    xInic = (tabuleiro.nL / 3) * 2; // cordenadas iniciais (canto inferior direito com quatro posições deslocadas em direção ao centro)
    yInic = (tabuleiro.nC / 5) * 2;
    if (xInic < 2 || yInic < 2)
    {
        xInic = 10;
        yInic = 10;
    }

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j];

    // preenche padrão na matriz
}

void inicInvasorDois(Tab tabuleiro)
{
    char padrao[4][3] =
    {
        {ORG, ORG, ORG},
        {ORG, VAZ, VAZ},
        {VAZ, ORG, ORG},
        {ORG, VAZ, VAZ},
    }; // definição do elemento Glider na matriz
    int i, j, xInic, yInic;

    xInic = (tabuleiro.nL / 7) * 2; // cordenadas iniciais (canto inferior direito com quatro posições deslocadas em direção ao centro)
    yInic = (tabuleiro.nC / 8) * 2;
    if (xInic < 2 || yInic < 2)
    {
        xInic = 10;
        yInic = 10;
    }

    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preenche padrão na matriz
}

void inicInvasorTerceiro(Tab tabuleiro) // função responsavel por gerar o padrão de jogo invasor
{

    char padrao[4][3] =
    {
        {VAZ, ORG, VAZ},
        {ORG, ORG, VAZ},
        {ORG, VAZ, ORG},
        {VAZ, ORG, VAZ},
    }; // definição do elemento Glider na matriz
    int i, j, xInic, yInic;

    xInic = (tabuleiro.nL / 5) * 2; // cordenadas iniciais (canto inferior direito com quatro posições deslocadas em direção ao centro)
    yInic = (tabuleiro.nC / 3) * 2;
    if (xInic < 2 || yInic < 2)
    {
        xInic = 10;
        yInic = 10;
    }

    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j];

    // preenche padrão na matriz
}

void inicInvasorQuarto(Tab tabuleiro)
{

    char padrao[4][3] =
    {
        {VAZ, VAZ, VAZ},
        {ORG, VAZ, VAZ},
        {VAZ, ORG, ORG},
        {ORG, VAZ, VAZ},
    }; // definição do elemento Glider na matriz
    int i, j, xInic, yInic;

    xInic = (tabuleiro.nL / 4) * 2; // cordenadas iniciais (canto inferior direito com quatro posições deslocadas em direção ao centro)
    yInic = (tabuleiro.nC / 6) * 3;
    if (xInic < 2 || yInic < 2)
    {
        xInic = 10;
        yInic = 10;
    }

    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preenche padrão na matriz
}

void inicInvasorQuinto(Tab tabuleiro)
{

    char padrao[4][3] =
    {
        {VAZ, VAZ, VAZ},
        {VAZ, VAZ, ORG},
        {VAZ, ORG, VAZ},
        {ORG, VAZ, VAZ},
    }; // definição do elemento Glider na matriz
    int i, j, xInic, yInic;

    xInic = (tabuleiro.nL / 3) * 2; // cordenadas iniciais (canto inferior direito com quatro posições deslocadas em direção ao centro)
    yInic = (tabuleiro.nC / 2) * 2;
    if (xInic < 2 || yInic < 2)
    {
        xInic = 10;
        yInic = 10;
    }

    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preenche padrão na matriz
}

void inicInvasorSexto(Tab tabuleiro)
{

    char padrao[4][3] =
    {
        {VAZ, VAZ, VAZ},
        {ORG, VAZ, VAZ},
        {VAZ, ORG, VAZ},
        {ORG, VAZ, VAZ},
    }; // definição do elemento Glider na matriz
    int i, j, xInic, yInic;

    xInic = (tabuleiro.nL / 4) * 3; // cordenadas iniciais (canto inferior direito com quatro posições deslocadas em direção ao centro)
    yInic = (tabuleiro.nC / 5) * 2;
    if (xInic < 2 || yInic < 2)
    {
        xInic = 10;
        yInic = 10;
    }

    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preenche padrão na matriz
}

void inicInvasorSete(Tab tabuleiro)

{

    char padrao[4][3] =
    {
        {VAZ, VAZ, VAZ},
        {ORG, VAZ, VAZ},
        {VAZ, VAZ, ORG},
        {ORG, VAZ, VAZ},
    }; // definição do elemento Glider na matriz
    int i, j, xInic, yInic;

    xInic = (tabuleiro.nL / 6) * 2; // cordenadas iniciais (canto inferior direito com quatro posições deslocadas em direção ao centro)
    yInic = (tabuleiro.nC / 7) * 2;
    if (xInic < 2 || yInic < 2)
    {
        xInic = 10;
        yInic = 10;
    }

    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            tabuleiro.m[xInic + i][yInic + j] = padrao[i][j]; // preenche padrão na matriz
}
