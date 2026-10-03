// Factory.h
#pragma once

#include <string>
#include <vector>

#include "Car.h"
#include "ProductionLine.h"
#include "Employee.h"
#include "Machine.h"
#include "raylib.h"

class Factory
{
public:
    Factory();

    void Update(float dt);
    void Draw() const;

    void AddProductionLine();
    void AddMachine(const Machine& machine);
    void AddEmployee(const Employee& employee);
    void UnlockCarModel(const std::string& name);
    void SpawnInitialVehicles();

    void SetLevel(int level);
    int GetLevel() const;

    void SetWarehouseCapacity(int capacity);
    int GetWarehouseCapacity() const;

    void SetProductionLineCount(int count);
    int GetProductionLineCount() const;

    bool CanBuildNewLine() const;
    int GetActiveWorkers() const;

    std::vector<ProductionLine>& GetProductionLines();
    const std::vector<ProductionLine>& GetProductionLines() const;

    const std::vector<Car>& GetCompletedCars() const;
    std::vector<Car> ConsumeCompletedCars();
    void AddCompletedCar(const Car& car);
    void ClearCompletedCars();

    const std::vector<Machine>& GetMachines() const;
    const std::vector<Employee>& GetEmployees() const;

    const std::vector<std::string>& GetUnlockedCarNames() const;
    void SetUnlockedCars(const std::vector<std::string>& names);

    std::vector<int> GetMachineLevels() const;
    std::vector<int> GetEmployeeLevels() const;
    void SetMachineLevels(const std::vector<int>& levels);
    void SetEmployeeLevels(const std::vector<int>& levels);

private:
    int level_;
    int warehouseCapacity_;
    int maxProductionLines_;
    float factoryRotation_;

    std::vector<ProductionLine> productionLines_;
    std::vector<Car> completedCars_;
    std::vector<Car> unlockedCars_;
    std::vector<Machine> machines_;
    std::vector<Employee> employees_;
    std::vector<std::string> unlockedCarNames_;
};
