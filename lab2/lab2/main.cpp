#include <iostream>
#include <math.h>

const double Eps = 0.0001;

const int a = 4, b = 4;

int matrix[a][b] =
{
{15,3,3,0},
{1,14,5,-7},
{-2,1,18,-4},
{3,3,-4,14},
};

int bi[a] =
{
	3,
	7,
	5,
	4,
};

double answ1[a] =
{
	0,
	0,
	0,
	
};
double answ2[a] =
{
	0,
	0,
	0,
	
};


void iteration();
bool prverka(double *answ1, double *answ2);
bool shodimost();
void iter(double *answ1, double *answ2);
using namespace std;
int main()
{
	if (shodimost()) 
	{
	
		iteration();
	 
	}
	else cout << "ne shoditsya(";


	

	system("pause");
	return 0;
}

bool shodimost()
{


	double sum = 0;

	for (int ca = 0; ca < a; ca++)
	{
		sum = 0;
		for (int cb = 0; cb < b; cb++)
			if (ca != cb)sum += abs(matrix[ca][cb]);

		if (abs(matrix[ca][ca]) < sum)return false;
	}

	return true;
}

void iteration()
{
	while (true)
	{
		iter(answ1, answ2);
		if (prverka(answ1, answ2))
		{
			for (int ca = 0; ca < a; ca++)
				cout << answ1[ca] << '\n';
			break;
		}
		iter(answ2, answ1);
		if (prverka(answ2, answ1))
		{
			for (int ca = 0; ca < a; ca++)
				cout << answ2[ca] << '\n';
			break;
		}
	}

}
bool prverka(double *answ1, double *answ2)
{
	for (int ca = 0; ca < a; ca++)
		if ((abs(answ2[ca] - answ1[ca])) > Eps)
			return false;
	return true;
}

void iter(double *answ1, double *answ2)
{
	double sum = 0;
	for (int ca = 0; ca < a; ca++)
	{
		sum = 0;

		for (int cb = 0; cb < b; cb++)
			if (ca != cb)
				sum += matrix[ca][cb] * answ2[ca];
		
		sum = bi[ca] - sum;
		answ1[ca] = sum / matrix[ca][ca];		
	}
}