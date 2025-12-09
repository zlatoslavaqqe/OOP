#pragma once
#include <string>

class Bankomat
{
private:
    int id;
    int minWithdraw;
    int maxWithdraw;

    int n10, n20, n50, n100, n200, n500, n1000;

    int totalMoney() const;

public:
    // Конструктори та деструктор
    Bankomat();
    Bankomat(int _id, int minW, int maxW);
    Bankomat(const Bankomat& other);
    ~Bankomat();

    // Методи
    bool Init(int _id, int minW, int maxW);
    void Read();
    void loadCash();
    bool withdraw(int sum);
    void Display();
    std::string toString();
};
