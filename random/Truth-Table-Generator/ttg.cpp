#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

bool expression( int A, int B, int C, int D )
{
    // EXAMPLES:
    // return ( A || !B );
    // return ( A || !B ) && ( C || D );
    // return ( A || !B ) && ( C || D );
    // return ( A || !B ) && !( C || ( A && D ) );

    return /* INSERT YOUR EXPRESSION HERE */;
}

int main()
{
    int x;
    int counter = 0;

    fstream file;

    cout << "How many variables are there in your expression? (Max 4)\n";
    cin >> x;

    file.open("table.txt", std::ios::out);

    if( x == 1 )
    {
        file << setw(3) << counter << " | A | S\n";
        for( int A = 0; A < 2; A++ )
        {
            counter++;
            file << setw(3) << counter << " | " << A << " | ";

            if( expression( A, 0, 0, 0 ) )
                file << "1";
            else
                file << "0";

            file << endl;
        }
    }

    if( x == 2 )
    {
        file << setw(3) << counter << " | A B | S\n";
        for( int A = 0; A < 2; A++ )
        {
            for( int B = 0; B < 2; B++ )
            {
                counter++;
                file << setw(3) << counter << " | " << A << " " << B << " | ";
                
                if( expression( A, B, 0, 0 ) )
                    file << "1";
                else
                    file << "0";

                file << endl;
            }
        }
    }

    if( x == 3 )
    {
        file << setw(3) << counter << " | A B C | S\n";
        for( int A = 0; A < 2; A++ )
        {
            for( int B = 0; B < 2; B++ )
            {
                for( int C = 0; C < 2; C++ )
                {
                    counter++;
                    file << setw(3) << counter << " | " << A << " " << B << " " << C << " | ";
                    
                    if( expression( A, B, C, 0 ) )
                        file << "1";
                    else
                        file << "0";

                    file << endl;
                }
            }
        }
    }

    if( x == 4 )
    {
        file << setw(3) << counter << " | A B C D | S\n";
        for( int A = 0; A < 2; A++ )
        {
            for( int B = 0; B < 2; B++ )
            {
                for( int C = 0; C < 2; C++ )
                {
                    for( int D = 0; D < 2; D++ )
                    {
                        counter++;
                        file << setw(3) << counter << " | " << A << " " << B << " " << C << " " << D << " | ";
                    
                        if( expression( A, B, C, D ) )
                            file << "1";
                        else
                            file << "0";

                        file << endl;
                    }
                }
            }
        }
    }

    return 0;
}
