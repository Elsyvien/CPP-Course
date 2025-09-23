#include "Amoeba.h"
//TODO: task f)
Amoeba::Amoeba() 
  : Food(9,9,9,9,9) // Your code here
    // Your code here
    {
      name = "Amoeba";
    };

Amoeba::Amoeba(double health_, double power_, double defence_, double dna_level_th)
    : Food(health_, power_, defence_, 0, 0)
    // Your code here
    {
      name = "Amoeba";
    };

Amoeba::~Amoeba(){};
//TODO: task k)
Food *Amoeba::clone() const {
  return 0; // Your Code here
}
//TODO: task h)
void Amoeba::eat(double health, double dna) {
  // Your Code here
}
