/****************************************************************************
Задача 3_1.

Дан отсортированный массив целых чисел A[0..n-1] и массив
целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите
минимальный индекс k минимального элемента массива A, равного или
превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет,
выведите n. Время работы поиска k для каждого элемента B[i]: O(log(k)).
n, m ≤ 10000.

*Формат входных данных.*
В первой строчке записаны числа n и m. Во второй и третьей массивы A и B
соответственно.

  in       | out
  ---------|-------
  2 1      | 1
  1 2      |
  2        | 

  in       | out
  ---------|-------
  4 3      | 1 3 0
  2 4 5 7  | 
  4 6 1    | 

****************************************************************************/

#include <iostream>

using namespace std;

int middle(int a, int b){
return (a+b)/2;
}
	

int main(){
	int n,m,right,left,par,ans;
	bool boo = true;
	cin>>n>>m;
	int a[n],b[m];

	for(int i = 0; i<n;++i){
		cin>>a[i];
	}

	for(int i = 0; i<m;++i){
		cin>>b[i];
	}
	for(int i = 0;i<m;++i){
		par = 1;
		while(a[par]<b[i]and par<n){
			par *= 2;
		}
		left = par/2;
		if (par>n){
			par = n - 1;
		}
		right = par;
		if (left>right){
			int swap = right;
			right = left;
			left = swap;
		}
		while(left<right){
			if (a[middle(right,left)]<b[i]){
				left = middle(right,left) + 1;
			}else{
				right = middle(right,left);
			}
			if (a[middle(right,left)]==b[i]){
				right = middle(right,left);
				break;
			}
		}
		ans = right;
		if (left>right){
			int swap = left;
			left = right;
			right = swap;
		}
		boo = false;
		for(int j = left;j<=right;++j){
			if (b[i]<=a[j]) boo = true;
		}
		if (boo){
			cout<<ans<<" ";
		}else{
			cout<<n<<" ";
		}
	}
	return 0;
}
