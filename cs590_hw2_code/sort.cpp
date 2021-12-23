#include <cstdio>
#include <cstdlib>

#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	return -1;
      else
	return 1;
    }
} /*>>>*/

void insertion_sort(char** A, int l, int r)
{ 
	int i;
	char* key;

	for (int j = l+1; j <= r; j++)
	{
		key = A[j];
		i = j - 1;

		while ((i >= l) && (string_compare(A[i], key) > 0))
		{
			A[i+1] = A[i];
			i = i - 1;
		}

		A[i+1] = key;
	}
}

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{
	char* key;
	int key_length;
	int i;
	char temp_id;
	char key_id;
	
	for(int j = 1; j <= r; j++)
	{
		key = A[j];
		key_length = A_len[j];
		i = j - 1;
		
		if(A_len[i] < d)
		{
			temp_id = 0;
		}
		else
		{
			temp_id = A[i][d];
		}
		
		if(key_length < d)
		{
			key_id = 0;
		}
		else
		{
			key_id = key[d];
		}
		
		while(i >= 0 && (temp_id > key_id))
		{
			A_len[i+1] = A_len[i];
			A[i+1] = A[i];
			i = i - 1;
			
			if(i >= 0)
			{
				if(A_len[i] < d)
				{
					temp_id = 0;
				}
				else
				{
					temp_id = A[i][d];
				}
			}
		}
		A_len[i+1] = key_length;	
		A[i+1] = key;
	}
}

void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d)
{
int* countArray = new int[256];

  for(int i = 0; i <256; i++) 
  {
	  countArray[i] = 0;
  }
  
  for(int i=0; i <n; i++){
    if(A_len[i]-1>=d)
	{
      countArray[A[i][d]] += 1;
    }
    else
	{
      countArray[0] += 1;
    }

  }
  for(int i = 1; i <255;i++){
    countArray[i] += countArray[i-1];
  }

  for(int j = n-1;j >=0;--j){
    if(A_len[j]-1>=d){
        B[countArray[A[j][d]]-1] = A[j];
        B_len[countArray[A[j][d]]-1] = A_len[j];
        --countArray[A[j][d]];
    }
    else{
      B[countArray[0]-1] = A[j];
      B_len[countArray[0]-1] = A_len[j];
      --countArray[0];
    }
  }
  
  for(int i = 0; i < n;i++){
    A[i] = B[i];
    A_len[i] =B_len[i];
  }
}

void radix_sort_is(char** A, int* A_len, int n, int m)
{
	for(int i = m-1; i >= 0; i--)
	{
		insertion_sort_digit(A, A_len, 0, n-1, i);
	}
}

void radix_sort_cs(char** A, int* A_len, int n, int m)
{ 
	char** B;
	int* B_len;
	B = new char* [n];
	B_len = new int[n];
	char** A_temp;
	int* A_temp_length;
	char** B_temp;
	int* B_temp_length;
	A_temp = A;
	B_temp = B;
	A_temp_length = A_len;
	B_temp_length = B_len;
	
	for(int i = m-1; i >= 0; i--)
	{
		counting_sort_digit(A_temp, A_temp_length, B_temp, B_temp_length, n-1, i);
	}
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}