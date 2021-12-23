#include <cstdio>
#include <cstdlib>
#include<iostream>
#include<math.h>
#include<limits>

#include "sort.h"
using namespace std;

int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++) {
    sum += (v[i] < 0) ? -v[i] : v[i];
  }

  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int** A, int n, int l, int r)
{ 
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

/*
*   TO IMPLEMENT: Improved Insertion Sort for problem 1.
*/
void insertion_sort_im(int** A, int n, int l, int r)
{ 
   int* key;
   int key_value;
   int* comp_len_arr = new int[r+1];

   int i = 0;
   
   for(int j = 0; j <= r; j++) {
      comp_len_arr[i++] = ivector_length(A[j], n);
   }
   
   for(int j = 1; j <= r; j++) {
      key = A[j];
      key_value = comp_len_arr[j];
      i = j - 1;
	  
      while(i >= l && (comp_len_arr[i] > key_value)) {
         A[i+1] = A[i];
         comp_len_arr[i+1] = comp_len_arr[i];

         i = i - 1;
      }

      A[i+1] = key;
      comp_len_arr[i+1] = key_value;
   }    
}

/*
*   TO IMPLEMENT: Improved Merge Sort for problem 2.
*/
void merge_sort(int** A, int n, int p, int r)
{
	int* comp_len_arr = new int[r+1];
	int i = 0;
	
	for(int j = 0; j <= r; j++) {
		comp_len_arr[i++] = ivector_length(A[j], n);
	}
	
	mergeDivide(A, comp_len_arr, n, p, r);
}

void mergeDivide(int** A, int* comp_len_arr, int n, int p, int r) {
	if(p < r) {
		int midpoint = floor((p + r)/2);
		
		mergeDivide(A, comp_len_arr, n, p, midpoint);
		mergeDivide(A, comp_len_arr, n, midpoint + 1, r); 
		
		mergeSort(A, comp_len_arr, n, p, midpoint, r);
	}
}


void mergeSort(int** A, int* comp_len_arr, int n, int p, int midpoint, int r) {	
	int first_number = midpoint - p + 1;
	int second_number = r - midpoint;
	
	int** left_array = new int*[first_number];
	int* left_length = new int[first_number + 1];
	
	int** right_array = new int*[second_number];
	int* right_length = new int[second_number + 1];
	
	for(int i = 0; i < first_number; i++) {
		left_array[i] = new int[n];
		left_length[i] = comp_len_arr[p + i];
		left_array[i] = A[p + i];
	}
	
	for(int j = 0; j < second_number; j++) {
		right_array[j] = new int[n];
		right_length[j] = comp_len_arr[midpoint + j + 1];
		right_array[j] = A[midpoint + j + 1];
	}
	
	left_length[first_number] = numeric_limits<int>::max();
	right_length[second_number] = numeric_limits<int>::max();
	
	int i = 0;
	int j = 0;
	
	for(int k = p; k <= r; k++) {
		if(left_length[i] <= right_length[j]) {
			comp_len_arr[k] = left_length[i];
			A[k] = left_array[i];
			i += 1;
		} else {
			comp_len_arr[k] = right_length[j];
			A[k] = right_array[j];
			j += 1;
		}
	}
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}

