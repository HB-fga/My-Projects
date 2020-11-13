#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

    int a, b;
    int mdc, mmc, n;
    int upper[100];
    int middle[100];
    int bottom[100];
    int dio_column[100];
    dio_column[0] = 1;

    while(1)
    {
        cout << "INSERT 2 INTEGERS (INSERT \"0 0\" TO QUIT):" << endl;

        cin >> a >> b;
        if( a == 0 && b == 0 ) break;

        if(b > a)
        {
            int swap = b;
            b = a;
            a = swap;
        }

        middle[0] = a;
        middle[1] = b;


        for(int i = 0; ; i++)
        {
            upper[i] = middle[i]/middle[i+1];
            bottom[i] = middle[i]%middle[i+1];
            middle[i+2] = bottom[i];

            if(middle[i]%middle[i+1] == 0)
            {
                mdc = middle[i+1];
                mmc = (a*b) / mdc;
                n = i;
                break;
            }
        }

        for(int i = 0; i <= n; i++)
        {
            if(i == 0) cout << "|   ";
            cout << "|" << setw(3) << upper[i];
        }
        cout << "|" << endl;

        for(int i = 0; i <= n + 1; i++)
        {
            cout << "|" << setw(3) << middle[i];
        }
        cout << "|" << endl;

        for(int i = 0; i <= n; i++)
        {
            cout << "|" << setw(3) << bottom[i];
        }
        cout << "|   |" << endl << endl;

        dio_column[1] = upper[n-1];
        // cout << "upper n-1 = " << upper[n-1] << endl;

        cout << " q | xy" << endl;
        cout << " - |" << setw(3) << dio_column[0] << endl;
        cout << setw(3) << upper[n-1] << "|" << setw(3) << dio_column[1] << endl;

        for(int i = 2; i <= n; i++ )
        {
            dio_column[i] = ( upper[n-i] * dio_column[i-1]) + dio_column[i-2];
            cout << setw(3) << upper[n-i] << "|" << setw(3) << dio_column[i] << endl;
        }
        cout << endl;

        n%2 == 0 ? cout << "q = even\n" : cout << "q = odd\n";
        cout << "MDC = " << mdc << endl;
        cout << "MMC = " << mmc << endl << endl;
    }

    return 0;
}