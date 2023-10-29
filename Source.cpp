#include <iostream>
#include <random>  
#include <ctime>
#include<time.h>  
using namespace std;


///������� �������� ���������� � ������� �� ������

long long int vozv(long long int a, long long int x, long long int p)

{

    long long int r = 1;

    while (x != 0)

    {

        if (x % 2 == 0)

        {

            a = (a * a) % p;

            x = x / 2;

        }

        else

        {

            x--;

            r = (r * a) % p;

        }

    }



    return r;

}


//������� ����������� ���� ������

long long int SHAMIR(int m, int Ca, int Cb, int Da, int Db, int p)

{

    long long int x1, x2, x3, x4;



    x1 = vozv(m, Ca, p);

    cout << "x1=" << x1;

    x2 = vozv(x1, Cb, p);

    cout << " x2=" << x2;

    x3 = vozv(x2, Da, p);

    cout << " x3=" << x3;

    x4 = vozv(x3, Db, p);

    cout << " x4=" << x4 << endl;

    if (m == x4)

    {

        cout << "������� � ������� ��������� m" << endl;

        return x4;

    }

    else

        cout << "Error" << endl;

}

long long int ev(long long int a, long long int b)
{
    long long int temp;
    if (a < b)
    {
        temp = a;
        a = b;
        b = temp;
    }
    long long int c, NOD;
    long long int x1 = 1, y1 = 0, x2 = 0, y2 = 1;
    long long int x, y, xr, yr;
    while (b > 0)
    {
        c = a / b;
        NOD = a - b * c;
        if (NOD != 0)
        {
            xr = x1 - c * x2;
            yr = y1 - c * y2;
            x1 = x2;
            y1 = y2;
            x2 = xr;
            y2 = yr;
            a = b;
            b = NOD;
        }
        else
        {
            NOD = b;
            break;
        }
    }
    return NOD;
}


long long int evy(long long int a, long long int b)
{
    int temp;
    if (a < b)
    {
        temp = a;
        a = b;
        b = temp;
    }
    long long int c, NOD;
    long long int x1 = 1, y1 = 0, x2 = 0, y2 = 1;
    long long int x, y, xr, yr;
    while (b > 0)
    {
        c = a / b;
        NOD = a - b * c;
        if (NOD != 0)
        {
            xr = x1 - c * x2;
            yr = y1 - c * y2;
            x1 = x2;
            y1 = y2;
            x2 = xr;
            y2 = yr;
            a = b;
            b = NOD;
        }
        else
        {
            NOD = b;
            break;
        }
    }
    return yr;
}

int main() {
    long long int p;

    setlocale(0, "rus");
    cout << "���� ������" << endl;
    cout << "����������� ������� ����� �" << endl;
    mt19937 gen(time(0));        // ����������
    uniform_int_distribution<> uid(10000, 1000000000);
    p = uid(gen);                  // ������� ����� �
    long long bar = sqrt(p);
    bool flag = true;
    do {
        flag = true;
        for (int i = 2; i <= bar; i++) {
            if (p % i == 0) {
                flag = false;
                p = uid(gen);
                bar = sqrt(p);
            }
        }
    } while (flag != true);
    cout << "�������� ������� ������� �= " << p << endl;

    //// ������ ��������� m � ������
    string userString;
    char ch = ' ';

    cout << "������� ��������� m ";
    cin >> userString;
    for (unsigned int i = 0; i < userString.size(); i++) {

        ch = userString.at(i);
        if (ch == ' ') {
            cout << 0 << " ";
        }
        else {
            int m = ch - '1' + 1; // ������� ����� � �������� ��������, ����� A B C D E  � ��� �������
            cout << m << " "; //�������� �������� � �����
        }

    }

    cout << endl;
    srand(time(0));
    long long int m, Ca, Cb, Da, Db;
    Ca = rand();
    while (ev(Ca, (p - 1)) != 1) //������� Ca ������� ������� � (p-1)
        Ca = rand();
    cout << "Ca=" << Ca << endl;


    Da = evy(Ca, (p - 1));
    if (Da < 0) //� ������� ev ������� Da
        Da = Da + (p - 1);
    cout << "Da=" << Da << endl;

    int rez1 = (Ca * Da) % (p - 1);
    cout << "(Ca*Da)mod(p-1)=" << rez1 << endl;

    Cb = rand();
    while (ev(Cb, (p - 1)) != 1)
        Cb = rand();
    cout << "Cb=" << Cb << endl;

    Db = evy(Cb, (p - 1));
    if (Db < 0)
        Db = Db + (p - 1);
    cout << "Db=" << Db << endl;
    int rez2 = (Cb * Db) % (p - 1);
    cout << "(Cb*Db)mod(p-1)=" << rez2 << endl;
    cout << "m=" << m << endl;

    SHAMIR(m, Ca, Da, Cb, Db, p);
}