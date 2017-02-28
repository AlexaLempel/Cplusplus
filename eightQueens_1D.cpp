//Lempel, Alexa

//1D Eight Queens Solutions 

#include <iostream>
using namespace std;

int main() {		
			int n= 8;
			int b[n];			//Our board.
			int col = 0;
			int solutionCount = 0;		//Keep track of how many solutions
							//found, for printed headings.
			b[0]=0;
		

	 next_col:	if(++col>n-1) goto print;	//Increment column, then
							//print board if all 8 queens
							//are successfully placed.

			b[col]=-1;			//Jump to right above board.

	 next_row:	if(++b[col]>n-1) goto backtrack;	//Increment row, then
								//backtrack if we run out of
								//rows in our column.

			for(int i=0; i<col; i++)
				if(b[i]==b[col] || col-i==abs(b[i]-b[col]))	//Test row & diags
					goto next_row;

			goto next_col;				//Passed tests, move to next col.

	backtrack:	if(--col<0) return 0;			//Move back a column, then 
								//end if covered all possibilities
			
			goto next_row;				//Then advance rows.
			

	    print:	cout<<endl<<"Solution "<<++solutionCount<<": "<<"b{ ";
			for(int i=0; i<n; i++) cout<<b[i]<<" ";
			cout<<"}"<<endl;

			for(int j=0; j<n; j++) {		//Print the board.
				for(int i=0; i<n; i++) {
					if(b[i]==j) cout<<1<<" ";
					else cout<<0<<" ";
				}
			cout<<endl;
			}

			goto backtrack;				//Look for more solutions.
	
}
