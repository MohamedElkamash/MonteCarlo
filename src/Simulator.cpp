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
        Neutron neutron = neutron_queue.front();
        std::cout << neutron.x() << "   " << neutron.id() << "    " << neutron.mu() << std::endl;
        std::cout << _domain.xNearestSurface() << "       " << _domain.xNextCollision() << std::endl;
        neutron_queue.pop();
    } 
    std::cout << neutron_queue.size() << std::endl;
}
    
    