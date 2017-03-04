//Lempel, Alexa

/* 1D 8 Queens Solution, without goto */

#include <iostream>
using namespace std;

bool testsOK(int b[], int col);
bool backtrack(int &col);
void printBoard(int b[], int n, int &solutionCount);


int main() {		
	int n = 8;			//Size of board.
	int b[n];			//Our board.
	int col = 0;			//Column index.

	int solutionCount = 0;		//Keep track of how many solutions
					//are found, for printed headings.

	b[0]=0;				//Place queen in upper left square.
	
	/*While keeps looping until the "backtrack" function confirms 
	  that all possible 8 Queen arrangements have been found. */
	while(true){

		/*If increments column, then checks if we've exceeded the last 
		  column on the board. Prints then backtracks if true.*/
		if(++col>n-1) {
			printBoard(b, n, solutionCount);
			backtrack(col);
		}
		else b[col]=-1;		//Otherwise, jump to above board.				
		
		/*While loops through rows within given col, and calls tests
		  on each row. Breaks when a given spot passes tests.*/ 	
		while(true) {
			/*If increments row, then checks if we've exceeded 
			  the last row on the board. Backtracks if true.*/
			if(++b[col]>n-1){
				if(backtrack(col))	//Backtrack returns true and If
					return 0;	//ends program when all solutions found.
			}			
			else if(testsOK(b, col))
				break;

		}					
	}	
}//end main

/*TestsOK does row and diagonal tests. Returns true if pass, false if fail.*/
bool testsOK(int b[], int col) {
	for(int i=0; i<col; i++)
		if(b[i]==b[col] || col-i==abs(b[i]-b[col]))
			return false;
	return true;

}//end tests

/*Backtrack moves back one column,and tests if col has fallen off the left
  side of the board, indicating that all solutions have been found.
  If yes, returns true. used by main to trigger the end of the program.
  Otherwise, returns false. */ 
bool backtrack(int &col) {
	if(--col<0)
		return true;
	return false;	
}//end backtrack

/*PrintBoard prints the board.*/
void printBoard(int b[], int n, int &solutionCount) {
	cout<<endl<<"Solution "<<++solutionCount<<": "<<"b{ ";
	for(int i=0; i<n; i++) cout<<b[i]<<" ";
	cout<<"}"<<endl;

	for(int j=0; j<n; j++) {
		for(int i=0; i<n; i++) {
			if(b[i]==j) cout<<1<<" ";
			else cout<<0<<" ";
		}
		cout<<endl;
	}		
}//end printBoard
