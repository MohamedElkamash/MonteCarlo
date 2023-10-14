#include "Initialization.h"

#include <iostream>
#include <random>

void initialization::domain(InputParameters & parameters, std::vector<Material> & materials, std::vector<Cell> & cells,
                            std::vector<double> & surfaces)
{
    initialization::materials(parameters, materials);
    int main_cell_count = parameters.mainCellCount();
    int cell_count = initialization::cellCount(parameters);
    std::map<int, int> cell_material_map;
    initialization::cellMaterialMap(parameters, cell_material_map);
    initialization::cells(parameters, materials, cells, surfaces);
}
    
void initialization::materials(InputParameters & parameters, std::vector<Material> & materials)
{
    int material_count = parameters.materialCount();

    for (int material_id = 0; material_id < material_count; ++material_id)
    {
        Material material(material_id, parameters.crossSections(material_id));
        materials.push_back(material);
    }
}

int initialization::cellCount(InputParameters & parameters)
{
    int main_cell_count = parameters.mainCellCount();
    int cell_count = 0;

    for (int main_cell = 0; main_cell < main_cell_count; ++main_cell)
        cell_count += parameters.binsPerMainCellCount(main_cell);

    return cell_count;
}

void initialization::cellMaterialMap(InputParameters & parameters, std::map<int, int> & cell_material_map)
{
    int main_cell_count = parameters.mainCellCount();
    int cell_index = 0; 
    
    for (int main_cell = 0; main_cell < main_cell_count; ++main_cell)
    {
        for (int bin = 0; bin < parameters.binsPerMainCellCount(main_cell); ++bin)
        {
            cell_material_map[cell_index] = parameters.mainCellMaterialMap()[main_cell];
            ++cell_index;
        }
    }
}

void initialization::cells(InputParameters & parameters, std::vector<Material> & materials, std::vector<Cell> & cells,
                           std::vector<double> & surfaces)
{
    double cell_count = initialization::cellCount(parameters);
    std::map<int, int> cell_material_map;
    initialization::cellMaterialMap(parameters, cell_material_map);
    int main_cell_count = parameters.mainCellCount();
    std::vector<double> cell_width_vector;     
    
    for (int main_cell = 0; main_cell < main_cell_count; ++main_cell)
    {
        double cell_width = (parameters.cellCoordinates(main_cell)[1] - parameters.cellCoordinates(main_cell)[0])
                             /static_cast<double> (parameters.binsPerMainCellCount(main_cell)) ;

        for (int bin = 0; bin < parameters.binsPerMainCellCount(main_cell); ++bin)
        {
            cell_width_vector.push_back(cell_width);
        }
    }
    
    double x_left = parameters.cellCoordinates(0)[0];
    double x_right = x_left;
    surfaces.push_back(x_left);

    for (int cell_id = 0; cell_id < cell_count; ++cell_id)
    {
        int material_id = cell_material_map[cell_id];
        x_right += cell_width_vector[cell_id];
        Cell cell(x_left, x_right, materials[material_id]);
        cells.push_back(cell);
        surfaces.push_back(x_right);
        x_left = x_right;
    } 
}

