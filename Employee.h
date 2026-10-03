// Employee.h
#pragma once

#include <string>

#include "raylib.h"

enum class EmployeeRole
{
    Worker,
    Mechanic,
    Painter,
    QualityInspector,
    Warehouse,
    Manager
};

class Employee
{
public:
    Employee();
    Employee(std::string nameValue,
             EmployeeRole roleValue,
             double salaryValue,
             float efficiencyValue,
             int levelValue = 1);

    void Update(float dt);
    void Draw3D(Vector3 position, float timeOffset) const;

    std::string name;
    EmployeeRole role;
    double salary;
    float efficiency;
    int level;
    bool hired;
    Vector3 position;
    float walkPhase;
};
