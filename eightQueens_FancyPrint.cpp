//Alexa Lempel

//Fancy Print -- 1D Eight Queens

#include <iostream>
using namespace std;

int main() {		
			int b[8];			//Our board.
			int col = 0;
			int solutionCount = 0;		//Keep track of how many solutions
							//found, for printed headings.

			typedef string square[5][11];	//Defines type square
			square wb,bb,wq,bq;		//wb=White Box;   bb=Black Box
							//wq=WB w. Queen; bq=BB w. Queen

			square* board[8][8];		//A board-sized array of pointers 
							//to squares.

			string fill = "\u25a9";		  
			string vrline ="\174";		   
			string hzline ="\u2015";	

			/*Fill black and white squares*/
			for(int i=0;i<5;i++){
				for(int j=0;j<11;j++){
					bb[i][j]=fill;
					bq[i][j]=fill;
					wb[i][j]=' ';
					wq[i][j]=' ';
				}
			}
			
			/*Put queen glyph into wq and bq squares*/ 
			for(int i=2;i<4;i++){
				for(int j=3;j<8;j++){
					bq[i][j]=' ';
					wq[i][j]=fill;
				}
			} 
			bq[1][3]=bq[1][5]=bq[1][7]=' ';
			wq[1][3]=wq[1][5]=wq[1][7]=fill;
			
	/*--------------Start finding solutions to 8 Queens--------------*/
			
			b[0]=0;				//Place seed queend in 
							//upper left corner.

	 next_col:	if(++col>7) goto print;		//Increment column, then
							//print board if all 8 queens
							//are successfully placed.

			b[col]=-1;			//Jump to right above board.

	 next_row:	if(++b[col]>7) goto backtrack;	//Increment row, then
							//backtrack if we run out of
							//rows in our column.

			for(int i=0; i<col; i++)
				if(b[i]==b[col] || col-i==abs(b[i]-b[col]))	//Test row
					goto next_row; 				//& diags


			goto next_col;				//Passed tests, move to
								//next col.

	backtrack:	if(--col<0) return 0;			//Move back a column, then 
								//end if covered all
								//possibilities
			
			goto next_row;				//Then advance rows.
			

	    print:	cout<<endl<<"Solution "<<++solutionCount<<": "<<"b{ ";
			for(int i=0; i<8; i++) cout<<b[i]<<" ";
			cout<<"}"<<endl;

			/*Fill *board with alternating wb and bb addresses*/
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					if((i+j)%2)
						board[i][j]=&wb;
					else
						board[i][j]=&bb;
				}
			}
			/*Ammend *board so squares with queens from solution point
			  to the appropriate color wq/bq square.*/
			for(int i=0; i<8; i++){
				if((i+b[i])%2)
					board[i][b[i]]=&wq;
				else
					board[i][b[i]]=&bq;
			}
			
			cout<<"     ";
			for(int i=0;i<11*8;i++)			//Print upper border
				cout<<hzline;
			cout<<endl;
			
			/*Print board*/
			for(int i=0; i<8; i++){
				for(int k=0; k<5; k++){
					cout<<"    "<<vrline;
					for(int j=0; j<8; j++){
						for(int m=0; m<11; m++){
							cout<<(*board[i][j])[k][m];
						}
					}
					cout<<vrline<<endl;
				}
			}
			
			cout<<"     ";				//Print lower border
			for(int i=0;i<11*8;i++)
				cout<<hzline;
			cout<<endl;

			goto backtrack;				//Look for more solutions.
	
}