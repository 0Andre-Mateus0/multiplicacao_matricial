//Headers
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

/*
05/09(AM): Essa foi a melhor maneira que eu consegui para criar par�metros opcionais. � mais leg�vel e possui uma f�cil manuten��o.
*/

//Estrutura para configura��o do desenho da GUI
typedef struct {
    int espacY1; //Define o qu�o para baixo come�ar� o texto.
    int espacX1; //Define o qu�o � direita est� o texto.
    int espacY2; //Define o qu�o para baixo estar� o que quer que seja.
    int espacX2; //Define o qu�o � direita estar� o que quer que seja.
} configGUI;

//MACROS (constantes)
/*
    05/09 (AM): Tive que criar esse macro pois pGUI � um ponteiro e se eu quisesse calcular internamente o tamanho do array eu teria que usar NULL para marcar o fim do array. E eu n�o t� com saco pra isso.
*/
//Macro para calcular tamanho.
#define TAM_ARRAY(arr) (sizeof(arr)/sizeof((arr)[0]))
//Valor padr�o para configGUI (Nunca ser� usado :3 )
#define CONFIG_PADRAO {0,0,0,0}

/*
//Fun��es prototipos
//05/09 (AM): � obrigat�rio escrever aqui as fun��es auxliares, se n�o d� erro de declara��o impl�cita.
  05/09 (AM): Aparentemente eu estava enganado. Ops...
void desenharGUI();
int ordemMatrizes();
*/

//Fun��es auxiliares

//Cria uma tela de t�tulo, �bvio (AM)
//04/09 (AM): Eu vou tentar transformar essa fun��o numa recurs�o.
/*
05/09 (AM): N�o d�.
      (AM): Eu vou tentar tornar essa fun��o em uma fun��o geral com par�metros opcionais.
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

//Pede as ordens das matrizes e, se forem compat�veis parte para a fun��o que pede os n�meros.
int ordemMatrizes() {
    int matrizAOrd1, matrizAOrd2, matrizBOrd1, matrizBOrd2;

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

    printf("\n");
    for(int i = 0; i < 50; i++) printf(" ");
}


//Main
void main() {
    setlocale(LC_ALL,"");

    //Vari�veis
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

    //Desenha a tela de t�tulo
    desenharGUI(telaInicial,TAM_ARRAY(telaInicial),(configGUI){.espacY1 = 10, .espacX1 = 10, .espacY2 = 3, .espacX2 = 50});
    printf("<ENTER> para executar");
    getch();
    system("cls");

    ordemMatrizes();
    printf("<ENTER> para continuar");
    getch();
    system("cls");
}




/*
                    Instru��es gerais
                    por: Andr� Mateus

  1. Tela onde � pedida do usu�rio as ordens das
     matrizes.

  2. Caso a condi��o de multiplica��o matricial
     n�o for atendida: 2.1; caso contr�rio: 3;

    2.1. Tela avisando ao usu�rio que d� erro e
         possui duas op��es: o usu�rio p�r outros
         n�meros como ordem ou sair.

  3. Pergunta se o usu�rio se ele quer esoolher
     manualmente os n�meros ou pseudoaleat�rio.

  4. Finalizada a multiplica��o, pergunta se o usu�rio
     quer refazer com outros n�meros ou sair.

*/
