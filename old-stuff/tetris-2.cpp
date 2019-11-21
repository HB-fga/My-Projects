#include <stdio.h>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

void big_score(int x) {

	string scr = to_string(x);
	for(int j = 0;j<16;j++)
	{
		switch (j)
		{
			case 0:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"     000000000       ";
							break;
						case '1':
							cout<<"  1111111     ";
							break;
						case '2':
							cout<<" 222222222222222      ";
							break;
						case '3':
							cout<<" 333333333333333     ";
							break;
						case '4':
							cout<<"       444444444    ";
							break;
						case '5':
							cout<<"555555555555555555   ";
							break;
						case '6':
							cout<<"        66666666     ";
							break;
						case '7':
							cout<<"77777777777777777777  ";
							break;
						case '8':
							cout<<"     888888888       ";
							break;
						case '9':
							cout<<"     999999999       ";
							break;
					}
				}
				break;
			case 1:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"   00:::::::::00     ";
							break;
						case '1':
							cout<<"  1111111     ";
							break;
						case '2':
							cout<<"2:::::::::::::::22    ";
							break;
						case '3':
							cout<<"3:::::::::::::::33   ";
							break;
						case '4':
							cout<<"      4::::::::4    ";
							break;
						case '5':
							cout<<"5::::::::::::::::5   ";
							break;
						case '6':
							cout<<"       6::::::6      ";
							break;
						case '7':
							cout<<"7::::::::::::::::::7  ";
							break;
						case '8':
							cout<<"   88:::::::::88     ";
							break;
						case '9':
							cout<<"   99:::::::::99     ";
							break;
					}
				}
				break;
			case 2:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<" 00:::::::::::::00   ";
							break;
						case '1':
							cout<<"1:::::::1     ";
							break;
						case '2':
							cout<<"2::::::222222:::::2   ";
							break;
						case '3':
							cout<<"3::::::33333::::::3  ";
							break;
						case '4':
							cout<<"     4:::::::::4    ";
							break;
						case '5':
							cout<<"5::::::::::::::::5   ";
							break;
						case '6':
							cout<<"      6::::::6       ";
							break;
						case '7':
							cout<<"7::::::::::::::::::7  ";
							break;
						case '8':
							cout<<" 88:::::::::::::88   ";
							break;
						case '9':
							cout<<" 99:::::::::::::99   ";
							break;
					}
				}
				break;
			case 3:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0:::::::000:::::::0  ";
							break;
						case '1':
							cout<<"111:::::1     ";
							break;
						case '2':
							cout<<"2222222     2:::::2   ";
							break;
						case '3':
							cout<<"3333333     3:::::3  ";
							break;
						case '4':
							cout<<"    4::::44::::4    ";
							break;
						case '5':
							cout<<"5:::::555555555555   ";
							break;
						case '6':
							cout<<"     6::::::6        ";
							break;
						case '7':
							cout<<"777777777777:::::::7  ";
							break;
						case '8':
							cout<<"8::::::88888::::::8  ";
							break;
						case '9':
							cout<<"9::::::99999::::::9  ";
							break;
					}
				}
				break;
			case 4:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0::::::0   0::::::0  ";
							break;
						case '1':
							cout<<"   1::::1     ";
							break;
						case '2':
							cout<<"            2:::::2   ";
							break;
						case '3':
							cout<<"            3:::::3  ";
							break;
						case '4':
							cout<<"   4::::4 4::::4    ";
							break;
						case '5':
							cout<<"5:::::5              ";
							break;
						case '6':
							cout<<"    6::::::6         ";
							break;
						case '7':
							cout<<"           7::::::7   ";
							break;
						case '8':
							cout<<"8:::::8     8:::::8  ";
							break;
						case '9':
							cout<<"9:::::9     9:::::9  ";
							break;
					}
				}
				break;
			case 5:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0:::::0     0:::::0  ";
							break;
						case '1':
							cout<<"   1::::1     ";
							break;
						case '2':
							cout<<"            2:::::2   ";
							break;
						case '3':
							cout<<"            3:::::3  ";
							break;
						case '4':
							cout<<"  4::::4  4::::4    ";
							break;
						case '5':
							cout<<"5:::::5              ";
							break;
						case '6':
							cout<<"   6::::::6          ";
							break;
						case '7':
							cout<<"          7::::::7    ";
							break;
						case '8':
							cout<<"8:::::8     8:::::8  ";
							break;
						case '9':
							cout<<"9:::::9     9:::::9  ";
							break;
					}
				}
				break;
			case 6:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0:::::0     0:::::0  ";
							break;
						case '1':
							cout<<"   1::::1     ";
							break;
						case '2':
							cout<<"         2222::::2    ";
							break;
						case '3':
							cout<<"    33333333:::::3   ";
							break;
						case '4':
							cout<<" 4::::4   4::::4    ";
							break;
						case '5':
							cout<<"5:::::5555555555     ";
							break;
						case '6':
							cout<<"  6::::::6           ";
							break;
						case '7':
							cout<<"         7::::::7     ";
							break;
						case '8':
							cout<<" 8:::::88888:::::8   ";
							break;
						case '9':
							cout<<" 9:::::99999::::::9  ";
							break;
					}
				}
				break;
			case 7:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0:::::0     0:::::0  ";
							break;
						case '1':
							cout<<"   1::::1     ";
							break;
						case '2':
							cout<<"    22222::::::22     ";
							break;
						case '3':
							cout<<"    3:::::::::::3    ";
							break;
						case '4':
							cout<<"4::::444444::::444  ";
							break;
						case '5':
							cout<<"5:::::::::::::::5    ";
							break;
						case '6':
							cout<<" 6::::::::66666      ";
							break;
						case '7':
							cout<<"        7::::::7      ";
							break;
						case '8':
							cout<<"  8:::::::::::::8    ";
							break;
						case '9':
							cout<<"  99::::::::::::::9  ";
							break;
					}
				}
				break;
			case 8:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0:::::0     0:::::0  ";
							break;
						case '1':
							cout<<"   1::::1     ";
							break;
						case '2':
							cout<<"  22::::::::222       ";
							break;
						case '3':
							cout<<"    33333333:::::3   ";
							break;
						case '4':
							cout<<"4::::::::::::::::4  ";
							break;
						case '5':
							cout<<"555555555555:::::5   ";
							break;
						case '6':
							cout<<"6::::::::::::::66    ";
							break;
						case '7':
							cout<<"       7::::::7       ";
							break;
						case '8':
							cout<<" 8:::::88888:::::8   ";
							break;
						case '9':
							cout<<"    99999::::::::9   ";
							break;
					}
				}
				break;
			case 9:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0:::::0     0:::::0  ";
							break;
						case '1':
							cout<<"   1::::1     ";
							break;
						case '2':
							cout<<" 2:::::22222          ";
							break;
						case '3':
							cout<<"            3:::::3  ";
							break;
						case '4':
							cout<<"4444444444:::::444  ";
							break;
						case '5':
							cout<<"            5:::::5  ";
							break;
						case '6':
							cout<<"6::::::66666:::::6   ";
							break;
						case '7':
							cout<<"      7::::::7        ";
							break;
						case '8':
							cout<<"8:::::8     8:::::8  ";
							break;
						case '9':
							cout<<"         9::::::9    ";
							break;
					}
				}
				break;
			case 10:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0:::::0     0:::::0  ";
							break;
						case '1':
							cout<<"   1::::1     ";
							break;
						case '2':
							cout<<"2:::::2               ";
							break;
						case '3':
							cout<<"            3:::::3  ";
							break;
						case '4':
							cout<<"          4::::4    ";
							break;
						case '5':
							cout<<"            5:::::5  ";
							break;
						case '6':
							cout<<"6:::::6     6:::::6  ";
							break;
						case '7':
							cout<<"     7::::::7         ";
							break;
						case '8':
							cout<<"8:::::8     8:::::8  ";
							break;
						case '9':
							cout<<"        9::::::9     ";
							break;
					}
				}
				break;
			case 11:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0::::::0   0::::::0  ";
							break;
						case '1':
							cout<<"   1::::1     ";
							break;
						case '2':
							cout<<"2:::::2               ";
							break;
						case '3':
							cout<<"            3:::::3  ";
							break;
						case '4':
							cout<<"          4::::4    ";
							break;
						case '5':
							cout<<"5555555     5:::::5  ";
							break;
						case '6':
							cout<<"6:::::6     6:::::6  ";
							break;
						case '7':
							cout<<"    7::::::7          ";
							break;
						case '8':
							cout<<"8:::::8     8:::::8  ";
							break;
						case '9':
							cout<<"       9::::::9      ";
							break;
					}
				}
				break;
			case 12:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"0:::::::000:::::::0  ";
							break;
						case '1':
							cout<<"111::::::111  ";
							break;
						case '2':
							cout<<"2:::::2       222222  ";
							break;
						case '3':
							cout<<"3333333     3:::::3  ";
							break;
						case '4':
							cout<<"          4::::4    ";
							break;
						case '5':
							cout<<"5::::::55555::::::5  ";
							break;
						case '6':
							cout<<"6::::::66666::::::6  ";
							break;
						case '7':
							cout<<"   7::::::7           ";
							break;
						case '8':
							cout<<"8::::::88888::::::8  ";
							break;
						case '9':
							cout<<"      9::::::9       ";
							break;
					}
				}
				break;
			case 13:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<" 00:::::::::::::00   ";
							break;
						case '1':
							cout<<"1::::::::::1  ";
							break;
						case '2':
							cout<<"2::::::2222222:::::2  ";
							break;
						case '3':
							cout<<"3::::::33333::::::3  ";
							break;
						case '4':
							cout<<"        44::::::44  ";
							break;
						case '5':
							cout<<" 55:::::::::::::55   ";
							break;
						case '6':
							cout<<" 66:::::::::::::66   ";
							break;
						case '7':
							cout<<"  7::::::7            ";
							break;
						case '8':
							cout<<" 88:::::::::::::88   ";
							break;
						case '9':
							cout<<"     9::::::9        ";
							break;
					}
				}
				break;
			case 14:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"   00:::::::::00     ";
							break;
						case '1':
							cout<<"1::::::::::1  ";
							break;
						case '2':
							cout<<"2::::::::::::::::::2  ";
							break;
						case '3':
							cout<<"3:::::::::::::::33   ";
							break;
						case '4':
							cout<<"        4::::::::4  ";
							break;
						case '5':
							cout<<"   55:::::::::55     ";
							break;
						case '6':
							cout<<"   66:::::::::66     ";
							break;
						case '7':
							cout<<" 7::::::7             ";
							break;
						case '8':
							cout<<"   88:::::::::88     ";
							break;
						case '9':
							cout<<"    9::::::9         ";
							break;
					}
				}
				break;
			case 15:
				for(int i=0;i<scr.size();i++)
				{
					switch(scr[i])
					{
						case '0':
							cout<<"     000000000       ";
							break;
						case '1':
							cout<<"111111111111  ";
							break;
						case '2':
							cout<<"22222222222222222222  ";
							break;
						case '3':
							cout<<" 333333333333333     ";
							break;
						case '4':
							cout<<"        4::::::::4  ";
							break;
						case '5':
							cout<<"     555555555       ";
							break;
						case '6':
							cout<<"     666666666       ";
							break;
						case '7':
							cout<<"77777777              ";
							break;
						case '8':
							cout<<"     888888888       ";
							break;
						case '9':
							cout<<"   99999999          ";
							break;
					}
				}
				break;
		}
		cout<<endl;
	}
}

int main() {
	
	char direction='.';
	long long int score=0;
	int board[20][10];
	int cycle=0, next=0, check=0, rot=0;
	int pl1=0, pl2=0, pl3=0, pl4=0;
	int pc1=0, pc2=0, pc3=0, pc4=0;
	
	system("tput reset");

	//Title Screen
	printf("\n					TTTTTTTTTTTTTTTTTTTTTTT                         tttt                              iiii                   \n					T:::::::::::::::::::::T                      ttt:::t                             i::::i                  \n					T:::::::::::::::::::::T                      t:::::t                              iiii                   \n					T:::::TT:::::::TT:::::T                      t:::::t                                                     \n					TTTTTT  T:::::T  TTTTTTeeeeeeeeeeee    ttttttt:::::ttttttt   rrrrr   rrrrrrrrr  iiiiiii     ssssssssss   \n					        T:::::T      ee::::::::::::ee  t:::::::::::::::::t   r::::rrr:::::::::r i:::::i   ss::::::::::s  \n					        T:::::T     e::::::eeeee:::::eet:::::::::::::::::t   r:::::::::::::::::r i::::i ss:::::::::::::s \n					        T:::::T    e::::::e     e:::::etttttt:::::::tttttt   rr::::::rrrrr::::::ri::::i s::::::ssss:::::s\n					        T:::::T    e:::::::eeeee::::::e      t:::::t          r:::::r     r:::::ri::::i  s:::::s  ssssss \n					        T:::::T    e:::::::::::::::::e       t:::::t          r:::::r     rrrrrrri::::i    s::::::s      \n					        T:::::T    e::::::eeeeeeeeeee        t:::::t          r:::::r            i::::i       s::::::s   \n					        T:::::T    e:::::::e                 t:::::t    ttttttr:::::r            i::::i ssssss   s:::::s \n					      TT:::::::TT  e::::::::e                t::::::tttt:::::tr:::::r           i::::::is:::::ssss::::::s\n					      T:::::::::T   e::::::::eeeeeeee        tt::::::::::::::tr:::::r           i::::::is::::::::::::::s \n					      T:::::::::T    ee:::::::::::::e          tt:::::::::::ttr:::::r           i::::::i s:::::::::::ss  \n					      TTTTTTTTTTT      eeeeeeeeeeeeee            ttttttttttt  rrrrrrr           iiiiiiii  sssssssssss    \n");
	
	printf("\n						`a` = Move a peca para a esquerda                       `d` = Move a peca para a direita\n");
	printf("						`s` = Move a peca para baixo                            `w` = Gira a peca\n\n");
	printf("										PRESSIONE ENTER PARA JOGAR!\n");
	
	scanf("%*c");
	system("tput reset");
	
	while(1)
	{
	
		for(int i=0;i<20;i++)
		{ //spawn board
			for(int j=0;j<10;j++)
			{
				board[i][j]=0;
			}
		}
		
		direction='.';
		
		cycle=0;
		next=0;
		check=0;
		rot=0;
		
		pl1=0;
		pl2=0;
		pl3=0;
		pl4=0;
		
		pc1=0;
		pc2=0;
		pc3=0;
		pc4=0;
		
		score=0;
		
		while(1)
		{
			if(cycle==0)
			{ //spawn square
				pl1=0;
				pl2=1;
				pl3=0;
				pl4=0;
				
				pc1=4;
				pc2=5;
				pc3=0;
				pc4=0;
				
				if(board[pl1][pc1]!=0 || board[pl1][pc2]!=0 || board[pl2][pc1]!=0 || board[pl2][pc2]!=0){break;}
				
				board[pl1][pc1]=1;
				board[pl1][pc2]=1;
				board[pl2][pc1]=1;
				board[pl2][pc2]=1;
				
				cycle++;
			}
			else if(cycle==2)
			{ //spawn s
				rot=0;
				pl1=0;
				pl2=1;
				pl3=0;
				pl4=0;
				
				pc1=3;
				pc2=4;
				pc3=5;
				pc4=0;
				
				if(board[pl1][pc2]!=0 || board[pl1][pc3]!=0 || board[pl2][pc1]!=0 || board[pl2][pc2]!=0){break;}
				
				board[pl1][pc2]=1;
				board[pl1][pc3]=1;
				board[pl2][pc1]=1;
				board[pl2][pc2]=1;
				
				cycle++;
			}
			else if(cycle==4)
			{ //spawn L
				rot=0;
				pl1=0;
				pl2=1;
				pl3=2;
				pl4=0;
				
				pc1=4;
				pc2=5;
				pc3=0;
				pc4=0;
				
				if(board[pl1][pc1]!=0 || board[pl2][pc1]!=0 || board[pl3][pc1]!=0 || board[pl3][pc2]!=0){break;}
				
				board[pl1][pc1]=1;
				board[pl2][pc1]=1;
				board[pl3][pc1]=1;
				board[pl3][pc2]=1;
				
				cycle++;
			}
			else if(cycle==6)
			{ //spawn T
				rot=0;
				pl1=0;
				pl2=1;
				pl3=0;
				pl4=0;
				
				pc1=3;
				pc2=4;
				pc3=5;
				pc4=0;
				
				if(board[pl1][pc1]!=0 || board[pl1][pc2]!=0 || board[pl1][pc3]!=0 || board[pl2][pc2]!=0){break;}
				
				board[pl1][pc1]=1;
				board[pl1][pc2]=1;
				board[pl1][pc3]=1;
				board[pl2][pc2]=1;
				
				cycle++;
			}
			else if(cycle==8)
			{ //spawn |
				rot=0;
				pl1=0;
				pl2=1;
				pl3=2;
				pl4=3;
				
				pc1=4;
				pc2=0;
				pc3=0;
				pc4=0;
				
				if(board[pl1][pc1]!=0 || board[pl2][pc1]!=0 || board[pl3][pc1]!=0 || board[pl4][pc1]!=0){break;}
				
				board[pl1][pc1]=1;
				board[pl2][pc1]=1;
				board[pl3][pc1]=1;
				board[pl4][pc1]=1;
				
				cycle++;
			}
			else if(cycle==10)
			{ //spawn |-
				rot=0;
				pl1=0;
				pl2=1;
				pl3=2;
				pl4=0;
				
				pc1=4;
				pc2=5;
				pc3=0;
				pc4=0;
				
				if(board[pl1][pc1]!=0 || board[pl1][pc2]!=0 || board[pl2][pc1]!=0 || board[pl3][pc1]!=0){break;}
				
				board[pl1][pc1]=1;
				board[pl1][pc2]=1;
				board[pl2][pc1]=1;
				board[pl3][pc1]=1;
				
				cycle++;
			}
			else if(cycle==12)
			{ //spawn z
				rot=0;
				pl1=0;
				pl2=1;
				pl3=0;
				pl4=0;
				
				pc1=3;
				pc2=4;
				pc3=5;
				pc4=0;
				
				if(board[pl1][pc1]!=0 || board[pl1][pc2]!=0 || board[pl2][pc2]!=0 || board[pl2][pc3]!=0){break;}
				
				board[pl1][pc1]=1;
				board[pl1][pc2]=1;
				board[pl2][pc2]=1;
				board[pl2][pc3]=1;
				
				cycle++;
			}
			
			printf("										XXXXXXXXXXXX\n");
			for(int i=0;i<20;i++)
			{ //print board
				printf("										X");
				for(int j=0;j<10;j++)
				{
					if(board[i][j]==0)
					{
						printf(" ");
					}
					else if(board[i][j]==1)
					{
						//char x = (rand()%y)+z
						//cout<<x;
						printf("0");
					}
				}
				printf("X\n");
			}
			printf("										XXXXXXXXXXXX\n");
			
			big_score(score);

			score+=1;

			system("stty raw");
			direction=getchar();
			system("stty cooked");
			
			system("tput reset");
			
			if(direction=='w')
			{ //rotate
				if(cycle==3)
				{ //s - 2
					if(rot==0)
					{
						if((board[pl2][pc2+1]==0) && (board[pl2+1][pc2+1]==0) && (pl2!=19))
						{
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							
							pc3=0;
							pl3=pl2+1;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl3][pc2]=1;
							
							rot++;
						}
					}
					else if(rot==1)
					{
						if((board[pl2][pc2+1]==0) && (board[pl2+1][pc2+1]==0) && (pc2!=9))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl3][pc2]=0;
							
							pc3=pc2+1;
							pl3=0;
							
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							
							rot=0;
						}
					}
				}
				else if(cycle==5)
				{ //L - 4
					if(rot==0)
					{
						if((board[pl2][pc1-1]==0) && (board[pl2][pc1+1]==0) && (board[pl3][pc1-1]==0) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl3][pc1]=0;
							board[pl3][pc2]=0;
							
							pl1=pl1+1;
							pl2=pl2+1;
							pl3=0;
							pc1=pc1-1;
							pc2=pc2-1;
							pc3=pc2+1;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc1]=1;
							
							rot++;
						}
					}
					else if(rot==1)
					{
						if((board[pl1-1][pc1]==0) && (board[pl1-1][pc2]==0) && (board[pl1+1][pc2]==0))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
							
							pl1=pl1-1;
							pl2=pl2-1;
							pl3=pl2+1;
							pc3=0;
														
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl2][pc2]=1;
							board[pl3][pc2]=1;
							
							rot++;
						}
					}
					else if(rot==2)
					{
						if((board[pl1+1][pc1]==0) && (board[pl1][pc2+1]==0) && (board[pl2][pc2+1]==0) && (pc2!=9))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl2][pc2]=0;
							board[pl3][pc2]=0;
							
							pl3=0;
							pc3=pc2+1;
							
							board[pl1][pc3]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							
							rot++;
						}
					}
					else if(rot==3)
					{
						if((board[pl1][pc3-1]==0) && (board[pl2+1][pc2]==0) && (board[pl2+1][pc3]==0) && (pl2!=19))
						{
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pl3=pl2+1;
							pc1=pc2;
							pc2=pc3;
							pc3=0;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl3][pc1]=1;
							board[pl3][pc2]=1;
							
							rot=0;
						}
					}
				}
				else if(cycle==7)
				{ //T - 4
					if(rot==0)
					{
						if(board[pl1-1][pc2]==0)
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc2]=0;
							
							pl1=pl1-1;
							pl2=pl2-1;
							pl3=pl2+1;
							pc3=0;
							
							board[pl1][pc2]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl3][pc2]=1;
							
							rot++;
						}
					}
					else if(rot==1)
					{
						if((board[pl2][pc2+1]==0) && (pc2!=9))
						{
							board[pl1][pc2]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl3][pc2]=0;
							
							pc3=pc2+1;
							pl3=0;
							
							board[pl1][pc2]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							
							rot++;
						}
					}
					else if(rot==2)
					{
						if((board[pl2+1][pc2]==0) && (pl2!=19))
						{
							board[pl1][pc2]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pl3=pl2+1;
							pc1=pc2;
							pc2=pc3;
							pc3=0;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl3][pc1]=1;
							
							rot++;
						}
					}
					else if(rot==3)
					{
						if((board[pl2][pc1-1]==0) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl3][pc1]=0;
							
							pl1=pl2;
							pl2=pl3;
							pl3=0;
							pc1=pc1-1;
							pc2=pc2-1;
							pc3=pc2+1;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc2]=1;
							
							rot=0;
						}
					}
				}
				else if(cycle==9)
				{ // | - 2
					if(rot==0)
					{
						if((board[pl2][pc1+1]==0) && (board[pl2][pc1+2]==0) && (board[pl2][pc1-1]==0) && (pc1<8) && (pc1>0))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl3][pc1]=0;
							board[pl4][pc1]=0;
							
							pl1=0;
							pl3=0;
							pl4=0;
							
							pc1-=1;
							pc2=pc1+1;
							pc3=pc1+2;
							pc4=pc1+3;
							
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							board[pl2][pc4]=1;
							
							rot++;
						}
					}
					else if(rot==1)
					{
						if((board[pl2-1][pc2]==0) && (board[pl2+1][pc2]==0) && (board[pl2+2][pc2]==0) && (pl2<18))
						{
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							board[pl2][pc4]=0;
							
							pc1=pc2;
							pc2=0;
							pc3=0;
							pc4=0;
							
							pl1=pl2-1;
							pl3=pl2+1;
							pl4=pl2+2;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl3][pc1]=1;
							board[pl4][pc1]=1;
							
							rot=0;
						}
					}
				}
				else if(cycle==11)
				{ // |- - 4
					if(rot==0)
					{
						if((board[pl2][pc1-1]==0) && (board[pl2][pc1+1]==0) && (board[pl3][pc1+1]==0) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl2][pc1]=0;
							board[pl3][pc1]=0;
							
							pl1=pl2;
							pl2=pl3;
							pl3=0;
							pc1=pc1-1;
							pc2=pc2-1;
							pc3=pc2+1;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc3]=1;
							
							rot++;
						}
					}
					else if(rot==1)
					{
						if((board[pl1+1][pc1]==0) && (board[pl1+1][pc2]==0) && (board[pl1-1][pc2]==0))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc3]=0;
							
							pl1=pl1-1;
							pl2=pl2-1;
							pl3=pl2+1;
							pc3=0;
							
							board[pl1][pc2]=1;
							board[pl2][pc2]=1;
							board[pl3][pc1]=1;
							board[pl3][pc2]=1;
							
							rot++;
						}
					}
					else if(rot==2)
					{
						if((board[pl1][pc2-1]==0) && (board[pl2][pc2-1]==0) && (board[pl2][pc2+1]==0) && (pc2!=9))
						{
							board[pl1][pc2]=0;
							board[pl2][pc2]=0;
							board[pl3][pc1]=0;
							board[pl3][pc2]=0;
							
							pl3=0;
							pc3=pc2+1;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							
							rot++;
						}
					}
					else if(rot==3)
					{
						if((board[pl2-1][pc2]==0) && (board[pl2-1][pc3]==0) && (board[pl2+1][pc2]==0) && (pl2!=19))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pl3=pl2+1;
							pc1=pc2;
							pc2=pc3;
							pc3=0;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl2][pc1]=1;
							board[pl3][pc1]=1;
							
							rot=0;
						}
					}
				}
				else if(cycle==13)
				{ // z - 2
					if(rot==0)
					{
						if((board[pl2+1][pc2]==0) && (board[pl1][pc3]==0) && (pl2!=19))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pc1=0;
							pl3=pl2+1;
							
							board[pl1][pc3]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							board[pl3][pc2]=1;
							
							rot++;
						}
					}
					else if(rot==1)
					{
						if((board[pl1][pc2]==0) && (board[pl1][pc2-1]==0) && (pc2!=0))
						{
							board[pl1][pc3]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							board[pl3][pc2]=0;
							
							pl3=0;
							pc1=pc2-1;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							
							rot=0;
						}
					}
				}
			}
			else if(direction=='a')
			{ //left
				if(cycle==1)
				{ //square
					if(((board[pl1][pc1-1]==0) && (board[pl2][pc1-1]==0)) && (pc1!=0))
					{
						board[pl1][pc1]=0;
						board[pl1][pc2]=0;
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						
						pc1--;
						pc2--;
						
						board[pl1][pc1]=1;
						board[pl1][pc2]=1;
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
					}
				}
				else if(cycle==3)
				{ //s
					if(rot==0)
					{
						if(((board[pl2][pc1-1]==0) && (board[pl1][pc2-1]==0)) && (pc1!=0))
						{
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							
							pc1--;
							pc2--;
							pc3--;
							
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
						}
					}
					else if(rot==1)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc1-1]==0) && (board[pl3][pc2-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl3][pc2]=0;
							
							pc1--;
							pc2--;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl3][pc2]=1;
						}
					}
				}
				else if(cycle==5)
				{ //L
					if(rot==0)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc1-1]==0) && (board[pl3][pc1-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl3][pc1]=0;
							board[pl3][pc2]=0;
							
							pc1--;
							pc2--;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl3][pc1]=1;
							board[pl3][pc2]=1;
						}
					}
					else if(rot==1)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc1-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
							
							pc1--;
							pc2--;
							pc3--;
							
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
						}
					}
					else if(rot==2)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc2-1]==0) && (board[pl3][pc2-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl2][pc2]=0;
							board[pl3][pc2]=0;
							
							pc1--;
							pc2--;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl2][pc2]=1;
							board[pl3][pc2]=1;
						}
					}
					else if(rot==3)
					{
						if(((board[pl1][pc3-1]==0) && (board[pl2][pc1-1]==0)) && (pc1!=0))
						{
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pc1--;
							pc2--;
							pc3--;
							
							board[pl1][pc3]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
						}
					}
					
				}
				else if(cycle==7)
				{ //T
					if(rot==0)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc2-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc2]=0;
							
							pc1--;
							pc2--;
							pc3--;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc2]=1;
						}
					}
					else if(rot==1)
					{
						if(((board[pl1][pc2-1]==0) && (board[pl2][pc1-1]==0) && (board[pl3][pc2-1]==0)) && (pc1!=0))
						{
							board[pl1][pc2]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl3][pc2]=0;
							
							pc1--;
							pc2--;
							
							board[pl1][pc2]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl3][pc2]=1;
						}
					}
					else if(rot==2)
					{
						if(((board[pl1][pc2-1]==0) && (board[pl2][pc1-1]==0)) && (pc1!=0))
						{
							board[pl1][pc2]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pc1--;
							pc2--;
							pc3--;
							
							board[pl1][pc2]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
						}
					}
					else if(rot==3)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc1-1]==0) && (board[pl3][pc1-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl3][pc1]=0;
							
							pc1--;
							pc2--;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl3][pc1]=1;
						}
					}
				}
				else if(cycle==9)
				{ // |
					if(rot==0)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc1-1]==0) && (board[pl3][pc1-1]==0) && (board[pl4][pc1-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl3][pc1]=0;
							board[pl4][pc1]=0;
							
							pc1--;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl3][pc1]=1;
							board[pl4][pc1]=1;
						}
					}
					else if(rot==1)
					{
						if((board[pl2][pc1-1]==0) && (pc1!=0))
						{
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							board[pl2][pc4]=0;
							
							pc1--;
							pc2--;
							pc3--;
							pc4--;
							
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							board[pl2][pc4]=1;
						}
					}
				}
				else if(cycle==11)
				{ // |-
					if(rot==0)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc1-1]==0) && (board[pl3][pc1-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl2][pc1]=0;
							board[pl3][pc1]=0;
							
							pc1--;
							pc2--;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl2][pc1]=1;
							board[pl3][pc1]=1;
						}
					}
					else if(rot==1)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc3-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc3]=0;
							
							pc1--;
							pc2--;
							pc3--;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc3]=1;
						}
					}
					else if(rot==2)
					{
						if(((board[pl1][pc2-1]==0) && (board[pl2][pc2-1]==0) && (board[pl3][pc1-1]==0)) && (pc1!=0))
						{
							board[pl1][pc2]=0;
							board[pl2][pc2]=0;
							board[pl3][pc1]=0;
							board[pl3][pc2]=0;
							
							pc1--;
							pc2--;
							
							board[pl1][pc2]=1;
							board[pl2][pc2]=1;
							board[pl3][pc1]=1;
							board[pl3][pc2]=1;
						}
					}
					else if(rot==3)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc1-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pc1--;
							pc2--;
							pc3--;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
						}
					}
				}
				else if(cycle==13)
				{ // z
					if(rot==0)
					{
						if(((board[pl1][pc1-1]==0) && (board[pl2][pc2-1]==0)) && (pc1!=0))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pc1--;
							pc2--;
							pc3--;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
						}
					}
					else if(rot==1)
					{
						if((board[pl1][pc3-1]==0) && (board[pl2][pc2-1]==0) && (board[pl3][pc2-1]==0) && (pc2!=0))
						{
							board[pl1][pc3]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							board[pl3][pc2]=0;
							
							pc2--;
							pc3--;
							
							board[pl1][pc3]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							board[pl3][pc2]=1;
						}
					}
				}
			}
			else if(direction=='d')
			{ //right
				if(cycle==1)
				{ //square
					if(((board[pl1][pc2+1]==0) && (board[pl2][pc2+1]==0)) && (pc2!=9))
					{
						board[pl1][pc1]=0;
						board[pl1][pc2]=0;
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						
						pc1++;
						pc2++;
						
						board[pl1][pc1]=1;
						board[pl1][pc2]=1;
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
					}
				}
				else if(cycle==3)
				{ //s
					if(rot==0)
					{
						if(((board[pl1][pc3+1]==0) && (board[pl2][pc2+1]==0)) && (pc3!=9))
						{
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							
							pc1++;
							pc2++;
							pc3++;
							
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
						}
					}
					else if(rot==1)
					{
						if(((board[pl1][pc1+1]==0) && (board[pl2][pc2+1]==0) && (board[pl3][pc2+1]==0)) && (pc2!=9))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl3][pc2]=0;
							
							pc1++;
							pc2++;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl3][pc2]=1;
						}
					}
				}
				else if(cycle==5)
				{ //L
					if(rot==0)
					{
						if(((board[pl1][pc1+1]==0) && (board[pl2][pc1+1]==0) && (board[pl3][pc2+1]==0)) && (pc2!=9))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl3][pc1]=0;
							board[pl3][pc2]=0;
							
							pc1++;
							pc2++;
												
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl3][pc1]=1;
							board[pl3][pc2]=1;
						}
					}
					else if(rot==1)
					{
						if(((board[pl1][pc3+1]==0) && (board[pl2][pc1+1]==0)) && (pc3!=9))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
							
							pc1++;
							pc2++;
							pc3++;
												
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc1]=1;
						}
					}
					else if(rot==2)
					{
						if(((board[pl1][pc2+1]==0) && (board[pl2][pc2+1]==0) && (board[pl3][pc2+1]==0)) && (pc2!=9))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl2][pc2]=0;
							board[pl3][pc2]=0;
							
							pc1++;
							pc2++;
												
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl2][pc2]=1;
							board[pl3][pc2]=1;
						}
					}
					else if(rot==3)
					{
						if(((board[pl1][pc3+1]==0) && (board[pl2][pc3+1]==0)) && (pc3!=9))
						{
							board[pl1][pc3]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pc1++;
							pc2++;
							pc3++;
												
							board[pl1][pc3]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
						}
					}
				}
				else if(cycle==7)
				{ //T
					if(rot==0)
					{
						if(((board[pl1][pc3+1]==0) && (board[pl2][pc2+1]==0)) && (pc3!=9))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc2]=0;
							
							pc1++;
							pc2++;
							pc3++;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc2]=1;
						}
					}
					else if(rot==1)
					{
						if(((board[pl1][pc2+1]==0) && (board[pl2][pc2+1]==0) && (board[pl3][pc2+1]==0)) && (pc2!=9))
						{
							board[pl1][pc2]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl3][pc2]=0;
							
							pc1++;
							pc2++;
							
							board[pl1][pc2]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl3][pc2]=1;
						}
					}
					else if(rot==2)
					{
						if(((board[pl1][pc2+1]==0) && (board[pl2][pc3+1]==0)) && (pc3!=9))
						{
							board[pl1][pc2]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pc1++;
							pc2++;
							pc3++;
							
							board[pl1][pc2]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
						}
					}
					else if(rot==3)
					{
						if(((board[pl1][pc1+1]==0) && (board[pl2][pc2+1]==0) && (board[pl3][pc1+1]==0)) && (pc2!=9))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl3][pc1]=0;
							
							pc1++;
							pc2++;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl3][pc1]=1;
						}
					}
				}
				else if(cycle==9)
				{ // |
					if(rot==0)
					{
						if(((board[pl1][pc1+1]==0) && (board[pl2][pc1+1]==0) && (board[pl3][pc1+1]==0) && (board[pl4][pc1+1]==0)) && (pc1!=9))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl3][pc1]=0;
							board[pl4][pc1]=0;
							
							pc1++;
												
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl3][pc1]=1;
							board[pl4][pc1]=1;
						}
					}
					else if(rot==1)
					{
						if((board[pl2][pc4+1]==0) && (pc4!=9))
						{
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							board[pl2][pc4]=0;
							
							pc1++;
							pc2++;
							pc3++;
							pc4++;
							
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							board[pl2][pc4]=1;
						}
					}
				}
				else if(cycle==11)
				{ // |-
					if(rot==0)
					{
						if(((board[pl1][pc2+1]==0) && (board[pl2][pc1+1]==0) && (board[pl3][pc1+1]==0)) && (pc2!=9))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl2][pc1]=0;
							board[pl3][pc1]=0;
							
							pc1++;
							pc2++;
												
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl2][pc1]=1;
							board[pl3][pc1]=1;
						}
					}
					else if(rot==1)
					{
						if(((board[pl1][pc3+1]==0) && (board[pl2][pc3+1]==0)) && (pc3!=9))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl1][pc3]=0;
							board[pl2][pc3]=0;
							
							pc1++;
							pc2++;
							pc3++;
							
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl1][pc3]=1;
							board[pl2][pc3]=1;
						}
					}
					else if(rot==2)
					{
						if(((board[pl1][pc2+1]==0) && (board[pl2][pc2+1]==0) && (board[pl3][pc2+1]==0)) && (pc2!=9))
						{
							board[pl1][pc2]=0;
							board[pl2][pc2]=0;
							board[pl3][pc1]=0;
							board[pl3][pc2]=0;
							
							pc1++;
							pc2++;
							
							board[pl1][pc2]=1;
							board[pl2][pc2]=1;
							board[pl3][pc1]=1;
							board[pl3][pc2]=1;
						}
					}
					else if(rot==3)
					{
						if(((board[pl1][pc1+1]==0) && (board[pl2][pc3+1]==0)) && (pc3!=9))
						{
							board[pl1][pc1]=0;
							board[pl2][pc1]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pc1++;
							pc2++;
							pc3++;
							
							board[pl1][pc1]=1;
							board[pl2][pc1]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
						}
					}
				}
				else if(cycle==13)
				{ //z
					if(rot==0)
					{
						if(((board[pl1][pc2+1]==0) && (board[pl2][pc3+1]==0)) && (pc3!=9))
						{
							board[pl1][pc1]=0;
							board[pl1][pc2]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							
							pc1++;
							pc2++;
							pc3++;
												
							board[pl1][pc1]=1;
							board[pl1][pc2]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
						}
					}
					else if(rot==1)
					{
						if((board[pl1][pc3+1]==0) && (board[pl2][pc3+1]==0) && (board[pl3][pc2+1]==0) && (pc3!=9))
						{
							board[pl1][pc3]=0;
							board[pl2][pc2]=0;
							board[pl2][pc3]=0;
							board[pl3][pc2]=0;
							
							pc2++;
							pc3++;
							
							board[pl1][pc3]=1;
							board[pl2][pc2]=1;
							board[pl2][pc3]=1;
							board[pl3][pc2]=1;
						}
					}
				}
			}
			
			//drop piece
			if(cycle==1)
			{ //square
				if(((board[pl2+1][pc1]==0) && (board[pl2+1][pc2]==0)) && (pl2!=19))
				{
					board[pl1][pc1]=0;
					board[pl1][pc2]=0;
					board[pl2][pc1]=0;
					board[pl2][pc2]=0;
					
					pl1++;
					pl2++;
					
					board[pl1][pc1]=1;
					board[pl1][pc2]=1;
					board[pl2][pc1]=1;
					board[pl2][pc2]=1;
				}
				else
				{
					next=1;
				}
			}
			else if(cycle==3)
			{ //s
				if(rot==0)
				{
					if(((board[pl2+1][pc1]==0) && (board[pl2+1][pc2]==0) && (board[pl1+1][pc3]==0)) && (pl2!=19))
					{
						board[pl1][pc2]=0;
						board[pl1][pc3]=0;
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						
						pl1++;
						pl2++;
						
						board[pl1][pc2]=1;
						board[pl1][pc3]=1;
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==1)
				{
					if(((board[pl2+1][pc1]==0) && (board[pl3+1][pc2]==0)) && (pl3!=19))
					{
						board[pl1][pc1]=0;
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						board[pl3][pc2]=0;
						
						pl1++;
						pl2++;
						pl3++;
						
						board[pl1][pc1]=1;
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
						board[pl3][pc2]=1;
					}
					else
					{
						next=1;
					}
				}
			}
			else if(cycle==5)
			{ //L
				if(rot==0)
				{
					if(((board[pl3+1][pc1]==0) && (board[pl3+1][pc2]==0)) && (pl3!=19))
					{
						board[pl1][pc1]=0;
						board[pl2][pc1]=0;
						board[pl3][pc1]=0;
						board[pl3][pc2]=0;
						
						pl1++;
						pl2++;
						pl3++;
						
						board[pl1][pc1]=1;
						board[pl2][pc1]=1;
						board[pl3][pc1]=1;
						board[pl3][pc2]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==1)
				{
					if(((board[pl2+1][pc1]==0) && (board[pl1+1][pc2]==0) && (board[pl1+1][pc3]==0)) && (pl2!=19))
					{
						board[pl1][pc1]=0;
						board[pl1][pc2]=0;
						board[pl1][pc3]=0;
						board[pl2][pc1]=0;
						
						pl1++;
						pl2++;
						
						board[pl1][pc1]=1;
						board[pl1][pc2]=1;
						board[pl1][pc3]=1;
						board[pl2][pc1]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==2)
				{
					if(((board[pl1+1][pc1]==0) && (board[pl3+1][pc2]==0)) && (pl3!=19))
					{
						board[pl1][pc1]=0;
						board[pl1][pc2]=0;
						board[pl2][pc2]=0;
						board[pl3][pc2]=0;
						
						pl1++;
						pl2++;
						pl3++;
						
						board[pl1][pc1]=1;
						board[pl1][pc2]=1;
						board[pl2][pc2]=1;
						board[pl3][pc2]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==3)
				{
					if(((board[pl2+1][pc1]==0) && (board[pl2+1][pc2]==0) && (board[pl2+1][pc3]==0)) && (pl2!=19))
					{
						board[pl1][pc3]=0;
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						board[pl2][pc3]=0;
						
						pl1++;
						pl2++;
						
						board[pl1][pc3]=1;
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
						board[pl2][pc3]=1;
					}
					else
					{
						next=1;
					}
				}
			}
			else if(cycle==7)
			{ //T
				if(rot==0)
				{
					if(((board[pl1+1][pc1]==0) && (board[pl1+1][pc3]==0) && (board[pl2+1][pc2]==0)) && (pl2!=19))
					{
						board[pl1][pc1]=0;
						board[pl1][pc2]=0;
						board[pl1][pc3]=0;
						board[pl2][pc2]=0;
						
						pl1++;
						pl2++;
						
						board[pl1][pc1]=1;
						board[pl1][pc2]=1;
						board[pl1][pc3]=1;
						board[pl2][pc2]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==1)
				{
					if(((board[pl2+1][pc1]==0) && (board[pl3+1][pc2]==0)) && (pl3!=19))
					{
						board[pl1][pc2]=0;
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						board[pl3][pc2]=0;
						
						pl1++;
						pl2++;
						pl3++;
						
						board[pl1][pc2]=1;
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
						board[pl3][pc2]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==2)
				{
					if(((board[pl2+1][pc1]==0) && (board[pl2+1][pc2]==0) && (board[pl2+1][pc3]==0)) && (pl2!=19))
					{
						board[pl1][pc2]=0;
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						board[pl2][pc3]=0;
						
						pl1++;
						pl2++;
						
						board[pl1][pc2]=1;
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
						board[pl2][pc3]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==3)
				{
					if(((board[pl3+1][pc1]==0) && (board[pl2+1][pc2]==0)) && (pl3!=19))
					{
						board[pl1][pc1]=0;
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						board[pl3][pc1]=0;
						
						pl1++;
						pl2++;
						pl3++;
						
						board[pl1][pc1]=1;
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
						board[pl3][pc1]=1;
					}
					else
					{
						next=1;
					}
				}
			}
			else if(cycle==9)
			{ // |
				if(rot==0)
				{
					if(((board[pl4+1][pc1]==0)) && (pl4!=19))
					{
						board[pl1][pc1]=0;
						board[pl2][pc1]=0;
						board[pl3][pc1]=0;
						board[pl4][pc1]=0;
						
						pl1++;
						pl2++;
						pl3++;
						pl4++;
						
						board[pl1][pc1]=1;
						board[pl2][pc1]=1;
						board[pl3][pc1]=1;
						board[pl4][pc1]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==1)
				{
					if((board[pl2+1][pc1]==0) && (board[pl2+1][pc2]==0) && (board[pl2+1][pc3]==0) && (board[pl2+1][pc4]==0) && (pl2!=19))
					{
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						board[pl2][pc3]=0;
						board[pl2][pc4]=0;
						
						pl2++;
						
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
						board[pl2][pc3]=1;
						board[pl2][pc4]=1;
					}
					else
					{
						next=1;
					}
				}
			}
			else if(cycle==11)
			{ // |-
				if(rot==0)
				{
					if(((board[pl3+1][pc1]==0) && (board[pl1+1][pc2]==0)) && (pl3!=19))
					{
						board[pl1][pc1]=0;
						board[pl1][pc2]=0;
						board[pl2][pc1]=0;
						board[pl3][pc1]=0;
						
						pl1++;
						pl2++;
						pl3++;
						
						board[pl1][pc1]=1;
						board[pl1][pc2]=1;
						board[pl2][pc1]=1;
						board[pl3][pc1]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==1)
				{
					if(((board[pl1+1][pc1]==0) && (board[pl1+1][pc2]==0) && (board[pl2+1][pc3]==0)) && (pl2!=19))
					{
						board[pl1][pc1]=0;
						board[pl1][pc2]=0;
						board[pl1][pc3]=0;
						board[pl2][pc3]=0;
						
						pl1++;
						pl2++;
						
						board[pl1][pc1]=1;
						board[pl1][pc2]=1;
						board[pl1][pc3]=1;
						board[pl2][pc3]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==2)
				{
					if(((board[pl3+1][pc1]==0) && (board[pl3+1][pc2]==0)) && (pl3!=19))
					{
						board[pl1][pc2]=0;
						board[pl2][pc2]=0;
						board[pl3][pc1]=0;
						board[pl3][pc2]=0;
						
						pl1++;
						pl2++;
						pl3++;
						
						board[pl1][pc2]=1;
						board[pl2][pc2]=1;
						board[pl3][pc1]=1;
						board[pl3][pc2]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==3)
				{
					if(((board[pl2+1][pc1]==0) && (board[pl2+1][pc2]==0) && (board[pl2+1][pc3]==0)) && (pl2!=19))
					{
						board[pl1][pc1]=0;
						board[pl2][pc1]=0;
						board[pl2][pc2]=0;
						board[pl2][pc3]=0;
						
						pl1++;
						pl2++;
						
						board[pl1][pc1]=1;
						board[pl2][pc1]=1;
						board[pl2][pc2]=1;
						board[pl2][pc3]=1;
					}
					else
					{
						next=1;
					}
				}
			}
			else if(cycle==13)
			{ // z
				if(rot==0)
				{
					if(((board[pl1+1][pc1]==0) && (board[pl2+1][pc2]==0) && (board[pl2+1][pc3]==0)) && (pl2!=19))
					{
						board[pl1][pc1]=0;
						board[pl1][pc2]=0;
						board[pl2][pc2]=0;
						board[pl2][pc3]=0;
						
						pl1++;
						pl2++;
						
						board[pl1][pc1]=1;
						board[pl1][pc2]=1;
						board[pl2][pc2]=1;
						board[pl2][pc3]=1;
					}
					else
					{
						next=1;
					}
				}
				else if(rot==1)
				{
					if((board[pl3+1][pc2]==0) && (board[pl2+1][pc3]==0) && (pl3!=19))
					{
						board[pl1][pc3]=0;
						board[pl2][pc2]=0;
						board[pl2][pc3]=0;
						board[pl3][pc2]=0;
						
						pl1++;
						pl2++;
						pl3++;
						
						board[pl1][pc3]=1;
						board[pl2][pc2]=1;
						board[pl2][pc3]=1;
						board[pl3][pc2]=1;
					}
					else
					{
						next=1;
					}
				}
			}
			
			if(next==1)
			{
				next=0;
				
				for(int i=0;i<20;i++)
				{ // linhas completadas
					for(int j=0;j<10;j++)
					{
						check+=board[i][j];
						if(check==10)
						{
							for(int h=0;h<10;h++)
							{ // zera a linha
								board[i][h]=0;
							}
							
							for(int h=i;h>=0;h--)
							{
								for(int z=0;z<10;z++)
								{
									if(h!=0)
									{
										board[h][z]=board[h-1][z];
									}
									else
									{
										board[h][z]=0;
									}
								}
							}
							score+=250;
						}
					}
					check=0;
				}
				check=0;
				
				if(cycle==13)
				{
					cycle=0;
				}
				else
				{
					cycle++;
				}
			}
		}
		direction='.';

		printf("\n        GGGGGGGGGGGGG                                                                        OOOOOOOOO                                                                   \n     GGG::::::::::::G                                                                      OO:::::::::OO                                                                 \n   GG:::::::::::::::G                                                                    OO:::::::::::::OO                                                               \n  G:::::GGGGGGGG::::G                                                                   O:::::::OOO:::::::O                                                              \n G:::::G       GGGGGG  aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee         O::::::O   O::::::Ovvvvvvv           vvvvvvv eeeeeeeeeeee    rrrrr   rrrrrrrrr   \nG:::::G                a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee       O:::::O     O:::::O v:::::v         v:::::vee::::::::::::ee  r::::rrr:::::::::r  \nG:::::G                aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee     O:::::O     O:::::O  v:::::v       v:::::ve::::::eeeee:::::eer:::::::::::::::::r \nG:::::G    GGGGGGGGGG           a::::a m::::::::::::::::::::::me::::::e     e:::::e     O:::::O     O:::::O   v:::::v     v:::::ve::::::e     e:::::err::::::rrrrr::::::r\nG:::::G    G::::::::G    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e     O:::::O     O:::::O    v:::::v   v:::::v e:::::::eeeee::::::e r:::::r     r:::::r\nG:::::G    GGGGG::::G  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e      O:::::O     O:::::O     v:::::v v:::::v  e:::::::::::::::::e  r:::::r     rrrrrrr\nG:::::G        G::::G a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee       O:::::O     O:::::O      v:::::v:::::v   e::::::eeeeeeeeeee   r:::::r            \n G:::::G       G::::Ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e                O::::::O   O::::::O       v:::::::::v    e:::::::e            r:::::r            \n  G:::::GGGGGGGG::::Ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e               O:::::::OOO:::::::O        v:::::::v     e::::::::e           r:::::r            \n   GG:::::::::::::::Ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee        OO:::::::::::::OO          v:::::v       e::::::::eeeeeeee   r:::::r            \n     GGG::::::GGG:::G a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e          OO:::::::::OO             v:::v         ee:::::::::::::e   r:::::r            \n        GGGGGG   GGGG  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee            OOOOOOOOO                vvv            eeeeeeeeeeeeee   rrrrrrr            \n");

		printf("\n\nScore:\n\n");

		big_score(score);

		printf("Continuar? [y]=Sim [n]=Nao\n\n");
		
		while(direction=='.')
		{ // continue?
			scanf(" %c", &direction);
			if(direction=='n')
			{
				return 0;
			}
			else if(direction=='y')
			{
			
			}
			else
			{
				direction='.';
			}
		}
		
		system("tput reset");
	}
	
	return 0;
}
