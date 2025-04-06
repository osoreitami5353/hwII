#ifndef EJERCICIOIV_H
#define EJERCICIOIV_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

class SavingsBank; // Declaración previa

class BankAccount {
    protected:
        double balance;
        std::string accountHolder;

    public:
        BankAccount(std::string holder, double openingBalance);
        void deposit(double amount);
        virtual void withdraw(double amount) = 0;
        virtual void showInfo() = 0;
        virtual ~BankAccount() {}
        std::string getHolderName() const { return accountHolder; }
};

class SavingsBank : public BankAccount {
    private:
        int timesShown;

    public:
        SavingsBank(std::string holder, double openingBalance);
        void withdraw(double amount) override;
        void showInfo() override;
        friend class CheckingAccount;
};

class CheckingAccount : public BankAccount {
    private:
        SavingsBank* cashboxLinked;

    public:
        CheckingAccount(std::string holder, double openingBalance, SavingsBank* cashbox);
        void withdraw(double amount) override;
        void showInfo() override;
};

int searchHolderSavingsAccounts(const std::string& name, const std::vector<SavingsBank*>& accounts);
int searchHolderCheckingAccounts(const std::string& name, const std::vector<CheckingAccount*>& accounts);
int option1();
int option2();
int option3();
int option4();

// ------------ VECTORES GLOBALES ------------
extern std::vector<SavingsBank*> savingsAccounts;
extern std::vector<CheckingAccount*> checkingAccounts;

#endif
