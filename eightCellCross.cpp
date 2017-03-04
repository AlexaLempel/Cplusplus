//Alexa Lempel

/*8 Numbers Cross Solution*/

#include <iostream>
using namespace std;

bool testsOK(int cr[], int cell);
bool backtrack(int &cell);
void printCross(int cr[], int &solutionCount);


int main() {		
	int cr[8];			//Array of cells in cross
	int cell = 0;			//Cell index

	int solutionCount = 0;		//Keep track of how many solutions
					//are found, for printed headings.

	cr[0]=1;				//Place 1 in upper left square.

	/*While keeps looping until the "backtrack" function confirms 
	  that all possible arrangements have been found. */
	while(true){

		/*If increments cell, then checks if we've exceeded the last 
		  cell in the cross. Prints then backtracks if true.*/
		if(++cell>7){
			printCross(cr,solutionCount);
			backtrack(cell);
		}
		else cr[cell]=0;

		/*While loops numbers 1 through 8 within given cell, and calls tests
		  on each number. Breaks when the given cell passes tests.*/ 
		while(true) {

			/*If increments number, then checks if we've exceeded 8.
			  Backtracks if true.*/
			if(++cr[cell]>8) {
				if(backtrack(cell))	//Backtrack returns true and If
					return 0;	//ends program when all solutions 
							//found.
			} 
			else if(testsOK(cr,cell))
				break;
		}
	}	
}//end main

/*TestsOK checks to see if value in a cell obeys the rules. 
  Returns true if pass, false if fail.*/
bool testsOK(int cr[], int cell){
	
	/*For each cell (represented by a row), indices of 
          which preceding cell(s) are adjacent stored to the left of -1.*/
	int rules[8][5] = {{-1,0,0,0,0},  // 0
			   {0,-1,0,0,0},  // 1
			   {0,-1,0,0,0},  // 2
			   {0,1,2,-1,0},  // 3
			   {0,1,3,-1,0},  // 4
 			   {1,4,-1,0,0},  // 5
			   {2,3,4,-1,0},  // 6 
			   {3,4,5,6,-1}}; // 7

	/*Check no repeats.*/		    
	for(int i = 0; i<cell; i++)
		if(cr[i]==cr[cell]) return false;

	/*Check no adjacent cells with consecutive values.*/
	for(int j=0; rules[cell][j] != -1; j++)
		if(cr[(rules[cell][j])]==cr[cell]-1||cr[(rules[cell][j])]==cr[cell]+1)
			return false;
	return true;	
}

/*Backtrack moves back one cell, and tests if cell has fallen off the left
  side of the cross, indicating that all solutions have been found.
  If yes, returns true, used by main to trigger the end of the program.
  Otherwise, returns false. */ 
bool backtrack(int &cell){
	if(--cell<0) return true;
	return false;
}

/*PrintCross prints the cross.*/
void printCross(int cr[], int &solutionCount){
	int c = 0;
	cout<<endl<<"Solution "<<++solutionCount<<": "<<endl;
	for(int i=0; i<3; i++){
		for(int j=0; j<4; j++) {
			if((i==0||i==2) && (j==0||j==3))cout<<"  ";
			else cout<<cr[c++]<<" ";
		}
		cout<<endl;
	}
	
}

