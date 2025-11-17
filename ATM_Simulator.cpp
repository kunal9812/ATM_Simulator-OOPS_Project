#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Account{

    private:
    string acc_holder_name;
    int account_num;
    static int next_acc_num;
    int pin;
    double balance;

    public:
    Account(){
        acc_holder_name = "";
        account_num = 0;
        pin = 0;
        balance = 0.0;
    }
    Account(string name, int p, double Bal){
        acc_holder_name = name;
        pin = p;
        balance = Bal;
        account_num = ++next_acc_num;
    }

    void set_info(){
        cout << endl <<"Set a Pin : ";
        cin >> pin;
        
        cout << endl << "Set a Initial Balance : ";
        cin >> balance;
    }

    void deposit(float amount){
        if(amount <= 0){
            cout << "Invalid deposit amount.\n";
        }
        else{
            balance += amount;
            cout << "Amount deposited successfully.\n";
        }
    }

    void withdraw(float amount){
        if(amount <= 0){
            cout << "Invalid ammount.\n";
        }
        else if(amount > balance){
            cout << "Insufficient Funds.\n";
        }
        else{
            balance -= amount;
        }
    }

    bool aunthication(int P){
        if(pin == P){
            return true;
        }
        else{
            return false;
        }
    }

    void display(){
        cout << "Account Holder's name : " << acc_holder_name << "\nAccount Number : " << account_num;
        cout << "\nCurrent balance : " << balance;
    }
    void getBalance() { cout << "\nCurrent balance : " << balance; }

    void changePin(int newPin) {
        pin = newPin;
        cout << "PIN changed successfully.\n";
    }

    void saveToFile() {
        ofstream file(to_string(account_num) + ".txt");
        file << account_num << endl;
        file << pin << endl;
        file << balance << endl;
        file.close();
    }

    bool loadFromFile(string accNo) {
        ifstream file(accNo + ".txt");
        if (!file.is_open())
            return false;
        file >> account_num;
        file >> pin;
        file >> balance;
        file.close();
        return true;
    }
};
int Account::next_acc_num = 101;

class Bank{
    private:
    Account New_acc;

    public:
    void create_acc(){
        string name;
        int enteredpin;
        double balance;
        cout << "Enter Customer's name : ";
        cin >> name;
        cout << "Enter Pin : ";
        cin >> enteredpin;
        cout << "Set Initial Balance :";
        cin >> balance;
        New_acc = Account(name, enteredpin, balance);
        New_acc.saveToFile();
        cout << "-----Account Created-----\n";
        New_acc.display();
    }
};

class ATM {
private:
    Account currentAccount;

public:
    void run() {
        cout << "Enter Account Number: ";
        string accNo;
        cin >> accNo;
        if (!currentAccount.loadFromFile(accNo)) {
            cout << "Account not found. Create new account through Bank.\n";
        }
        else{
        cout << "Enter PIN: ";
        int enteredPin;
        cin >> enteredPin;
        if (!currentAccount.aunthication(enteredPin)) {
            cout << "Incorrect PIN. Exiting...\n";
            return;
        }
        else{
                int choice;
                do {
                    cout << "\n--------- MENU ---------\n";
                    cout << "1. Check Balance\n";
                    cout << "2. Deposit\n";
                    cout << "3. Withdraw\n";
                    cout << "4. Change PIN\n";
                    cout << "5. Exit\n";
                    cout << "Choose option: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            currentAccount.getBalance();
                            break;
                        case 2: {
                            double amt;
                            cout << "Enter deposit amount: ";
                            cin >> amt;
                            currentAccount.deposit(amt);
                            break;
                        }
                        case 3: {
                            double amt;
                            cout << "Enter withdrawal amount: ";
                            cin >> amt;
                            currentAccount.withdraw(amt);
                            break;
                        }
                        case 4: {
                            int newPin;
                            cout << "Enter new PIN: ";
                            cin >> newPin;
                            currentAccount.changePin(newPin);
                            break;
                        }
                        case 5:
                            cout << "Transaction complete. Thank you!\n";
                            currentAccount.saveToFile();
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }
                } while (choice != 5);
            }
        }
    }
};

int main()
{
    Bank b;
    ATM a;
    int choice;
    do
    {
        cout << "\n--------- MENU ---------\n";
        cout << "1. Create Account\n2. Use ATM\n3. Exit\nChoose option: ";
        cin >> choice;

        switch(choice){
            case 1:
            b.create_acc();
            break;

            case 2:
            a.run();
            break;

            case 3:
            cout << "Transaction complete. Thank you!\n";
            break;
            default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);
    

    return 0;
}