#ifndef EJERCICIOIV_H
#define EJERCICIOIV_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

class SavingsBank; // Declaración previa

class BankAccount {
    protected:
        double balance;             // protected: permite que las clases derivadas accedan al saldo directamente, pero evita el acceso externo no autorizado.
        std::string accountHolder;  // protected: se usa para que las subclases puedan acceder al titular sin exponerlo públicamente.

    public:
        BankAccount(std::string holder, double openingBalance);     // public: se necesita acceso libre para crear cuentas desde fuera de la clase.
        void deposit(double amount);                                // public: accesible desde el exterior, permite realizar depósitos sobre cualquier cuenta.
        virtual void withdraw(double amount) = 0;                   // public y virtual: debe poder ser llamado externamente y sobreescrito por las subclases.
        virtual void showInfo() = 0;                                // public y virtual: accesible desde cualquier parte, implementado en subclases según el tipo de cuenta.
        virtual ~BankAccount() {}                                   // public: destructor virtual público para asegurar destrucción correcta vía puntero base.
        std::string getHolderName() const { return accountHolder; } // public: permite leer el nombre del titular sin modificarlo.
};

class SavingsBank : public BankAccount {
    private:
        int timesShown;// private: se usa sólo internamente para llevar cuenta de las veces que se muestra info. No debe ser accesible ni por herencia ni externamente.

    public:
        SavingsBank(std::string holder, double openingBalance); // public: permite crear objetos desde el exterior.
        void withdraw(double amount) override;                  // public: método obligatorio accesible desde fuera, según la lógica del sistema bancario.
        void showInfo() override;                               // public: se necesita mostrar información al usuario.
        friend class CheckingAccount;                           // Permite acceso a atributos privados desde CheckingAccount. Esto reduce encapsulamiento, pero se justifica si se requiere alta cooperación entre clases.
};

class CheckingAccount : public BankAccount {
    private:
        SavingsBank* cashboxLinked; // private: el vínculo con una caja de ahorro es interno a la cuenta corriente. No debe modificarse directamente desde fuera.

    public:
        CheckingAccount(std::string holder, double openingBalance, SavingsBank* cashbox);   // public: se necesita acceso para crear estas cuentas y vincularlas.
        void withdraw(double amount) override;                                              // public: se usa externamente.
        void showInfo() override;                                                           // public: el sistema necesita mostrar los datos de la cuenta al usuario.
};

int searchHolderSavingsAccounts(const std::string& name, const std::vector<SavingsBank*>& accounts);
int searchHolderCheckingAccounts(const std::string& name, const std::vector<CheckingAccount*>& accounts);
int option1();
int option2();
int option3();
int option4();

// ------------ VECTORES GLOBALES ------------
// Se usan extern para que sean accedidos desde otros archivos, manteniendo una sola instancia compartida en todo el programa.
extern std::vector<SavingsBank*> savingsAccounts;
extern std::vector<CheckingAccount*> checkingAccounts;

#endif
