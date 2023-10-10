#pragma once

//number of neutrons simulated per cycle
const int NEUTRONS_PER_CYCLE = 10;

//number of inactive cycles to converge fission source
const int INACTIVE_CYCLES = 1;

//number of active cycles to calculate criticality and flux
const int ACTIVE_CYCLES = 0;

//used to transport neutron little bit away from the surface
const double epilson = 1e-10;

//pi value
const double pi = 3.14159265359;
