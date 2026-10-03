// UI.cpp
#include "UI.h"

UI::UI()
{
}

void UI::Draw(const Factory& factory, const Economy& economy)
{
    DrawTopBar(factory, economy);
    DrawLeftBar();
    DrawStatsPanel(factory, economy);
    DrawProductionPanel(factory);
    DrawVehiclesPanel(factory);
}

void UI::DrawTopBar(const Factory& factory, const Economy& economy)
{
    DrawRectangle(0, 0, GetScreenWidth(), 80, (Color){ 17, 20, 24, 220 });
    DrawText(TextFormat("Money: $%.2f", economy.GetMoney()), 20, 20, 28, GOLD);
    DrawText(TextFormat("Income/min: $%.2f", economy.GetIncomePerMinute()), 260, 20, 20, GREEN);
    DrawText(TextFormat("Daily: $%.2f", economy.GetDailyIncome()), 500, 20, 20, SKYBLUE);
    DrawText(TextFormat("Factory Lvl: %d", factory.GetLevel()), 800, 20, 20, WHITE);
    DrawText(TextFormat("Workers: %d", factory.GetActiveWorkers()), 1010, 20, 20, WHITE);
    DrawText(TextFormat("Cars Sold: %d", economy.GetCarsSold()), 1210, 20, 20, WHITE);
}

void UI::DrawLeftBar()
{
    DrawRectangle(0, 80, 220, GetScreenHeight() - 80, (Color){ 34, 39, 45, 220 });
    DrawText("Factory", 30, 110, 24, WHITE);
    DrawText("Production", 30, 160, 24, WHITE);
    DrawText("Cars", 30, 210, 24, WHITE);
    DrawText("Workers", 30, 260, 24, WHITE);
    DrawText("Upgrades", 30, 310, 24, WHITE);
    DrawText("Store", 30, 360, 24, WHITE);
    DrawText("Settings", 30, 410, 24, WHITE);
}

void UI::DrawStatsPanel(const Factory& factory, const Economy& economy)
{
    Rectangle panel = { 250.0f, 110.0f, 320.0f, 220.0f };
    DrawRectangleRounded(panel, 0.12f, 6, (Color){ 38, 46, 55, 220 });
    DrawText("Overview", 270, 130, 22, WHITE);
    DrawText(TextFormat("Profit/min: $%.2f", economy.GetIncomePerMinute() - economy.GetExpensesPerMinute()), 270, 170, 18, LIME);
    DrawText(TextFormat("Expenses/min: $%.2f", economy.GetExpensesPerMinute()), 270, 200, 18, ORANGE);
    DrawText(TextFormat("Warehouse: %d / %d", factory.GetProductionLineCount() * 10, factory.GetWarehouseCapacity()), 270, 230, 18, WHITE);
    DrawText(TextFormat("Workers: %d", factory.GetActiveWorkers()), 270, 260, 18, WHITE);
    DrawText(TextFormat("Cars Produced: %d", economy.GetCarsProduced()), 270, 290, 18, WHITE);
}

void UI::DrawProductionPanel(const Factory& factory)
{
    Rectangle panel = { 610.0f, 110.0f, 350.0f, 220.0f };
    DrawRectangleRounded(panel, 0.12f, 6, (Color){ 38, 46, 55, 220 });
    DrawText("Production Lines", 630, 130, 22, WHITE);

    for (size_t i = 0; i < factory.GetProductionLines().size(); ++i)
    {
        const auto& line = factory.GetProductionLines()[i];
        DrawText(TextFormat("Line %zu: %s", i + 1, line.IsBusy() ? "Busy" : "Idle"), 630, 170 + static_cast<float>(i * 42), 18, WHITE);
        DrawText(TextFormat("Progress: %.0f%%", line.GetProgress() * 100.0f), 630, 195 + static_cast<float>(i * 42), 16, SKYBLUE);
    }
}

void UI::DrawVehiclesPanel(const Factory& factory)
{
    Rectangle panel = { 1010.0f, 110.0f, 520.0f, 240.0f };
    DrawRectangleRounded(panel, 0.12f, 6, (Color){ 38, 46, 55, 220 });
    DrawText("Vehicle Catalog", 1030, 130, 22, WHITE);

    const auto& unlocked = factory.GetUnlockedCarNames();
    for (size_t i = 0; i < unlocked.size(); ++i)
    {
        DrawText(TextFormat("%zu. %s", i + 1, unlocked[i].c_str()), 1030, 170 + static_cast<float>(i * 32), 18, LIME);
    }
}
