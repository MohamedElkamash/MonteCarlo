#include "Simulator.h"

#include <iostream>

Simulator::Simulator(Domain & domain):
_domain(domain)
{}
 
void Simulator::run()
{
    std::cout << _domain.neutrons().size() << std::endl;

    std::queue<Neutron> & neutron_queue = _domain.neutrons();

    while(!neutron_queue.empty())
    {
        Neutron & neutron = neutron_queue.front();

        double x_nearest_surface = _domain.xNearestSurface();
        double x_next_collision = _domain.xNextCollision();

        bool will_collide = _domain.isNeutronMovingToRight() && x_nearest_surface > x_next_collision || 
                           !_domain.isNeutronMovingToRight() && x_nearest_surface < x_next_collision;

        std::cout << neutron.x() << "         " << neutron.mu() << std::endl;
        std::cout << x_nearest_surface << "        " << x_next_collision << std::endl;
        
        if (will_collide)
        {
            neutron.xUpdate(x_next_collision);
        }

        else
        {
            neutron.xUpdate(x_nearest_surface);;
        }

        std::cout << neutron.x() << "         " << neutron.mu() << std::endl;
        
        neutron_queue.pop();    
    }
    
    std::cout << neutron_queue.size() << std::endl;
}

bool Simulator::isFirstCloser(double x, double y, double mu)
{ return x < y && mu > 0 || x > y && mu < 0; }

bool Simulator::isLeaked(double x, double mu)
{ return x > _domain.xMax() && mu > 0 || x < _domain.xMin() && mu < 0; }


void Simulator::simulate(Neutron & neutron)
{
    bool is_absorbed = false;
    bool is_leaked = false;
    bool is_material_changed = false;
    double x = neutron.x();
    double mu = neutron.mu();
    double x_next_collision = _domain.xNextCollision();
    double x_nearest_surface = _domain.xNearestSurface();
    
    int material_index = _domain.cells()[cell_index].material().id();
    bool is_collision_closer = true;

    bool is_material_changed = false;

    //if (is_material_changed)
        //x_next_collision = _domain.xNextCollision();

    
    while (!is_absorbed || !is_leaked)
    {
        int cell_index = _domain.neutronCellIndex(x);
        is_collision_closer = isFirstCloser(x_next_collision, x_nearest_surface, mu);
        if (is_collision_closer)
        {
            update x to collision position
            sample interaction;
            if (scattering)
            {
                sample phi
                sample scattering angle
                update mu
                x_nex_collision = _domain.xNextCollision();
            }
            else (absorption)
            {
                absorbed = true
            }
        }
        else(no collision)
        {
                material_index
                x_limit
                x_nearest_surface
                x_nearest_collision
                for (int i = cell_index; i < _domain.cells()[_domain.cells().size()]; ++i)
                {
                    if (isleaked)
                        isleaked = true;
                        xupdate to xnextsurface
                        break

                    ++x_nearest_surface
                    ++cell_index 
                    material index = new_material_index
                    if (material_index != old_material_index)
                        x_nearest_collision = 
                        update x to x nearest surface
                        break
                    
                    if(x nearest surface > x next collision)
                        xupdate to collide position
                        collide
                        break
                    
                    


                }
            }


        }



        
        
            









    }

}

