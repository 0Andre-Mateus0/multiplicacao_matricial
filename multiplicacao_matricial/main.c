//Headers
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//MACROS (constantes)

//Funções prototipos
void telaTitulo();

//Main
void main() {
    setlocale(LC_ALL,"");
    telaTitulo();
}


//Funções auxiliares

//Cria uma tela de título, óbvio (AM)
//04/09 (AM): Eu vou tentar transformar essa função numa recursão.
void telaTitulo() {
    char *titulo[] = {
        "___  ___      _ _   _       _ _                            ___  ___      _        _      _       _ ",
        "|  \\/  |     | | | (_)     | (_)                           |  \\/  |     | |      (_)    (_)     | |",
        "| .  . |_   _| | |_ _ _ __ | |_  ___ __ _  ___ __ _  ___   | .  . | __ _| |_ _ __ _  ___ _  __ _| |",
        "| |\\/| | | | | | __| | '_ \\| | |/ __/ _` |/ __/ _` |/ _ \\  | |\\/| |/ _` | __| '__| |/ __| |/ _` | |",
        "| |  | | |_| | | |_| | |_) | | | (_| (_| | (_| (_| | (_) | | |  | | (_| | |_| |  | | (__| | (_| | |",
        "\\_|  |_/\\__,_|_|\\__|_| .__/|_|_|\\___\\__,_|\\___\\__,_|\\___/  \\_|  |_/\\__,_|\\__|_|  |_|\\___|_|\\__,_|_|",
        "                     | |                                                                           ",
        "                     |_|                                                                           "
    };
    int tamArray = sizeof(titulo)/sizeof(titulo[0]);

    for(int i = 0; i < 10; i++) { printf("\n"); }
    for(int i = 0; i < tamArray; i++) {
        for(int j = 0; j < 10; j++) { printf(" "); }
        printf("%s\n",titulo[i]);
    }
    for(int i = 0; i < 3; i++) { printf("\n"); }
    for(int i = 0; i < 50; i++) { printf(" "); }
    printf("<ENTER> para executar");
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
