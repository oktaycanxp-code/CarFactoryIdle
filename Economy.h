// Economy.h
#pragma once

#include <string>

class Factory;

class Economy
{
public:
    Economy();

    void Update(float dt, Factory& factory);
    void AddMoney(double amount);
    void SpendMoney(double amount);
    void SetMoney(double amount);
    double GetMoney() const;
    double GetIncomePerMinute() const;
    double GetDailyIncome() const;
    double GetExpensesPerMinute() const;
    int GetCarsSold() const;
    int GetCarsProduced() const;
    void SetCarsProduced(int count);
    void SetCarsSold(int count);
    void AddCarsProduced(int count);
    void AddCarsSold(int count);

private:
    double money_;
    double incomePerMinute_;
    double dailyIncome_;
    double expensesPerMinute_;
    int carsProduced_;
    int carsSold_;
    float timer_;
};
