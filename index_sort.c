#include "index_sort.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int* array;
	const int n;
} Array;

void print_arr(int*, int);
void sort(int*, int);
static void add(int*, int*, int);

static int get_map_n (int* arr, int n, const int pos) {
	int out=arr[0];
	for(int i=1; i<n; i++) {
		if (pos&&out<arr[i])
			out=arr[i];
		if (!pos&&out>arr[i])
			out=arr[i];
	}
	return abs(out);
}

static void init_maps(int* main_arr, int main_n, 
	int* map_neg, int* map_zero, int* map_pos) {

	for(int i=0; i<main_n; i++) {
		int curr=main_arr[i];
		if(curr>0) {
			map_pos[curr]++;
		} else if (curr<0) {
			map_neg[abs(curr)]++;
		} else {
			(*map_zero)++;
		}
	}
}

static void extract_map(int* main_arr, int* map_neg, int map_neg_n,
	int map_zero, int* map_pos, int map_pos_n) {

	int arr_idx=0;
	for (int i=map_neg_n-1; i>0; i--) {
		while(map_neg[i]>0) {
			add(main_arr, &arr_idx, -i);
			map_neg[i]--;
		}
	}
	while(map_zero>0) {
		add(main_arr, &arr_idx, 0);
		map_zero--;
	}
	for(int i=0; i<map_pos_n; i++) {
		while(map_pos[i]>0) {
			add(main_arr, &arr_idx, i);
			map_pos[i]--;
		}
	}

}

void sort(int* arr, const int n) {
	int map_zero=0;
	const int map_neg_n=get_map_n(arr, n, 0)+1;
	const int map_pos_n=get_map_n(arr, n, 1)+1;
	int* map_neg=calloc(map_neg_n, sizeof(int));
	int* map_pos=calloc(map_pos_n, sizeof(int));

	init_maps(arr, n, map_neg, &map_zero, map_pos);
	extract_map(arr, map_neg, map_neg_n, map_zero, map_pos, map_pos_n);
	
	free(map_pos);
	free(map_neg);
}

static void add(int* arr, int* idx_p, int v) {
	arr[(*idx_p)]=v;
	(*idx_p)++;
}

void print_arr(int* arr, int n) {
	for(int i=0; i<n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int is_sorted(int* arr, int n) {
	int prev=arr[0];
	for(int i=1; i<n; i++) {
		if (prev>arr[i])
			return 0;
		prev=arr[i];
	}
	return 1;
}
