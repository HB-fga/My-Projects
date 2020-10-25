#include <stdio.h>

int main() {
	
	char a='x', br='x';
	int key=0, scrm=0, rk=1;
	long int t=0;
	
	//	0
	printf("Voce acaba de acordar em uma prisao\n");
	scanf("%c", &br);
	printf("O ambiente esta muito escuro\n");
	scanf("%c", &br);
	printf("Uma goteira pinga algumas vezes dentro da sua camiseta suja\n");
	scanf("%c", &br);
	printf("Sua cabeca doi\n");
	scanf("%c", &br);
	printf("Tudo esta muito umido\n");
	scanf("%c", &br);
	printf("Tudo esta muito sujo\n");
	scanf("%c", &br);
	printf("Tudo esta muito quieto\n");
	scanf("%c", &br);
	printf("Voce observa com cuidado os seus arredores\n");
	scanf("%c", &br);
	printf("Voce esta em uma pequena cela com apenas uma porta e uma sutil abertura no teto\n");
	scanf("%c", &br);
	printf("A escuridao te impede de enxergar atraves da sutil abertura\n");
	scanf("%c", &br);
	printf("A porta esta apenas encostada logo a sua frente\n");
	scanf("%c", &br);
	printf("Qual eh o seu instinto?\n[A]-Abrir a porta\n[E]-Esperar\n[G]-Gritar\n\n");
	scanf(" %c", &a);
	//	0.1
	if (a == 'E')
	{
		a='x';
		scanf("%c", &br);
		printf("Por quantos minutos voce espera?\n");
		scanf("%ld", &t);
		if (t < 60)
		{
			t=0;
			scanf("%c", &br);
			printf("Voce espera sentado, mas nada de relevante acontece\n");
			scanf("%c", &br);
			printf("Qual eh o seu instinto?\n[A]-Abrir a porta\n[G]-Gritar\n");
			scanf(" %c", &a);
		}
		else if ((t >= 60) && (t < 1440))
		{
			t=0;
			scanf("%c", &br);
			printf("Voce espera por um longo periodo de tempo\n");
			scanf("%c", &br);
			printf("Voce esta distraido olhando para um mosquito\n");
			scanf("%c", &br);
			printf("Quando de repente voce escuta um impacto no chao\n");
			scanf("%c", &br);
			printf("No chao voce encontra um pequeno brasao de vidro\n");
			scanf("%c", &br);
			printf("Qual eh o seu instinto?\n[P]-Pegar o brasao\n[D]-Deixar o objeto no chao\n");
			scanf(" %c", &a);
			if (a == 'P')
			{
				a='x';
				key++;
				scanf("%c", &br);
				printf("Voce guarda o objeto em seu bolso\n");
				scanf("%c", &br);
				printf("Qual eh o seu instinto?\n[A]-Abrir a porta\n[G]-Gritar\n");
				scanf(" %c", &a);
			}
			else
			{
				scanf("%c", &br);
				printf("Voce ignora o objeto\n");
				scanf("%c", &br);
				printf("Qual eh o seu instinto?\n[A]-Abrir a porta\n[G]-Gritar\n");
				scanf(" %c", &a);
			}
		}
		else if (t >= 1440 && t < 52560000)
		{
			t=0;
			scanf("%c", &br);
			printf("Voce acabou dormindo de tanto esperar\n");
			scanf("%c", &br);
			printf("Voce comeca a acordar\n");
			a = 'D';
		}
		//	FAIL
		else if (t >= 52560000)
		{
			t=0;
			scanf("%c", &br);
			printf("Voce morreu de velhice\n");
		}
	}
	//	0.2
	if (a == 'G')
	{
		a='x';
		scrm++;
		scanf("%c", &br);
		printf("Voce grita com todas as suas forcas, mas ninguem responde\n");
		scanf("%c", &br);
		printf("De repente voce eh dominado pelo medo de que algo ou alguem mal intencionado siga o som dos seus recentes gritos\n");
		scanf("%c", &br);
		printf("Sem muitas opcoes, voce acaba passando pela porta aberta em sua frente\n");
		a='A';
	}
	
	//	1
	if (a == 'A')
	{
		a='x';
		scanf("%c", &br);
		printf("Voce sai de sua cela\n");
		scanf("%c", &br);
		printf("Voce esta no meio de um longo corredor de celas\n");
		scanf("%c", &br);
		printf("Voce percebe uma forte luz avermelhada a sua direita\n");
		scanf("%c", &br);
		printf("Voce certamente se encontra em uma situacao tenebrosa\n");
		scanf("%c", &br);
		printf("Mas voce nao pode simplesmente ficar parado ai\n");
		scanf("%c", &br);
		printf("Qual eh o seu instinto?\n[E]-Seguir pela esquerda\n[O]-Observar os arredores\n[D]-Investigar a iluminacao\n");
		scanf(" %c", &a);
	}
		//	1.1
		if (a == 'O')
		{
			a='x';
			scanf("%c", &br);
			printf("Voce observa o cenario\n");
			scanf("%c", &br);
			printf("A atmosfera nao eh muito diferente da cela em que voce acordou\n");
			scanf("%c", &br);
			printf("Lodo esta crescendo pelas paredes\n");
			scanf("%c", &br);
			printf("O lugar inteiro cheira a mofo\n");
			scanf("%c", &br);
			printf("Voce eh capaz de perceber manchas vermelhas pelas paredes\n");
			scanf("%c", &br);
			printf("Voce reza para que as mesmas sejam fruto de algum processo de oxidacao...\n");
			scanf("%c", &br);
			printf("Entre duas celas voce percebe uma rachadura na parede\n");
			scanf("%c", &br);
			printf("Qual eh o seu instinto?\n[A]-Acertar a rachadura com uma pedra\n[I]-Ignorar a Rachadura\n");
			scanf(" %c", &a);
			if (a == 'A')
			{
				a='x';
				while (rk <= 55)
				{
					scanf("%c", &br);
					printf("Voce acerta a rachadura, mas nada acontece\n");
					scanf("%c", &br);
					printf("Qual eh o seu instinto?\n[T]-Tentar de novo\n[D]-Desistir\n");
					scanf(" %c", &a);
					if (a == 'T')
					{
						a = 'x';
						rk++;
						if ((rk > 20) && (scrm == 1))
						{
							a = 'x';
							scanf("%c", &br);
							printf("Voce tem um mau pressentimento\n");
							scanf("%c", &br);
							printf("Algo parece ter escutado as batidas\n");
							scanf("%c", &br);
							printf("Uma forma humana comeca a se aproximar\n");
							scanf("%c", &br);
							printf("Voce esta paralisado de medo\n");
							scanf("%c", &br);
							printf("Voce percebe que estava muito enganado\n");
							scanf("%c", &br);
							printf("Aquilo nao e humano\n");
							scanf("%c", &br);
							printf("O rosto deles parece derreter lentamente quando voce encara eles nos olhos\n");
							scanf("%c", &br);
							printf("Em um rapido e bruto movimento ele te agarra pelos ombros e suspende voce no ar\n");
							scanf("%c", &br);
							printf("Qual eh o seu instinto?\n[C]-Chutar a Virilha\n[N]-Nao fazer nada\n");
							scanf(" %c", &a);
							if (a == 'C')
							{
								a = 'x';
								scanf("%c", &br);
								printf("Voce chuta a criatura entre as pernas com toda a sua forca\n");
								scanf("%c", &br);
								printf("Ela te larga e rola no chao agonizando de dor\n");
								scanf("%c", &br);
								printf("Voce aproveita a fraqueza do inimigo para realizar uma retirada estrategica\n");
								scanf("%c", &br);
								printf("Voce corre por alguns minutos\n");
								a = 'E';
								rk = 60;
							}
							//	FAIL
							else if (a == 'N')
							{
								a = 'x';
								scanf("%c", &br);
								printf("Mais criaturas comecam a aparecer\n");
								scanf("%c", &br);
								printf("Voce esta cercado de horrores\n");
								scanf("%c", &br);
								printf("A situacao eh extremamente desesperadora\n");
								scanf("%c", &br);
								printf("Seu peito comeca a doer\n");
								scanf("%c", &br);
								printf("Voce nao se sente nada bem\n");
								scanf("%c", &br);
								printf("Voce esta tendo um ataque cardiaco\n");
								scanf("%c", &br);
								printf("Voce\n");
								scanf("%c", &br);
								printf("Morreu\n");
								rk = 60;
							}
						}
						else if (rk > 49)
						{
							a = 'W';
							rk = 60;
						}
					}
					if (a == 'D')
					{
						a = 'I';
						rk = 60;
					}
				}
			//	ALT
			if (a == 'W')
			{
				a='x';
				scanf("%c", &br);
				printf("Apos inumeros golpes na rachadura...\n");
				scanf("%c", &br);
				printf("Voce acaba derrubando a parede inteira!\n");
				scanf("%c", &br);
				printf("Com boa parte da estrutura em ruinas voce percebe que se encontra em um set de filmagem\n");
				scanf("%c", &br);
				printf("Um funcionario magrelo usando bone se aproxima e comeca a falar\n");
				scanf("%c", &br);
				printf("'Caramba cara! Olha o estrago que voce fez! Sabe que vao descontar isso do seu salario ne? Meus pesames parceiro.'\n");
				scanf("%c", &br);
				printf("Voce finalmente se lembra!\n");
				scanf("%c", &br);
				printf("Voce esta no meio do set de filmagem do mais aguardado filme de terror da atualidade\n");
				scanf("%c", &br);
				printf("'Fuga da prisao assombrada 4: O carcere maldito'\n");
				scanf("%c", &br);
				printf("E voce eh o protagonista!\n");
				scanf("%c", &br);
				printf("Voce\n");
				scanf("%c", &br);
				printf("Venceu!\n");
				scanf("%c", &br);
				printf("###PARABENS###\n");
			}
			}
			if (a == 'I')
			{
				a='x';
				scanf("%c", &br);
				printf("Qual eh o seu instinto?\n[E]-Seguir pela esquerda\n[D]-Investigar a iluminacao\n");
				scanf(" %c", &a);
			}
		}
		//	1.2
		if (a == 'D')
		{
			a='x';
			scanf("%c", &br);
			printf("Voce avista uma fogueira e algumas formas humanoides envolta da mesma\n");
			scanf("%c", &br);
			printf("Voce nao consegue entender muito bem a ocasiao\n");
			scanf("%c", &br);
			printf("Qual eh o seu instinto?\n[A]-Se aproximar e tentar contato\n[C]-Correr para o lado contrario\n");
			scanf(" %c", &a);
			//	FAIL
			if (a == 'A')
			{
				a='x';
				scanf("%c", &br);
				printf("Voce se aproxima\n");
				scanf("%c", &br);
				printf("Voce tenta fazer contato\n");
				scanf("%c", &br);
				printf("Voce finalmente percebe que aqueles seres nao sao humanos\n");
				scanf("%c", &br);
				printf("O rosto deles parece derreter lentamente quando voce encara eles nos olhos\n");
				scanf("%c", &br);
				printf("Eles nao sao amigaveis\n");
				scanf("%c", &br);
				printf("Eles avancam em voce\n");
				scanf("%c", &br);
				printf("Seu peito comeca a doer\n");
				scanf("%c", &br);
				printf("Voce nao se sente nada bem\n");
				scanf("%c", &br);
				printf("Voce esta tendo um ataque cardiaco\n");
				scanf("%c", &br);
				printf("Voce\n");
				scanf("%c", &br);
				printf("Morreu\n");
			}
			else if (a == 'C')
			{
				a='x';
				scanf("%c", &br);
				printf("Voce corre feito louco\n");
				a='E';
			}
		}
		//	2
		if (a == 'E')
		{
			a='x';
			scanf("%c", &br);
			printf("O ambiente comeca a esclarecer um pouco!\n");
			scanf("%c", &br);
			printf("Voce consegue enxergar uma saida!\n");
			scanf("%c", &br);
			printf("Proximo a saida voce ve um pequeno bau de vidro em cima de alguns escombros\n");
			scanf("%c", &br);
			printf("Qual eh o seu instinto?\n[T]-Tentar abrir o bau\n[D]-Dar o fora!\n");
			scanf(" %c", &a);
			//	FAIL
			if (a == 'D')
			{
				a='x';
				scanf("%c", &br);
				printf("Tomado pela euforia e esperanca de sair daquele lugar voce corre em direcao a saida\n");
				scanf("%c", &br);
				printf("Por um simples descuido voce acaba acidentalmente tropecando nos escombros e caindo de cabeca no chao\n");
				scanf("%c", &br);
				printf("Voce nao resiste a queda\n");
				scanf("%c", &br);
				printf("Voce\n");
				scanf("%c", &br);
				printf("Morreu\n");
			}
			if (a == 'T')
			{
				a='x';
				//	WIN
				if (key == 1)
				{
					scanf("%c", &br);
					printf("Voce percebe que o brasao se encaixa perfeitamente na fechadura do bau\n");
					scanf("%c", &br);
					printf("Voce abre o bau cheio de esperanca\n");
					scanf("%c", &br);
					printf("E dentro do bau voce encontra\n");
					scanf("%c", &br);
					scanf("%c", &br);
					scanf("%c", &br);
					printf("Absolutamente nada...\n");
					scanf("%c", &br);
					printf("Chateado pela ausencia de espolios voce lentamente caminha para fora da prisao\n");
					scanf("%c", &br);
					printf("Voce\n");
					scanf("%c", &br);
					printf("Venceu!\n");
					scanf("%c", &br);
					printf("###PARABENS###\n");
				}
				//	FAIL
				else
				{
					scanf("%c", &br);
					printf("Voce nao tem a chave\n");
					scanf("%c", &br);
					printf("Voce eh tomado pela frustracao\n");
					scanf("%c", &br);
					printf("Em um momento de furia e descuido voce acerta a parede e uma pedra cai em sua cabeca!\n");
					scanf("%c", &br);
					printf("Voce\n");
					scanf("%c", &br);
					printf("Morreu\n");
				}
			}
		}

	return 0;
}
