// Economy.cpp
#include "Economy.h"

#include <algorithm>

#include "Factory.h"

Economy::Economy()
    : money_(25000.0), incomePerMinute_(0.0), dailyIncome_(0.0), expensesPerMinute_(0.0), carsProduced_(0), carsSold_(0), timer_(0.0f)
{
}

void Economy::Update(float dt, Factory& factory)
{
    timer_ += dt;

    std::vector<Car> soldCars = factory.ConsumeCompletedCars();
    double saleValue = 0.0;
    for (const auto& car : soldCars)
    {
        saleValue += car.salePrice;
        ++carsSold_;
        ++carsProduced_;
        money_ += car.salePrice;
    }

    double salaryCost = 0.0;
    for (const auto& employee : factory.GetEmployees())
    {
        if (employee.hired)
        {
            salaryCost += employee.salary * (dt / 60.0);
        }
    }

    double maintenanceCost = 0.0;
    for (const auto& machine : factory.GetMachines())
    {
        maintenanceCost += machine.maintenanceCost * machine.level * (dt / 60.0);
    }

    double salesIncome = saleValue * (dt / 12.0);
    double idleRevenue = static_cast<double>(factory.GetLevel()) * 160.0 * (dt / 60.0);
    double totalIncome = salesIncome + idleRevenue;
    double totalExpenses = salaryCost + maintenanceCost;

    money_ += totalIncome;
    money_ -= totalExpenses;

    incomePerMinute_ = (totalIncome * 60.0) + static_cast<double>(carsSold_) * 17.0;
    expensesPerMinute_ = (totalExpenses * 60.0) + static_cast<double>(factory.GetActiveWorkers()) * 90.0;
    dailyIncome_ = incomePerMinute_ * 24.0 * 60.0;
}

void Economy::AddMoney(double amount)
{
    money_ += amount;
}

void Economy::SpendMoney(double amount)
{
    money_ -= amount;
}

void Economy::SetMoney(double amount)
{
    money_ = amount;
}

double Economy::GetMoney() const
{
    return money_;
}

double Economy::GetIncomePerMinute() const
{
    return incomePerMinute_;
}

double Economy::GetDailyIncome() const
{
    return dailyIncome_;
}

double Economy::GetExpensesPerMinute() const
{
    return expensesPerMinute_;
}

int Economy::GetCarsSold() const
{
    return carsSold_;
}

int Economy::GetCarsProduced() const
{
    return carsProduced_;
}

void Economy::SetCarsProduced(int count)
{
    carsProduced_ = count;
}

void Economy::SetCarsSold(int count)
{
    carsSold_ = count;
}

void Economy::AddCarsProduced(int count)
{
    carsProduced_ += count;
}

void Economy::AddCarsSold(int count)
{
    carsSold_ += count;
}
