#include <iostream>
#include<conio.h>
#include<vector>
using namespace std;


class BankAccount {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(string accNumber, string accHolderName, double bal) 
        : accountNumber(accNumber), accountHolderName(accHolderName), balance(bal) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
        } else {
            cout << "Insufficient funds." << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    virtual void calculateInterest() const {
    
    }

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string accNumber, string accHolderName, double bal, double intRate)
        : BankAccount(accNumber, accHolderName, bal), interestRate(intRate) {}

    void calculateInterest() const override {
        double interest = balance * interestRate / 100;
        cout << "Interest for Savings Account: " << interest << endl;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string accNumber, string accHolderName, double bal, double odLimit)
        : BankAccount(accNumber, accHolderName, bal), overdraftLimit(odLimit) {}

    void checkOverdraft(double amount) const {
        if (balance + overdraftLimit >= amount) {
            cout << "Withdrawal within overdraft limit." << endl;
        } else {
            cout << "Withdrawal exceeds overdraft limit." << endl;
        }
    }

    void withdraw(double amount) override {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
        } else {
            cout << "Insufficient funds including overdraft limit." << endl;
        }
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};

class FixedDepositAccount : public BankAccount {
private:
    int term; 

public:
    FixedDepositAccount(string accNumber, string accHolderName, double bal, int termDuration)
        : BankAccount(accNumber, accHolderName, bal), term(termDuration) {}

    void calculateInterest() const override {
        
        double interestRate = 5.0;
        double interest = balance * interestRate / 100 * (term / 12.0);
        cout << "Interest for Fixed Deposit Account: " << interest << endl;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Term Duration: " << term << " months" << endl;
    }
};


void displayMenu() {
    cout << "1. Create Savings Account" << endl;
    cout << "2. Create Checking Account" << endl;
    cout << "3. Create Fixed Deposit Account" << endl;
    cout << "4. Deposit" << endl;
    cout << "5. Withdraw" << endl;
    cout << "6. Display Account Info" << endl;
    cout << "7. Calculate Interest" << endl;
    cout << "8. Exit" << endl;
BankAccount* createAccount() {
    int choice;
    cout << "Select Account Type:" << endl;
    cout << "1. Savings Account" << endl;
    cout << "2. Checking Account" << endl;
    cout << "3. Fixed Deposit Account" << endl;
    cin >> choice;

    string accNumber, accHolderName;
    double balance;
    cout << "Enter Account Number: ";
    cin >> accNumber;
    cout << "Enter Account Holder Name: ";
    cin >> accHolderName;
    cout << "Enter Initial Balance: ";
    cin >> balance;

    if (choice == 1) {
        double interestRate;
        cout << "Enter Interest Rate (%): ";
        cin >> interestRate;
        return new SavingsAccount(accNumber, accHolderName, balance, interestRate);
    } else if (choice == 2) {
        double overdraftLimit;
        cout << "Enter Overdraft Limit: ";
        cin >> overdraftLimit;
        return new CheckingAccount(accNumber, accHolderName, balance, overdraftLimit);
    } else if (choice == 3) {
        int term;
        cout << "Enter Term Duration (months): ";
        cin >> term;
        return new FixedDepositAccount(accNumber, accHolderName, balance, term);
    } else {
        cout << "Invalid choice!" << endl;
        return nullptr;
    }
}

int main() {
    vector<BankAccount*> accounts;
    int choice;
    
    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 8) {
            break;
        }

        switch (choice) {
            case 1:
            case 2:
            case 3: {
                BankAccount* account = createAccount();
                if (account) {
                    accounts.push_back(account);
                    cout << "Account created successfully!" << endl;
                }
                break;
            }
            case 4: {
                int accIndex;
                double amount;
                cout << "Enter Account Index: ";
                cin >> accIndex;
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                if (accIndex < accounts.size()) {
                    accounts[accIndex]->deposit(amount);
                } else {
                    cout << "Invalid Account Index!" << endl;
                }
                break;
            }
            case 5: {
                int accIndex;
                double amount;
                cout << "Enter Account Index: ";
                cin >> accIndex;
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                if (accIndex < accounts.size()) {
                    accounts[accIndex]->withdraw(amount);
                } else {
                    cout << "Invalid Account Index!" << endl;
                }
                break;
            }
            case 6: {
                int accIndex;
                cout << "Enter Account Index: ";
                cin >> accIndex;
                if (accIndex < accounts.size()) {
                    accounts[accIndex]->displayAccountInfo();
                } else {
                    cout << "Invalid Account Index!" << endl;
                }
                break;
            }
            case 7: {
                int accIndex;
                cout << "Enter Account Index: ";
                cin >> accIndex;
                if (accIndex < accounts.size()) {
                    accounts[accIndex]->calculateInterest();
                } else {
                    cout << "Invalid Account Index!" << endl;
                }
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }

}
