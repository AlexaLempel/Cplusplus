//Lempel, Alexa

//2D Eight Queens

#include <iostream>
using namespace std;

int main() {
			int b[8][8]  = {0};		//The board, initially blank.
			int col = 0;
			int row;
			int solutionCount = 0;		//Keep track of how many solutions
							//found, for printed headings.

			b[0][0] = 1;			//Seed board with top left queen.

	 next_col:	if(++col>7) goto print;		//Increment column, then
							//print board if all 8 queens
							//are successfully placed.
			row = -1;			//Otherwise, move to top of board.

	 next_row:	if(++row>7) goto backtrack;	//Increment row, then
							//backtrack if we run out of
							//rows in our column.

			for(int i=0; i < col; i++)		//Go to next row if same row
				if(b[row][i] == 1) 		//already has a queen left of 
					goto next_row;		//the current column.

			for(int i=1; i<=col && i <=row; i++)	//Go to next row if up left
				if(b[row - i][col - i] == 1) 	//diagonal already has a queen.
					goto next_row;
			
			for(int i=1; i<=col && i+row<8; i++)	//Go to next row if down left
				if(b[row+i][col-i] == 1) 	//diagonal already has a queen.
					goto next_row;

			b[row][col] = 1;			//Passed all tests, so place a queen. 
			goto next_col;				//And move to next column.

	backtrack:	if(--col<0) return 0;			//Move back a column, then 
								//end if covered all possibilities
			row=0;	
			while(b[row][col]==0)			//Search for this column's queen,
				row++;
			b[row][col] = 0;			//and remove it when found.
			goto next_row;				//Then advance rows.
			

	    print:	cout<<endl<<"Solution "<<++solutionCount<<": "<<endl;
			for(int r=0; r<8; r++) {
				for(int c=0; c<8; c++)
					cout<<b[r][c]<<" ";
				cout<<endl;			//Print board.
			}
			goto backtrack;				//Look for more solutions.
	
}