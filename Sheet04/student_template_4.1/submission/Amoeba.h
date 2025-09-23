#pragma once

#include "Food.h"

class Amoeba : public Food {
public:
  Amoeba();

  Amoeba(double health_, double power_, double defence_, double dna_level_th);

  ~Amoeba();

  virtual Food *clone() const override;

  void eat(double health, double dna);

protected:
  double dna_level{};
  //TODO: task f)
};
