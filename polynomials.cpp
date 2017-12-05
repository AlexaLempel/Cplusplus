#include <fstream>
#include <map>

/*A class for dealing with polynomials specified by a file called input.txt
 *  in the same directory as the program. 
 *  Each line (terminated by a newline character) in the file will represent
 *  a polynomial. The line will contain a list of integers, which when taken
 *  in pairs, will represents the coefficient and exponent of each of the 
 *  terms in the polynomial.*/
class Poly{

	/* A map of the polynomial terms, <power,base>. 
	 * The map data structure was chosen to simplify the process
	 * of outputting the polynomials in canonical form, which requires
	 * that: (a) The polynomial is written from the highest powers to
	 * the lowest, and (b) All terms with the same power are consolidated.*/ 
	std::map<int,int> poly;	

	public:

	/*Default constructor*/
	Poly(){}

	/*Copy constructor*/
	Poly(const Poly & p){
		poly = p.poly;
	}

	/*Construct from file stream*/
	Poly(std::ifstream & fin){
		int power, base;	
		std::map<int,int>::iterator it;
		
		/*Skip over  newline character from the preceding istream line*/
		if(fin.peek() == '\n') fin.ignore();

		/*Loop while there is still more stream, and the next char
		 *is not a newline character.*/
		while(fin.good() && fin.peek() != '\n'){
			/*Extract next base-power pair*/
			fin >> base >> power; 
			/*Ignore if base is 0.*/
			if( base ){
				/*Do we already have a term for this power?*/
				it = poly.find(power);
				/*If yes, combine the terms*/
				if(it != poly.end()){
					poly[power] += base;
					if( ! poly[power] ) //Remove if now 0.
						poly.erase(power);
				}
				/*Otherwise enter as a new term*/
				else
					poly[power] = base;			
			}
		}
	}
	
	/*Overloaded Addition Operator*/
	Poly operator+(const Poly & p){
		std::map<int,int>::iterator it;
		int power, base;
		Poly temp(*this); //Copy initialize temp from left-hand side.
		
		/*Loop through every term of right-hand side*/
		for(auto i : p.poly){
			power = i.first;
			base = i.second;
			/*Ignore if base is 0.*/
			if( base ){
				/*Do we already have a term for this power?*/
				it = temp.poly.find(power);
				/*If yes, combine the terms*/
				if(it != temp.poly.end()){
					temp.poly[power] += base;
					if( ! temp.poly[power] ) //Remove if now 0.
						temp.poly.erase(power);
				}
				/*Otherwise enter as a new term*/
				else
					temp.poly[power] = base;			
			}
		}
		return temp; //Return combined Poly by value
	}

	/*Overloaded Subtraction Operator*/
	Poly operator-(const Poly & p){	
		std::map<int,int>::iterator it;
		int power, base;
		Poly temp(*this);
		
		for(auto i : p.poly){
			power = i.first;
			base = i.second;
			/*Ignore if base is 0.*/
			if( base ){
				/*Do we already have a term for this power?*/
				it = temp.poly.find(power);
				/*If yes, combine the terms*/
				if(it != temp.poly.end()){
					temp.poly[power] -= base;
					if( ! temp.poly[power] ) //Remove if now 0.
						temp.poly.erase(power);
				}
				/*Otherwise enter as a new term*/
				else
					temp.poly[power] = -1*base;		
			}
		}
		return temp; //Return combined Poly by value.
	}

	/*Overloaded Multiplication Operator*/
	Poly operator*(const Poly & p){
		Poly temp;
		std::map<int,int>::iterator it;
		int power, base;
		
		/* Multiply every term of left-hand Poly by every term of
		 * right-hand Poly, and store in temp.*/
		for(auto i : poly){
			for(auto j : p.poly){
				power = i.first + j.first;
				base = 	i.second * j.second;
				
				it = temp.poly.find(power);
				if(it != temp.poly.end() ) 
					temp.poly[power] += base;
				else
					temp.poly[power] = base;
				if( ! temp.poly[power] )
					temp.poly.erase(power);
			}	
		}

		return temp; //Return resulting Poly by value	
	}
	
	/*Non-member overloaded file stream i/o operators*/
	friend std::ostream & operator<<(std::ostream & fout, Poly p);
	friend std::istream & operator>>(std::istream & fin, Poly & p);

}; //end Poly 

/* Overloaded output stream left-shift operator.
 * Outputs polynomial to stream in canonical form.*/
std::ostream & operator<<(std::ostream & fout, Poly p){
	
	std::map<int,int>::reverse_iterator it;
	
	for(it = p.poly.rbegin(); it != p.poly.rend(); it++){
		if(it != p.poly.rbegin() && it->second >= 0)
			fout << " +";
		fout<<" ";	
		if(it->second != 1) 
			fout << it->second;
		if(it->first){
			fout << "x";
			if(it->first != 1)
				fout << "^" << it->first;		
		}
	}
	fout << std::endl;
	return fout;
}

/*Overloaded input stream right-shift operator*/
std::istream & operator>>(std::istream & fin, Poly & p){

	int power, base;	
	std::map<int,int>::iterator it;
	
	/*Skip over  newline character from the preceding istream line*/
	if(fin.peek() == '\n') fin.ignore();

	/*Loop while there is still more stream, and the next char
	 *is not a newline character.*/
	while(fin.good() && fin.peek() != '\n'){
		/*Extract next base-power pair*/
		fin >> base >> power; 
		/*Ignore if base is 0.*/
		if( base ){
			/*Do we already have a term for this power?*/
			it = p.poly.find(power);
			/*If yes, combine the terms*/
			if(it != p.poly.end()){
				p.poly[power] += base;
				if( ! p.poly[power] ) //Remove if now 0.
					p.poly.erase(power);
			}
			/*Otherwise enter as a new term*/
			else
				p.poly[power] = base;			
		}
	}
	return fin;
}

int main(){
	std::ifstream fin("input.txt", std::ios::in);
	std::ofstream fout("output.txt", std::ios::out);

	Poly p1;
	Poly p2;
	while(fin.good()){
		fin >> p1;
		fin >> p2;		
	
		fout << "p1 = " << p1; 
		fout << "p2 = " << p2;

		fout << "p1 + p2 = " << p1+p2;
		fout << "p1 - p2 = " << p1-p2;
		fout << "p1 * p2 = " << p1*p2;
		
		fout << std::endl;
	}
	fin.close();
	fout.close();

	return 0;
}
