// lab 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

void sift(int *A, int *Ind, int i, int m)
{
	int j = i, k = i * 2 + 1, temp;	 // левый сын
	while (k <= m)
	{
		if (k<m && A[Ind[k]]<A[Ind[k + 1]]) k++; // больший сын
		if (A[Ind[j]] < A[Ind[k]])
		{
			//swap(A[j], A[k]);
			temp = Ind[j]; Ind[j] = Ind[k]; Ind[k] = temp;
			j = k; k = k * 2 + 1;
		}
		else break;
	}
}

bool test(int *A, int n) 
{
	for (int i = 0;i < n-1;i++) if (A[i] > A[i+1]) return false;
	return true;
}

bool test2(int *A, int *Ind, int n)
{
	for (int i = 0; i < n - 1; i++) if (A[Ind[i]] > A[Ind[i + 1]]) return false;
	return true;
}

class sort
{
public:
	static void merge_sort(int *A, int n);
	static void shell_sort(int *A, int *Ind, int n);
	static void heap_sort(int *A, int *Ind, int n);
	static void quick_sort(int *A, int b, int e);
};

void sort::merge_sort(int *A, int n)
{
	int s, b, c, e;
	int *D = new int[n];
	for (s = 1; s < n; s *= 2) {
		int k = 0;
		for (b = 0; b < n; b += s * 2) 
		{
			c = min(b + s - 1, n - 1);
			e = min(c + s, n - 1);
			//слияние
			int i1, i2;
			i1 = b; i2 = c + 1;
			while ((i1 <= c) && (i2 <= e))
				if (A[i1] < A[i2])
				{
					D[k] = A[i1];
					i1++; k++;
				}
				else {
					D[k] = A[i2];
					i2++; k++;
				}
				while (i1 <= c)
				{
					D[k] = A[i1]; i1++; k++;
				}
				while (i2 <= e)
				{
					D[k] = A[i2]; i2++; k++;
				}
		}
		for (b = 0; b < n; b++) A[b] = D[b];
	}
	delete[] D;
}

void sort::shell_sort(int *A, int *Ind, int n)  //косвенная 
{
	int i, j, h, temp;
	for (h = 1; h <= n / 9; h = h * 3 + 1);
	while (h >= 1)
	{
		for (i = h; i < n; i++)
			for (j = i - h; j >= 0 && A[Ind[j]] > A[Ind[j + h]]; j -= h)
			{
				temp = Ind[j]; Ind[j] = Ind[j + h]; Ind[j + h] = temp;
			}
			h = (h - 1) / 3;
	}
}

void sort::heap_sort(int *A, int *Ind, int n)  //косвенная
{
	int i, m, temp;
	// построение пирамиды
	for (i = n / 2; i >= 0; i--)
		sift(A, Ind, i, n - 1);
	// сортировка массива
	for (m = n - 1; m >= 1; m--)
	{
		//swap(A[0], A[m]);
		temp = Ind[0]; Ind[0] = Ind[m]; Ind[m] = temp;
		sift(A, Ind, 0, m - 1);
	}
}

void sort::quick_sort(int *A, int b, int e)
{
	int x; int i, j, c = b, d = e;
	while (c < d) {
		x = A[(c + d) / 2]; i = c; j = d;
		while (i < j) {
			while (A[i] < x) i++;
			while (A[j] > x) j--;
			if (i <= j)
			{
				swap(A[i], A[j]); i++; j--;
			}
		}
		if (j - c < d - i)
		{
			if (c < j) quick_sort(A, c, j); c = i;
		}
		else { if (i<d) quick_sort(A, i, d); d = j; }
	}
}


int main()
{
	srand(time(0));
	//проверка реккурентного слияния
	/*int *A; int n; int i;
	n = 10;
	A = new int[n];
	for (i = 0;i < n;i++) A[i] = rand() % 100 + 1;
	for (i = 0;i < n;i++) cout << A[i] << ' ';
	sort::merge_sort(A, n);
	cout << endl;
	for (i = 0;i < n;i++) cout << A[i] << ' ';*/

	//косвенная сортировка Шелла + время + тест 
	/*int *A, *Ind; int n; int i;
	n = 10000;
	A = new int[n];
	Ind = new int[n];
	for (i = 0;i < n;i++) Ind[i] = i;
	for (i = 0;i < n;i++) A[i] = rand() % 100 + 1;
	double t1 = clock();
	sort::shell_sort(A, Ind, n);
	double t2 = clock();
	cout << ((t2 - t1) / 1000) << endl;
	if (test2(A, Ind, n) == true) cout << "true";
	else cout << "false";
	cout << endl;*/

	//проверка косвенной пирамидальной сортировки
	/*int *A, *Ind; int n; int i;
	n = 10;
	A = new int[n];
	Ind = new int[n];
	for (i = 0;i < n;i++) Ind[i] = i;
	for (i = 0;i < n;i++) A[i] = rand() % 100 + 1;
	for (i = 0;i < n;i++) cout << A[i] << ' ';
	sort::heap_sort(A,Ind,n);
	cout << endl;
	for (i = 0;i < n;i++) cout << A[Ind[i]] << ' ';*/
	
	//быстрая сортировка с 1 рекурсивным вызовом + время + тест
	/*int *A; int n; int i;
	n = 1000000;
	A = new int[n];
	for (i = 0;i < n;i++) A[i] = rand() % 100 + 1;
	double t1 = clock();
	sort::quick_sort(A, 0, n-1);
	double t2 = clock();
	cout << ((t2 - t1) / 1000) << endl;
	if (test(A, n) == true) cout << "true";
	else cout << "false";
	cout << endl;*/

	int *A, *Ind, n, i; double t1, t2;
	n = 1000000; A = new int[n]; Ind = new int[n];
	/*merge_sort*/
	/*1*/
	for (i = 0; i < n; i++) A[i] = i;
	cout << "merge sort: " << endl;
	t1 = clock();
	sort::merge_sort(A, n);
	t2 = clock();
	cout << "1) " << ((t2 - t1) / 1000) << ' ';
	if (test(A, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*2*/
	for (i = 0; i < n; i++) A[i] = n - i;
	t1 = clock();
	sort::merge_sort(A, n);
	t2 = clock();
	cout << "2) " << ((t2 - t1) / 1000) << ' ';
	if (test(A, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*3*/
	for (i = 0; i < n; i++) A[i] = rand() % 10000 + 1;
	t1 = clock();
	sort::merge_sort(A, n);
	t2 = clock();
	cout << "3) " << ((t2 - t1) / 1000) << ' ';
	if (test(A, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*shell_sort*/
	/*1*/
	for (i = 0; i < n; i++) Ind[i] = i;
	for (i = 0; i < n; i++) A[i] = i;
	cout << "shell sort: " << endl;
	t1 = clock();
	sort::shell_sort(A, Ind, n);
	t2 = clock();
	cout << "1) " << ((t2 - t1) / 1000) << ' ';
	if (test2(A, Ind, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*2*/
	for (i = 0; i < n; i++) Ind[i] = i;
	for (i = 0; i < n; i++) A[i] = n - i;
	t1 = clock();
	sort::shell_sort(A, Ind, n);
	t2 = clock();
	cout << "2) " << ((t2 - t1) / 1000) << ' ';
	if (test2(A, Ind, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*3*/
	for (i = 0; i < n; i++) Ind[i] = i;
	for (i = 0; i < n; i++) A[i] = rand() % 10000 + 1;
	t1 = clock();
	sort::shell_sort(A, Ind, n);
	t2 = clock();
	cout << "3) " << ((t2 - t1) / 1000) << ' ';
	if (test2(A, Ind, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*heap_sort*/
	/*1*/
	for (i = 0; i < n; i++) Ind[i] = i;
	for (i = 0; i < n; i++) A[i] = i;
	cout << "heap sort: " << endl;
	t1 = clock();
	sort::heap_sort(A, Ind, n);
	t2 = clock();
	cout << "1) " << ((t2 - t1) / 1000) << ' ';
	if (test2(A, Ind, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*2*/
	for (i = 0; i < n; i++) Ind[i] = i;
	for (i = 0; i < n; i++) A[i] = n - i;
	t1 = clock();
	sort::heap_sort(A, Ind, n);
	t2 = clock();
	cout << "2) " << ((t2 - t1) / 1000) << ' ';
	if (test2(A, Ind, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*3*/
	for (i = 0; i < n; i++) Ind[i] = i;
	for (i = 0; i < n; i++) A[i] = rand() % 10000 + 1;
	t1 = clock();
	sort::heap_sort(A, Ind, n);
	t2 = clock();
	cout << "3) " << ((t2 - t1) / 1000) << ' ';
	if (test2(A, Ind, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*quick_sort*/
	/*1*/
	for (i = 0; i < n; i++) A[i] = i;
	cout << "quick sort: " << endl;
	t1 = clock();
	sort::quick_sort(A, 0, n-1);
	t2 = clock();
	cout << "1) " << ((t2 - t1) / 1000) << ' ';
	if (test(A, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*2*/
	for (i = 0; i < n; i++) A[i] = n - i;
	t1 = clock();
	sort::quick_sort(A, 0, n - 1);
	t2 = clock();
	cout << "2) " << ((t2 - t1) / 1000) << ' ';
	if (test(A, n) == true) cout << "true" << endl;
	else cout << "false" << endl;

	/*3*/
	for (i = 0; i < n; i++) A[i] = rand() % 10000 + 1;
	t1 = clock();
	sort::quick_sort(A, 0, n - 1);
	t2 = clock();
	cout << "3) " << ((t2 - t1) / 1000) << ' ';
	if (test(A, n) == true) cout << "true" << endl;
	else cout << "false" << endl;
	return 0;
}

