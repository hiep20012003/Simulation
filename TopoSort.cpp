#include<iostream>
using namespace std;
struct SUCCESSOR
{
	int SUC;
	SUCCESSOR* next;
};
struct NODE
{
	int COUNT;
	SUCCESSOR* TOP;
};
int QLINK[40];
int main()
{
	SUCCESSOR* P;
	int out[40];
	NODE A[40];
	int N, num_relation;
	cin >> N >> num_relation;
	int number = N;
	for (int i = 1; i <= N; i++)
	{
		A[i].COUNT = 0;
		A[i].TOP = nullptr;
	}

	// input
	for (int i = 0; i < num_relation; i++)
	{
		int x, y;
		cin >> x >> y;
		A[y].COUNT = A[y].COUNT + 1;
		P = (SUCCESSOR*)malloc(sizeof(SUCCESSOR));
		P->SUC = y;
		P->next = A[x].TOP;
		A[x].TOP = P;
	}

	// hang cho
	int R = 0, F;
	QLINK[0] = 0;
	for (int i = 1; i <= number; i++)
	{
		if (A[i].COUNT == 0)
		{
			QLINK[R] = i;
			R = i;
		}
	}

	// topo
	int nout = 0;
	for (F = QLINK[0]; F != 0; F = QLINK[F])
	{
		out[nout++] = F;
		N--;
		for (P = A[F].TOP; P != nullptr; P = P->next)
		{
			A[P->SUC].COUNT--;
			if (A[P->SUC].COUNT == 0)
			{
				QLINK[R] = P->SUC;
				R = P->SUC;
			}
		}
	}
	out[nout++] = 0;
	{
		for (int i = 0; i <= number; i++)
			cout << out[i] << " ";
	}
	getchar();
	return 1;
}