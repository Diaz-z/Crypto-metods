#include <iostream>
#include <math.h>
#include <ctime>
#include <time.h>
#include <random>
#include <cstring>
using namespace std;
long long stepen(long long a, long long x, long long p) //a^x mod p
{
	long long i = 0;

	long long x2[30];
	long long vi = x;

	while (x >= 1)
	{
		x2[i] = x % 2;
		x /= 2;
		i++;
	}
	long long n = i;
	long long* arr = new long long[n];
	arr[0] = a;
	for (long long i = 1; i < n; i++)
	{
		arr[i] = (arr[i - 1] % p * arr[i - 1] % p) % p;
	}
	long long v = 1;
	for (long long j = 0; j < n; j++)
	{
		if (x2[j] > 0)
		{
			v = (v % p * x2[j] % p * arr[j] % p) % p;
		}
	}
	delete[] arr;
	return v;
}
bool isprime(long long p) //проверка на простое число
{
	if (p <= 1)
		return false;
	long long b = (long long)pow(p, 0.5);
	for (long long i = 2; i <= b; i++)
	{
		if ((p % i) == 0)
			return false;
	}
	return true;
}
long long NOD(long long x, long long y) 
{
	long long tmp_res = 0;
	vector<long long> vector_a;

	if (x < y)
	{
		swap(x, y);
	}

	vector_a.push_back(x);
	vector_a.push_back(y);

	while (vector_a[1] != 0)
	{
		tmp_res = vector_a[0] % vector_a[1];
		if (tmp_res < vector_a[1])
		{
			swap(vector_a[0], vector_a[1]);
			vector_a[1] = tmp_res;
		}
		else
		{
			vector_a[0] = tmp_res;
		}
		/*cout << "TMP pare: " << vector_a[0] << ' ' << vector_a[1] << endl;*/
	}
	return vector_a[0];
}
vector<long long> XYNODfind(long long a, long long b)
{
	long long q;
	vector<long long> U, V, T;
	U = { a, 1, 0 };
	V = { b, 0, 1 };
	while (V[0] != 0)
	{
		if (U[0] < V[0])
		{
			swap(V, U);
		}
		q = U[0] / V[0];
		T = { U[0] % V[0], U[1] - q * V[1], U[2] - q * V[2] };
		U = V;
		V = T;
	}
	return U; //возвращает массив: NOD,x,y;
}
long long int GetRandomNumber(long long min,long long int max)
{
	long long num = min + rand() % (max - min + 1);
	return num;
}
long long BigPrime() {
	long long  p;
	//mt19937 gen(time(0));        // БИБЛИОТЕКА
	//uniform_int_distribution<> uid(10000, 1000000000);
	p = GetRandomNumber(10000, 100000);                  // БОЛЬШОЕ ЧИСЛО Р
	do { p = GetRandomNumber(10000, 100000); } while (isprime(p) != true);
	return(p);
}
vector<long long int> GeneratePG() {
	long range = 100000;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long long> dist(1000, range);
	long long int p, g, q;
	do
	{
		q = BigPrime();
		p = 2 * q + 1;
	} while (!isprime(q) || !isprime(p));
	do
	{
		g = GetRandomNumber(1, p - 1);
	} while (stepen(g, q, (p)) == 1);
	vector<long long int> PG = { p,g };
	return PG;
}
long long shamir(long long m,long long int p) { 
	long long int Ca=rand(), Da, Cb=rand(), Db;
	while (NOD(Ca, (p - 1)) != 1) Ca = rand();
	Da = XYNODfind(Ca, (p - 1))[1];
	if (Da < 0) //с помощью ev находим Da
		Da = Da + (p - 1);
	while (NOD(Cb, (p - 1)) != 1) Cb = rand();
	Db = XYNODfind(Cb, (p - 1))[1];
	if (Db < 0) //с помощью ev находим Da
		Db = Db + (p - 1);
	long long x1 = stepen(m, Ca, p); //1-е число для Б
	long long x2 = stepen(x1, Cb, p); //1-е число для А
	cout << "shifrated shamir: " << x2<<endl;
	long long x3 = stepen(x2, Da, p); //2-е чилсло для Б
	long long x4 = stepen(x3, Db, p); //сообщение m
	return(x4);
}
long long ElGamal(long long int m,long long int p, long long int g) {
	long long int Ca = GetRandomNumber(1, p - 1),Cb= GetRandomNumber(1, p - 1),Da,Db;
	Da = stepen(g, Ca, p); //открытые числа
	Db = stepen(g, Cb, p);
	if (m >= p) {
		cout << "сообщение слишком большое";
		return(0);
	}
	long long int k = GetRandomNumber(1, p - 2);
	long long int r = stepen(g, k, p);
	long long int e = (m * stepen(Db, k, p))%p;
	long long int m2 = (e * stepen(r, (p - 1 - Cb), p))%p;
	cout << "shiаrated ElGamal: " << e<<" "<< r;
	return(m2);
}
long long RSA(long long int m) {
	long long int pa = BigPrime(), qa = BigPrime(), pb = BigPrime(), qb = BigPrime();
	long long int Na = qa * pa, Nb = qb * pb; //open key
	long long int phia = (pa - 1) * (qa - 1),phib= (pb - 1) * (qb - 1);
	long long int da, db;
	do
	{
		da = GetRandomNumber(1,phia);
	} while (NOD(da, phia) != 1);
	do
	{
		db = GetRandomNumber(1, phib);
	} while (NOD(db, phib) != 1);
	long long int ca, cb;
	ca = XYNODfind(da, phia)[1];
	if (ca < 0) //с помощью ev находим Da
		ca = ca + phia;
	cb = XYNODfind(db, phib)[1];
	if (cb < 0) //с помощью ev находим Da
		cb = cb + phib;
	long long int e = stepen(m, db,Nb);
	cout << "Shifrated RSA: " << e<<endl;
	long long int m1 = stepen(e, cb, Nb);
	return(m1);
}
long long Vernam(long long m) {
	long long key=rand();//Определяем необходимые переменные 
	long long sh = m ^ key;
	long long de = sh ^ key;
	cout << "Shifrated Vernam: " << sh<<endl;
	return de;
}
int main() {
	srand(time(0));
	setlocale(0, "rus");
	long long m = 12345;
	cout <<"Your message " << m << endl;
	cout <<"Shamir " << shamir(m, BigPrime()) << endl;
	long long int p = GeneratePG()[0]; //числа сети 
	long long int g = GeneratePG()[1];
	long long int EG = ElGamal(m, p, g);
	cout<<endl<<"Elgamal " << EG << endl;
	cout <<"RSA " << RSA(m) << endl;
	cout<<"Vernam " << Vernam(m);
	return 0;
}