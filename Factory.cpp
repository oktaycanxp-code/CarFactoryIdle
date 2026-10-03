// Factory.cpp
#include "Factory.h"

#include <algorithm>
#include <string>

Factory::Factory()
    : level_(1), warehouseCapacity_(30), maxProductionLines_(1), factoryRotation_(0.0f)
{
    productionLines_.emplace_back();

    machines_.emplace_back(Machine(MachineType::Conveyor, 1500.0, 0.15f, 60.0, 1));
    machines_.emplace_back(Machine(MachineType::RobotArm, 2200.0, 0.22f, 80.0, 1));

    employees_.emplace_back(Employee("Ali", EmployeeRole::Worker, 1800.0, 1.0f, 1));
    employees_.emplace_back(Employee("Mehmet", EmployeeRole::Mechanic, 2400.0, 1.2f, 1));
    employees_.emplace_back(Employee("Burak", EmployeeRole::Manager, 3200.0, 1.1f, 1));
}

void Factory::Update(float dt)
{
    factoryRotation_ += dt * 8.0f;

    int workerBonus = GetActiveWorkers() / 2 + level_ * 2;
    int machineBonus = 0;
    for (const auto& machine : machines_)
    {
        machineBonus += machine.level;
    }

    for (auto& line : productionLines_)
    {
        line.Update(dt, workerBonus, machineBonus);
    }

    for (auto& line : productionLines_)
    {
        std::vector<Car> producedCars = line.ConsumeCompletedCars();
        for (const auto& car : producedCars)
        {
            AddCompletedCar(car);
        }
    }
}

void Factory::Draw() const
{
    DrawGrid(24, 2.5f);

    DrawCube((Vector3){ 0.0f, 0.0f, 0.0f }, 36.0f, 1.0f, 30.0f, (Color){ 60, 62, 70, 255 });

    DrawCube((Vector3){ 0.0f, 2.5f, 0.0f }, 18.0f, 5.0f, 12.0f, (Color){ 82, 94, 108, 255 });
    DrawCube((Vector3){ 0.0f, 5.8f, 0.0f }, 19.5f, 1.2f, 13.5f, (Color){ 115, 122, 132, 255 });

    DrawCube((Vector3){ -10.0f, 2.0f, 8.0f }, 5.0f, 4.0f, 6.0f, (Color){ 95, 103, 113, 255 });
    DrawCube((Vector3){ 10.0f, 1.5f, 8.0f }, 5.0f, 3.0f, 6.0f, (Color){ 95, 103, 113, 255 });
    DrawCube((Vector3){ -10.0f, 1.5f, -9.0f }, 5.0f, 3.0f, 6.0f, (Color){ 95, 103, 113, 255 });
    DrawCube((Vector3){ 10.0f, 1.5f, -9.0f }, 5.0f, 3.0f, 6.0f, (Color){ 95, 103, 113, 255 });

    DrawSphere((Vector3){ -8.0f, 6.5f, 0.0f }, 0.45f, (Color){ 255, 228, 120, 255 });
    DrawSphere((Vector3){ 8.0f, 6.5f, 0.0f }, 0.45f, (Color){ 255, 228, 120, 255 });

    for (size_t i = 0; i < productionLines_.size(); ++i)
    {
        productionLines_[i].Draw3D((Vector3){ -4.0f + static_cast<float>(i) * 4.5f, 0.0f, 0.0f }, static_cast<int>(i));
    }

    for (size_t i = 0; i < machines_.size(); ++i)
    {
        Vector3 pos = (Vector3){ -12.0f + static_cast<float>(i) * 7.5f, 2.4f, -4.0f };
        machines_[i].Draw3D(pos, factoryRotation_ + i * 1.6f);
    }

    for (size_t i = 0; i < employees_.size(); ++i)
    {
        Vector3 pos = (Vector3){ -11.0f + static_cast<float>(i) * 7.0f, 0.5f, 10.5f };
        employees_[i].Draw3D(pos, static_cast<float>(i));
    }
}

void Factory::AddProductionLine()
{
    if (productionLines_.size() < static_cast<size_t>(maxProductionLines_))
    {
        productionLines_.emplace_back();
    }
}

void Factory::AddMachine(const Machine& machine)
{
    machines_.push_back(machine);
}

void Factory::AddEmployee(const Employee& employee)
{
    employees_.push_back(employee);
}

void Factory::UnlockCarModel(const std::string& name)
{
    if (std::find(unlockedCarNames_.begin(), unlockedCarNames_.end(), name) == unlockedCarNames_.end())
    {
        unlockedCarNames_.push_back(name);
    }
}

void Factory::SpawnInitialVehicles()
{
    unlockedCars_.clear();
    unlockedCars_.emplace_back(Car("Economy Sedan", 11000.0, 16000.0, 14.0f, 55, 0, RED));
    unlockedCars_.emplace_back(Car("Hatchback", 18000.0, 23000.0, 17.0f, 65, 0, BLUE));
    unlockedCars_.emplace_back(Car("SUV", 26000.0, 33000.0, 22.0f, 72, 0, GREEN));

    unlockedCarNames_.clear();
    unlockedCarNames_.push_back("Economy Sedan");
    unlockedCarNames_.push_back("Hatchback");
    unlockedCarNames_.push_back("SUV");
}

void Factory::SetLevel(int level)
{
    level_ = level;
    maxProductionLines_ = 1 + level_;
    warehouseCapacity_ = 30 + level_ * 20;
}

int Factory::GetLevel() const
{
    return level_;
}

void Factory::SetWarehouseCapacity(int capacity)
{
    warehouseCapacity_ = capacity;
}

int Factory::GetWarehouseCapacity() const
{
    return warehouseCapacity_;
}

void Factory::SetProductionLineCount(int count)
{
    productionLines_.clear();
    for (int i = 0; i < count; ++i)
    {
        productionLines_.emplace_back();
    }
}

int Factory::GetProductionLineCount() const
{
    return static_cast<int>(productionLines_.size());
}

bool Factory::CanBuildNewLine() const
{
    return productionLines_.size() < static_cast<size_t>(maxProductionLines_);
}

int Factory::GetActiveWorkers() const
{
    int count = 0;
    for (const auto& worker : employees_)
    {
        if (worker.hired)
        {
            ++count;
        }
    }
    return count;
}

std::vector<ProductionLine>& Factory::GetProductionLines()
{
    return productionLines_;
}

const std::vector<ProductionLine>& Factory::GetProductionLines() const
{
    return productionLines_;
}

const std::vector<Car>& Factory::GetCompletedCars() const
{
    return completedCars_;
}

std::vector<Car> Factory::ConsumeCompletedCars()
{
    std::vector<Car> completed = completedCars_;
    completedCars_.clear();
    return completed;
}

void Factory::AddCompletedCar(const Car& car)
{
    completedCars_.push_back(car);
}

void Factory::ClearCompletedCars()
{
    completedCars_.clear();
}

const std::vector<Machine>& Factory::GetMachines() const
{
    return machines_;
}

const std::vector<Employee>& Factory::GetEmployees() const
{
    return employees_;
}

const std::vector<std::string>& Factory::GetUnlockedCarNames() const
{
    return unlockedCarNames_;
}

void Factory::SetUnlockedCars(const std::vector<std::string>& names)
{
    unlockedCarNames_ = names;
}

std::vector<int> Factory::GetMachineLevels() const
{
    std::vector<int> levels;
    for (const auto& machine : machines_)
    {
        levels.push_back(machine.level);
    }
    return levels;
}

std::vector<int> Factory::GetEmployeeLevels() const
{
    std::vector<int> levels;
    for (const auto& employee : employees_)
    {
        levels.push_back(employee.level);
    }
    return levels;
}

void Factory::SetMachineLevels(const std::vector<int>& levels)
{
    for (size_t i = 0; i < machines_.size() && i < levels.size(); ++i)
    {
        machines_[i].level = levels[i];
    }
}

void Factory::SetEmployeeLevels(const std::vector<int>& levels)
{
    for (size_t i = 0; i < employees_.size() && i < levels.size(); ++i)
    {
        employees_[i].level = levels[i];
    }
}
