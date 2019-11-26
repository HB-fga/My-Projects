#include <stdio.h>

void revela_zeros(int campo_minado[9][10], char espelho[9][10], int x, int y) {

    // ACERTOU UMA BOMBA
    if(campo_minado[x][y] == -1)
    {
        printf("GAME OVER!\n");
    }
    else // NAO ACERTOU UMA BOMBA
    {
        //ACERTOU UM ZERO
        if(campo_minado[x][y] == 0 && espelho[x][y] == '#')
        {
            espelho[x][y] = '0';
            // printf("before 1st recursion\n");
            if(x != 8) revela_zeros(campo_minado, espelho, x+1, y);
            // printf("before 2nd recursion\n");
            if(y != 9) revela_zeros(campo_minado, espelho, x, y+1);
            // printf("before 3rd recursion\n");
            if(x != 8 && y != 9) revela_zeros(campo_minado, espelho, x+1, y+1);
            // printf("before 4th recursion\n");
            if(x != 0) revela_zeros(campo_minado, espelho, x-1, y);
            // printf("before 5th recursion\n");
            if(y != 0) revela_zeros(campo_minado, espelho, x, y-1);
            // printf("before 6th recursion\n");
            if(x != 0 && y != 0) revela_zeros(campo_minado, espelho, x-1, y-1);
            // printf("before 7th recursion\n");
            if(x != 8 && y != 0) revela_zeros(campo_minado, espelho, x+1, y-1);
            // printf("before 8th recursion\n");
            if(x != 0 && y != 9) revela_zeros(campo_minado, espelho, x-1, y+1);
            // printf("after recursion\n");
        }
        else // ACERTOU UM NUMERO
        {
            espelho[x][y] = campo_minado[x][y] + '0';
        }
        
    }
    

    return;
}

// FUNCAO QUE COLOCA OS NUMEROS EM VOLTA DAS BOMBAS
void sinaliza_bombas(int campo_minado[9][10]) {

    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            if(campo_minado[i][j] == -1)
            {
                if(campo_minado[i+1][j] != -1) campo_minado[i+1][j]++;
                if(campo_minado[i][j+1] != -1) campo_minado[i][j+1]++;
                if(campo_minado[i+1][j+1] != -1) campo_minado[i+1][j+1]++;
                if(campo_minado[i-1][j] != -1) campo_minado[i-1][j]++;
                if(campo_minado[i][j-1] != -1) campo_minado[i][j-1]++;
                if(campo_minado[i-1][j-1] != -1) campo_minado[i-1][j-1]++;
                if(campo_minado[i+1][j-1] != -1) campo_minado[i+1][j-1]++;
                if(campo_minado[i-1][j+1] != -1) campo_minado[i-1][j+1]++;
            }
        }
    }

    return;
}

int main() {

    int x, y;

    int campo_minado[9][10];
    char espelho[9][10];

    // PREENCHENDO CAMPO
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            campo_minado[i][j] = 0;
        }
    }

    // PREENCHENDO ESPELHO
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            espelho[i][j] = '#';
        }
    }


    // COLOCANDO MINAS MANUALMENTE
    campo_minado[1][1] = -1;
    campo_minado[7][1] = -1;
    campo_minado[7][2] = -1;
    campo_minado[7][4] = -1;
    campo_minado[6][4] = -1;
    campo_minado[5][4] = -1;
    campo_minado[8][9] = -1;

    sinaliza_bombas(campo_minado);

    // LACO DE REPETICAO INFINITO ONDE O JOGO RODA
    while(1)
    {

        for(int i = 0;i < 9;i++)
        {
            for(int j = 0;j < 10;j++)
            {
                // printf("%d", campo_minado[i][j]);

                printf("%c", espelho[i][j]);
            }

            printf("\n");
        }

        printf("insira a coordenada X e Y que deseja revelar: ");

        scanf(" %d %d", &x, &y);

        revela_zeros(campo_minado, espelho, x, y);

    }

    return 0;
}