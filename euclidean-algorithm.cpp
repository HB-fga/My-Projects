#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

    int a, b;
    int mdc, mmc, n;
    int v1[100];
    int v2[100];
    int v3[100];

    cout << "Insert 2 integers:" << endl;

    cin >> a >> b;

    if(b > a)
    {
        int swap = b;
        b = a;
        a = swap;
    }

    v2[0] = a;
    v2[1] = b;

    for(int i = 0; ;i++)
    {
        v1[i] = v2[i]/v2[i+1];
        v3[i] = v2[i]%v2[i+1];
        v2[i+2] = v3[i];

        if(v2[i]%v2[i+1] == 0)
        {
            mdc = v3[i-1];
            mmc = (a*b) / mdc;
            n = i;
            break;
        }
    }

    for(int i = 0; i <= n; i++)
    {
        if(i == 0) cout << "|   ";
        cout << "|" << setw(3) << v1[i];
    }
    cout << "|" << endl;

    for(int i = 0; i <= n + 1; i++)
    {
        cout << "|" << setw(3) << v2[i];
    }
    cout << "|" << endl;

    for(int i = 0; i <= n; i++)
    {
        cout << "|" << setw(3) << v3[i];
    }
    cout << "|   |" << endl;

    cout << "MDC = " << mdc << endl;
    cout << "MMC = " << mmc << endl;

    return 0;
}