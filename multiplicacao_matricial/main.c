//Headers
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <limits.h>
#include <unistd.h>

//Estrutura para configuração do desenho da GUI
typedef struct {
    int espacY1; //Define o quâo para baixo começará o texto.
    int espacX1; //Define o quâo à direita está o texto.
    int espacY2; //Define o quâo para baixo estará o que quer que seja.
    int espacX2; //Define o quâo à direita estará o que quer que seja.
} configGUI;

//Estrutura para armazenar o resultado da multiplicação com verificação de overflow
typedef struct {
    int** resultado;
    int erro; // 0 = sem erro, 1 = overflow detectado
} ResultadoMatriz;

//MACROS (constantes)
//Macro para calcular tamanho.
#define TAM_ARRAY(arr) (sizeof(arr)/sizeof((arr)[0]))
//Valor padrão para configGUI (Nunca será usado :3 )
#define CONFIG_PADRAO {0,0,0,0}

//Funções prototipos
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

    //Variáveis
    int ia, ja, ib, jb;

    //Desenha a tela de título
    telaTitulo();
    ordemMatrizes(&ia, &ja, &ib, &jb);
    defineValor(&ia, &ja, &ib, &jb);
}

//Funções auxiliares

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

//Pede as ordens das matrizes e, se forem compatíveis parte para a função que pede os números.
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
        "Condição para multiplição matricial não foi atendida.",
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

    int larguraCel = 6; //Largura de cada célula

    //Desenhar borda superior
    gotoxy(inicioX, incioY + 1);
    printf("+");
    for (int j = 0; j < colunas; j++) {
        for (int k = 0; k < larguraCel - 1; k++) {
            printf("-");
        }
        printf("+");
    }

    //Desenhar linhas internas e células
    for (int i = 0; i < linhas; i++) {
        //Linha de células vazias
        gotoxy(inicioX, incioY + 2 + i * 2);
        printf("|");
        for (int j = 0; j < colunas; j++) {
            printf("%*s", larguraCel - 1, " "); //Espaço vazio
            printf("|");
        }

        //Linha separadora (sempre, inclusive após a última linha)
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

//Função para preencher matriz interativamente
void preencheMatriz(int inicioX, int incioY, int linhas, int colunas, int** matriz) {
    int larguraCel = 6;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            //Posicionar cursor no centro da célula
            int x = inicioX + 2 + j * larguraCel;
            int y = incioY + 2 + i * 2;

            respostaEntreTextos(y, x, &matriz[i][j]);

            //Mostrar valor digitado
            gotoxy(x, y);
            printf("%4d", matriz[i][j]);
        }
    }
}

// Função recursiva para multiplicação de matrizes com verificação de overflow
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
        // Avançar para a próxima linha, primeira coluna
        return multiplicarMatrizesRecursivo(A, B, C, i + 1, 0, 0, n, p, m);
    }

    //Caso base: percorremos todos os elementos da soma atual
    if (k >= p) {
        // Verificar se o resultado final cabe em int
        if (C[i][j] > INT_MAX || C[i][j] < INT_MIN) {
            resultado.erro = 1;
            return resultado;
        }
        //Avançar para a próxima coluna, primeiro elemento de soma
        return multiplicarMatrizesRecursivo(A, B, C, i, j + 1, 0, n, p, m);
    }

    //Verificar overflow na multiplicação do elemento atual
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

    //Atualizar o valor da célula
    C[i][j] += (int)produto;

    //Chamada recursiva para o próximo elemento da soma
    return multiplicarMatrizesRecursivo(A, B, C, i, j, k + 1, n, p, m);
}

//Função wrapper para iniciar a recursão
ResultadoMatriz multiplicarMatrizes(int** A, int** B, int n, int p, int m) {
    int** C = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        C[i] = calloc(m, sizeof(int)); //Inicializar com zeros
    }

    ResultadoMatriz resultado = multiplicarMatrizesRecursivo(A, B, C, 0, 0, 0, n, p, m);

    if (resultado.erro) {
        //Liberar memória em caso de erro
        for (int i = 0; i < n; i++) free(C[i]);
        free(C);
        resultado.resultado = NULL;
    }

    return resultado;
}

//Mostrar o resultado da multiplicação
void mostrarResultado(ResultadoMatriz resultado, int n, int m) {
    system("cls");

    if (resultado.erro) {
        printf("ERRO: Overflow detectado durante a multiplicação!\n");
        printf("Os valores excedem a capacidade de armazenamento.\n");
    } else if (resultado.resultado == NULL) {
        printf("ERRO: Não foi possível calcular a multiplicação.\n");
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

    //Mensagem de transição
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

    //Liberar memória
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
