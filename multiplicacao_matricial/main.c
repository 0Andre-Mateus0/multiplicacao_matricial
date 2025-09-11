//Headers
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <limits.h>
#include <unistd.h>

//Estrutura para configura��o do desenho da GUI
typedef struct {
    int espacY1; //Define o qu�o para baixo come�ar� o texto.
    int espacX1; //Define o qu�o � direita est� o texto.
    int espacY2; //Define o qu�o para baixo estar� o que quer que seja.
    int espacX2; //Define o qu�o � direita estar� o que quer que seja.
} configGUI;

//Estrutura para armazenar o resultado da multiplica��o com verifica��o de overflow
typedef struct {
    int** resultado;
    int erro; // 0 = sem erro, 1 = overflow detectado
} ResultadoMatriz;

//MACROS (constantes)
//Macro para calcular tamanho.
#define TAM_ARRAY(arr) (sizeof(arr)/sizeof((arr)[0]))
//Valor padr�o para configGUI (Nunca ser� usado :3 )
#define CONFIG_PADRAO {0,0,0,0}

//Fun��es prototipos
void telaTitulo();
void desenharGUI(const char *pGUI[], int tamArray, configGUI config);
void gotoxy(int y, int x);
void respostaEntreTextos(int coluna, int linha, int *resposta);
void ordemMatrizes(int *matrizAOrd1, int *matrizAOrd2, int *matrizBOrd1, int *matrizBOrd2);
void defineValor(int *Ai, int *Aj, int *Bi, int *Bj);
void desenhaMatriz(int inicioX, int incioY, int linhas, int colunas, const char* nome);
void preencheMatriz(int inicioX, int incioY, int linhas, int colunas, int** matriz);
ResultadoMatriz multiplicarMatrizesRecursivo(int** A, int** B, int** C, int i, int j, int k, int n, int p, int m);
ResultadoMatriz multiplicarMatrizes(int** A, int** B, int n, int p, int m);
void mostrarResultado(ResultadoMatriz resultado, int n, int m);

//Main
void main() {
    setlocale(LC_ALL,"");

    //Vari�veis
    int ia, ja, ib, jb;

    //Desenha a tela de t�tulo
    telaTitulo();
    ordemMatrizes(&ia, &ja, &ib, &jb);
    defineValor(&ia, &ja, &ib, &jb);
}

//Fun��es auxiliares

//Cria uma interface(AM)
void desenharGUI(const char *pGUI[], int tamArray, configGUI config) {
    for(int i = 0; i < config.espacY1; i++) { printf("\n"); }
    for(int i = 0; i < tamArray; i++) {
        for(int j = 0; j < config.espacX1; j++) { printf(" "); }
        printf("%s\n", pGUI[i]);
    }
    for(int i = 0; i < config.espacY2; i++) { printf("\n"); }
    for(int i = 0; i < config.espacX2; i++) { printf(" "); }
}

void telaTitulo() {
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

    desenharGUI(telaInicial, TAM_ARRAY(telaInicial), (configGUI){.espacY1 = 10, .espacX1 = 10, .espacY2 = 3, .espacX2 = 50});
    printf("<ENTER> para executar");
    getch();
    system("cls");
}

//Pede as ordens das matrizes e, se forem compat�veis parte para a fun��o que pede os n�meros.
void ordemMatrizes(int *matrizAOrd1, int *matrizAOrd2, int *matrizBOrd1, int *matrizBOrd2) {
    const char *instrucoesOrdens[] = {
        "Por favor, digite as ordens das matrizes:",
    }, *GUIOrdens[] = {
        "  ___                  ______ ",
        " / _ \\      __  __     | ___ \\",
        "/ /_\\ \\     \\ \\/ /     | |_/ /",
        "|  _  |      >  <      | ___ \\",
        "| | | |     /_/\\_\\     | |_/ /",
        "\\_| |_/  x             \\____/  x  "
    }, *avisoErro[] = {
        "Condi��o para multipli��o matricial n�o foi atendida.",
        "<ENTER> para escolher outras ordens."
    };

    int validade = 0;

    while(!validade) {
        system("cls");
        desenharGUI(instrucoesOrdens, TAM_ARRAY(instrucoesOrdens), (configGUI){.espacY1 = 10, .espacX1 = 40, .espacY2 = 3});
        desenharGUI(GUIOrdens, TAM_ARRAY(GUIOrdens), (configGUI){.espacX1 = 45, .espacY2 = 3});
        respostaEntreTextos(20, 53, matrizAOrd1);
        respostaEntreTextos(20, 56, matrizAOrd2);
        respostaEntreTextos(20, 75, matrizBOrd1);
        respostaEntreTextos(20, 78, matrizBOrd2);
        printf("\n");

        if(*matrizAOrd2 != *matrizBOrd1) {
            desenharGUI(avisoErro, TAM_ARRAY(avisoErro), (configGUI){.espacY1 = 2, .espacX1 = 40, .espacY2 = 3});
            getch();
        }
        else {
            validade = 1;
            for(int i = 0; i < 50; i++) { printf(" "); }
            printf("<ENTER> para continuar");
            getch();
            system("cls");
        }
    }
}

//Desenha a matriz na tela
void desenhaMatriz(int inicioX, int incioY, int linhas, int colunas, const char* nome) {
    //Desenhar nome da matriz
    gotoxy(inicioX, incioY);
    for(int i = 0; i < 50; i++) { printf(" "); }
    printf("%s:", nome);

    int larguraCel = 6; //Largura de cada c�lula

    //Desenhar borda superior
    gotoxy(inicioX, incioY + 1);
    printf("+");
    for (int j = 0; j < colunas; j++) {
        for (int k = 0; k < larguraCel - 1; k++) {
            printf("-");
        }
        printf("+");
    }

    //Desenhar linhas internas e c�lulas
    for (int i = 0; i < linhas; i++) {
        //Linha de c�lulas vazias
        gotoxy(inicioX, incioY + 2 + i * 2);
        printf("|");
        for (int j = 0; j < colunas; j++) {
            printf("%*s", larguraCel - 1, " "); //Espa�o vazio
            printf("|");
        }

        //Linha separadora (sempre, inclusive ap�s a �ltima linha)
        gotoxy(inicioX, incioY + 3 + i * 2);
        printf("+");
        for (int j = 0; j < colunas; j++) {
            for (int k = 0; k < larguraCel - 1; k++) {
                printf("-");
            }
            printf("+");
        }
    }
}

//Fun��o para preencher matriz interativamente
void preencheMatriz(int inicioX, int incioY, int linhas, int colunas, int** matriz) {
    int larguraCel = 6;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            //Posicionar cursor no centro da c�lula
            int x = inicioX + 2 + j * larguraCel;
            int y = incioY + 2 + i * 2;

            respostaEntreTextos(y, x, &matriz[i][j]);

            //Mostrar valor digitado
            gotoxy(x, y);
            printf("%4d", matriz[i][j]);
        }
    }
}

// Fun��o recursiva para multiplica��o de matrizes com verifica��o de overflow
ResultadoMatriz multiplicarMatrizesRecursivo(int** A, int** B, int** C, int i, int j, int k, int n, int p, int m) {
    ResultadoMatriz resultado;
    resultado.erro = 0;

    //Caso base: percorremos todas as linhas
    if (i >= n) {
        resultado.resultado = C;
        return resultado;
    }

    // aso base: percorremos todas as colunas da linha atual
    if (j >= m) {
        // Avan�ar para a pr�xima linha, primeira coluna
        return multiplicarMatrizesRecursivo(A, B, C, i + 1, 0, 0, n, p, m);
    }

    //Caso base: percorremos todos os elementos da soma atual
    if (k >= p) {
        // Verificar se o resultado final cabe em int
        if (C[i][j] > INT_MAX || C[i][j] < INT_MIN) {
            resultado.erro = 1;
            return resultado;
        }
        //Avan�ar para a pr�xima coluna, primeiro elemento de soma
        return multiplicarMatrizesRecursivo(A, B, C, i, j + 1, 0, n, p, m);
    }

    //Verificar overflow na multiplica��o do elemento atual
    long long produto = (long long)A[i][k] * (long long)B[k][j];
    if (A[i][k] != 0 && produto / A[i][k] != B[k][j]) {
        resultado.erro = 1;
        return resultado;
    }

    //Verificar overflow na soma acumulada
    long long soma_atual = (long long)C[i][j];
    if ((produto > 0 && soma_atual > LLONG_MAX - produto) ||
        (produto < 0 && soma_atual < LLONG_MIN - produto)) {
        resultado.erro = 1;
        return resultado;
    }

    //Atualizar o valor da c�lula
    C[i][j] += (int)produto;

    //Chamada recursiva para o pr�ximo elemento da soma
    return multiplicarMatrizesRecursivo(A, B, C, i, j, k + 1, n, p, m);
}

//Fun��o wrapper para iniciar a recurs�o
ResultadoMatriz multiplicarMatrizes(int** A, int** B, int n, int p, int m) {
    int** C = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        C[i] = calloc(m, sizeof(int)); //Inicializar com zeros
    }

    ResultadoMatriz resultado = multiplicarMatrizesRecursivo(A, B, C, 0, 0, 0, n, p, m);

    if (resultado.erro) {
        //Liberar mem�ria em caso de erro
        for (int i = 0; i < n; i++) free(C[i]);
        free(C);
        resultado.resultado = NULL;
    }

    return resultado;
}

//Mostrar o resultado da multiplica��o
void mostrarResultado(ResultadoMatriz resultado, int n, int m) {
    system("cls");

    if (resultado.erro) {
        printf("ERRO: Overflow detectado durante a multiplica��o!\n");
        printf("Os valores excedem a capacidade de armazenamento.\n");
    } else if (resultado.resultado == NULL) {
        printf("ERRO: N�o foi poss�vel calcular a multiplica��o.\n");
    } else {
        desenhaMatriz(2, 3, n, m, "Matriz Resultante");

        // Mostrar valores da matriz resultante
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                gotoxy(2 + 2 + j * 6, 3 + 2 + i * 2);
                printf("%4d", resultado.resultado[i][j]);
            }
        }
    }

    gotoxy(2, 3 + n * 2 + 2);
    for(int i = 0; i < 50; i++) { printf(" "); }
    printf("<ENTER> para finalizar");
    getchar(); // Limpar buffer
    getchar(); // Esperar enter
}

void defineValor(int *Ai, int *Aj, int *Bi, int *Bj) {
    //Alocar matrizes
    int **MatA = malloc(*Ai * sizeof(int*));
    int **MatB = malloc(*Bi * sizeof(int*));

    for (int i = 0; i < *Ai; i++) MatA[i] = malloc(*Aj * sizeof(int));
    for (int i = 0; i < *Bi; i++) MatB[i] = malloc(*Bj * sizeof(int));

    //TELA 1: Matriz A
    system("cls");
    desenhaMatriz(2, 3, *Ai, *Aj, "Matriz A");

    //Preencher matriz A
    gotoxy(2, 2);
    preencheMatriz(2, 3, *Ai, *Aj, MatA);

    //Mensagem de transi��o
    gotoxy(2, 3 + *Ai * 2 + 2);
    for(int i = 0; i < 45; i++) { printf(" "); }
    printf("<ENTER> para preencher a Matriz B");
    getchar(); //Limpar buffer
    getchar(); //Esperar enter

    //TELA 2: Matriz B
    system("cls");
    desenhaMatriz(2, 3, *Bi, *Bj, "Matriz B");

    //Preencher matriz B
    gotoxy(2, 2);
    preencheMatriz(2, 3, *Bi, *Bj, MatB);

    //Multiplicar as matrizes
    ResultadoMatriz resultado = multiplicarMatrizes(MatA, MatB, *Ai, *Aj, *Bj);

    //Mostrar resultado
    mostrarResultado(resultado, *Ai, *Bj);

    //Liberar mem�ria
    for (int i = 0; i < *Ai; i++) free(MatA[i]);
    free(MatA);
    for (int i = 0; i < *Bi; i++) free(MatB[i]);
    free(MatB);

    if (resultado.resultado != NULL) {
        for (int i = 0; i < *Ai; i++) free(resultado.resultado[i]);
        free(resultado.resultado);
    }
}

//Pra fazer respostaEntreTextos funcionar :3
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

//Digitar resposta entre textos
void respostaEntreTextos(int linha, int coluna, int *resposta) {
   gotoxy(coluna, linha);
    scanf("%d", resposta);
}
