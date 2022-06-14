# CS32Project4

Our UCLA CS 32 Spring 2022 Project 4 had us implement a NameTable class that would account for scoping and shadowing.
Below are the specifications: 

Every compiler has a name table, a component that keeps track of the identifiers in a program as well as information about them, such as their types. Your assignment is to write a good implementation of a name table class. To keep things simple for this project, the only information you need to keep track of for each identifier is the line number in which it is declared.

  An object of type NameTable is intended to be used as follows as the compiler processes the text of a program from top to bottom:

  Whenever a scope is entered, the enterScope member function is called.

  Whenever a scope is exited, the exitScope member function is called. It returns true unless there have been more calls to exitScope than prior calls to enterScope. (I.e., you can't leave a scope that hasn't been entered.)

  Whenever an identifier is declared, the declare member function is called to record the line number associated with that declaration. It returns true unless that identifier has already been declared in the current scope or that so-called identifier is the empty string, in which cases it returns false without changing the name table. We'll consider any non-empty string to be a valid identifier.

  Whenever an identifier is used, the find member function is called to determine the line number of the declaration corresponding to that use. It returns that line number, or -1 if the identifier has no active declaration.
  

In order to implement this fastest and accurate NameTable that would outperform the given implementation of the slow NameTable, I used a hashtable that was a vector of linked lists, containing structs. I also used a secondary data structure that was a vector of structs to keep track of scoping. 
