// Game.h
#pragma once

#include "raylib.h"
#include "Factory.h"
#include "Economy.h"
#include "UI.h"
#include "SaveSystem.h"

class Game
{
public:
    Game();
    ~Game();

    void Run();
    void Update(float dt);
    void Draw();
    void HandleInput(float dt);
    void SaveGame();
    void LoadGame();
    void AddMoney(double amount);

    Factory& GetFactory() { return factory_; }
    Economy& GetEconomy() { return economy_; }
    UI& GetUI() { return ui_; }

private:
    Factory factory_;
    Economy economy_;
    UI ui_;
    SaveSystem saveSystem_;
    Camera3D camera_;
    bool mouseDragging_;
    Vector2 lastMousePos_;
    float autoSaveTimer_;
    std::string savePath_;
};
