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
    int espacY1;
    int espacX1;
    int espacY2;
    int espacX2;
} configGUI;

//MACROS (constantes)
/*
    05/09 (AM): Tive que criar esse macro pois pGUI � um ponteiro e se eu quisesse calcular internamente o tamanho do array eu teria que usar NULL para marcar o fim do array. E eu n�o t� com saco pra isso.
*/
//Macro para calcular tamanho.
#define TAM_ARRAY(arr) (sizeof(arr)/sizeof((arr)[0]))
//Valor padr�o para configGUI
#define CONFIG_PADRAO {0,0,0,0}


//Fun��es prototipos
//05/09 (AM): � obrigat�rio escrever aqui as fun��es auxliares, se n�o d� erro de declara��o impl�cita.
void desenharGUI();


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



//Main
void main() {
    setlocale(LC_ALL,"");

    const char *titulo[] = {
        "___  ___      _ _   _       _ _                            ___  ___      _        _      _       _ ",
        "|  \\/  |     | | | (_)     | (_)                           |  \\/  |     | |      (_)    (_)     | |",
        "| .  . |_   _| | |_ _ _ __ | |_  ___ __ _  ___ __ _  ___   | .  . | __ _| |_ _ __ _  ___ _  __ _| |",
        "| |\\/| | | | | | __| | '_ \\| | |/ __/ _` |/ __/ _` |/ _ \\  | |\\/| |/ _` | __| '__| |/ __| |/ _` | |",
        "| |  | | |_| | | |_| | |_) | | | (_| (_| | (_| (_| | (_) | | |  | | (_| | |_| |  | | (__| | (_| | |",
        "\\_|  |_/\\__,_|_|\\__|_| .__/|_|_|\\___\\__,_|\\___\\__,_|\\___/  \\_|  |_/\\__,_|\\__|_|  |_|\\___|_|\\__,_|_|",
        "                     | |                                                                           ",
        "                     |_|                                                                           "
    };

    desenharGUI(titulo,TAM_ARRAY(titulo),(configGUI){.espacY1 = 10, .espacX1 =10, .espacY2 = 3, .espacX2 = 50});
    printf("<ENTER> para executar");
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
