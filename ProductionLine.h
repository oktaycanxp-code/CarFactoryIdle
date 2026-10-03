// ProductionLine.h
#pragma once

#include <vector>

#include "Car.h"
#include "raylib.h"

class ProductionLine
{
public:
    ProductionLine();

    void Update(float dt, int workerBonus, int machineBonus);
    void Draw3D(Vector3 basePos, int index) const;

    bool IsBusy() const;
    void StartCar(const Car& car);
    void SetLevel(int level);
    int GetLevel() const;
    int GetQueueSize() const;
    float GetProgress() const;
    std::vector<Car> ConsumeCompletedCars();

private:
    int level_;
    float progress_;
    float currentDuration_;
    bool active_;
    Car activeCar_;
    std::vector<Car> queue_;
    std::vector<Car> completedCars_;
    int conveyorState_;
};
