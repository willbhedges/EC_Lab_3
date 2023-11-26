#include <string>
#include <iostream>
using namespace std;

class Account {     // The class
  public:           // Access specifier
    string accountNumber;
    string accountHolder;
    float balance;
     virtual void showDetails(ostream& os) const {
        os << "Account Details for Account(ID:" << accountNumber << "):";
        os << "\n" << "   Holder: " << accountHolder << "\n";
        printf("   Balance: $%.2f", balance);
    }

    friend ostream& operator<<(ostream& os, const Account& account) {
        account.showDetails(os);
        return os;
    }

    void displayDetails() const
    {  // Method/function defined inside the class
      cout << "Acount Details for Savings Account(ID:" << accountNumber << "):";
      cout << "\n" << "Holder: " << accountHolder << "\n";
      printf("Balance: $%.2f",balance);
      cout << endl;
    }

    void deposit(float amount) 
    {  // Method/function defined inside the class
      balance = balance + amount;
    }


    void withdraw(float amount) 
    {  // Method/function defined inside the class
        if (balance - amount < 0)
        {
            balance = 0;
            cout << "can only withdraw up to " << balance;
        }
        else
        {
            balance = balance - amount;
        }
      
    }

  Account(const string& number, const string& holder, float initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}


Account operator+(const Account& b) const {
    Account result = *this;
    float min_in_balance = 1200;
    if (b.balance - min_in_balance < 0)
    {
        return result;
    }
    else
    {
    float add_amount;
    add_amount = b.balance - min_in_balance;
    result.balance += add_amount;
    Account& temp_b = const_cast<Account&>(b);
    temp_b.balance -= add_amount;
    }
    

    return result;
}

//     friend ostream& operator<<(ostream& os, const Account& a)
//   {
//     a.displayDetails();
//     return os;
//   }

    Account() 
    {     // Constructor
      ;
    }
};

class SavingsAccount : public Account {
public:
    float interestRate;

    void showDetails(ostream& os) const override {
        Account::showDetails(os);
        os << "\n";
        printf("   Interest Rate: %.2f%%", interestRate*100);
        os << endl << endl;
    }
    void displayDetails() const 
    {
        cout << "Account Details for Savings Account(ID:" << accountNumber << "):";
        cout << "\n" << "   Holder: " << accountHolder << "\n";
        printf("   Balance: $%.2f", balance);
        cout<<endl;
        printf("   Interest Rate: %.2f%%", interestRate*100);
        cout<<endl<<endl;
    }

    void withdraw(float amount) 
    {
        if (balance - amount < 1200.0)
        {
            cout << "Insufficient funds to maintain minimum balance";
        }
        else
        {
            balance = balance - amount;
        }
    }

    SavingsAccount(string my_accountNumber, string my_accountHolder, float my_balance, float my_interestRate)
        : Account(my_accountNumber, my_accountHolder, my_balance), interestRate(my_interestRate) {}
};



class CurrentAccount : public Account {
public:
    float overdraftlimit;
    void showDetails(ostream& os) const override {
        Account::showDetails(os);
        os << endl;
        printf("   Overdraft Limit: $%.2f", overdraftlimit);
        os << endl;
    }
    void displayDetails() const 
    {
        cout << "Account Details for Current Account(ID:" << accountNumber << "):";
        cout << "\n" << "   Holder: " << accountHolder << "\n";
        printf("   Balance: $%.2f", balance);
        cout << endl;
        printf("   Overdraft Limit: $%.2f", overdraftlimit);
        cout << endl << endl;
    }

    void withdraw(float amount) 
    {
        if (balance - amount < overdraftlimit)
        {
            cout << "Overdrafts only allowed up to $" << overdraftlimit;
        }
        else
        {
            balance = balance - amount;
        }
    }
    CurrentAccount& operator=(const Account& other)
    {
        if (this != &other)
        {
            // Assuming you want to copy only the balance, adjust as needed
            balance = other.balance;
        }
        return *this;
    }
    /*CurrentAccount& operator=(const CurrentAccount& other)
{
    if (this != &other)
    {
        // Perform member-wise assignment
        Account::operator=(other); // Call the base class assignment operator
        overdraftlimit = other.overdraftlimit;
    }
    return *this;
}
*/

    CurrentAccount(string my_accountNumber, string my_accountHolder, float my_balance, float my_overdraftlimit)
        : Account(my_accountNumber, my_accountHolder, my_balance), overdraftlimit(my_overdraftlimit) {}
};





int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    //using the cout to show that << is overloaded
    cout << savings;
    cout << current;

    savings.deposit(500);
    current.withdraw(1000);

    cout << endl << "Account Details after deposit and withdrawl" << endl;
    
    //showing .displayDetails to show that we included that method
    savings.displayDetails();
    current.displayDetails();

    // Transfer 300 from savings to current
    current = current + savings;

    cout << "Account Details after transfer" << endl;
    cout << savings;
    cout << current;

    return 0;
}