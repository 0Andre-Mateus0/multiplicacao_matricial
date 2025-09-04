//Headers
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//MACROS (constantes)

//Fun��es prototipos
void telaTitulo();

//Main
void main() {
    setlocale(LC_ALL,"");
    telaTitulo();
}


//Fun��es auxiliares

//Cria uma tela de t�tulo, �bvio (AM)
//04/09 (AM): Eu vou tentar transformar essa fun��o numa recurs�o.
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
