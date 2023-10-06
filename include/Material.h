#pragma once

#include <string>
#include <map>

class Material
{
    public:
    
    //Constructor
    Material(int id, const std::map<std::string, double> & cross_sections);

    //returns material id
    int id();
    
    //returns cross sections of the material
    std::map<std::string, double> crossSections();

    private:

    //material id
    int _id;
    
    //macroscopic cross sections in units cm^-1
    std::map<std::string, double> _cross_sections;
};