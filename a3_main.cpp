#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "Date.h"
  
using namespace std;

class Transaction {
private:
	Date date;
	double amount, balance;
	string transaction_type;
	

public:
	Transaction(string type, double& amt, double& bal, Date& dt) {
		transaction_type = type;
		amount = amt;
		balance = bal;
		date = dt;
	}

	string get_transaction_type() {
		return transaction_type;
	}
	
	Transaction() {
		transaction_type = "";
		amount = 0.0;
		balance = 0.0;
	}


	Date get_date() {
		return date;
	}


	double get_amount() {
		return amount;
	}

	double get_balance() {
		return balance;
	}

	string to_string() {
		stringstream t;
		t << "                        | " << left << setw(10) << setfill(' ') << transaction_type
			<< " | " << setw(10) << setfill(' ') << date.to_string()
			<< " | " << right << setw(12) << fixed << setprecision(3) << setfill(' ') << amount
			<< " | " << right << setw(13) << fixed << setprecision(3) << setfill(' ') << balance << " |" << endl;
		return t.str();
	}
};

class Customer {
    private:
		string name, address,customer_type, telephone_number;
		int age, customer_number;

	public:
		Customer(string& name_, string& address_, string& customer_type_ ,int& age_, string& telephone_number_, int& customer_number_) {
			name = name_;
			address = address_;
			customer_type = customer_type_; 
			age = age_;
			telephone_number = telephone_number_;
			customer_number = customer_number_;
		}

		virtual double get_savings_interest() = 0;
		virtual double get_checking_interest() = 0;
		virtual double get_checking_charges() = 0;
		virtual int get_overdraft_penalty() = 0;

		void set_customer_type(string& customer_type) {
			this->customer_type = customer_type;
		}

		string get_name() {
			return name;
		}
		string get_address() {
			return address;
		}
		string get_customer_type() {
			return customer_type;
		}
		int get_age() {
			return age;
		}
		string get_telephone_number() {
			return telephone_number;
		}
		int get_customer_number() {
			return customer_number;
		}
};

class Senior :public Customer {
public:
	Senior(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_) : Customer(name_, address_, customer_type_, age_, telephone_number_, customer_number_) {};
	const double SAVINGS_INTEREST = 4;
	const double CHECK_INTEREST = 1;
	const double CHECK_CHARGE = 1;
	const int OVERDRAFT_PENALTY = 25;

	double get_savings_interest() { return SAVINGS_INTEREST; }
	double get_checking_interest() { return CHECK_INTEREST; }
	double get_checking_charges() { return CHECK_CHARGE; }
	int get_overdraft_penalty() { return OVERDRAFT_PENALTY; }
};

class Adult : public Customer {
public:
	Adult(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_) : Customer(name_, address_, customer_type_, age_, telephone_number_, customer_number_) {};
	const double SAVINGS_INTEREST = 3;
	const double CHECK_INTEREST = 1;
	const double CHECK_CHARGE = 3;
	const int OVERDRAFT_PENALTY = 25;

	double get_savings_interest() { return SAVINGS_INTEREST; }
	double get_checking_interest() { return CHECK_INTEREST; }
	double get_checking_charges() { return CHECK_CHARGE; }
	int get_overdraft_penalty() { return OVERDRAFT_PENALTY; }
};

class Student :public Customer {
public:
	Student(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_) : Customer(name_, address_, customer_type_, age_, telephone_number_, customer_number_) {};
	const double SAVINGS_INTEREST = 4;
	const double CHECK_INTEREST = 1;
	const double CHECK_CHARGE = 2;
	const int OVERDRAFT_PENALTY = 25;

	double get_savings_interest() { return SAVINGS_INTEREST; }
	double get_checking_interest() { return CHECK_INTEREST; }
	double get_checking_charges() { return CHECK_CHARGE; }
	int get_overdraft_penalty() { return OVERDRAFT_PENALTY; }
};

class Account {
private:
	double balance;
	Customer *customer;
	string account_type;
	vector<Transaction*> transactions;
	int transac_count;
	int account_number;
	


public:
	Account(int &acc_num,string &acc_type) {
		balance = 0.0;
		account_number = acc_num;
		account_type = acc_type;
		transac_count = 0;
	}

	string get_account_type() {
		return account_type;
	}

	void set_balance(double& bal) {
		balance = bal;
	}


	int get_account_number() {
		return account_number;
	}

	double get_balance() {
		return balance;
	}

	void set_customer(Customer *customer_) {
		customer = customer_;
	}

	virtual void add_interest()= 0;
	virtual double deposit(double amt, Date date) = 0;
	virtual double withdrawal(double amt, Date date) = 0;

	Customer* get_customer() {
		return customer;
	}

	void add_transaction(Transaction *transaction) {
		transactions.push_back(transaction);
	}

	vector<Transaction*> get_transactions() {
		return transactions;
	}

	void printTransaction(Transaction *tr) {
		
	}

};

class Savings_Account :public Account {
private:
    Date l_date;
	double balance;
	Transaction* l_trans_date;

public:
	Savings_Account(int& acc_num, string& acc_type) : Account(acc_num, acc_type) {
		balance = 0;
		l_trans_date = nullptr;
	}


	double deposit(double amt, Date date) {

		if (!get_transactions().empty()) { 
			l_trans_date = get_transactions().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Past or future dates are not allowed." << endl;
				return -1;
			}
		}
		balance = get_balance();
		balance += amt;
		set_balance(balance);
		add_transaction(new Transaction("DEP", amt, balance, date));
		return balance;
	}
    
	void add_interest() {
		time_t now = time(0);
		Date date(now);

		l_trans_date = get_transactions().back();
		l_date = l_trans_date->get_date();
		long days = date - l_date;
		double interest_amt = (l_trans_date->get_balance() * get_customer()->get_savings_interest() * days) / (100 * 365);
		balance = get_balance();
		balance += interest_amt;
		set_balance(balance);
		add_transaction(new Transaction("INT CR", interest_amt, balance, date));
	}


	double withdrawal(double amt,Date date) {
		balance = get_balance();
		if (!get_transactions().empty()) {
			l_trans_date = get_transactions().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Past or future dates are not allowed." << endl;
				return -1;
			}
		}
		if (balance < amt) {
			balance = balance - amt;
			add_transaction(new Transaction("WD", amt, balance, date));

			double overdraft_penalty = (double)get_customer()->get_overdraft_penalty();
			balance = balance - overdraft_penalty;
			add_transaction(new Transaction("ODC", overdraft_penalty, balance, date));
			set_balance(balance);
			return balance;
        }
	    else {
	        balance  = balance - amt;
			set_balance(balance);
			add_transaction(new Transaction("WD", amt, balance, date));

			return balance;
	    }
	}
};

class Checking_Account :public Account {
private:

	Date l_date;
	double balance;
	Transaction* l_trans_date;
	

public:
	Checking_Account( int& acc_num, string& acc_type) : Account( acc_num, acc_type) {
		balance = 0;
		l_trans_date = nullptr;
		/*interest_rate = get_customer()->get_checking_interest();
		chk_chg_rate = get_customer()->get_checking_charges();*/
	}


	double deposit(double amt, Date date) {
		if (!get_transactions().empty()) {
			l_trans_date = get_transactions().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Past or future dates are not allowed." << endl;
				return -1;
			}
		}
		balance = get_balance();
		balance += amt;
		set_balance(balance);
		add_transaction(new Transaction("DEP", amt, balance, date));
		return balance;
	}

	void add_interest() {
		time_t now = time(0);
		Date date(now);
		
		l_trans_date = get_transactions().back();
		l_date = l_trans_date->get_date();
		long days = date - l_date;
		double interest_amt = (l_trans_date->get_balance() * get_customer()->get_checking_interest() * days) / (100 * 365);
		balance = get_balance();
		balance += interest_amt;
		set_balance(balance);
		add_transaction(new Transaction("INT CR", interest_amt, balance, date));
	}

	double withdrawal(double amt, Date date) {
		balance = get_balance();
		if (!get_transactions().empty()) {
			l_trans_date = get_transactions().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Past or future dates are not allowed." << endl;
				return -1;
			}
		}
		if (balance < amt) {
			balance = balance - amt;
			add_transaction(new Transaction("WD", amt, balance, date));

			double overdraft_penalty = (double)get_customer()->get_overdraft_penalty();
			balance = balance - overdraft_penalty;
			add_transaction(new Transaction("ODC", overdraft_penalty, balance, date));
			set_balance(balance);
			return balance;
		}
		else {
			balance = balance - amt;
			set_balance(balance);
			add_transaction(new Transaction("WD", amt, balance, date));

			return balance;
		}
	}
};

class Bank {
private:
	vector<Account*> accounts;
	int customerNumber;
	Customer* customer;
	int day, month, year;
	int accountNumber;

public:
	Bank() 
	{   
		accountNumber = -1;
		customerNumber = -1;
		day = 0;
		month = 0;
		year = 0;
		customer = nullptr;
		
	}

	int add_account(string& name, string& address, string& telephoneNumber, int& age, int& accType, int& custType) {

		Account* newAccount = nullptr;
		string customerType, accountType;
		customerNumber++;
		accountNumber++;
		if (custType == 0) {
			customerType = "Senior";
			customer = new Senior(name, address, customerType, age, telephoneNumber, customerNumber);
		}
		else if (custType == 1) {
			customerType = "Adult";
			customer = new Adult(name, address, customerType, age, telephoneNumber, customerNumber);
		}
		else if (custType == 2) {
			customerType = "Student";
			customer = new Student(name, address, customerType, age, telephoneNumber, customerNumber);
		}

		if (accType == 1) {
			accountType = "Savings";
			newAccount = new Savings_Account(accountNumber,accountType);
		}
		else if (accType == 0) {
			accountType = "Checking";
			newAccount = new Checking_Account(accountNumber, accountType);
		}

		if (newAccount != nullptr) {
			newAccount->set_customer(customer);
			accounts.push_back(newAccount);
			return accountNumber;
		}
	}


	void make_withdrawal(int& accountNumber, double& amt, string &dt) {
		month = stoi(dt.substr(5, 2));
		day = stoi(dt.substr(8, 2));
		year = stoi(dt.substr(0, 4));
		Date date(day, month, year);
		if (accountNumber >= 0 and accountNumber <= (int)accounts.size() - 1) {
			double balance = accounts[accountNumber]->withdrawal(amt, date);
			if (balance != -1)
			{
				accounts[accountNumber]->add_interest();
				cout << "Withdrawal in " << accountNumber << " Account: $" << amt << " on " + date.to_string() + " | New balance: $" << balance << "\n";
			}
		}
		else {
			cout << "Account not found ! Please try entering a valid account number." << endl;
			return;
		}
	}

	Account* get_account(int& accountNumber) {
		if (accountNumber >= 0 and accountNumber <= (int)accounts.size() - 1) {
			time_t now = time(0);
			Date date(now);
			double chk_chg = (accounts[accountNumber]->get_customer()->get_checking_charges()) / 100.0;
			double balance = accounts[accountNumber]->get_balance();
			balance -= chk_chg;
			accounts[accountNumber]->set_balance(balance);
			accounts[accountNumber]->add_transaction(new Transaction("CHK CHG", chk_chg, balance, date));

			return accounts[accountNumber];
		}
		else {
			cout << "Account not found ! Please try entering a valid account number." << endl;
			return nullptr;
		}
	}

	void make_deposit(int &accountNumber, double &amt,string &dt) {
		month = stoi(dt.substr(5, 2));
		day = stoi(dt.substr(8, 2));
		year = stoi(dt.substr(0, 4));
		Date date(day,month,year);
		if (accountNumber >= 0 and accountNumber <= (int)accounts.size() - 1) {
			double balance = accounts[accountNumber]->deposit(amt, date);
			if (balance != -1) {
				accounts[accountNumber]->add_interest();
				cout << "Deposit in " << accountNumber << " Account: $" << amt << " on " + date.to_string() + " | New balance: $" << balance << "\n";
			}
		}
		else {
			cout << "Account not found ! Please try entering a valid account number." << endl;
			return;
		}
	}

};

class Application {
private:
    Account* account;
	Customer* customer;
	int choice,customerType,accountType,accountNumber;
	int age;
	Bank * bank;
	vector<Transaction*> transactions;
	string name, address,date, telephoneNumber;
	double amount;
	
	

public:
	Application() 
	{
		accountNumber = -1;
		choice = -1;
		customerType = -1;
		accountType = -1;
		amount = 0.0;
		bank = new Bank();
		account = nullptr;
		customer = nullptr;
		age = 0;
		telephoneNumber = "";
		
		
	}
	void run() {
		while (true) {
			cout << "Kindly select an option from below :\n0 : Add Account\n1 : Make Deposit\n2 : Make Withdrawal\n3 : Check Account\n4 : Exit" << endl;
			cin >> choice;
			switch (choice)
			{
			case 0:
				cout << "Enter Customer Name : ";
				cin >> name;
				cout << "Enter Customer Address : ";
				cin >> address;
				cout << "Enter Customer Age : ";
				cin >> age;
				cout << "Enter Customer Phone Number : ";
				cin >> telephoneNumber;
				getCustType:
				cout << "Select :\n0 : Senior\n1 : Adult\n2 : Student\n";
				cin >> customerType;
				if (customerType > 2 or customerType < 0) {
					cout << "Kindly choose Customer type from given choices only" << endl;
					goto getCustType;
				}
			getAccType:
				cout << "Select :\n0 : Checking\n1 : Savings\n";
				cin >> accountType;
				if (accountType < 0 or accountType > 1) {
					cout << "Kindly choose Account type from given choices only" << endl;
					goto getAccType;
				}
				cout << "Account Number : " << bank->add_account(name, address, telephoneNumber, age, accountType, customerType) << " Added" << endl;
				break;
			case 1:
				cout << "Enter Account Number : ";
				cin >> accountNumber;
				cout << "Enter the Amount : ";
				cin >> amount;
				cout << "Enter the Date [yyyy-mm-dd] : ";
				cin >> date;
				bank->make_deposit(accountNumber, amount, date);
				break;
			case 2:
				cout << "Enter Account Number : ";
				cin >> accountNumber;
				cout << "Enter the Amount : ";
				cin >> amount;
				cout << "Enter the Date [yyyy-mm-dd] : ";
				cin >> date;
				bank->make_withdrawal(accountNumber, amount, date);
				break;
			case 3:
				cout << "Enter Account Number : ";
				cin >> accountNumber;
				account = bank->get_account(accountNumber);
				if (account != nullptr) {
					customer = account->get_customer();
					transactions = account->get_transactions();
					cout << "Account : " << to_string(account->get_account_number()) << endl;
					cout << "Owner : " << customer->get_name() << endl;
					cout << "Type of customer : " << customer->get_customer_type() << endl;
					cout << "Balance : " << fixed << setprecision(3) << account->get_balance() << endl;
					if (!transactions.empty()) {
						cout << "                        ----------------------------------------------------------" << endl;
						cout << "                        |    Type    |    Date    |    Amount    |    Balance    |" << endl;
						for (Transaction* tr : transactions) {
							cout << "                        |------------|------------|--------------|---------------|" << endl;
							cout << tr->to_string();
						}
						cout << "                        ----------------------------------------------------------" << endl;
					}
					else {
						cout << "                        " << "NO TRANSACTIONS FOUND !" << endl;
					}
				}
				break;
			case 4:
				return;
				break;
			default:
				cout << "Incorrect option selected ! Kindly choose from 0 to 4." << endl;
				break;
			}
		}
	}
};

int main() {
	Application* app = new Application();
	app->run();
}