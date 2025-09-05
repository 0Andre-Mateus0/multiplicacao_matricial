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
    int espacY1;
    int espacX1;
    int espacY2;
    int espacX2;
} configGUI;

//MACROS (constantes)
/*
    05/09 (AM): Tive que criar esse macro pois pGUI é um ponteiro e se eu quisesse calcular internamente o tamanho do array eu teria que usar NULL para marcar o fim do array. E eu não tô com saco pra isso.
*/
//Macro para calcular tamanho.
#define TAM_ARRAY(arr) (sizeof(arr)/sizeof((arr)[0]))
//Valor padrão para configGUI
#define CONFIG_PADRAO {0,0,0,0}


//Funções prototipos
//05/09 (AM): É obrigatório escrever aqui as funções auxliares, se não dá erro de declaração implícita.
void desenharGUI();


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
