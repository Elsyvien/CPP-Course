#include "Amoeba.h"
//TODO: task f)
Amoeba::Amoeba()
    : Food(1000.0, 50.0, 50.0, 0.0, 0.0) {
  name = "Amoeba";
  dna_level = 0.0;
  dna_level_th = 100.0;
}

Amoeba::Amoeba(double health_, double power_, double defence_, double dna_level_th)
: Food(health_, power_, defence_, 0.0, 0.0) 
{
  name = "Amoeba";
  
  this->dna_level = 0.0;
  this->dna_level_th = dna_level_th;
}
Amoeba::~Amoeba(){};
//TODO: task k)
Food *Amoeba::clone() const {
  return new Amoeba(*this);
}

void Food::print_header() {
  std::cout << std::setw(10) << "name" << " | ";
  std::cout << std::setw(10) << "health" << " | ";
  std::cout << std::setw(10) << "power" << " | ";
  std::cout << std::setw(10) << "defence" << " | ";
  std::cout << std::setw(10) << "dna lvl" << " | ";
  std::cout << std::setw(10) << "dna lvl threshhold" << std::endl;
}

void Food::print() {
  std::cout << std::setw(10) << name << " | ";
  std::cout << std::setw(10) << health << " | ";
  std::cout << std::setw(10) << power << " | ";
  std::cout << std::setw(10) << defence << " | ";
  std::cout << std::setw(10) << dna_level << " | ";
  std::cout << std::setw(10) << dna_level_th << std::endl;
}

//TODO: task h)
void Amoeba::eat(double health, double dna) {
  this->dna_level += dna;
  this->health += health;

  if (this->dna_level >= this->dna_level_th) {
    this->power *= 1.2;
    this->defence *= 1.2;
    this->dna_level = 0.0;
  }
}
