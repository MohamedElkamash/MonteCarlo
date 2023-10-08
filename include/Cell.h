#pragma once

#include "Material.h"

class Cell
{
    public:

    //constructor
    Cell(double x_left, double x_right, const Material & material);

    //returns x coordinate of the left boundary of the cell
    double xLeft();

    //returns x coordinate of the right boundary of the cell
    double xRight();

    //sets the x coordinate of the left boundary of the cell
    void setXLeft(double x_left);

    //sets the x coordinate of the right boundary of the cell
    void setXRight(double x_right);

    //returns the material inside the cell
    Material material();

    private:

    //x coordinate of the left boudnary of the cell
    double _x_left;

    //x coordinate of the right boundary of the cell
    double _x_right;

    //material inside the cell
    const Material & _material;
};
