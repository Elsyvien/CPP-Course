#include "Virus.hpp"

Virus::Virus(double health_, double power_, double defence_)
: Food(health_, power_, defence_, 200.0, 250.0) {
  name = "Virus";
}

Virus::~Virus() {}

Food *Virus::clone() const {
  return new Virus(health, power, defence);
}
