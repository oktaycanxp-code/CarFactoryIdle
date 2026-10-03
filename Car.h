// Car.h
#pragma once

#include <string>

#include "raylib.h"

class Car
{
public:
    Car();
    Car(std::string modelName,
        double productionCost,
        double salePrice,
        float productionTime,
        int quality,
        int unlockCost,
        Color color);

    std::string name;
    double productionCost;
    double salePrice;
    float productionTime;
    int quality;
    int unlockCost;
    bool unlocked;
    Color color;
    int modelLevel;
};
