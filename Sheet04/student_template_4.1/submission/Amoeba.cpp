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
//TODO: task h)
void Amoeba::eat(double health, double dna) {
  // Your Code here
}
