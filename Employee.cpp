// Employee.cpp
#include "Employee.h"

Employee::Employee()
    : name("Worker"), role(EmployeeRole::Worker), salary(1800.0), efficiency(1.0f), level(1), hired(true), position({ 0.0f, 0.0f, 0.0f }), walkPhase(0.0f)
{
}

Employee::Employee(std::string nameValue,
                   EmployeeRole roleValue,
                   double salaryValue,
                   float efficiencyValue,
                   int levelValue)
    : name(std::move(nameValue)),
      role(roleValue),
      salary(salaryValue),
      efficiency(efficiencyValue),
      level(levelValue),
      hired(true),
      position({ 0.0f, 0.0f, 0.0f }),
      walkPhase(0.0f)
{
}

void Employee::Update(float dt)
{
    walkPhase += dt * 2.5f;
}

void Employee::Draw3D(Vector3 positionValue, float timeOffset) const
{
    Vector3 bodyPos = positionValue;
    DrawCylinder((Vector3){ bodyPos.x, bodyPos.y + 1.0f, bodyPos.z }, 0.25f, 0.25f, 1.2f, 8, (Color){ 50, 110, 200, 255 });
    DrawSphere((Vector3){ bodyPos.x, bodyPos.y + 1.9f, bodyPos.z }, 0.42f, (Color){ 220, 220, 220, 255 });
    DrawCylinder((Vector3){ bodyPos.x, bodyPos.y + 0.5f, bodyPos.z }, 0.12f, 0.12f, 0.8f, 6, (Color){ 130, 130, 130, 255 });

    (void)timeOffset;
}
