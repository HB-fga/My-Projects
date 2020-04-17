#include <iostream>
#include <unistd.h>
#include <math.h>

using namespace std;

void countdown(int s, int i1, int i2, string str) {

    while(s--)
    {
        system("clear");

        if(str == "")
        {
            cout << "Treino " << i1 << endl;
            cout << "Exercicio " << i2 << endl;
        }
        else
            cout << str << endl;

        cout << s+1 << endl;
        sleep(1);
    }

    system("clear");
    cout << "!\a" << endl;
    // system("aplay when.mp3");
    sleep(1);
}

int main() {

    execlp("mpg123", "mpg123", "-q", "when.mp3", 0); 

    int exercise_time = 0;
    int exercise_pause = 0;
    int workout_pause = 0;

    int exercises = 0;
    int workouts = 0;

    char confirmation = 'x';

    system("clear");

    while(1)
    {
        cout << "Defina quantos segundos dura cada exercicio: ";
        cin >> exercise_time;
        system("clear");

        cout << "Defina quantos segundos dura cada pausa entre exercicios: ";
        cin >> exercise_pause;
        system("clear");

        cout << "Defina quantos segundos dura cada pausa entre treinos: ";
        cin >> workout_pause;
        system("clear");

        cout << "Exercicio: " << exercise_time << " segundos\n";
        cout << "Pausa entre exercicios: " << exercise_pause << " segundos\n";
        cout << "Pausa entre treinos: " << workout_pause << " segundos\n";
        cout << "Confirma? (\"s\" ou \"n\"): ";
        cin >> confirmation;
        system("clear");

        if(confirmation != 'n') break;
    }

    while(1)
    {
        cout << "Informe quantos exercicios voce tem em cada treino: ";
        cin >> exercises;
        system("clear");

        cout << "Informe quantos treinos voce pretende fazer: ";
        cin >> workouts;
        system("clear");

        cout << exercises << " Exercicios\n";
        cout << workouts << " Treinos\n";
        cout << "Confirma? (\"s\" ou \"n\"): ";
        cin >> confirmation;
        system("clear");

        if(confirmation != 'n') break;
    }

    cout << "Envie qualquer tecla para comecar";
    scanf("%*c%*c");
    system("clear");

    countdown(3, 0, 0, "Preparado?");

    for(int i = 1;i <= workouts;i++)
    {
        for(int j = 1;j <= exercises;j++)
        {
            countdown(exercise_time, i, j, "");

            if(j != exercises)
                countdown(exercise_pause, i, j, "Pausa curta");
        }
        if(i != workouts)
            countdown(workout_pause, i, 0, "Pausa longa");
    }

    system("clear");
    cout << "Treino Finalizado!\n";

    return 0;
}
