// Car.cpp
#include "Car.h"

Car::Car()
    : name("Economy Sedan"),
      productionCost(11000.0),
      salePrice(16000.0),
      productionTime(14.0f),
      quality(55),
      unlockCost(0),
      unlocked(true),
      color(RED),
      modelLevel(1)
{
}

Car::Car(std::string modelName,
         double productionCostValue,
         double salePriceValue,
         float productionTimeValue,
         int qualityValue,
         int unlockCostValue,
         Color modelColor)
    : name(std::move(modelName)),
      productionCost(productionCostValue),
      salePrice(salePriceValue),
      productionTime(productionTimeValue),
      quality(qualityValue),
      unlockCost(unlockCostValue),
      unlocked(true),
      color(modelColor),
      modelLevel(1)
{
}
