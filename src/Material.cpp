#include "Material.h"

#include <string>
#include <map>

Material::Material(int id, const std::map<std::string, double> & cross_sections):
_id(id),
_cross_sections(cross_sections)
{}

int Material::id()
{ return _id; }

std::map<std::string, double> Material::crossSections()
{ return _cross_sections; }


double Material::totalCrossSection()
{ 
    double total_cross_section = 0;

    for (auto i = _cross_sections.begin(); i != _cross_sections.end(); i++)
        total_cross_section += 
        

}
