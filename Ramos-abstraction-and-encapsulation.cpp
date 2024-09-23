#include <iostream>
#include <limits>
using namespace std;

// Abstraction
class Menus {
    public:
        virtual void displayMenu() = 0;
};

class SubMenu : public Menus {
    private:
        int choice;
        double money;                                                       //money to input by user
        double savingsBal;
        double currentBal;
        double min_savingsBal = 1000.0;
        bool isFirstDeposit = true;

        //input validation for choice (int)
        int getValidInput() {
            int input;
            while (true) {
                cin >> input;
                if (cin.fail()) {
                    cout << "Invalid input. Kindly enter a number.\n\n";
                    cout << "Enter your choice: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } 
                else {
                    break;
                }
            }
            return input;
        }

        //input validation for money (double)
        double getValidMoney() {
            double input;
            while (true) {
                cin >> input;
                if (cin.fail()) {
                    cout << "Invalid input. Kindly enter a valid amount.\n";
                    cout << "Amount: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } 
                else {
                    break;
                }
            }
            return input;
        }

    public:
        //constructor
        SubMenu() : savingsBal(0.0), currentBal(0.0), choice(0) {}

        //function to deposit for both Savings and Current accounts
        void deposit(double& accountBal, bool isSavings = false) {
            if (isSavings && isFirstDeposit) {                              //for Savings Account at first deposit
                cout << "First deposit for Savings Account must be at least P" << min_savingsBal << ".\n";

                double money;
                do {
                    cout << "Amount to deposit: ";
                    money = getValidMoney();
                    if (money < min_savingsBal) {
                        cout << "\nThe amount you entered is less than the required minimum balance of P1000.\n\n";
                    }
                } while (money < min_savingsBal);

                accountBal += money;
                isFirstDeposit = false;                                     //first deposit done
                cout << "\nDeposit successful!\n\nAmount Deposited: " << money << "\n\n";
            } 
            else {                                                          //for Current Account
                cout << "Amount to deposit: ";  
                double money = getValidMoney();
                accountBal += money;
                cout << "\nDeposit successful!\n\nAmount Deposited: " << money << "\n\n";
            }
            cout << "Returning to Sub Menu...\n";
        }

        //withdraw function
        void withdraw(double& accountBal, bool isSavings = false) {
            cout << "Amount to withdraw: ";
            double money = getValidMoney();
            if (isSavings && ((accountBal - money) < min_savingsBal)) {
                cout << "\nUnable to withdraw. The minimum balance for Savings Account is P" << min_savingsBal << ".\n\n";
            } 
            else if (accountBal >= money) {
                accountBal -= money;
                cout << "\nWithdraw successful!\n";
                cout << "\nAmount withdrew: " << money << "\n\n";
            } 
            else {
                cout << "\nInsufficient funds!" << "\n\n";
            }
            cout << "Returning to Sub Menu...\n";
        }

        //display account balance
        void displayBal(double& accountBal) {
            cout << "Current Balance: " << accountBal << "\n\n";
            cout << "Returning to Sub Menu...\n";
        }

        //display submenu
        void displayMenu(double& accountBal, bool isSavings = false) {
            do {
                cout << "========== SUB MENU ==========\n";
                cout << "1 - Deposit" << endl
                     << "2 - Withdraw" << endl
                     << "3 - Check Balance" << endl
                     << "4 - Back" << "\n\n";
                cout << "Enter your choice: ";
                choice = getValidInput();                                   //input choice validation
                cout << "\nProceeding to the next...\n";
                system("pause");
                system("cls");

                switch (choice) {
                    case 1:
                        cout << "========== DEPOSIT ==========\n";
                        deposit(accountBal, isSavings);                     //deposit function
                        system("pause");
                        system("cls");
                        break;

                    case 2:
                        cout << "========== WITHDRAW ==========\n";
                        withdraw(accountBal, isSavings);                    //withdraw function
                        system("pause");
                        system("cls");
                        break;

                    case 3:
                        cout << "========== BALANCE CHECK ==========\n";
                        displayBal(accountBal);                             //balance check function
                        system("pause");
                        system("cls");
                        break;

                    case 4:
                        cout << "Going back to the Main Menu...\n";         
                        system("pause");
                        system("cls");
                        break;

                    default:
                        cout << "Invalid input. Kindly enter numbers 1 to 4 only.\n\n";
                        cout << "Returning to Sub Menu...\n";
                        system("pause");
                        system("cls");
                }
            } while (choice != 4);
        }

        //get the balance for Savings Account
        double& getSavingsBal() {
            return savingsBal;
        }

        //get thebalance for Current Account
        double& getCurrentBal() {
            return currentBal;
        }

        void displayMenu() override {}
};

class MainMenu : public Menus {
private:
    int choice;
    SubMenu subMenu;

    //input validation for choice (int)
    int getValidInput() {
        int input;
        while (true) {
            cin >> input;
            if (cin.fail()) {
                cout << "Invalid input. Kindly enter a number.\n\n";
                cout << "Enter your choice: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } 
            else {
                break;
            }
        }
        return input;
    }

public:
    //constructor
    MainMenu() : choice(0) {}

    void displayMenu() override {
        do {
            cout << "========== MAIN MENU ==========\n";
            cout << "1 - Savings Account" << endl
                 << "2 - Current Account" << endl
                 << "3 - Exit" << "\n\n";
            cout << "Enter your choice: ";
            choice = getValidInput();
            cout << "\nProceeding to the next...\n";
            system("pause");
            system("cls");

            switch (choice) {
                case 1:
                    subMenu.displayMenu(subMenu.getSavingsBal(), true);                 //to display submenu and get the Savings Account Balance
                    break;

                case 2:
                    subMenu.displayMenu(subMenu.getCurrentBal(), false);                //to display submenu and get the Current Account Balance
                    break;

                case 3:
                    cout << "Thank you!\n\nExiting from the bank...";
                    break;

                default:
                    cout << "Invalid input. Kindly enter numbers 1 to 3 only.\n\n";
                    cout << "Returning to Main Menu...\n";
                    system("pause");
                    system("cls");
            }
        } while (choice != 3);
    }
};

int main() {
    MainMenu mm1;                                                                       //object for MainMenu class
    mm1.displayMenu();                                                                  //call displayMenu function from MainMenu class
    
    return 0;
}