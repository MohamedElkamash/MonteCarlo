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


double Material::totalXS()
{ 
    return _cross_sections["scattering_xs"] + _cross_sections["absorption_xs"];
}
