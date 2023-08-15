#include "network_sort.h"
#include <stdlib.h>

#define COMPARE_SWAP(a, b) {int x = base[a]; int y = base[b]; base[a] = x > y ? y : x; base[b] = x > y ? x : y;}

void network_sort(int* base, int length, int (*compare)(const void*, const void*)) {
	switch(length) {
		case 11:
			network_sort11(base, compare);
			break;
		case 12:
			network_sort12(base, compare);
			break;
		case 13:
			network_sort13(base, compare);
			break;
		case 14:
			network_sort14(base, compare);
			break;
		case 15:
			network_sort15(base, compare);
			break;
		case 16:
			network_sort16(base, compare);
			break;
		default:
			qsort(base, length, sizeof(int), compare);
	}
}

// For small numbers of elements, sorting networks turn out to be more efficient than qsort.
// Initial testing shows a 15%-20% speedup in the overall generation performance
// https://www.cs.brandeis.edu/~hugues/sorting_networks.html
// The implementations lower than 16 inputs were developed by simply removing the affected sort lines

void network_sort11(int* base, int (*compare)(const void*, const void*)) {
	COMPARE_SWAP(0,1)
	COMPARE_SWAP(2,3)
	COMPARE_SWAP(4,5)
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
	//COMPARE_SWAP(10,11)
	//COMPARE_SWAP(12,13)
	//COMPARE_SWAP(14,15)
	
	
	COMPARE_SWAP(0,2)
	COMPARE_SWAP(4,6)
	COMPARE_SWAP(8,10)
	//COMPARE_SWAP(12,14)
	
	COMPARE_SWAP(1,3)
	COMPARE_SWAP(5,7)
	//COMPARE_SWAP(9,11)
	//COMPARE_SWAP(13,15)
	
	
	COMPARE_SWAP(0,4)
	//COMPARE_SWAP(8,12)
	
	COMPARE_SWAP(1,5)
	//COMPARE_SWAP(9,13)
	
	COMPARE_SWAP(2,6)
	//COMPARE_SWAP(10,14)
	
	COMPARE_SWAP(3,7)
	//COMPARE_SWAP(11,15)
	
	
	COMPARE_SWAP(0,8)
	COMPARE_SWAP(1,9)
	COMPARE_SWAP(2,10)
	//COMPARE_SWAP(3,11)
	//COMPARE_SWAP(4,12)
	//COMPARE_SWAP(5,13)
	//COMPARE_SWAP(6,14)
	//COMPARE_SWAP(7,15)
	
	COMPARE_SWAP(5,10)
	COMPARE_SWAP(6,9)
	//COMPARE_SWAP(3,12)
	//COMPARE_SWAP(13,14)
	//COMPARE_SWAP(7,11)
	
	COMPARE_SWAP(1,2)
	COMPARE_SWAP(4,8)
	COMPARE_SWAP(1,4)
	//COMPARE_SWAP(7,13)
	
	COMPARE_SWAP(2,8)
	//COMPARE_SWAP(11,14)
	
	COMPARE_SWAP(2,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(9,10)
	//COMPARE_SWAP(11,13)
	
	COMPARE_SWAP(3,8)
	
	//COMPARE_SWAP(7,12)
	
	COMPARE_SWAP(6,8)
	//COMPARE_SWAP(10,12)
	
	COMPARE_SWAP(3,5)
	COMPARE_SWAP(7,9)
	
	COMPARE_SWAP(3,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(7,8)
	COMPARE_SWAP(9,10)
	//COMPARE_SWAP(11,12)
	
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
}

void network_sort12(int* base, int (*compare)(const void*, const void*)) {
	COMPARE_SWAP(0,1)
	COMPARE_SWAP(2,3)
	COMPARE_SWAP(4,5)
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
	COMPARE_SWAP(10,11)
	//COMPARE_SWAP(12,13)
	//COMPARE_SWAP(14,15)
	
	
	COMPARE_SWAP(0,2)
	COMPARE_SWAP(4,6)
	COMPARE_SWAP(8,10)
	//COMPARE_SWAP(12,14)
	
	COMPARE_SWAP(1,3)
	COMPARE_SWAP(5,7)
	COMPARE_SWAP(9,11)
	//COMPARE_SWAP(13,15)
	
	
	COMPARE_SWAP(0,4)
	//COMPARE_SWAP(8,12)
	
	COMPARE_SWAP(1,5)
	//COMPARE_SWAP(9,13)
	
	COMPARE_SWAP(2,6)
	//COMPARE_SWAP(10,14)
	
	COMPARE_SWAP(3,7)
	//COMPARE_SWAP(11,15)
	
	
	COMPARE_SWAP(0,8)
	COMPARE_SWAP(1,9)
	COMPARE_SWAP(2,10)
	COMPARE_SWAP(3,11)
	//COMPARE_SWAP(4,12)
	//COMPARE_SWAP(5,13)
	//COMPARE_SWAP(6,14)
	//COMPARE_SWAP(7,15)
	
	COMPARE_SWAP(5,10)
	COMPARE_SWAP(6,9)
	//COMPARE_SWAP(3,12)
	//COMPARE_SWAP(13,14)
	COMPARE_SWAP(7,11)
	
	COMPARE_SWAP(1,2)
	COMPARE_SWAP(4,8)
	COMPARE_SWAP(1,4)
	//COMPARE_SWAP(7,13)
	
	COMPARE_SWAP(2,8)
	//COMPARE_SWAP(11,14)
	
	COMPARE_SWAP(2,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(9,10)
	//COMPARE_SWAP(11,13)
	
	COMPARE_SWAP(3,8)
	
	//COMPARE_SWAP(7,12)
	
	COMPARE_SWAP(6,8)
	//COMPARE_SWAP(10,12)
	
	COMPARE_SWAP(3,5)
	COMPARE_SWAP(7,9)
	
	COMPARE_SWAP(3,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(7,8)
	COMPARE_SWAP(9,10)
	//COMPARE_SWAP(11,12)
	
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
}


void network_sort13(int* base, int (*compare)(const void*, const void*)) {
	COMPARE_SWAP(0,1)
	COMPARE_SWAP(2,3)
	COMPARE_SWAP(4,5)
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
	COMPARE_SWAP(10,11)
	//COMPARE_SWAP(12,13)
	//COMPARE_SWAP(14,15)
	
	
	COMPARE_SWAP(0,2)
	COMPARE_SWAP(4,6)
	COMPARE_SWAP(8,10)
	//COMPARE_SWAP(12,14)
	
	COMPARE_SWAP(1,3)
	COMPARE_SWAP(5,7)
	COMPARE_SWAP(9,11)
	//COMPARE_SWAP(13,15)
	
	
	COMPARE_SWAP(0,4)
	COMPARE_SWAP(8,12)
	
	COMPARE_SWAP(1,5)
	//COMPARE_SWAP(9,13)
	
	COMPARE_SWAP(2,6)
	//COMPARE_SWAP(10,14)
	
	COMPARE_SWAP(3,7)
	//COMPARE_SWAP(11,15)
	
	
	COMPARE_SWAP(0,8)
	COMPARE_SWAP(1,9)
	COMPARE_SWAP(2,10)
	COMPARE_SWAP(3,11)
	COMPARE_SWAP(4,12)
	//COMPARE_SWAP(5,13)
	//COMPARE_SWAP(6,14)
	//COMPARE_SWAP(7,15)
	
	COMPARE_SWAP(5,10)
	COMPARE_SWAP(6,9)
	COMPARE_SWAP(3,12)
	//COMPARE_SWAP(13,14)
	COMPARE_SWAP(7,11)
	
	COMPARE_SWAP(1,2)
	COMPARE_SWAP(4,8)
	COMPARE_SWAP(1,4)
	//COMPARE_SWAP(7,13)
	
	COMPARE_SWAP(2,8)
	//COMPARE_SWAP(11,14)
	
	COMPARE_SWAP(2,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(9,10)
	//COMPARE_SWAP(11,13)
	
	COMPARE_SWAP(3,8)
	
	COMPARE_SWAP(7,12)
	
	COMPARE_SWAP(6,8)
	COMPARE_SWAP(10,12)
	
	COMPARE_SWAP(3,5)
	COMPARE_SWAP(7,9)
	
	COMPARE_SWAP(3,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(7,8)
	COMPARE_SWAP(9,10)
	COMPARE_SWAP(11,12)
	
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
}

void network_sort14(int* base, int (*compare)(const void*, const void*)) {
	COMPARE_SWAP(0,1)
	COMPARE_SWAP(2,3)
	COMPARE_SWAP(4,5)
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
	COMPARE_SWAP(10,11)
	COMPARE_SWAP(12,13)
	//COMPARE_SWAP(14,15)
	
	
	COMPARE_SWAP(0,2)
	COMPARE_SWAP(4,6)
	COMPARE_SWAP(8,10)
	//COMPARE_SWAP(12,14)
	
	COMPARE_SWAP(1,3)
	COMPARE_SWAP(5,7)
	COMPARE_SWAP(9,11)
	//COMPARE_SWAP(13,15)
	
	
	COMPARE_SWAP(0,4)
	COMPARE_SWAP(8,12)
	
	COMPARE_SWAP(1,5)
	COMPARE_SWAP(9,13)
	
	COMPARE_SWAP(2,6)
	//COMPARE_SWAP(10,14)
	
	COMPARE_SWAP(3,7)
	//COMPARE_SWAP(11,15)
	
	
	COMPARE_SWAP(0,8)
	COMPARE_SWAP(1,9)
	COMPARE_SWAP(2,10)
	COMPARE_SWAP(3,11)
	COMPARE_SWAP(4,12)
	COMPARE_SWAP(5,13)
	//COMPARE_SWAP(6,14)
	//COMPARE_SWAP(7,15)
	
	COMPARE_SWAP(5,10)
	COMPARE_SWAP(6,9)
	COMPARE_SWAP(3,12)
	//COMPARE_SWAP(13,14)
	COMPARE_SWAP(7,11)
	
	COMPARE_SWAP(1,2)
	COMPARE_SWAP(4,8)
	COMPARE_SWAP(1,4)
	COMPARE_SWAP(7,13)
	
	COMPARE_SWAP(2,8)
	//COMPARE_SWAP(11,14)
	
	COMPARE_SWAP(2,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(9,10)
	COMPARE_SWAP(11,13)
	
	COMPARE_SWAP(3,8)
	
	COMPARE_SWAP(7,12)
	
	COMPARE_SWAP(6,8)
	COMPARE_SWAP(10,12)
	
	COMPARE_SWAP(3,5)
	COMPARE_SWAP(7,9)
	
	COMPARE_SWAP(3,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(7,8)
	COMPARE_SWAP(9,10)
	COMPARE_SWAP(11,12)
	
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
}


void network_sort15(int* base, int (*compare)(const void*, const void*)) {
	COMPARE_SWAP(0,1)
	COMPARE_SWAP(2,3)
	COMPARE_SWAP(4,5)
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
	COMPARE_SWAP(10,11)
	COMPARE_SWAP(12,13)
	//COMPARE_SWAP(14,15)
	
	
	COMPARE_SWAP(0,2)
	COMPARE_SWAP(4,6)
	COMPARE_SWAP(8,10)
	COMPARE_SWAP(12,14)
	
	COMPARE_SWAP(1,3)
	COMPARE_SWAP(5,7)
	COMPARE_SWAP(9,11)
	//COMPARE_SWAP(13,15)
	
	
	COMPARE_SWAP(0,4)
	COMPARE_SWAP(8,12)
	
	COMPARE_SWAP(1,5)
	COMPARE_SWAP(9,13)
	
	COMPARE_SWAP(2,6)
	COMPARE_SWAP(10,14)
	
	COMPARE_SWAP(3,7)
	//COMPARE_SWAP(11,15)
	
	
	COMPARE_SWAP(0,8)
	COMPARE_SWAP(1,9)
	COMPARE_SWAP(2,10)
	COMPARE_SWAP(3,11)
	COMPARE_SWAP(4,12)
	COMPARE_SWAP(5,13)
	COMPARE_SWAP(6,14)
	//COMPARE_SWAP(7,15)
	
	COMPARE_SWAP(5,10)
	COMPARE_SWAP(6,9)
	COMPARE_SWAP(3,12)
	COMPARE_SWAP(13,14)
	COMPARE_SWAP(7,11)
	
	COMPARE_SWAP(1,2)
	COMPARE_SWAP(4,8)
	COMPARE_SWAP(1,4)
	COMPARE_SWAP(7,13)
	
	COMPARE_SWAP(2,8)
	COMPARE_SWAP(11,14)
	
	COMPARE_SWAP(2,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(9,10)
	COMPARE_SWAP(11,13)
	
	COMPARE_SWAP(3,8)
	
	COMPARE_SWAP(7,12)
	
	COMPARE_SWAP(6,8)
	COMPARE_SWAP(10,12)
	
	COMPARE_SWAP(3,5)
	COMPARE_SWAP(7,9)
	
	COMPARE_SWAP(3,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(7,8)
	COMPARE_SWAP(9,10)
	COMPARE_SWAP(11,12)
	
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
}

void network_sort16(int* base, int (*compare)(const void*, const void*)) {
	COMPARE_SWAP(0,1)
	COMPARE_SWAP(2,3)
	COMPARE_SWAP(4,5)
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
	COMPARE_SWAP(10,11)
	COMPARE_SWAP(12,13)
	COMPARE_SWAP(14,15)
	
	
	COMPARE_SWAP(0,2)
	COMPARE_SWAP(4,6)
	COMPARE_SWAP(8,10)
	COMPARE_SWAP(12,14)
	
	COMPARE_SWAP(1,3)
	COMPARE_SWAP(5,7)
	COMPARE_SWAP(9,11)
	COMPARE_SWAP(13,15)
	
	
	COMPARE_SWAP(0,4)
	COMPARE_SWAP(8,12)
	
	COMPARE_SWAP(1,5)
	COMPARE_SWAP(9,13)
	
	COMPARE_SWAP(2,6)
	COMPARE_SWAP(10,14)
	
	COMPARE_SWAP(3,7)
	COMPARE_SWAP(11,15)
	
	
	COMPARE_SWAP(0,8)
	COMPARE_SWAP(1,9)
	COMPARE_SWAP(2,10)
	COMPARE_SWAP(3,11)
	COMPARE_SWAP(4,12)
	COMPARE_SWAP(5,13)
	COMPARE_SWAP(6,14)
	COMPARE_SWAP(7,15)
	
	COMPARE_SWAP(5,10)
	COMPARE_SWAP(6,9)
	COMPARE_SWAP(3,12)
	COMPARE_SWAP(13,14)
	COMPARE_SWAP(7,11)
	
	COMPARE_SWAP(1,2)
	COMPARE_SWAP(4,8)
	COMPARE_SWAP(1,4)
	COMPARE_SWAP(7,13)
	
	COMPARE_SWAP(2,8)
	COMPARE_SWAP(11,14)
	
	COMPARE_SWAP(2,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(9,10)
	COMPARE_SWAP(11,13)
	
	COMPARE_SWAP(3,8)
	
	COMPARE_SWAP(7,12)
	
	COMPARE_SWAP(6,8)
	COMPARE_SWAP(10,12)
	
	COMPARE_SWAP(3,5)
	COMPARE_SWAP(7,9)
	
	COMPARE_SWAP(3,4)
	COMPARE_SWAP(5,6)
	COMPARE_SWAP(7,8)
	COMPARE_SWAP(9,10)
	COMPARE_SWAP(11,12)
	
	COMPARE_SWAP(6,7)
	COMPARE_SWAP(8,9)
}
