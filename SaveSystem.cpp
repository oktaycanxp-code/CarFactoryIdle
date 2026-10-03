// SaveSystem.cpp
#include "SaveSystem.h"

#include <fstream>
#include <sstream>
#include <string>

SaveSystem::SaveSystem()
{
}

void SaveSystem::Save(const std::string& path, const SaveData& data)
{
    std::ofstream out(path, std::ios::out | std::ios::trunc);
    if (!out.is_open())
    {
        return;
    }

    out << data.money << '\n';
    out << data.factoryLevel << '\n';
    out << data.warehouseCapacity << '\n';
    out << data.productionLineCount << '\n';
    out << data.totalCarsProduced << '\n';
    out << data.totalCarsSold << '\n';

    out << data.unlockedCars.size() << '\n';
    for (const auto& name : data.unlockedCars)
    {
        out << name << '\n';
    }

    out << data.machineLevels.size() << '\n';
    for (const auto& level : data.machineLevels)
    {
        out << level << '\n';
    }

    out << data.employeeLevels.size() << '\n';
    for (const auto& level : data.employeeLevels)
    {
        out << level << '\n';
    }

    out.close();
}

bool SaveSystem::Load(const std::string& path, SaveData& data)
{
    std::ifstream in(path);
    if (!in.is_open())
    {
        return false;
    }

    std::string line;
    if (!std::getline(in, line))
    {
        return false;
    }
    data.money = std::stod(line);

    if (!std::getline(in, line)) return false;
    data.factoryLevel = std::stoi(line);

    if (!std::getline(in, line)) return false;
    data.warehouseCapacity = std::stoi(line);

    if (!std::getline(in, line)) return false;
    data.productionLineCount = std::stoi(line);

    if (!std::getline(in, line)) return false;
    data.totalCarsProduced = std::stoi(line);

    if (!std::getline(in, line)) return false;
    data.totalCarsSold = std::stoi(line);

    if (!std::getline(in, line)) return false;
    size_t unlockedCount = static_cast<size_t>(std::stoi(line));
    data.unlockedCars.clear();
    for (size_t i = 0; i < unlockedCount; ++i)
    {
        if (!std::getline(in, line)) return false;
        data.unlockedCars.push_back(line);
    }

    if (!std::getline(in, line)) return false;
    size_t machineCount = static_cast<size_t>(std::stoi(line));
    data.machineLevels.clear();
    for (size_t i = 0; i < machineCount; ++i)
    {
        if (!std::getline(in, line)) return false;
        data.machineLevels.push_back(std::stoi(line));
    }

    if (!std::getline(in, line)) return false;
    size_t employeeCount = static_cast<size_t>(std::stoi(line));
    data.employeeLevels.clear();
    for (size_t i = 0; i < employeeCount; ++i)
    {
        if (!std::getline(in, line)) return false;
        data.employeeLevels.push_back(std::stoi(line));
    }

    return true;
}
