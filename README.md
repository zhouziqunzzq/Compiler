# Compiler
## Introduction
A naive C-like compiler implemented in C++.  
The compiler is just a toy for the final project of
 the course, Principle of Compiler. It's not intended
 to be used in production scenarios.
 
## Build & Run
To build the project, there're two options:
- Import Compiler.cbp to Code::Blocks and build in it
- Using cmake(>=3.5) to build in debug mode like
  ```$shell
  mkdir bin
  cd bin
  cmake .. -DDEBUG=on
  make
  ```
  or build in release mode like
  ```$shell
  mkdir bin
  cd bin
  cmake .. -DRELEASE=on
  make
  ```
  Then you can run the executable file like
  ```$shell
  ./naive_c_compiler <input_file>
  ```