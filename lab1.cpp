#include <iostream>
#include <windows.h>    
using namespace std;
 
struct Salary
{
   double first;  
   int second;    
 
   bool Init(double f, int s)
   {
       if (f <= 0 || s < 0 || s > 31)
           return false;
 
       first = f;
       second = s;
       return true;
   }
 
   void Read()
   {
       double f;
       int s;
 
       do {
           cout << "Введіть оклад (додатне число): ";
           cin >> f;
       } while (f <= 0);
 
       do {
           cout << "Введіть кількість відпрацьованих днів (0–31): ";
           cin >> s;
       } while (s < 0 || s > 31);
 
       Init(f, s);
   }
 
   void Display()
   {
       cout << "\n--- Дані про зарплату ---\n";
       cout << "Оклад: " << first << endl;
       cout << "Відпрацьовані дні: " << second << endl;
   }
 
   double summa(int daysInMonth)
   {
       if (daysInMonth <= 0 || daysInMonth > 31)
       {
           cout << "Помилка: некоректна кількість днів у місяці.\n";
           return 0;
       }
 
       return (first / daysInMonth) * second;
   }
};
 
int main()
{
   SetConsoleOutputCP(1251);
   SetConsoleCP(1251);
 
   Salary A;
 
   cout << "Введення даних:\n";
   A.Read();
 
   A.Display();
 
   int days;
   cout << "\nВведіть кількість днів у місяці (28–31): ";
   cin >> days;
 
   cout << "\nНарахована сума: " << A.summa(days) << endl;
 
   return 0;
}
 
