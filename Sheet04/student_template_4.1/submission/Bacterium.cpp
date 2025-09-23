#include "Bacterium.hpp"

Bacterium::Bacterium(double health_, double power_, double defence_)
: Food::Food(health_, power_, defence_, 400.0, 400.0) 
{
    name = "Bacterium";    
}

Bacterium::~Bacterium() {}

Food *Bacterium::clone() const {
    return new Bacterium(health, power, defence);
}