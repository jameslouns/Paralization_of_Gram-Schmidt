# Paralization_of_Gram-Schmidt
Gram-Schmidt is a mathematical process used to find an orthonormal basis out of N vectors of K length. In instances where number of vectors are equal to the length of the vectors and gaussian elimination method can be used, which is slightly computationally simpler.
# Programs
**Sequential**
Gram-Schmidt.c- is using the original method of finding an orthonormal basis 
Gram-Schmidt-GE.c- is using the gaussian elimination method

**Parallel**
Gram-Schmidt-OMP.c and Gram-Schmidt-OMP-GE.c are identical to their counter parts except they are parallelized using OpenMP.

**Other**
Timer.c- used to time the runtime of the programs
record.sh and Txt_To_Csv.py- are used to run a few different example problem sizes and then export their results to a csv file to be used for data analysis. 
