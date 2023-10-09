#include "Simulator.h"

#include "Constants.h"
#include <iostream>

Simulator::Simulator(Domain & domain):
_domain(domain)
{}
 
void Simulator::run()
{
    //std::cout << _domain.neutrons().size() << std::endl;
    std::queue<Neutron> & neutron_queue = _domain.neutrons();

    while(!neutron_queue.empty())
    {
        Neutron & neutron = neutron_queue.front();
        std::cout << "neutron id: " << neutron.id() << std::endl;
        simulate(neutron);
        neutron_queue.pop();
        std::cout << std::endl;  
    }
    //std::cout << neutron_queue.size() << std::endl;
}

bool Simulator::isFirstCloser(double x, double y, double mu)
{ return x < y && mu > 0 || x > y && mu < 0; }

bool Simulator::isLeaked(double x, double mu)
{ return x >= _domain.xMax() && mu > 0 || x <= _domain.xMin() && mu < 0; }

void Simulator::absorb(Neutron & neutron)
{
    std::cout << "absorbed" << std::endl;
}

void Simulator::scatter(Neutron & neutron)
{
    std::cout << "scattered" << std::endl;
    //sample scattering angle
    //sample phi
    //update mu
}

void Simulator::simulate(Neutron & neutron)
{
    bool is_absorbed = false;
    bool is_leaked = false;
    bool is_collision_closer = true;
    double x_nearest_collision = _domain.xNextCollision();
    double x_nearest_surface = _domain.xNearestSurface();
    std::cout << neutron.x() << std::endl;
    std::cout << neutron.mu() << std::endl;
    
    while (!is_absorbed && !is_leaked)
    {
        int neutron_cell_index = _domain.neutronCellIndex(neutron.x());
        int current_cell_material_id = _domain.cells()[neutron_cell_index].material().id();
        is_collision_closer = isFirstCloser(x_nearest_collision, x_nearest_surface, neutron.mu());
        if (is_collision_closer)
        {
            neutron.xUpdate(x_nearest_collision);
            is_absorbed = _domain.isAbsorbed(current_cell_material_id);
            if(is_absorbed)
            {
                absorb(neutron);
            }
            else //scattered
            {
                scatter(neutron);
                x_nearest_collision = _domain.xNextCollision();
            }
        }

        else //no first collision
        {
            neutron_cell_index = _domain.neutronCellIndex(neutron.x());
            if (neutron.mu() > 0)
                for (int i = neutron_cell_index; i < _domain.cells().size(); ++i)
                {
                    if (isLeaked(x_nearest_surface, neutron.mu()))
                    {
                        is_leaked = true;
                        neutron.xUpdate(x_nearest_surface);
                        std::cout << "leaked" << std::endl;
                        break;
                    } 

                    std::cout << "changed cell" << std::endl;

                    x_nearest_surface += _domain.cellWidth();
                    current_cell_material_id = _domain.cells()[i].material().id();
                    int adjacent_cell_material_id = _domain.cells()[i+1].material().id();
                    if (current_cell_material_id != adjacent_cell_material_id)
                    {
                        neutron.xUpdate(x_nearest_surface - _domain.cellWidth() + eta);
                        x_nearest_collision = _domain.xNextCollision();
                        std::cout << "new cell has different material" << std::endl;
                        break;
                    }
                    std::cout << "new cell has same material" << std::endl;

                    if (x_nearest_surface > x_nearest_collision)
                    {
                        std::cout << "interacted in the new cell" << std::endl;
                        neutron.xUpdate(x_nearest_collision);
                        is_absorbed = _domain.isAbsorbed(current_cell_material_id);
                        if(is_absorbed)
                        {
                            absorb(neutron);
                        }
                        else //scattered
                        {
                            scatter(neutron);
                            x_nearest_collision = _domain.xNextCollision();
                        }
                        break;
                    }
                }

            else //mu < 0
                for (int i = neutron_cell_index; i >= 0; --i)
                {
                    if (isLeaked(x_nearest_surface, neutron.mu()))
                    {
                        is_leaked = true;
                        neutron.xUpdate(x_nearest_surface);
                        std::cout << "leaked" << std::endl;
                        break;
                    } 
                    std::cout << "changed cell" << std::endl;

                    x_nearest_surface -= _domain.cellWidth();
                    current_cell_material_id = _domain.cells()[i].material().id();
                    int adjacent_cell_material_id = _domain.cells()[i-1].material().id();
                    if (current_cell_material_id != adjacent_cell_material_id)
                    {
                        neutron.xUpdate(x_nearest_surface + _domain.cellWidth() - eta);
                        x_nearest_collision = _domain.xNextCollision();
                        std::cout << "new cell has different material" << std::endl;
                        break;
                    }

                    std::cout << "new cell has same material" << std::endl;

                    if (x_nearest_surface < x_nearest_collision) //it will collide becasue mu is negative
                    {
                        std::cout << "interacted in the new cell" << std::endl;
                        neutron.xUpdate(x_nearest_collision);
                        is_absorbed = _domain.isAbsorbed(current_cell_material_id);
                        if(is_absorbed)
                        {
                            absorb(neutron);
                        }
                        else //scattered
                        {
                            scatter(neutron);
                            x_nearest_collision = _domain.xNextCollision();
                        }
                        break;
                    }
                }
        } //end no first collision
    } 
}

