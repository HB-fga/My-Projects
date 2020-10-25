#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

void displayTime(int time)
{
    cout << setfill('0') << setw(2) << (time/60)/60 << ":" << setfill('0') << setw(2) << (time/60)%60 << ":" << setfill('0') << setw(2) << time%60 << endl;
    return;
}

int main()
{
    vector<int> seconds;
    vector<int> minutes;
    vector<int> hours;
    vector<int> total;

    char c_input;
    int i_input;

    fstream classes;
    string line;

    classes.open("classes.txt", std::ios::in);

    if(classes)
    {
        while(classes >> line)
        {
            cout << line << endl;
            hours.push_back  ( (line[0] - '0')*10 + (line[1] - '0'));
            minutes.push_back( (line[3] - '0')*10 + (line[4] - '0'));
            seconds.push_back( (line[6] - '0')*10 + (line[7] - '0'));
        }
    }

    classes.close();

    while(1)
    {
        cout << "O que deseja fazer? [V]er | [R]emover | [I]nserir | [S]alvar e Sair\n";
        cin >> c_input;

        if( c_input == 's' || c_input == 'S' ) break;

        switch(c_input)
        {
            case 'V':
            case 'v':

                cout << endl;

                total.push_back(0);

                for(int i = 0; i < seconds.size(); i++)
                {
                    cout << "Aula " << i + 1 << " - ";
                    cout << setfill('0') << setw(2) << hours[i] << ":" << setfill('0') << setw(2) << minutes[i] << ":" << setfill('0') << setw(2) << seconds[i] << endl;

                    total[0] += seconds[i] + (minutes[i]*60) + (hours[i]*60*60);
                }

                total.push_back(total[0]/2 + total[0]/4 + total[0]/8);
                total.push_back(total[0]/2 + total[0]/4);
                total.push_back(total[0]/2);
                
                cout << endl;
                cout << "Speed 1x    = ";
                displayTime(total[0]);

                cout << "Speed 1,25x = ";
                displayTime(total[1]);

                cout << "Speed 1,5x  = ";
                displayTime(total[2]);

                cout << "Speed 2x    = ";
                displayTime(total[3]);
                cout << endl;

                total.clear();

                break;

            case 'R':
            case 'r':

                while(1)
                {
                    for(int i = 0; i < seconds.size(); i++)
                    {
                        cout << "Aula " << i + 1 << " - ";
                        cout << setfill('0') << setw(2) << hours[i] << ":" << setfill('0') << setw(2) << minutes[i] << ":" << setfill('0') << setw(2) << seconds[i] << endl;
                    }

                    cout << "\nIndice do elemento que deseja remover ou [S]air\n";
                    cin >> c_input;

                    if( c_input != 's' && c_input != 'S' )
                    {
                        hours.erase  ( hours.begin  () + (c_input - '0' - 1) );
                        minutes.erase( minutes.begin() + (c_input - '0' - 1) );
                        seconds.erase( seconds.begin() + (c_input - '0' - 1) );
                    }
                    else break;
                }

                break;
            case 'I':
            case 'i':

                while(1)
                {
                    for(int i = 0; i < seconds.size(); i++)
                    {
                        cout << "Aula " << i + 1 << " - ";
                        cout << setfill('0') << setw(2) << hours[i] << ":" << setfill('0') << setw(2) << minutes[i] << ":" << setfill('0') << setw(2) << seconds[i] << endl;
                    }

                    cout << "\nHoras ou -1 para sair\n";
                    cin >> i_input;

                    if( i_input != -1 )
                    {
                        hours.push_back( i_input );

                        cout << "Minutos\n";
                        cin >> i_input;
                        minutes.push_back( i_input );

                        cout << "Segundos\n";
                        cin >> i_input;
                        seconds.push_back( i_input );
                    }
                    else break;
                }

                break;
        }

    }

    classes.open("classes.txt", std::ios::out);

    if(classes)
    {
        int n = seconds.size();
        for(int i = 0; i < seconds.size(); i++)
        {
            classes << setfill('0') << setw(2) << hours[i] << ":" << setfill('0') << setw(2) << minutes[i] << ":" << setfill('0') << setw(2) << seconds[i] << endl;
        }
    }

    classes.close();
    
    return 0;
}
