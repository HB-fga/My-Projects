// Pool size of Skill points per level =1/2∗(SP2+SP)∗1800

// Where SP is the Skill Point of dwellers (1 ~ 9)

// Points per second =(1+0.02∗(D−1))∗(1+0.05∗(T−1))∗(1+H)

// Where D is the number of dwellers training in the room (1 ~ 6)
// T is the tier of the training room (1 ~ 3)
// H is the Vault happiness bonus (0.01~0.1)

#include <iostream>
#include <fstream>

using namespace std;

int find_special(int i_stat) {

    char special;

    switch (i_stat)
    {
        case 1:
            special = 'S';
            break;
        case 2:
            special = 'P';
            break;
        case 3:
            special = 'E';
            break;
        case 4:
            special = 'C';
            break;
        case 5:
            special = 'I';
            break;
        case 6:
            special = 'A';
            break;
        case 7:
            special = 'L';
            break;
    }

    return special;

}

int time_left(int level, int goal) {

    int time = 0;

    for(int i = level; i < goal; i++)
    {
        time += ((i * i + i) * 1800) / 2;
    }

    return time;
}

double points_per_second(int room_lv) {

    double pps;

    double happiness = 0.09;
    int dwellers_training = 6;

    pps = (1 + 0.02 * (dwellers_training - 1)) * (1 + 0.05 * (room_lv - 1)) * (1 + happiness);

    return pps;
}

int time_in_seconds(int time, double multiplier) {

    int time_in_s = time / multiplier;

    return time_in_s;
}

void print_time(int time_in_s) {

    int days = time_in_s / 86400;
    int hours = (time_in_s % 86400) / 3600;
    int minutes = ((time_in_s % 86400) % 3600) / 60;
    int seconds = ((time_in_s % 86400) % 3600) % 60;

    cout << days << "d, " << hours << "h, " << minutes << "m e " << seconds << "s." << endl;

}

int main() {

    system("clear");

    char special;
    int i_dweller;
    int i_stat;
    int room_lv;
    string dweller_name;
    string linha;
    fstream arquivo_io;

    cout << "informe o nivel da sala de treinamento: ";
    cin >> room_lv;

    i_dweller = 0;
    arquivo_io.open("habitantes.txt", std::ios::in);

    if(arquivo_io.is_open())
    {
        while(!arquivo_io.eof())
        {  
            getline(arquivo_io,linha);

            if(linha == ".")
                break;

            i_stat = 0;
            if(i_dweller != 0)
            {
                string delimiter = "\t";
                size_t pos = 0;
                string token;
                while ((pos = linha.find(delimiter)) != string::npos) {
                    token = linha.substr(0, pos);
                    
                    if(i_stat == 0)
                        cout << endl << token << ":" << endl;
                    else
                    {
                        special = find_special(i_stat);
                        cout << special << token << " para 7: ";
                        print_time(time_in_seconds(time_left(stoi(token), 7), points_per_second(room_lv)));
                    }

                    linha.erase(0, pos + delimiter.length());

                    i_stat++;
                }

                special = find_special(i_stat);
                cout << special << linha << " para 7: ";
                print_time(time_in_seconds(time_left(stoi(linha), 7), points_per_second(room_lv)));
            }

            i_dweller++;
        }
        arquivo_io.close();
    }

    return 0;
}