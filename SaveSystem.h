// SaveSystem.h
#pragma once

#include <string>
#include <vector>

struct SaveData
{
    double money = 25000.0;
    int factoryLevel = 1;
    int warehouseCapacity = 30;
    int productionLineCount = 1;
    int totalCarsProduced = 0;
    int totalCarsSold = 0;
    std::vector<std::string> unlockedCars;
    std::vector<int> machineLevels;
    std::vector<int> employeeLevels;
};

class SaveSystem
{
public:
    SaveSystem();
    void Save(const std::string& path, const SaveData& data);
    bool Load(const std::string& path, SaveData& data);
};
