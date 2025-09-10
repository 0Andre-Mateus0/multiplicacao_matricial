//Headers
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

/*
05/09(AM): Essa foi a melhor maneira que eu consegui para criar parâmetros opcionais. É mais legível e possui uma fácil manutenção.
*/

//Estrutura para configuração do desenho da GUI
typedef struct {
    int espacY1; //Define o quâo para baixo começará o texto.
    int espacX1; //Define o quâo à direita está o texto.
    int espacY2; //Define o quâo para baixo estará o que quer que seja.
    int espacX2; //Define o quâo à direita estará o que quer que seja.
} configGUI;

//MACROS (constantes)
/*
    05/09 (AM): Tive que criar esse macro pois pGUI é um ponteiro e se eu quisesse calcular internamente o tamanho do array eu teria que usar NULL para marcar o fim do array. E eu não tô com saco pra isso.
*/
//Macro para calcular tamanho.
#define TAM_ARRAY(arr) (sizeof(arr)/sizeof((arr)[0]))
//Valor padrão para configGUI (Nunca será usado :3 )
#define CONFIG_PADRAO {0,0,0,0}

/*
//Funções prototipos
//05/09 (AM): É obrigatório escrever aqui as funções auxliares, se não dá erro de declaração implícita.
  05/09 (AM): Aparentemente eu estava enganado. Ops...
void desenharGUI();
int ordemMatrizes();
*/

//Funções auxiliares

//Cria uma tela de título, óbvio (AM)
//04/09 (AM): Eu vou tentar transformar essa função numa recursão.
/*
05/09 (AM): Não dá.
      (AM): Eu vou tentar tornar essa função em uma função geral com parâmetros opcionais.
      (AM): Eba!!
*/
void desenharGUI(const char *pGUI[], int tamArray, configGUI config) {
    for(int i = 0; i < config.espacY1; i++) { printf("\n"); }
    for(int i = 0; i < tamArray; i++) {
        for(int j = 0; j < config.espacX1; j++) { printf(" "); }
        printf("%s\n",pGUI[i]);
    }
    for(int i = 0; i < config.espacY2; i++) { printf("\n"); }
    for(int i = 0; i < config.espacX2; i++) { printf(" "); }
}

//Pra fazer respostaEntreTextos funcionar :3
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

//Digitar resposta entre textos
void respostaEntreTextos(int coluna, int linha,int *resposta) {
    gotoxy(coluna,linha);
    scanf("%d",resposta);
}

//Pede as ordens das matrizes e, se forem compatíveis parte para a função que pede os números.
int ordemMatrizes(int *matrizAOrd1, int *matrizAOrd2, int *matrizBOrd1, int *matrizBOrd2) {
    // ponteiro é um bicho escroto Deus me livre
    int funcional = 1;

    while(funcional == 1) {
        const char *instrucoesOrdens[] = {
            "Por favor, digite as ordens das matrizes:",
        }, *GUIOrdens[] = {
            "  ___                  ______ ",
            " / _ \\      __  __     | ___ \\",
            "/ /_\\ \\     \\ \\/ /     | |_/ /",
            "|  _  |      >  <      | ___ \\",
            "| | | |     /_/\\_\\     | |_/ /",
            "\\_| |_/  x             \\____/  x  "
        };


        desenharGUI(instrucoesOrdens,TAM_ARRAY(instrucoesOrdens),(configGUI){.espacY1 = 10, .espacX1 = 40, .espacY2 = 3});
        desenharGUI(GUIOrdens,TAM_ARRAY(GUIOrdens),(configGUI){.espacX1 = 45, .espacY2 = 3});
        respostaEntreTextos(53,20,&matrizAOrd1);
        respostaEntreTextos(56,20,&matrizAOrd2);
        respostaEntreTextos(75,20,&matrizBOrd1);
        respostaEntreTextos(78,20,&matrizBOrd2);

        if(*matrizAOrd2 == *matrizBOrd1) funcional = 0;
        else {
            funcional = 1;
            printf("Essas Matrizes nao podem ser Multiplicadas, escolha outras!");
            system("cls");
        }
    }
    printf("\n");
    for(int i = 0; i < 50; i++) printf(" ");
}

int definevalor(int ia, int ja, int ib, int jb, int MatA[ia][ja], int MatB[ib][jb]) {
    for(int i = 0; i < ia; i++) {
        for(int j = 0; j < ja; j++) {
            printf("MatA[%d][%d]: ", i, j);
            scanf("%d", &MatA[i][j]);
            system("cls");
        }
    }
    for(int i = 0; i < ib; i++) {
        for(int j = 0; j < jb; j++) {
            printf("MatB[%d][%d]: ", i, j);
            scanf("%d", &MatB[i][j]);
            system("cls");
        }
    }
     mostrarmatrizes(ia, ja, ib, jb, MatA, MatB);
}

int mostrarmatrizes(int ia, int ja, int ib, int jb, int MatA[ia][ja], int MatB[ib][jb]) {
    printf("MATRIZ A:");
    for (int j = 0; j < ja; j++){
        printf("\n");
        for (int i = 0;i < ia; i++){
            printf("%d ", MatA[i][j]);
        }
    }
    printf("\nMATRIZ B:");
    for (int j = 0; j < jb; j++){
        printf("\n");
        for (int i = 0;i < ib; i++){
            printf("%d ", MatB[i][j]);
        }
    }
}

//Main
void main() {
    setlocale(LC_ALL,"");

    //Variáveis
    int ia,ja,ib,jb // linhas e colunas das matrizes A e B, respectivamente;
    const char *telaInicial[] = {
        "___  ___      _ _   _       _ _                            ___  ___      _        _      _       _ ",
        "|  \\/  |     | | | (_)     | (_)                           |  \\/  |     | |      (_)    (_)     | |",
        "| .  . |_   _| | |_ _ _ __ | |_  ___ __ _  ___ __ _  ___   | .  . | __ _| |_ _ __ _  ___ _  __ _| |",
        "| |\\/| | | | | | __| | '_ \\| | |/ __/ _` |/ __/ _` |/ _ \\  | |\\/| |/ _` | __| '__| |/ __| |/ _` | |",
        "| |  | | |_| | | |_| | |_) | | | (_| (_| | (_| (_| | (_) | | |  | | (_| | |_| |  | | (__| | (_| | |",
        "\\_|  |_/\\__,_|_|\\__|_| .__/|_|_|\\___\\__,_|\\___\\__,_|\\___/  \\_|  |_/\\__,_|\\__|_|  |_|\\___|_|\\__,_|_|",
        "                     | |                                                                           ",
        "                     |_|                                                                           "
    };

    //Desenha a tela de título
    desenharGUI(telaInicial,TAM_ARRAY(telaInicial),(configGUI){.espacY1 = 10, .espacX1 = 10, .espacY2 = 3, .espacX2 = 50});
    printf("<ENTER> para executar");
    getch();
    system("cls");

    ordemMatrizes(&ia,&ja,&ib,&jb);
    int MatA[ia][ja], MatB[ib][jb];
    printf("<ENTER> para continuar");
    getch();
    system("cls");
    definevalor(ia, ja, ib, jb, MatA, MatB);
}




/*
                    Instruções gerais
                    por: André Mateus

  1. Tela onde é pedida do usuário as ordens das
     matrizes.

  2. Caso a condição de multiplicação matricial
     não for atendida: 2.1; caso contrário: 3;

    2.1. Tela avisando ao usuário que dá erro e
         possui duas opções: o usuário pôr outros
         números como ordem ou sair.

  3. Pergunta se o usuário se ele quer esoolher
     manualmente os números ou pseudoaleatório.

  4. Finalizada a multiplicação, pergunta se o usuário
     quer refazer com outros números ou sair.

*/
