#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accNumber, double initialBalance){
        this->accountNumber = accNumber;
        if (initialBalance < 0) {
            throw invalid_argument("Начальный баланс не может быть отрицательным");
        }
        this->balance = initialBalance;
        this->interestRate = 0;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Количество внесенных средств должно быть больше нуля");
        }

        balance = balance +  amount;
        cout << "Средства успешно внесены. Остаток на счете: " << balance << endl;
    }

    void withdraw(double amount) {
        try {
            if (balance < amount || amount <= 0) {
                throw runtime_error("Количество средств не должно превышать баланс и должно быть больше 0");
            }

            balance -= amount;

            cout << "Средства успешно сняты. Остаток на счете: " << balance << endl;
        }
        catch (const runtime_error& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    double getInterest() const {
        return balance * interestRate / 12;
    }

    void setInterestRate(double rate) {
        interestRate = rate;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    bool transfer(BankAccount acc1, BankAccount acc2, double Money) {
        if (Money <= 0) {
            throw invalid_argument("Количество перведенных денег должно быть больше нуля");
            return false;
        }
        if (acc1.balance < Money) {
            throw invalid_argument("Баланс на первом счете недостаточен");
            return false;
        }
        acc1.balance -= Money;
        acc2.balance += Money;
        cout << "Средства успешно переведены. Баланс на аккаунтах:  " << acc1.balance << "\n" << acc2.balance << endl;
        return true;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    int a;
    double d;
    BankAccount acc1(12345, 1000);
    BankAccount acc2(123456, 2000);

    while (true) {
        cout << "Выберите действие: \n1. Внести средства на счет \n2. Снять средства со счета \n3. Узнать текущий баланс \n4. Рассчитать сумму процентов \n5. Обновить процентную ставку \n6. Получить номер банковского счета \n7. Перевести деньги" << endl;
        cin >> a;

        switch (a) {
        case 1:
            cout << "Введите количество средств для пополнения: ";
            cin >> d;
            acc1.deposit(d);
            break;
        case 2:
            cout << "Введите количество средств для снятия: ";
            cin >> d;
            acc1.withdraw(d);
            break;
        case 3:
            cout << "Текущий баланс: " << acc1.getBalance() << endl;
            break;
        case 4:
            cout << "Сумма процентов: " << acc1.getInterest() << endl;
            break;
        case 5:
            cout << "Введите процентную ставку: ";
            cin >> d;
            acc1.setInterestRate(d);
            break;
        case 6:
            cout << "Номер банковского счета: " << acc1.getAccountNumber() << endl;
            break;
        case 7:
            acc1.transfer(acc1, acc2, 500);
            break;
        default:
            cout << "Выбрано недопустимое действие" << endl;
            break;
        }
    }
}