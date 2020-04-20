// Linha de compilacao
// g++ workout_timer.cpp -w -lSDL2 -lSDL2_mixer -o prog

#include <iostream>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

Mix_Chunk *gBeep = NULL;

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
	}

	return success;
}

bool load_media()
{
    bool success = true;

    gBeep = Mix_LoadWAV("beep.wav");
    if(gBeep == NULL)
    {
        printf( "Failed to load notification sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void close()
{
    Mix_FreeChunk(gBeep);
    gBeep = NULL;

    Mix_Quit();
    SDL_Quit();
}

void countdown(int s, int i1, int i2, string str) {

    while(s--)
    {
        system("clear");

        cout << s+1 << endl;

        if(str != "Preparado?")
        {
            cout << "Treino " << i1 << endl;
            cout << "Exercicio " << i2 << endl;
            cout << str << endl;
        }
        else
            cout << str << endl;
        
        sleep(1);
    }

    system("clear");

    cout << "!" << endl;
    Mix_PlayChannel(-1, gBeep, 0);
    sleep(4);
}

int main() {

    if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !load_media() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
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

                if(confirmation != 'n' && confirmation != 'N') break;
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

                if(confirmation != 'n' && confirmation != 'N') break;
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
                        countdown(exercise_pause, i, j+1, "Descanse para o proximo Exercicio");
                }
                if(i != workouts)
                    countdown(workout_pause, i+1, 1, "Descanse para o proximo Treino");
            }

            system("clear");
            cout << "Treino Finalizado!\n";
        }
    }
    
    close();

    return 0;
}
