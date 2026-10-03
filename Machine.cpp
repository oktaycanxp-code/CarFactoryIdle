// Machine.cpp
#include "Machine.h"

Machine::Machine()
    : type(MachineType::Conveyor), cost(1500.0), speedBonus(0.1f), maintenanceCost(60.0), level(1), owned(true), label("Conveyor")
{
}

Machine::Machine(MachineType typeValue,
                 double costValue,
                 float speedBonusValue,
                 double maintenanceCostValue,
                 int levelValue)
    : type(typeValue),
      cost(costValue),
      speedBonus(speedBonusValue),
      maintenanceCost(maintenanceCostValue),
      level(levelValue),
      owned(true),
      label("Machine")
{
    switch (typeValue)
    {
        case MachineType::RobotArm:
            label = "Robot Arm";
            break;
        case MachineType::Conveyor:
            label = "Conveyor";
            break;
        case MachineType::Press:
            label = "Press";
            break;
        case MachineType::PaintBooth:
            label = "Paint Booth";
            break;
        case MachineType::EngineAssembly:
            label = "Engine Assembly";
            break;
        case MachineType::TireMachine:
            label = "Tire Machine";
            break;
        case MachineType::Welding:
            label = "Welding";
            break;
        case MachineType::Packaging:
            label = "Packaging";
            break;
        default:
            label = "Machine";
            break;
    }
}

void Machine::Upgrade()
{
    ++level;
    speedBonus += 0.08f;
    cost *= 1.35;
    maintenanceCost *= 1.12;
}

double Machine::GetUpgradeCost() const
{
    return cost * 1.45;
}

float Machine::GetSpeedBonus() const
{
    return speedBonus;
}

double Machine::GetMaintenanceCost() const
{
    return maintenanceCost * level;
}

void Machine::Draw3D(Vector3 position, float rotationY) const
{
    DrawCube(position, 1.2f, 1.6f, 1.2f, (Color){ 130, 138, 150, 255 });
    DrawCylinder((Vector3){ position.x, position.y + 0.8f, position.z }, 0.16f, 0.16f, 1.4f, 10, (Color){ 70, 70, 80, 255 });
    DrawCylinder((Vector3){ position.x + 0.7f, position.y + 0.8f, position.z }, 0.18f, 0.18f, 1.0f, 8, (Color){ 44, 44, 46, 255 });

    (void)rotationY;
}
