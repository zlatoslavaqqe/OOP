#include <iostream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bankomat
{
private:
    int id;
    int minWithdraw;
    int maxWithdraw;

    int n10, n20, n50, n100, n200, n500, n1000;

    int totalMoney() const
    {
        return n10 * 10 + n20 * 20 + n50 * 50 + n100 * 100 +
            n200 * 200 + n500 * 500 + n1000 * 1000;
    }

public:

    // конструктори
    Bankomat()
    {
        id = 0;
        minWithdraw = 0;
        maxWithdraw = 0;
        n10 = n20 = n50 = n100 = n200 = n500 = n1000 = 0;
    }

    Bankomat(int _id, int minW, int maxW)
    {
        if (!Init(_id, minW, maxW))
        {
            id = 0; minWithdraw = 0; maxWithdraw = 0;
        }
        n10 = n20 = n50 = n100 = n200 = n500 = n1000 = 0;
    }

    Bankomat(const Bankomat& other)
    {
        id = other.id;
        minWithdraw = other.minWithdraw;
        maxWithdraw = other.maxWithdraw;

        n10 = other.n10;  n20 = other.n20;  n50 = other.n50;
        n100 = other.n100; n200 = other.n200;
        n500 = other.n500; n1000 = other.n1000;
    }

    ~Bankomat() {}

    bool Init(int _id, int minW, int maxW)
    {
        if (_id <= 0 || minW <= 0 || maxW <= 0 || minW > maxW)
            return false;

        id = _id;
        minWithdraw = minW;
        maxWithdraw = maxW;
        return true;
    }

    // метод Read 
    void Read()
    {
        int _id, minW, maxW;

        do {
            cout << "Введіть ID банкомата: ";
            cin >> _id;
            cout << "Мінімальна сума: ";
            cin >> minW;
            cout << "Максимальна сума: ";
            cin >> maxW;
        } while (!Init(_id, minW, maxW));
    }

    // метод loadCash 
    void loadCash()
    {
        cout << "\n--- Завантаження купюр ---\n";
        cout << "Купюр по 10: "; cin >> n10;
        cout << "Купюр по 20: "; cin >> n20;
        cout << "Купюр по 50: "; cin >> n50;
        cout << "Купюр по 100: "; cin >> n100;
        cout << "Купюр по 200: "; cin >> n200;
        cout << "Купюр по 500: "; cin >> n500;
        cout << "Купюр по 1000: "; cin >> n1000;
    }

    // метод withdraw
    bool withdraw(int sum)
    {
        if (sum < minWithdraw)
        {
            cout << "❌ Сума менша за мінімальну.\n";
            return false;
        }
        if (sum > maxWithdraw)
        {
            cout << "❌ Сума перевищує максимальний ліміт.\n";
            return false;
        }
        if (sum > totalMoney())
        {
            cout << "❌ У банкоматі недостатньо коштів.\n";
            return false;
        }

        int s = sum;

        int take1000 = min(n1000, s / 1000); s -= take1000 * 1000;
        int take500 = min(n500, s / 500);  s -= take500 * 500;
        int take200 = min(n200, s / 200);  s -= take200 * 200;
        int take100 = min(n100, s / 100);  s -= take100 * 100;
        int take50 = min(n50, s / 50);   s -= take50 * 50;
        int take20 = min(n20, s / 20);   s -= take20 * 20;
        int take10 = min(n10, s / 10);   s -= take10 * 10;

        if (s != 0)
        {
            cout << "❌ Не можна видати таку суму потрібними номіналами.\n";
            return false;
        }

        n1000 -= take1000;
        n500 -= take500;
        n200 -= take200;
        n100 -= take100;
        n50 -= take50;
        n20 -= take20;
        n10 -= take10;

        cout << "✅ Видано " << sum << " грн\n";
        return true;
    }

    // метод Display 
    void Display()
    {
        cout << "\n=== Інформація про банкомат ===\n";
        cout << "ID: " << id << "\n";
        cout << "Мінімум: " << minWithdraw << "\n";
        cout << "Максимум: " << maxWithdraw << "\n";
        cout << "Баланс: " << totalMoney() << " грн\n";
    }

    // метод toString 
    string toString() const
    {
        stringstream ss;
        ss << "Баланс: " << totalMoney() << " грн\n";
        ss << "10: " << n10 << " | 20: " << n20 << " | 50: " << n50 << "\n";
        ss << "100: " << n100 << " | 200: " << n200
            << " | 500: " << n500 << " | 1000: " << n1000 << "\n";
        return ss.str();
    }

    // operator+ (поповнення)
    Bankomat operator+(int amount)
    {
        Bankomat temp = *this;

        while (amount >= 1000) { temp.n1000++; amount -= 1000; }
        while (amount >= 500) { temp.n500++;  amount -= 500; }
        while (amount >= 200) { temp.n200++;  amount -= 200; }
        while (amount >= 100) { temp.n100++;  amount -= 100; }
        while (amount >= 50) { temp.n50++;   amount -= 50; }
        while (amount >= 20) { temp.n20++;   amount -= 20; }
        while (amount >= 10) { temp.n10++;   amount -= 10; }

        return temp;
    }

    // operator- (зняття) 
    Bankomat operator-(int amount)
    {
        Bankomat temp = *this;
        temp.withdraw(amount);
        return temp;
    }

    // operator==
    bool operator==(const Bankomat& other)
    {
        return this->totalMoney() == other.totalMoney();
    }

    // operator<< 
    friend ostream& operator<<(ostream& os, const Bankomat& b)
    {
        os << b.toString();
        return os;
    }
};


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Bankomat atm;
    atm.Read();
    atm.loadCash();

    int choice;

    while (true)
    {
        cout << "\n МЕНЮ БАНКОМАТА \n";
        cout << "1 — Показати стан банкомата\n";
        cout << "2 — Поповнити банкомат (operator+)\n";
        cout << "3 — Зняти гроші (operator-)\n";
        cout << "4 — Перевірити рівність двох банкоматів (operator==)\n";
        cout << "0 — Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1)
        {
            cout << "\n" << atm;
        }
        else if (choice == 2)
        {
            int amount;
            cout << "Введіть суму для поповнення: ";
            cin >> amount;

            atm = atm + amount;
            cout << "Поповнення виконано!\n";
        }
        else if (choice == 3)
        {
            int amount;
            cout << "Введіть суму для зняття: ";
            cin >> amount;

            atm = atm - amount;
        }
        else if (choice == 4)
        {
            Bankomat temp(999, 100, 5000);
            temp = temp + 3000;

            if (atm == temp)
                cout << "Банкомати мають однаковий баланс!\n";
            else
                cout << "Банкомати різні.\n";
        }
    }

    return 0;
}

