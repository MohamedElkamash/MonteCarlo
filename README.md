# MonteCarlo
Elementary, 1D, one-speed monte carlo neutron transport code

User Guide
To reproduce the results in the report
clone the github repository
Adjust the InputParameters.cpp and Constants.h files as you wish. (Currently they are adjusted to reproduce scenario 1)
To reproduce scenario 2 
- change the number of bins per cell for cell to 10 (InputParameters.cpp)
- change the number of inactive cycles to 200 and the number of active cycles to 100 (Constant.h)
- Note that you could obtain reasonable results with much lower cycles.
Build the project using the following command from the repository directory: "g++ -std=c++17 -o output -I ./include ./src/*.cpp"
Run the executable using: ./output
The output of the program will be two files. 
The first is results.txt which contains the full results for the fission source, flux and k_eff.
The second file is results.csv which is simpler in plotting the results than the .txt file.

I am sorry I didn't have time to generate docstrings. I have already downloaded doxygen but didn't have time to use it, but I have inline comments and class description in each file. 


