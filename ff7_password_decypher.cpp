#include <bits/stdc++.h>

// A program I wrote to decypher the Final Fantasy 7 password of the huge materia on the rocket based on Cid's tips
// X = Cross button
// # = Square button
// O = Circle button
// A = Triangle button

// The program worked :)
// Password: O#XX

using namespace std;

char it_to_char(int x) {

    char a = '.';

    switch(x)
    {
        case 0:
            a = 'X';
            break;
        case 1:
            a = '#';
            break;
        case 2:
            a = 'O';
            break;
        case 3:
            a = 'A';
            break;
    }

    return a;
}

int main() {

    char password[6];
    int n[6];
    int counter = 1;

    for(int i = 0; i < 4;i++)
    {
        for(int j = 0; j < 4;j++)
        {
            for(int k = 0; k < 4;k++)
            {
                for(int l = 0; l < 4;l++)
                {
                    password[0] = it_to_char(i);
                    password[1] = it_to_char(j);
                    password[2] = it_to_char(k);
                    password[3] = it_to_char(l);

                    if(password[1] != 'A')
                        if(password[0] != '#')
                            if(password[2] == 'X')
                                if(password[3] == 'X' || password[3] == 'A')
                                {

                                    n[0] = 0;
                                    n[1] = 0;
                                    n[2] = 0;
                                    n[3] = 0;

                                    for(int q = 0;q < 4;q++)
                                    {
                                        switch(password[q])
                                        {
                                            case 'X':
                                                n[0]++;
                                                break;
                                            case '#':
                                                n[1]++;
                                                break;
                                            case 'A':
                                                n[2]++;
                                                break;
                                            case 'O':
                                                n[3]++;
                                                break;
                                        }
                                    }

                                    password[4] = '\0';

                                    if(n[0] > 1 || n[1] > 1 || n[2] > 1 || n[3] > 1)
                                    {
                                        cout << counter << " - " << password << endl;
                                        counter++;
                                    }
                                }
                }
            }
        }
    }

    return 0;
}