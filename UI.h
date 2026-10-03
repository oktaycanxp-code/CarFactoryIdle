// UI.h
#pragma once

#include <string>
#include <vector>

#include "Factory.h"
#include "Economy.h"
#include "raylib.h"

class UI
{
public:
    UI();
    void Draw(const Factory& factory, const Economy& economy);

private:
    void DrawTopBar(const Factory& factory, const Economy& economy);
    void DrawLeftBar();
    void DrawStatsPanel(const Factory& factory, const Economy& economy);
    void DrawProductionPanel(const Factory& factory);
    void DrawVehiclesPanel(const Factory& factory);
};
