#include "Tallies.h"
#include <string>
#include <fstream>

/* This class is responsible for printing the results in the output files
*/

class Finalizer
{
    public:

    //constructor
    Finalizer(std::ofstream & file, Tallies & tallies, int bins);

    //runs the output scripts
    void run();

    //prints a dashed line
    void dashLine();

    //prints a table title
    void tableTitle(std::string title);

    //prints data into csv
    void csv();


    //prints a 

    private:

    //file object to carry results
    std::ofstream & _file;

    Tallies & _tallies;

    int _bins;




};




/* namespace finalization
{
    //runs the tally output scripts
    void run(Tallies & tallies);

    void table1D(std::ofstream file, std::string title, Tallies & tallies, int i);

    void table2D(std::string & file, std::string title, Tallies & tallies, int i, int j);
} */