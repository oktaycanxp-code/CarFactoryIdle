// ProductionLine.cpp
#include "ProductionLine.h"

#include <algorithm>

ProductionLine::ProductionLine()
    : level_(1), progress_(0.0f), currentDuration_(0.0f), active_(false), conveyorState_(0)
{
}

void ProductionLine::Update(float dt, int workerBonus, int machineBonus)
{
    if (!active_ && !queue_.empty())
    {
        activeCar_ = queue_.front();
        queue_.erase(queue_.begin());
        active_ = true;
        progress_ = 0.0f;
        currentDuration_ = activeCar_.productionTime / static_cast<float>(level_ + workerBonus + machineBonus + 1);
    }

    if (!active_)
    {
        return;
    }

    progress_ += dt / std::max(0.4f, currentDuration_);
    conveyorState_ = static_cast<int>((GetTime() * 10.0) + activeCar_.quality) % 10;

    if (progress_ >= 1.0f)
    {
        completedCars_.push_back(activeCar_);
        active_ = false;
        activeCar_ = Car();
        progress_ = 0.0f;
        currentDuration_ = 0.0f;
    }
}

void ProductionLine::Draw3D(Vector3 basePos, int index) const
{
    DrawCube(basePos, 4.2f, 1.2f, 2.0f, (Color){ 54, 59, 66, 255 });
    DrawCube((Vector3){ basePos.x, basePos.y + 0.8f, basePos.z + 1.8f }, 3.8f, 0.6f, 0.4f, (Color){ 189, 198, 207, 255 });

    for (int i = 0; i < 5; ++i)
    {
        float xPos = basePos.x - 1.6f + i * 0.8f;
        DrawCube((Vector3){ xPos, basePos.y + 0.6f, basePos.z + 1.2f }, 0.55f, 0.55f, 0.55f, (Color){ 90, 90, 90, 255 });
    }

    if (active_)
    {
        Vector3 pos = { basePos.x, basePos.y + 1.5f, basePos.z + 0.2f };
        DrawCube(pos, 0.9f, 0.5f, 1.0f, activeCar_.color);
    }

    DrawTextEx(GetFontDefault(), TextFormat("Line %d", index + 1), (Vector2){ basePos.x - 18.0f, basePos.z * 0.7f + 180.0f }, 18.0f, 1.0f, WHITE);
}

bool ProductionLine::IsBusy() const
{
    return active_;
}

void ProductionLine::StartCar(const Car& car)
{
    queue_.push_back(car);
}

void ProductionLine::SetLevel(int level)
{
    level_ = level;
}

int ProductionLine::GetLevel() const
{
    return level_;
}

int ProductionLine::GetQueueSize() const
{
    return static_cast<int>(queue_.size());
}

float ProductionLine::GetProgress() const
{
    return progress_;
}

std::vector<Car> ProductionLine::ConsumeCompletedCars()
{
    std::vector<Car> output = completedCars_;
    completedCars_.clear();
    return output;
}
