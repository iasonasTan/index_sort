#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "index_sort.h"

int main()
{
	const int N=20;
	int arr[N]={};
	srand(time(NULL));
	const int LIMIT=20;
	for(int i=0; i<N; i++) {
		arr[i]=(rand()%LIMIT*2)-LIMIT;
	}

	sort(arr, N);
	print_arr(arr, N);

	int status=is_sorted(arr, N);
	printf("Sorted: %d\n", status);

	return 0;
}
