// Machine.h
#pragma once

#include <string>

#include "raylib.h"

enum class MachineType
{
    RobotArm,
    Conveyor,
    Press,
    PaintBooth,
    EngineAssembly,
    TireMachine,
    Welding,
    Packaging
};

class Machine
{
public:
    Machine();
    Machine(MachineType typeValue,
            double costValue,
            float speedBonusValue,
            double maintenanceCostValue,
            int levelValue = 1);

    void Upgrade();
    double GetUpgradeCost() const;
    float GetSpeedBonus() const;
    double GetMaintenanceCost() const;
    void Draw3D(Vector3 position, float rotationY) const;

    MachineType type;
    double cost;
    float speedBonus;
    double maintenanceCost;
    int level;
    bool owned;
    std::string label;
};
