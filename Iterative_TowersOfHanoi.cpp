//Lempel, Alexa
//CS211 Section 52C, Homework 14

/*Iterative Towers of Hanoi Solution*/

#include <iostream>
#include <vector>
using namespace std;

/*nextTo returns index of the next tower to the left or right of "from," wrapping around
  the set of three towers in the appropriate direction when >3 or <0. */    
int nextTo(int from, int direction){
	return (from+direction+3)%3;
}

int main(){
	int rings, to, from, candi, move, direction;

	vector<int> tower[3];

	cout<<"Enter a (positive integer) number of rings to be moved:"<<endl;
	cin>>rings;
	cout<<endl;

	/*Set direction based on odd/even number of rings.*/ 
	if(rings%2)  direction = 1;	//If odd, nextTo moves to right.
	else	direction = -1;		//Even, nextTo moves to left.

	/*Initialize towers*/
	for(int i=rings+1; i>0; i--)
		tower[0].push_back(i);	//Tower A
	tower[1].push_back(rings+1);	//Tower B
	tower[2].push_back(rings+1);	//Tower C

	/*Set up first move.*/
	move = 0;
	candi = 1;
	from = 0;
	to = nextTo(from, direction);

	/*Iterate through moves until all rings are on tower B*/
	while(tower[1].size()<rings+1){

		/*Describe move to user*/
		cout<<"Move number "<<++move<<": Transfer ring "<<candi<<
			" from tower "<<char(from+65)<<" to tower "<<char(to+65)<<endl;
		
		/*Perform move*/
		tower[to].push_back(candi);
		tower[from].pop_back();

		/*Select next candidate ring, and make the tower it's on the
		  "from" tower.*/
		if( tower[(to+1)%3].back() < tower[(to+2)%3].back() )
			from =(to+1)%3;
		else
			from =(to+2)%3;

		candi = tower[from].back();
		
		/*Pick next "to" tower to place the candidate ring on*/
		to = nextTo(from, direction);
		if( candi > tower[to].back() ) 
			to = nextTo(to, direction);
		
	}

	return 0;
}