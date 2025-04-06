#include "EjercicioIV.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

// ===================== CUENTA DE BANCO =====================

// Constructor de la clase BankAccount
BankAccount::BankAccount(std::string holder, double openingBalance)
                        : balance(openingBalance), accountHolder(holder) {}

// Método para depositar dinero en la cuenta
void BankAccount::deposit(double amount) {
    balance += amount;
    std::cout << "\n===============================================================" << std::endl;
    std::cout << "Depósito de $" << amount << " realizado con éxito.\n";
    std::cout << "===============================================================\n" << std::endl;

}

// ===================== CAJA DE AHORRO =====================

// Constructor de la clase SavingsBank
SavingsBank::SavingsBank(std::string holder, double openingBalance)
                        : BankAccount(holder, openingBalance), timesShown(0) {}

// Método para retirar dinero de la caja de ahorro
void SavingsBank::withdraw(double amount) {
    if (amount > balance) {
        std::cout << "Fondos insuficientes en caja de ahorro.\n";

    } else {
        balance -= amount;
        std::cout << "\nRetiro de $" << amount << " realizado con éxito desde caja de ahorro.\n";

    }

}

// Método para mostrar información de la caja de ahorro
void SavingsBank::showInfo() {
    timesShown++;
    std::cout << "\nTipo de cuenta: Caja de ahorro\n";
    std::cout << "Titular de la cuenta: " << accountHolder << "\n";
    std::string messege;

    if (timesShown > 2) {
        balance -= 20;
        messege = "Se ha cobrado una comisión de $20 por mostrar la información de la caja de ahorro más de 2 veces.\n";

    }

    std::cout << "Balance: $" << balance << "\n";
    std::cout << messege;
    std::cout << "===============================================================\n" << std::endl;

}

// ===================== CUENTA CORRIENTE =====================

// Constructor de la clase CheckingAccount
CheckingAccount::CheckingAccount(std::string holder, double openingBalance, SavingsBank* cashbox)
                                : BankAccount(holder, openingBalance), cashboxLinked(cashbox) {}

// Método para retirar dinero de la cuenta corriente
void CheckingAccount::withdraw(double amount) {
    if (amount <= balance) {
        balance -= amount;
        std::cout << "\nRetiro de $" << amount << " realizado con éxito desde cuenta corriente.\n";

    } else if (amount <= (balance + cashboxLinked->balance)) {
        double remaining = amount - balance;
        balance = 0;
        cashboxLinked->balance -= remaining;
        std::cout << "\nSe han retirado $" << amount << " usando cuenta corriente y caja de ahorro.\n";

    } else {
        std::cout << "Fondos insuficientes entre cuenta corriente y caja de ahorro.\n";

    }

}

// Método para mostrar información de la cuenta corriente
void CheckingAccount::showInfo() {
    std::cout << "\nTipo de cuenta: Cuenta Corriente\n";
    std::cout << "Titular de la cuenta: " << accountHolder << "\n";
    std::cout << "Balance: $" << balance << "\n";

}

// ===================== FUNCIONES DE MENÚ =====================

std::vector<SavingsBank*> savingsAccounts;
std::vector<CheckingAccount*> checkingAccounts;

// Función para buscar una caja de ahorro por el nombre del titular
int searchHolderSavingsAccounts(const std::string& name, const std::vector<SavingsBank*>& accounts) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i]->getHolderName() == name) return i;

    }

    return -1;

}

// Función para buscar una cuenta corriente por el nombre del titular
int searchHolderCheckingAccounts(const std::string& name, const std::vector<CheckingAccount*>& accounts) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i]->getHolderName() == name) return i;
    }

    return -1;

}

// Función para crear una nueva cuenta bancaria, con caja de ahorro y cuenta corriente correspondientes
int option1() {
    std::string name;

    std::cout << "Ingrese el nombre del titular de la cuenta: ";
    std::cin.ignore(); // Para limpiar el buffer
    std::getline(std::cin, name);

    if (searchHolderSavingsAccounts(name, savingsAccounts) != -1 ||
    searchHolderCheckingAccounts(name, checkingAccounts) != -1) {
        std::cout << "El titular ya tiene una cuenta creada.\n";

        return 1;

    }

    SavingsBank* newSavings = new SavingsBank(name, 0);
    CheckingAccount* newChecking = new CheckingAccount(name, 0, newSavings);

    savingsAccounts.push_back(newSavings);
    checkingAccounts.push_back(newChecking);

    std::cout << "\n==========================================================================================" << std::endl;
    std::cout << "Caja de ahorro y cuenta corriente creadas correctamente a nombre de " << name << "." << std::endl;
    std::cout << "==========================================================================================\n" << std::endl;

    return 0;

}

// Función para depositar dinero en la cuenta bancaria, siendo caja de ahorro o cuenta corriente
int option2() {
    double amount;
    int accType;
    std::string name;

    std::cout << "Ingrese el nombre del titular: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "\nIngrese el monto a depositar: ";
    std::cin >> amount;

    std::cout << "\n¿Dónde desea realizar el depósito?:\n1. Caja de ahorro\n2. Cuenta corriente\n";
    std::cout << "\nOpción seleccionada: ";
    std::cin >> accType;

    if (accType == 1) {
        int index = searchHolderSavingsAccounts(name, savingsAccounts);
        savingsAccounts[index]->deposit(amount);

    } else if (accType == 2) {
        int index = searchHolderCheckingAccounts(name, checkingAccounts);
        checkingAccounts[index]->deposit(amount);

    } else {
        std::cout << "\nOpción inválida.\n";
        exit(1);

    }

    return 0;

}

// Función para retirar dinero de la cuenta bancaria, siendo caja de ahorro o cuenta corriente
int option3() {
    std::string name;
    double amount;
    int accType;

    std::cout << "Ingrese el nombre del titular: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "\nIngrese el monto a retirar: ";
    std::cin >> amount;

    std::cout << "\n¿Desde dónde desea realizar el retiro?:\n1. Caja de ahorro\n2. Cuenta corriente\n";
    std::cout << "\nOpción seleccionada: ";
    std::cin >> accType;

    if (accType == 1) {
        int index = searchHolderSavingsAccounts(name, savingsAccounts);
        savingsAccounts[index]->withdraw(amount);

    } else if (accType == 2) {
        int index = searchHolderCheckingAccounts(name, checkingAccounts);
        checkingAccounts[index]->withdraw(amount);

    } else {
        std::cout << "\nOpción inválida.\n";
        exit(1);

    }

    return 0;

}

// Función para mostrar la información de la cuenta bancaria, siendo caja de ahorro o cuenta corriente
int option4() {
    std::string name;
    int accType;

    std::cout << "Ingrese el nombre del titular: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "\nSeleccione que información desea ver:\n1. Caja de ahorro\n2. Cuenta corriente\n";
    std::cout << "\nOpción seleccionada: ";
    std::cin >> accType;

    if (accType == 1) {
        int index = searchHolderSavingsAccounts(name, savingsAccounts);
        savingsAccounts[index]->showInfo();

    } else if (accType == 2) {
        int index = searchHolderCheckingAccounts(name, checkingAccounts);
        checkingAccounts[index]->showInfo();

    } else {
        std::cout << "\nOpción inválida.\n";
        exit(1);

    }

    return 0;

}