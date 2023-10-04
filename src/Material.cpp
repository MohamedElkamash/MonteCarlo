#include "Material.h"

#include "InputParameters.h"

#include <string>
#include <map>

Material::Material(const std::map<std::string, double> & cross_sections):
//_id(material_id),
_cross_sections(cross_sections)
{}

//int Material::id()
//{ return _id; }

std::map<std::string, double> Material::crossSections()
{ return _cross_sections; }
