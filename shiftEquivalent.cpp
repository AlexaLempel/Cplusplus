//Lempel, Alexa

//A function written to test if two 1D arrays of size n are shift equivalent.

#include <iostream>
using namespace std;

bool shiftEquivalent(int a[], int b[], int n) {
	int i = 0;	//Index in array a
	int j = 0;	//Index in array b
	int success = 0;	//Counts the number of successful a[i]==b[j] matches
	int fail =0;		//Counts failed matched

	while(i < n && fail < n) {	//Loops until shift eq is shown OR too many fails to be possible.  
		
		if(j >= n)
			j = 0;		//Carry the index of b[] if it steps off an edge of the array.
		if(j < 0)
			j += n;
					

		if(a[i] == b[j]) {
			i++;		//If arrays match at given position, sets next loop to check 
			j++;		//if next corresponsponding positions also match.
			success++;	//Keep track of successful matches in case we need to backtrack.
		}
		else {
			i -= success;	//Step back indices of a[] and b[] to before a misleading match 
			j -= success;
			success = 0;	//and resets success counter.
			
			j++;		//Jump to next b[j].
			
			fail++;	//Keep track of failed matches.
		}
	}

	if(fail < n)			//If the number of fails was less than the array size,
		return true;		//then the loop stopped because every a[i] found a corresponding
					//b[j] in the correct order. The arrays are shift equivalent!
	
	else 
		return false;
}


int main() {
   cout << boolalpha; // to show boolean value as "true" or "false"
   
   int a1[5] = {1, 2, 3, 4, 5};
   int a2[5] = {3, 4, 5, 1, 2};
   cout << shiftEquivalent(a1, a2, 5) << endl; // true
   
   int a3[3] = {1, 2, 3};
   int a4[3] = {2, 3, 3};
   cout << shiftEquivalent(a3, a4, 3) << endl; // false
   
   int a5[4] = {1, 1, 0, 1};
   int a6[4] = {1, 0, 1, 1};
   cout << shiftEquivalent(a5, a6, 4) << endl; // true
   
   
   return 0;
}
