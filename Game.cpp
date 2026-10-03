// Game.cpp
#include "Game.h"

#include <string>

Game::Game()
    : mouseDragging_(false), autoSaveTimer_(0.0f), savePath_("car_factory_idle_save.dat")
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1600, 900, "Car Factory Idle");
    SetTargetFPS(60);

    camera_ = { 0 };
    camera_.position = (Vector3){ 28.0f, 24.0f, 30.0f };
    camera_.target = (Vector3){ 0.0f, 4.0f, 0.0f };
    camera_.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera_.fovy = 42.0f;
    camera_.projection = CAMERA_PERSPECTIVE;

    factory_.SpawnInitialVehicles();
}

Game::~Game()
{
    CloseWindow();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        HandleInput(dt);
        Update(dt);
        Draw();
    }
}

void Game::HandleInput(float dt)
{
    (void)dt;

    if (IsKeyPressed(KEY_F5))
    {
        SaveGame();
    }

    if (IsKeyPressed(KEY_F9))
    {
        LoadGame();
    }

    if (IsKeyDown(KEY_W))
    {
        camera_.position.z -= 0.25f;
    }
    if (IsKeyDown(KEY_S))
    {
        camera_.position.z += 0.25f;
    }
    if (IsKeyDown(KEY_A))
    {
        camera_.position.x -= 0.25f;
    }
    if (IsKeyDown(KEY_D))
    {
        camera_.position.x += 0.25f;
    }
    if (IsKeyDown(KEY_Q))
    {
        camera_.position.y += 0.15f;
    }
    if (IsKeyDown(KEY_E))
    {
        camera_.position.y -= 0.15f;
    }

    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        if (!mouseDragging_)
        {
            lastMousePos_ = mousePos;
            mouseDragging_ = true;
        }

        Vector2 delta = { mousePos.x - lastMousePos_.x, mousePos.y - lastMousePos_.y };
        camera_.target.x -= delta.x * 0.03f;
        camera_.target.z -= delta.y * 0.03f;
        lastMousePos_ = mousePos;
    }
    else
    {
        mouseDragging_ = false;
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
    {
        Vector3 dir = Vector3Subtract(camera_.target, camera_.position);
        Vector3 scale = Vector3Scale(dir, 0.1f * wheel);
        camera_.position = Vector3Add(camera_.position, scale);
    }
}

void Game::Update(float dt)
{
    factory_.Update(dt);
    economy_.Update(dt, factory_);

    autoSaveTimer_ += dt;
    if (autoSaveTimer_ >= 25.0f)
    {
        SaveGame();
        autoSaveTimer_ = 0.0f;
    }
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground((Color){ 20, 24, 31, 255 });

    BeginMode3D(camera_);
    factory_.Draw();
    EndMode3D();

    ui_.Draw(factory_, economy_);

    EndDrawing();
}

void Game::SaveGame()
{
    SaveData data;
    data.money = economy_.GetMoney();
    data.factoryLevel = factory_.GetLevel();
    data.warehouseCapacity = factory_.GetWarehouseCapacity();
    data.productionLineCount = factory_.GetProductionLineCount();
    data.totalCarsProduced = economy_.GetCarsProduced();
    data.totalCarsSold = economy_.GetCarsSold();
    data.unlockedCars = factory_.GetUnlockedCarNames();
    data.machineLevels = factory_.GetMachineLevels();
    data.employeeLevels = factory_.GetEmployeeLevels();
    saveSystem_.Save(savePath_, data);
}

void Game::LoadGame()
{
    SaveData data;
    if (!saveSystem_.Load(savePath_, data))
    {
        return;
    }

    economy_.SetMoney(data.money);
    factory_.SetLevel(data.factoryLevel);
    factory_.SetWarehouseCapacity(data.warehouseCapacity);
    factory_.SetProductionLineCount(data.productionLineCount);
    factory_.SetUnlockedCars(data.unlockedCars);
    factory_.SetMachineLevels(data.machineLevels);
    factory_.SetEmployeeLevels(data.employeeLevels);
    economy_.SetCarsProduced(data.totalCarsProduced);
    economy_.SetCarsSold(data.totalCarsSold);
}

void Game::AddMoney(double amount)
{
    economy_.AddMoney(amount);
}
