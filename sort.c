/*
This is a group of sorting algorithms

Author: Roger Barker
Last Edit: 20150831

*/
#include "sort.h"

//------------------------------------------------------------
//Private Definitions
//------------------------------------------------------------
/*
(Put elements of 'a' in heap order, in-place)
procedure heapify(a, count) is
    (start is assigned the index in 'a' of the last parent node)
    (the last element in a 0-based array is at index count-1; find the parent of that element)
    start ← floor ((count - 2) / 2)
    
    while start ≥ 0 do
        (sift down the node at index 'start' to the proper place such that all nodes below
         the start index are in heap order)
        siftDown(a, start, count - 1)
        (go to the next parent node)
        start ← start - 1
    (after sifting down the root all nodes/elements are in heap order)
*/
void heapify( int* arrayToSort, int size );

/*
(Repair the heap whose root element is at index 'start', assuming the heaps rooted at its children are valid)
procedure siftDown(a, start, end) is
    root ← start

    while root * 2 + 1 ≤ end do    (While the root has at least one child)
        child ← root * 2 + 1       (Left child)
        swap ← root                (Keeps track of child to swap with)

        if a[swap] < a[child]
            swap ← child
        (If there is a right child and that child is greater)
        if child+1 ≤ end and a[swap] < a[child+1]
            swap ← child + 1
        if swap = root
            (The root holds the largest element. Since we assume the heaps rooted at the
             children are valid, this means that we are done.)
            return
        else
            swap(a[root], a[swap])
            root ← swap            (repeat to continue sifting down the child now)
*/
void siftDown( int* arrayToSort, int start, int end );

/*
Partition(A,p,r):
	x = A[r]
	i = p - 1
	for j = p to r - 1 do
		if A[j] <= x
			i++
			swap A[i] and A[j]
	swap A[i+1] with A[r]
	return i+1
*/
int partition( int* A, int p, int r);


/*
merge(A,p,q,r):
 n1 <- q - p + 1
 n2 <- r - q
 for i<-1 to n1 do
 	L[i] <- A[p+i-1]
 for j<-1 to n2 do
 	R[j] <- A[q+j]
 
 i = 1, j = 1
 for k<-p to r do
 	if L[i] <= R[j]
 		then A[k] = L[i]
 		i <- i+1
 	else
 		then A[k] = R[j]
 		j <- j+1
*/
void merge( int* arrayToSort, int lhv, int mv, int rhv );

//------------------------------------------------------------
//End Definitions
//------------------------------------------------------------

void selectionSort(int* arrayToSort, int size ){
	int i = 0;
	int j = 0;

	for(i = 0; i < size; i++){
		int min = i;
		int temp = 0;
		for(j = i+1; j < size; j++){
			if(arrayToSort[j] < arrayToSort[min]){
				min = j;
			}
		}
		
		temp = arrayToSort[i];
		arrayToSort[i] = arrayToSort[min];
		arrayToSort[min] = temp;
	}
}

void insertionSort( int* arrayToSort, int size ){
   int i = 0;
   int j = 0;
   int key = 0;
   for( j = 1; j < size; j++ ){
   		key = arrayToSort[j];
   		i = j - 1;
   		while(i >= 0 &&  key < arrayToSort[i]){
   			arrayToSort[i+1] = arrayToSort[i];
   			i = i - 1;
   		}
   		arrayToSort[i+1] = key;
   }
}

void mergeSort( int* arrayToSort, int p, int r ){
	if(p < r){
		int q = p + (r-p)/2;
		mergeSort(arrayToSort,p,q);
		mergeSort(arrayToSort,q+1,r);
		merge(arrayToSort,p,q,r);
	}
}

void merge( int* A, int l, int m, int r ){

	int i,j,k;
	int n1 = m-l+1;
	int n2 = r-m;
	
	int L[n1], R[n2];
	
	for(i = 0; i < n1; i++)
		L[i] = A[l+i];
	
	for(j = 0; j < n2; j++)
		R[j] = A[m+1+j];
		
	i = 0;
	j = 0;
	k = l;
	
	while( i < n1 && j < n2 ){
		if( L[i] <= R[j] )
			A[k] = L[i++];
		else
			A[k] = R[j++];
		k++;
	}
	
	while( i < n1 ){
		A[k] = L[i++];
		k++;
	}
	
	while( j < n2 ){
		A[k] = R[j++];
		k++;
	}
}

void quickSort( int* arrayToSort,int lhv, int rhv){
	if(lhv < rhv){
		int q = partition(arrayToSort,lhv,rhv);
		quickSort(arrayToSort, lhv, q - 1);
		quickSort(arrayToSort, q+1, rhv);
	}
}

int partition( int* A, int p, int r){
	int x = A[r];
	int i = p - 1;
	int j;
	int temp;
	for(j = p; j < r; j++){
		if(A[j] <= x ){
			i++;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	temp = A[i+1];
	A[i+1] = A[r];
	A[r] = temp;
	
	return i+1;
}

void bubbleSort( int* arrayToSort, int size ){
	BOOL swapped = TRUE;
	int j = 0;
	int i = 0;
	int temp;
	
	while( swapped ){
		swapped = FALSE;
		j++;
		for( i = 0; i < size - j; i++ ){
			if(arrayToSort[i] > arrayToSort[i+1]){
				temp = arrayToSort[i];
				arrayToSort[i] = arrayToSort[i+1];
				arrayToSort[i+1] = temp;
				swapped = TRUE;
			}
		}
	}
}

void heapSort( int* arrayToSort, int size ){
	int end;
	int temp;
	heapify( arrayToSort, size );
	
	end = size - 1;
	while( end > 0 ){
		temp = arrayToSort[0];
		arrayToSort[0] = arrayToSort[end];
		arrayToSort[end] = temp;
		end--;
		siftDown(arrayToSort, 0, end);
	}
}

void heapify( int* arrayToSort, int size ){
	int start = floor((size - 2) / 2 );
	
	while( start >= 0 ){
		siftDown( arrayToSort, start, size - 1 );
		start --;
	}
}

void siftDown( int* arrayToSort, int start, int end ){
	int root = start;
	int child;
	int swap;
	int temp;
	while( (root * 2 + 1) <= end ){
		child = root * 2 + 1;
		swap = root;
		
		if( arrayToSort[swap] < arrayToSort[child] ){
			swap = child;
		}
		
		if( (child+1) <= end && arrayToSort[swap] < arrayToSort[child+1] ){
			swap = child + 1;
		}
		
		if( swap == root ){ 
			break; 
		}else{
			temp = arrayToSort[root];
			arrayToSort[root] = arrayToSort[swap];
			arrayToSort[swap] = temp;
			root = swap;
		}
	}
}

//------------------------------------------------------------
void printArray( int* array, int size, int mod){
	int i = 0;
	printf("Array: ");
	for(i = 0; i < size; i++){
		if(i%mod == 0){ printf("\n"); }
		printf("%i ",array[i]);
	}
	
	printf("\n\n");
}

void randomizeArray( int* array, int size, int mod ){
	int i = 0;
	for(i = 0; i < size; i++){
		array[i] = rand() % mod + 1;
	}
}
//------------------------------------------------------------
