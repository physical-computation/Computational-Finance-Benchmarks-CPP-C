# Computational Finance Benchmarks
These computational finance C++ benchmarks are adapted from Python code from a course by Lech A. Grzelak: https://github.com/LechGrzelak/Computational-Finance-Course/tree/main
All benchmarks have 25 paths and 500 steps. You can edit the variables ```NoOfPaths``` and ```NoOfSteps``` to increase or decrease the number of paths and steps in each benchmark.
## C++ Computational Finance Benchmarks
To compile the C versions of the benchmarks type: ```g++ -std=c++11 <name of benchmark>.cpp``` in the directory of the benchmark you want to compile. 
To run the compiled benchmark type: ```./a.out``` in the directory of the benchmark you just compiled.  
## C Computational Finance Benchmarks
You will need to download and install the GNU Scientific Library to run the C versions of the benchmarks. For Mac OS you can use MacPorts or Brew. Use an appropriate package manager for you operating system. 
To compile the C versions of the benchmarks type: ```gcc -Wall -I/opt/local -lgsl -lgslcblas <name of benchmark>.c``` in the directory of the benchmark you want to compile. 
To run the compiled benchmark type: ```./a.out``` in the directory of the benchmark you just compiled.  
