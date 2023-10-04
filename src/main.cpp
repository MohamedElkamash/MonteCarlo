#include "InputParameters.h"
#include "Material.h"
#include "Cell.h"

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>


int main()
{
    //Read input parameters
    InputParameters parameters;
/*
    std::cout << parameters.cellCount() << std::endl;
    std::cout << parameters.binsPerCellCount(1) << std::endl;
    std::cout << parameters.materialCount() << std::endl;
    std::cout << parameters.cellCoordinates(1)[0] << std::endl;
    std::cout << parameters.crossSections(1)["scattering_xs"] << std::endl;
    std::cout << parameters.cellMaterialMap()[0] << std::endl;
    std::cout << parameters.cellMaterialMap()[1] << std::endl;
*/


    //Materials construction
    const int material_count = parameters.materialCount();
    std::vector<Material> materials;

    for (int material_id = 0; material_id < material_count; ++material_id)
    {
        Material material(material_id, parameters.crossSections(material_id));
        materials.push_back(material);
    }
//    std::cout << materials[0].crossSections()["scattering_xs"] << std::endl;
//    std::cout << materials[1].crossSections()["nu*fission_xs"] << std::endl;


    //Cells construction
    //number of main cells in the input file
    const int main_cell_count = parameters.mainCellCount();

    //actual number of cells after expanding each cell into multiple cells due to flux bins
    int cell_count = 0;

    for (int main_cell = 0; main_cell < main_cell_count; ++main_cell)
        cell_count += parameters.binsPerCellCount(main_cell);
    //std::cout << cell_count << std::endl;

    //create new cell to material map
    std::map<int, int> cell_material_map;

    int cell_index = 0;

    for (int main_cell = 0; main_cell < main_cell_count; ++main_cell)
    {
        for (int bin = 0; bin < parameters.binsPerCellCount(main_cell); ++bin)
        {
            cell_material_map[cell_index] = parameters.mainCellMaterialMap()[main_cell];
            ++cell_index;
        }
    }
    //for (int i = 0; i < cell_count; ++i)
    //    std::cout << cell_material_map[i] << std::endl;

        const double x_domain_left_boundary = parameters.cellCoordinates(0)[0];
        const double x_domain_right_boundary = parameters.cellCoordinates(main_cell_count - 1)[1];
        const double domain_width = x_domain_right_boundary - x_domain_left_boundary;
        const double cell_width = domain_width / cell_count;
/*
        std::cout << x_domain_left_boundary  << std::endl;
        std::cout << x_domain_right_boundary << std::endl;
        std::cout << domain_width            << std::endl;
        std::cout << cell_width              << std::endl;
*/
        std::vector<Cell> cells;

        double x_left = 0;
        double x_right = x_left + cell_width;



        for (int cell_id = 0; cell_id < cell_count; ++cell_id)
        {
            int material_id = cell_material_map[cell_id];
            Cell cell(x_left, x_right, materials[material_id]);
            cells.push_back(cell);
            x_left  += cell_width;
            x_right += cell_width;
        }
/*
        for (int i = 0; i < cell_count; ++i)
        {
            std::cout << "cell: " << i 
                      << ", x_left = " << cells[i].xLeft() 
                      << ", x_right = " << cells[i].xRight() 
                      << ", material id = " << cells[i].material().id()
                      << "nu*fission_xs = " << cells[i].material().crossSections()["nu*fission_xs"] 
                      << std::endl;
        }
*/
    
}