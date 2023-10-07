#include "Initialization.h"

#include <iostream>
#include <random>

void initialization::start(InputParameters & parameters, std::vector<Material> & materials, std::vector<Cell> & cells)
{
    initialization::materials(parameters, materials);
    int main_cell_count = parameters.mainCellCount();
    int cell_count = initialization::cellCount(parameters);
    std::map<int, int> cell_material_map;
    initialization::cellMaterialMap(parameters, cell_material_map);
    double cell_width = initialization::cellWidth(parameters);
    initialization::cells(parameters, materials, cells);
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

double initialization::cellWidth(InputParameters & parameters)
{
    int main_cell_count = parameters.mainCellCount();
    int cell_count = initialization::cellCount(parameters);
    double x_domain_left_boundary = parameters.cellCoordinates(0)[0];
    double x_domain_right_boundary = parameters.cellCoordinates(main_cell_count - 1)[1];
    double domain_width = x_domain_right_boundary - x_domain_left_boundary;
    double cell_width = domain_width / cell_count;
    return cell_width;
}

void initialization::cells(InputParameters & parameters, std::vector<Material> & materials, std::vector<Cell> & cells)
{
    double cell_count = initialization::cellCount(parameters);
    double cell_width = initialization::cellWidth(parameters);
    std::map<int, int> cell_material_map;
    initialization::cellMaterialMap(parameters, cell_material_map);
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
}

