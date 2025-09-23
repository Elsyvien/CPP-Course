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

//TODO: task k)
Food *Amoeba::clone() const {
  return new Amoeba(*this);
}

void Amoeba::print_header() {
  std::cout << std::setw(10) << "name" << " | ";
  std::cout << std::setw(10) << "health" << " | ";
  std::cout << std::setw(10) << "power" << " | ";
  std::cout << std::setw(10) << "defence" << " | ";
  std::cout << std::setw(10) << "dna level" << " | ";
  std::cout << std::setw(10) << "dna level threshold" << std::endl;
}

void Amoeba::print() {
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
  if (dna_level >= dna_level_th) { dna_level *= 2.0; dna_level = 0.0;}
}

Amoeba::~Amoeba(){}