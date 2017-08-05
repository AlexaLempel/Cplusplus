# Cplusplus
Projects written while learning C++
<hr>

<b>matrix</b><br>
Practicing: 
  - writing template friends for a template class, using forward declerations.
  - writing range-based for loop compatible classes, with begin and end iterators.
  - writing constructors that use intialization lists and curly brace initialization.
  - Throwing std exceptions.
An implementation of a template "safe array" class, SA. SA is an array data structure with a specifiable range indices (integers from data members "low" to "high," inclusive), which does not allow access outside of these array bounds. 
An implementation of a template Matrix class, a 2D SA.  

<hr>

<b>polynomials</b><br>
Practicing file i/o, writing a basic class with overloaded operators, and choosing data structures that simplify problems. A class Poly for dealing with polynomials specified by a file called input.txt in the same directory as the program. Each line (terminated by a newline character) in the file will represent a polynomial. The line will contain a list of integers, which when taken in pairs, will respectively represent the coefficient and exponent of each of the terms in the polynomial.

<hr>

<b>Iterative_TowersOfHanoi</b><br>
Practice developing an iterative approach to a classic recursive problem. Given three towers a, b, and c. We start with n rings on tower aand we need to transfer them to tower b subject to the following restrictions: 1. We can only move one ring at a time, and 2. We may never put a larger numbered ring on top of a smaller numberedone. There are always 3 towers. The program prompts the user for the number of rings, and prints the solution.

<hr>
<hr>
<i>
The following are a series of short programs that build upon the same backtracking algorithm, progressively exploring the way the implementation changes with varying choices of structure for data representation.</i><br>  

<br>

<b>eightQueens_FancyPrint</b><br> 
Practicing pointers and typedef. A program that uses pointers to print graphic solutions to the classic problem of how to place eight queens on a chessboard so that no queen is threatening any other. Uses a 1D array to represent the board, and makes use of the GOTO command to implement looping.

<br>

<b>eightCellCross</b><br>  
![alt text](http://i.imgur.com/inPvdwK.jpeg "8 Cell Cross") <br>
Exploring how compartmentalizing tasks into functions allow the same program to solve a completely different problem with only minor adjustments. Allocates the integers 1-8 to the cells arranged as in the above figure, subject to
the restrictions that no two adjacent (vertically, horizontally, or diagonally) cells contain consecutive integers.<br>
Uses the same backtracking scheme from the 8 Queens Problem solutions in this repository.<br>

<br>

<b>eightQueens_1D_noGOTO</b><br>
Getting away from GOTOs. Prints all solutions to the classic problem of how to place eight queens on a chessboard so that no queen is threatening any other. Uses a 1D array to represent the board, and specifically does not use the GOTO command to implement looping.

<br>

<b>eightQueens_1D</b><br> 
Exploring how just changing the structure in which data is represented (in this case, from 2D array chessboard to 1D array) can simplify implementating a given algorithm. Prints all solutions to the classic problem of how to place eight queens on a chessboard so that no queen is threatening any other. Uses a 1D array to represent the board, and makes use of the GOTO command to implement looping.

<br>

<b>eightQueens_2D</b><br>
A first foray into backtracking. Prints all solutions to the classic problem of how to place eight queens on a chessboard so that no queen is threatening any other. Uses the intuitively obvious 2D array representation of the board, and makes use of the GOTO command to implement looping.

<hr>
<hr>

<b>shiftEquivalent</b><br>
Learning how to write functions, and practicing basic algorithm design. A function that tests if two 1D arrays of equal length are shift equivalent using O(1) auxiliary space. 
