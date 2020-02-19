#include <stdio.h>
#include <iostream>
#include <math.h>

#include <ctime> 
using namespace std; 
  
// To generate random number 
// between x and y ie.. [x, y] 
int getRandom(int x, int y) 
{ 
    srand(time(NULL)); 
    return (x + rand() % (y-x+1)); 
} 
  
// A recursive randomized binary search function. 
// It returns location of x in 
// given array arr[l..r] is present, otherwise -1 
int randomFind(int *arr, int x , int l, int r) 
{ 
    if (r >= l) 
    { 
        // Here we have defined middle as 
        // random index between l and r ie.. [l, r] 
        int mid = getRandom(l, r); 
  
        // If the element is present at the 
        // middle itself 
        if (arr[mid] == x) 
            return mid; 
  
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (arr[mid] > x) 
          return randomFind(arr, x, l, 
                                    mid-1); 
  
        // Else the element can only be present 
        // in right subarray 
        return randomFind(arr, x, mid+1, 
                                         r); 
    } 
  
    // We reach here when element is not present 
    // in array 
    return -1; 
} 

int interpFind(int *arr, int x, int start, int end)
{
    // Find indexes of two corners
    int lo = start, hi = (end - 1);

    // Since array is sorted, an element present
    // in array must be in range defined by corner
    while (lo <= hi && x >= arr[lo] && x <= arr[hi])
    {
        if (lo == hi)
        {
            if (arr[lo] == x)
                return lo;
            return -1;
        }
        // Probing the position with keeping
        // uniform distribution in mind.
        int pos = lo + (((double)(hi - lo) /
                         (arr[hi] - arr[lo])) *
                        (x - arr[lo]));

        // Condition of target found
        if (arr[pos] == x)
            return pos;

        // If x is larger, x is in upper part
        if (arr[pos] < x)
            lo = pos + 1;

        // If x is smaller, x is in the lower part
        else
            hi = pos - 1;
    }
    return -1;
}

int seqFind(int *A, int x, int start, int end)
{

    for (int i = start; i <= end; i++)
    {
        if (A[i] == x)
            return i;
    }
    return -1;
}

int sipFind(int *A, int x, int start, int end, int guard=4)
{

    int left = start, right = end;
    int invslope = ((double)(A[right] - A[left]) /
                    (double)(right - left));
    int diff;
    x > A[left] ? diff = (double)x - (double)(A[left]) : diff = left;
    int expected = left +
                   diff / invslope;
    std::cout << "PRIMO CALCOLO " << left << " " << right << " " << expected << std::endl;
    while (left < right && left <= expected && right >= expected)
    {
        if (A[expected] < x)
        {
            left = expected + 1;
        }
        else if (A[expected] > x)
        {
            right = expected - 1;
        }
        else
        {
            return expected;
        }

        expected = expected +
                   ((double)x - (double)(A[expected])) / invslope;
        std::cout << "WHILE " << left << " " << right << " " << expected << std::endl;
        if(expected < 0 || expected + guard >= right || expected - guard <= left) 
            return seqFind(A, x, left, right);       
    }
    return -1;
}

int tipFind(int *A, int x, int start, int end, int guard=8)
{
    int left = start, right = end;
    int mid = end/2;
    int y0 = A[left] - x;
    int y1 = A[mid] - x;
    int y2 = A[right] - x;
    int expected = mid + ((y1*(mid-left)*(1+(y0-y1)/(y1-y2)))/y0-y2*((y0-y1)/(y1-y2)));

    while (left < right && left <= expected && right >= expected){

        if(abs(expected - mid) < guard){
            return seqFind(A, x, left, right);
        }
        if(A[mid] != A[expected]){
            left = mid;
        }else{
            right = mid;
        }
        if(expected+guard >= right || expected-guard <= left){
            return seqFind(A, x, left, right);
        }

        mid = expected;
        y0 = A[left] - x;
        y1 = A[mid] - x;
        y2 = A[right] - x;
        expected = mid + (y1*(mid-right)*(mid-left)*(y2-y0))/(y2*(mid-right)*(y0-y1)+y0*(mid-left)*(y1-y2));
    }
    return -1;
    
}

int branchfreeBS(int * A, int x,  int left, int right){
    const int *base = A+left;
    int n = right-left+1;
    while (n > 1) {
        const int half = n / 2;
        //printf("%d\n",half);
        base = (base[half] < x) ? &base[half] : base;
        n -= half;
    }
    return (*base < x) + base - A;
}

int prefetchBS(int * A, int x,  int left, int right){
    const int *base = A;
    int n = right;
    while (n > 1) {
        const int half = n / 2;
        base = (base[half] < x) ? &base[half] : base;
        n -= half;
    }
    return (*base < x) + base - A;
}

int* eytzeingerArray(int *A, int **B, int i, int n){
    

    if(i >= n) return A;

    A = eytzeingerArray(A, B,  2*i+1, n);

    B[0][i] = *A++;

    A = eytzeingerArray(A, B, 2*i+2, n);
}

int prefetchEytzBS(int * A, int x,  int left, int right){
    
    int i = 0;
    int n = right;
    int multiplier = 128;
    int offset = 3*multiplier/2-1;

    while (i < n) {
        __builtin_prefetch(A+(multiplier*i + offset));
        i = (x <= A[i]) ? (2*i + 1) : (2*i + 2);
    }
    int j = (i+1) >> __builtin_ffs(~(i+1));
    return (j == 0) ? n : j-1;
}

int prefetchBranchfreeIS(int * A, int x,  int left, int right){
    
    const int *base = A+left;
    int i = left;
    int n = right-left+1;
    int multiplier = 128;
    int offset = 3*multiplier/2-1;

    x = (x < A[left]) ? A[left] : x;
    x = (x > A[right]) ? A[right] : x;
    while (n > 1) {

        __builtin_prefetch(A+(multiplier*i + offset));
        double prod = (double)(x - *base)/(*(base+n-1) - *base);
        int pivot = (base-A) + (n-1) * floor(prod);
       

       
        if(*base == x){
            return base - A;
        }
        n = (*(base) < x) ? n-(pivot-(base-A)+1) : pivot-(base-A)+1;
        base = (*(base +pivot) < x) ? base+pivot : base;
        
    }
    return (*base < x) + base - A;
}

