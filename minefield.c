
//CÓDIGO DO MIKAEL

//Incluindo as bibliotecas que serão utilizadas no programa

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 

/*
Variáveis globais
*/
  int x;
  int y;
  char acao;
  struct minas preenche;
  int ndificuldade;
  int contador;

/*
parte de preenchimento
*/

  //preenche a matriz com zeros
  void matrizinicial(int matriz[9][10], int n, int m){    
    for(int i=0; i<9; i++){
      for(int j=0; j<10; j++){
        matriz[i][j]=0;
      }
    }

    //laço para teste de impressão da matriz;
    /*
    for(int i=0; i<9; i++){       
      for(int j=0;j<10;j++){
        printf("%d ", matriz[i][j]);
      }
        printf("\n");
    }
    */
    
    
  }

  //quantidade e posicao das minas na matriz
  struct minas{
    int qntdminas;
    int posx[90];
    int posy[90];
  };

  //funcao para sortear quantidade e posicao das bombas
  void sorteiobombas(){
    
    int h,f;
    h=ndificuldade;

    if(h==1){
      f=16;
    }
    if(h==2){
      f=21;
    }
    if(h==3){
      f=26;
    }
    //printf("\n\n\n%d\n\n\n", h);

    srand(time(NULL));

      int qntd= f + rand()%4;

    preenche.qntdminas=qntd;
    contador=qntd; 

    //printf("\nforam sorteadas %d bombas\n",contador);

    for(int i=0; i<preenche.qntdminas; i++){
      preenche.posx[i]=rand()%10;
      preenche.posy[i]=rand()%9;
      //printf("%d %d\n", preenche.posx[i], preenche.posy[i]);
    }

    //printf("\n");


    //valida coordenadas e nao deixa repetir
    for (int i=0; i<preenche.qntdminas; i++){
        for(int j=0; j<preenche.qntdminas; j++){
          
          if(i==j){
          }

          else{
                if(preenche.posx[i]==preenche.posx[j]){
                  if(preenche.posy[i]==preenche.posy[j]){
                    /*printf("'x'de %d é igual a 'x'de = %d = %d",j,i, preenche.posx[j]);*/
                      preenche.posx[j]=rand()%10;
                    /*printf(" foi trocada por valor = %d\n", preenche.posx[j]);*/
                }
              }
          }
        }
    }
      for(int i=0;i<preenche.qntdminas;i++){
      //printf(" bomba '%d' x=%d y=%d\n", i, preenche.posx[i],preenche.posy[i]);
    }


  }

  //apenas para ver o que está guardado na struct
  void mostrastruct(){
      printf("qntdminas = %d\n", preenche.qntdminas);

    for(int i=0; i< preenche.qntdminas; i++){
      printf("posx[%d] = %d\n",i, preenche.posx[i]);
      printf("posy[%d] = %d \n", i,preenche.posy[i]);
    }

  }
  //insere as bombas sorteadas na matriz de gabarito
  void bombanamatriz(int gabarito[9][10]){

    int k;
    int z;
    int i;
    for(i=0; i<preenche.qntdminas;i++){
      k=preenche.posx[i];
      z=preenche.posy[i];
      gabarito[z][k]=9;
    }

  }
  //Funcao para preencher espaços dos lados da bomba
  void completamatriz(int gabarito[9][10]){

    for(int i=0; i<9;i++){
      for(int j=0;j<10;j++){
        if(gabarito[i][j]==9){
          
              //primeira linha
            if(i!=0 && j!=0){
              if(gabarito[i-1][j-1]!=9){
                gabarito[i-1][j-1]++;
              }
            }
          
            if(i!=0){
              if(gabarito[i-1][j]!=9){
                gabarito[i-1][j]++;
              }
            }

            if(i!=0 && j!=9){
              if(gabarito[i-1][j+1]!=9){
                gabarito[i-1][j+1]++;
              }
            }
              

              //segunda linha
            if(j!=0){
              if(gabarito[i][j-1]!=9){
                gabarito[i][j-1]++;
              }
            }

            if(j!=9){  
              if(gabarito[i][j+1]!=9){
                gabarito[i][j+1]++;
              }
            }


              //terceira linha
            if(i!=8 && j!=0){
              if(gabarito[i+1][j-1]!=9){
                gabarito[i+1][j-1]++;
              }
            }

            if(i!=0){
              if(gabarito[i+1][j]!=9){
                gabarito[i+1][j]++;
              }
            }

            if(i!=8 && j!=9){
              if(gabarito[i+1][j+1]!=9){
                gabarito[i+1][j+1]++;
              }
            }
          
        }
      }
    }

  }



/*
parte de leitura
*/


  //preenche o campo com jogos da velha
  void espelhoinicial(char espelho[9][10]){
        for(int i=0;i<9;i++){
          for(int j=0;j<10;j++){
            espelho[i][j]='#';
          }
        }

      //print teste
      for(int i=0;i<9;i++){
          for(int j=0;j<10;j++){
            printf("%c ", espelho[i][j]);
          }
        printf("\n");
      }

  }
  // ler as coordenadas que o jogador insere
  void lerentrada(){
    printf("digite (x, y , ação)\n");
    scanf("%d %d %c", &x, &y, &acao);

  }
  //Valida a entrada do jogador e se não for valida, digita novamente
  int validaentrada(){

      if(x>=0 && x<10 && y<9 && y>=0 && (acao=='b' || acao=='r')){
        //printf("\nvalido \n");
        return 1;
      }
      else {
        printf("\nInvalido, digite novamente\n");
        return 2;
      }

  }
  //preenche o comando do usuario na matriz espelho
  int revelar(char espelho[9][10], int gabarito[9][10]){

    if(acao=='b'){
      espelho[y][x]='b';
      contador--;
      printf("\ntem %d bombas\n\n",contador);
      for(int i=0;i<9;i++){
          for(int j=0;j<10;j++){
            printf("%c ", espelho[i][j]);
          }
        printf("\n");
      }
    }
    if(acao=='r'){
      printf("\ntem %d bombas\n\n",contador);

      if(gabarito[y][x]==1){
        espelho[y][x]='1';
      }
      if(gabarito[y][x]==2){
        espelho[y][x]='2';
      }
      if(gabarito[y][x]==3){
        espelho[y][x]='3';
      }
      if(gabarito[y][x]==4){
        espelho[y][x]='4';
      }
      if(gabarito[y][x]==5){
        espelho[y][x]='5';
      }
      if(gabarito[y][x]==6){
        espelho[y][x]='6';
      }
      if(gabarito[y][x]==7){
        espelho[y][x]='7';
      }
      if(gabarito[y][x]==8){
        espelho[y][x]='8';
      }
      if(gabarito[y][x]==9){
        espelho[y][x]='9';

        printf("\nBomba !!, Game Over\n");

        for(int i=0;i<9;i++){
          for(int j=0;j<10;j++){
            if(gabarito[i][j]==9){
              printf("b ");
            }
            else{
              printf("%d ", gabarito[i][j]);
            }
          }
          printf("\n");
        }
        return 0;
      }
      
      for(int i=0;i<9;i++){
          for(int j=0;j<10;j++){
            printf("%c ", espelho[i][j]);
          }
        printf("\n");
      }
    }
    return 1; 
  }

/*
Parte de validação da dificuladade escolhida
*/
  int dificuldade;

  int validadificuldade(int dificuldade){
    if(dificuldade==1 || dificuldade==2 || dificuldade==3){
      return 1;
    }
    else{ 
      return 0;
    }
  }

  void escolhedificuldade(){
    printf("\nEscolha o nível de dificuldade:\n\n1-Fácil\n2-Médio\n3-Difícil\n\nDigite 1, 2 ou 3:\n");
      scanf("%d",&dificuldade);
      int c;
      c= validadificuldade(dificuldade);
      //printf("%d",c);
      if(c==0){
        while(c==0){
          printf("inválido, digite novamente:\n");
          scanf("%d",&dificuldade);
          c= validadificuldade(dificuldade);
        }
      }
      ndificuldade=dificuldade;
  }


int main(void) {



/*
Interação e tela inicial de interação com o usuário
*/
  char opcao;

  printf ("Bem vindo ao campo minado !!!\n\n");

    printf("Voce sabe jogar campo minado?\n");
    printf("Digite 's' para sim e 'n' nao\n");

  scanf("%c", &opcao);
  while(opcao != 110 && opcao != 115){
  printf("Sua opcao digitada foi invalida, digite novamente:\n");
  scanf(" %c", &opcao);
  }
  if (opcao == 's'){
    escolhedificuldade();
  }
  else if (opcao == 'n'){
    printf("   Instruções:   \n\n");

    printf ("\nA partir de um campo preenchido com hashtag(#), o jogador deverá escolher posições.\n  Em cada posição existe um elemento que pode variar entre bomba, número ou vazio.\n\n    Bomba:\nSe a posição que o jogador escolher for uma bomba, o jogo é encerrado e ele perde.\n\n    Número:\nSe a posição escolhida for um número diferente de 0, significa que existem o numero que apareceu de bombas adjacentes à posição escolhida. Exemplo:se o número for 2, indica que existem 2 bombas adjacentes a essa posição.\n\n    Vazio:\nCaso o que apareça na posição seja o número zero, indica que não existe nenhuma bomba adjacente aquela posição.\n\n O jogador vence quando consegue limpar todas as posições sem revelar nenhuma bomba.\n\n");

    printf("\n\n   Comandos:   \n\n");

    printf("Para escolher a posição desejada e a opção desejada(revelar a posição(r) ou marcar como bomba(b)),\npreencha as coordenadas da posição escolhida, sendo o primeiro número a coordenada em x(entre 0 e 9), o segundo a posição em y(entre 0 e 8) e a letra referente a ação escolhida('r' ou 'b').\n\n");

    printf("\n\n   Dificuldades:   \n\n");

    printf("Para jogar, existem 3 níveis de dificuldade difirentes.A principal diferença entre os níveis será a quantidade de bombas que será sorteada dentro do campo\n\n    Fácil:\nNo nível fácil, serão sorteadas de 15 a 20 bombas\n\n    Médio:\nNo nível médio, serão sorteadas de 20 a 25 bombas\n\n    Difícil:\nNo nível difícil, serão sorteadas de 25 a 30 bombas\n\n\n\n");

    printf("Vamos começar ?\n");
    escolhedificuldade();



  }

/*
Declaração das variáveis
*/
  int gabarito[9][10];
  int m=10;
  int n=9;
  int cont =0;
  char espelho[9][10];



/*
Parte de preenchimento
*/
  matrizinicial(gabarito, n, m);
  sorteiobombas();
  //mostrastruct();
  //printf("\n");
  bombanamatriz(gabarito);
  completamatriz(gabarito);
        
        for(int i=0;i<n;i++){
          for(int j=0;j<m;j++){
            //printf("%d ", gabarito[i][j]);
            if(gabarito[i][j]==9){
              cont++;
            }
          }
            //printf("\n");
        }
          printf("\ntem %d bombas\n\n", contador);

/*
Parte de leitura
*/
  
    espelhoinicial(espelho);
    

    lerentrada();
  while(revelar(espelho,gabarito)!=0){

    lerentrada();      
    while(validaentrada() ==2){
    lerentrada();
    }

    /*
    int c;
    c=revelar(espelho,gabarito);
    if(c==0){
      return 0;
    }
    */

  }



/*
Finalização
*/
  printf("O jogo acabou !\n\n");
  printf("Obrigado por jogar o Campo Minado ! ! !\n\n");
//
  return 0;
}
