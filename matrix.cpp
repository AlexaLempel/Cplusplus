#ifndef REDPILL_RUINED_MATRIX_QUOTES_FOREVER
#define REDPILL_RUINED_MATRIX_QUOTES_FOREVER

#include <iostream>
#include <stdexcept>

/****************************************************************************
 * Practice implementation of a template SafeArray class. SA is an array data 
 * structure with a specifiable range indices (integers from data members "low" 
 * to "high," inclusive), which does not allow access outside of these array 
 * bounds. A C-style array of type <T> in dynamic memory holds the objects
 * stored in the SA container, pointed to by SA data member "p".  
 ****************************************************************************/

template <class T> class SA;
template <class T> std::ostream & operator<<(std::ostream &os, const SA<T> &s);
template <class T> class Matrix;

template <class T> class SA{
	int low, high;	// Lower and upper bounds of SA indices.
	T *p;		// Pointer to array holding data in dynamic memory 

	public:
	
	typedef T * iterator; 
		
	/*Default constructor*/
	SA<T>(){
		low = 0;
		high = -1;	//high is -1 for empty so size high-low+1 = 0
		p = nullptr;
	}

	/*Copy Costructor*/
	SA<T>(const SA<T> &s){
		std::size_t sz = s.size();
		SA<T> temp(sz);	//RAII	
		low = s.low;
		high = s.high;
		p = temp.p;
		for(int i = 0; i < sz; i++)
			p[i] = s.p[i];
		temp.p = nullptr;	//temp destruct won't kill this SA
	}

	/*1 Arg Constructor*/
	// Takes array size as parameter, analagous to standard array  
	SA<T>(int sz){	
		if(sz < 0)
			throw std::invalid_argument("Neg. size not allowed.");
		low = 0;
		high = sz-1;
		p = new T[sz];
	}
	

	/*2 Arg constructor*/
	// Takes lower and upper index bounds as parameters.
	SA<T>(int l, int h){
		if (h >= l){	//Upper bound can't be smaller than the lower   
			low = l;
			high = h;
			p = new T[h-l+1];	//Allocate the array
		}
		else
			throw std::invalid_argument("Illegal SA bounds.");
	}	
	
	/*Initializer List Constructor*/
	SA<T>(const std::initializer_list<T> & list){
		low = 0;
		high = list.size() - 1;
		p = new T[list.size()];
		int i = 0;
		for(T element : list){
			p[i] = element;
			i++;
		}
	}

	/*Destructor*/
	~SA<T>(){
		delete[] p;
	}

	/*Copy Assignment*/
	SA<T> & operator=(const SA<T> & s){
		/*Make sure this isn't self-assignment before doing anything.*/
		if(this != &s){
			SA<T> temp(s); //RAII
			low = temp.low;
			high = temp.high;
			delete[] p;
			p = temp.p;
			temp.p = nullptr; //So temp destruct won't kill this SA  	
		}
		return *this;
	}

	/*SA Element Access*/
	const T & operator[](int i) const {
		if( i<low || i>high )
			throw std::invalid_argument("Illegal SA index.");
		return p[i-low];
	}

	T & operator[](int i){
		return p[i-low];
	}
	
	/*Get SA Size*/
	// returns number of elements this SA can hold
	std::size_t size() const { return high - low + 1; }
	
	/*Iterator pointing to the first element*/
	iterator begin() const { return p; }
	
	/*Iterator pointing to the past-the-end element*/
	iterator end() const { return p + high - low + 1; }

	/*Print SA Contents, non-member friend*/
	friend std::ostream & operator<< <T>(std::ostream &os, const SA<T> &s);
	
	template<class Q>
	friend class Matrix;

}; //end class SA

/*Print SA Contents*/
template <class T>
std::ostream & operator<<(std::ostream & os, const SA<T> & s){
	for(int i = 0; i < s.size(); i++)
		std::cout << s.p[i] << "\t";
	return os;
}

/****************************************************************************
 * Practice implementation of a template SafeMatrix class, which is a 2D SA 
 * container. Data is held in "mx," a SA of SAs. 
 ****************************************************************************/
template <class T> 
std::ostream & operator<<(std::ostream &os, const Matrix<T> &m);

template <class T> class Matrix{
	
	SA< SA<T> > mx;	//mx (for "matrix") SA of type SA<T> 

	public:
	
	/*Default constructor*/
	Matrix<T>() : mx() {}

	/*Copy constructor*/
	Matrix<T>(const Matrix<T> & m) : mx(m.mx) {}

	/*Constructor -- # rows and # columns specified*/
	Matrix<T>(int rows, int cols) : mx(rows) {
		for(auto &row : mx)
			row = SA<T>(cols);
	}

	/*Constructor -- bounds of each dimension specified.*/
	Matrix<T>(int rl, int rh, int cl, int ch) : mx(rl, rh) {
		for(auto &row : mx)
			row = SA<T>(cl,ch);
	}

	/*Initializer List Constrtuctor*/
	Matrix<T>(const std::initializer_list< SA<T> > & list) 
		: mx(list.size()) 
	{
		int i = 0;
		for(auto row : list){
			mx[i] = row;
			i++;
		}
	}

	/*Destructor*/
	~Matrix<T>(){}	

	/*Copy Assignment*/
	Matrix<T> & operator=(const Matrix<T> & m){
		if(this != &m){
			mx = m.mx;	
		}
		return *this;
	}

	/*Element Access*/
	SA<T> & operator[](int i){ return mx[i]; }

	/*Matrix Multiplication*/
	//TODO -- Implement Strassen's Algo instead
	Matrix<T> operator*(const Matrix<T> & m) const{
		int l_rows = mx.size();		//left matrix rows & cols #s
		int l_cols = (*mx.p).size();

		int r_rows = m.mx.size();	//right matrix rows & cols #s
		int r_cols = (*m.mx.p).size();

		if(l_cols != r_rows)
			throw std::invalid_argument("Matrices incompatible.");
		Matrix<T> product(l_rows, r_cols); //RAII
		for(int i = 0; i < l_rows; i++)
			for(int j = 0; j < r_cols; j++){
				product[i][j] = 0;
				for(int k = 0; k < l_cols; k++)
					product[i][j] += mx[i][k] * m.mx[k][j];
			}	
		
		return product;
	}	
	
	/*Get Size*/
	std::size_t size(){ return mx.size() * (*mx.p).size();}

	/*Print Matrix Contents*/
	friend std::ostream & operator<< <T>(std::ostream &os, const Matrix<T> &m);	

}; //end class Matrix 

/*Print Matrix Contents*/
template <class T>
std::ostream & operator<<(std::ostream &os, const Matrix<T> &m){
	for(auto row : m.mx)
		os << row << std::endl;
	return os;
}

#endif

int main(){
	//Curly brace initialization 
	Matrix<int> A = {{ 0, 0},
			 { 2, 4},
			 {13, 0},
			 { 4, 1}};
	
	Matrix<int> B = {{3,  4,  5,  6,  7},
	       		 {8,  9, 10, 11, 12}};	

	//ostream output and matrix multiplication  
	std::cout <<"A: \n" << A << "\nB: \n" << B << "\nAxB: \n" << A*B; 
	
	return 0;
}
