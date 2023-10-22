/**
1) Module Name: a3_class_methods.cpp
2) Author: Raj Panchal (rjp659@uregina.ca)
3) Date of creation: 2023-10-22
4) Purpose:This is the file which consists of implementation of the various functions declared in the header file inside different classes.
*/
#include "a3_header.h"
  
//! Initialize transaction data
Transaction::Transaction(string type, double& amt, double& bal, Date& dt) 
{
		tran_type = type;
		amount = amt;
		balance = bal;
		date = dt;
}

//! Get the transaction type
string Transaction::get_tran_type() 
{
		return tran_type;
}

//! Default constructor for Transaction class	
Transaction::Transaction() 
{       //! Initialize properties with default values
		tran_type = "";
		amount = 0.0;
		balance = 0.0;
}

//! Get the date of the transaction
Date Transaction::get_date() 
{
		return date;
}

//! Get the transaction amount
double Transaction::get_amount()
 {
		return amount;
 }

//! Get the account balance after the transaction
double Transaction::get_balance() 
{
		return balance;
}

//! Convert Transaction object to a formatted string
string Transaction::to_string() 
{
		stringstream t;
		t << "                        | " << left << setw(10) << setfill(' ') << tran_type
			<< " | " << setw(10) << setfill(' ') << date.to_string()
			<< " | " << right << setw(12) << fixed << setprecision(3) << setfill(' ') << amount
			<< " | " << right << setw(13) << fixed << setprecision(3) << setfill(' ') << balance << " |" << endl;
		return t.str();
}

//! Customer class constructor
Customer::Customer(string& name_, string& address_, string& customer_type_ ,int& age_, string& telephone_number_, int& customer_number_) 
{
	        //! Initialize customer properties
			name = name_;
			address = address_;
			customer_type = customer_type_; 
			age = age_;
			telephone_number = telephone_number_;
			customer_number = customer_number_;
}

	
//! Set the customer type
void Customer::set_customer_type(string& customer_type)
{
			this->customer_type = customer_type;
}

//! Get the customer's name
string Customer::get_name()
{
			return name;
}

//! Get the customer's address
string Customer::get_address()
{
			return address;
}

//! Get the customer's type
string Customer::get_customer_type()
{
			return customer_type;
}

//! Get the customer's age
int Customer::get_age()
{
			return age;
}

//! Get the customer's telephone number
string Customer::get_telephone_number() 
{
			return telephone_number;
}

//! Get the customer number
int Customer::get_customer_number()
{
			return customer_number;
}

//! Senior class constructor
Senior::Senior(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_) : Customer(name_, address_, customer_type_, age_, telephone_number_, customer_number_)
 {}
	
//! Get the savings account interest for senior customers
double Senior::get_sav_int()
 { return SAVINGS_INTEREST; }

 //! Get the checking account interest for senior customers
double Senior::get_chec_int() 
{ return CHECK_INTEREST; }

//! Get the checking account charges for senior customers
double Senior::get_chec_chrg() 
{ return CHECK_CHARGE; }

//! Get the overdraft penalty for senior customers
int Senior::get_od_plty() 
{ return OVERDRAFT_PENALTY; }


//! Adult class constructor
Adult::Adult(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_) : Customer(name_, address_, customer_type_, age_, telephone_number_, customer_number_) 
{}
	
//! Get the savings account interest for adult customers
double Adult::get_sav_int() 
{ return SAVINGS_INTEREST; }

//! Get the checking account interest for adult customers
double Adult::get_chec_int()
 { return CHECK_INTEREST; }

 //! Get the checking account charges for adult customers
double Adult::get_chec_chrg() 
{ return CHECK_CHARGE; }

//! Get the overdraft penalty for adult customers
int Adult::get_od_plty()
 { return OVERDRAFT_PENALTY; }

//! Student class constructor
Student::Student(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_) : Customer(name_, address_, customer_type_, age_, telephone_number_, customer_number_) 
{}

//! Get the savings account interest for student customers
double Student::get_sav_int() 
{ return SAVINGS_INTEREST; }

//! Get the checking account interest for student customers
double Student::get_chec_int()
 { return CHECK_INTEREST; }

//! Get the checking account charges for student customers
double Student::get_chec_chrg() 
{ return CHECK_CHARGE; }

//! Get the overdraft penalty for student customers
int Student::get_od_plty()
 { return OVERDRAFT_PENALTY; }

//! Account class constructor
Account::Account(int &acc_num,string &acc_type)
{
	    //! Initialize account properties
		balance = 0.0;
		account_number = acc_num;
		account_type = acc_type;
		transac_count = 0;
}

//! Get the account type
string Account::get_account_type()
{
		return account_type;
}

//! Set the balance for the account
void Account::set_balance(double& bal) 
{
		balance = bal;
}

//! Get the account number
int Account::get_account_number() 
{
		return account_number;
}

//! Get the account balance
double Account::get_balance()
{
		return balance;
}

//! Set the customer associated with the account
void Account::set_customer(Customer *customer_) 
{
		customer = customer_;
}


//! Get the customer associated with the account
Customer* Account::get_customer()
{
		return customer;
}

//! Add a transaction to the account
void Account::add_trans(Transaction *tran) 
{
		trans.push_back(tran);
}

//! Get the list of transactions for the account
vector<Transaction*> Account::get_trans() 
{
		return trans;
}

//! Convert Account object to a formatted string
string Account::to_string() const
{       stringstream str;
        str << "Account : " << account_number << endl
		 << "Owner : " << customer->get_name() << endl
		 << "Type of customer : " << customer->get_customer_type() << endl
		 << "Balance : " << fixed << setprecision(3) << balance << endl;

		 return str.str();
}


//! Savings_Account class constructor
Savings_Account::Savings_Account(int& acc_num, string& acc_type) : Account(acc_num, acc_type) 
{       
	    //! Initialize savings account properties
		balance = 0;
		l_trans_date = nullptr;
}

//! Deposit money into a savings account
double Savings_Account::deposit(double amt, Date date) 
{
        //! Checks if the transaction date is valid
		if (!get_trans().empty()) { 
			l_trans_date = get_trans().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Dates in past or future are not accepted. Try again after entering a valid date." << endl;
				return -1;
			}
		}
		balance = get_balance();
		balance += amt;
		set_balance(balance);
		add_trans(new Transaction("DEP", amt, balance, date));
		return balance;
}
    
//! Add interest to the savings account
void Savings_Account::add_interest()
 {
		time_t now = time(0);
		Date date(now);

		l_trans_date = get_trans().back();
		l_date = l_trans_date->get_date();
		long days = date - l_date;
		double interest_amt = (l_trans_date->get_balance() * get_customer()->get_sav_int() * days) / (100 * 365);
		balance = get_balance();
		balance += interest_amt;
		set_balance(balance);
		add_trans(new Transaction("INT CR", interest_amt, balance, date));
}

//! Withdraw money from a savings account
double Savings_Account::withdrawal(double amt,Date date) 
{
		balance = get_balance();
		if (!get_trans().empty()) {
			l_trans_date = get_trans().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Dates in past or future are not accepted. Try again after entering a valid date." << endl;
				return -1;
			}
		}
		if (balance < amt) {
			balance = balance - amt;
			add_trans(new Transaction("WD", amt, balance, date));

			double overdraft_penalty = (double)get_customer()->get_od_plty();
			balance = balance - overdraft_penalty;
			add_trans(new Transaction("ODC", overdraft_penalty, balance, date));
			set_balance(balance);
			return balance;
        }
	    else {
	        balance  = balance - amt;
			set_balance(balance);
			add_trans(new Transaction("WD", amt, balance, date));

			return balance;
	    }
}


//! Checking_Account class constructor
Checking_Account::Checking_Account( int& acc_num, string& acc_type) : Account( acc_num, acc_type)
{       
	    //! Initialize checking account properties
		balance = 0;
		l_trans_date = nullptr;
		
}


//! Deposit money into a checking account
double Checking_Account::deposit(double amt, Date date) 
{
		if (!get_trans().empty()) {
			l_trans_date = get_trans().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Dates in past or future are not accepted. Try again after entering a valid date." << endl;
				return -1;
			}
		}
		balance = get_balance();
		balance += amt;
		set_balance(balance);
		add_trans(new Transaction("DEP", amt, balance, date));
		return balance;
}

//! Add interest to the checking account
void Checking_Account::add_interest()
{
		time_t now = time(0);
		Date date(now);
		
		l_trans_date = get_trans().back();
		l_date = l_trans_date->get_date();
		long days = date - l_date;
		double interest_amt = (l_trans_date->get_balance() * get_customer()->get_chec_int() * days) / (100 * 365);
		balance = get_balance();
		balance += interest_amt;
		set_balance(balance);
		add_trans(new Transaction("INT CR", interest_amt, balance, date));
}

//! Withdraw money from a checking account
double Checking_Account::withdrawal(double amt, Date date) 
{
		balance = get_balance();
		if (!get_trans().empty()) {
			l_trans_date = get_trans().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Dates in past or future are not accepted. Try again after entering a valid date." << endl;
				return -1;
			}
		}
		if (balance < amt) {
			balance = balance - amt;
			add_trans(new Transaction("WD", amt, balance, date));

			double overdraft_penalty = (double)get_customer()->get_od_plty();
			balance = balance - overdraft_penalty;
			add_trans(new Transaction("ODC", overdraft_penalty, balance, date));
			set_balance(balance);
			return balance;
		}
		else {
			balance = balance - amt;
			set_balance(balance);
			add_trans(new Transaction("WD", amt, balance, date));

			return balance;
		}
}

//! Bank class constructor
Bank::Bank() 
{       
	    //! Initialize bank properties
		accountNumber = -1;
		customerNumber = -1;
		day = 0;
		month = 0;
		year = 0;
		customer = nullptr;
		
}

//! Add a new customer account
int Bank::add_account(string& name, string& address, string& telephoneNumber, int& age, int& accType, int& custType)
{
        //! Create a new account based on customer and account type
		Account* newAccount = nullptr;
		string cust_type, accountType;
		customerNumber++;
		accountNumber++;
		if (custType == 0) {
			cust_type = "Senior";
			customer = new Senior(name, address, cust_type, age, telephoneNumber, customerNumber);
		}
		else if (custType == 1) {
			cust_type = "Adult";
			customer = new Adult(name, address, cust_type, age, telephoneNumber, customerNumber);
		}
		else if (custType == 2) {
			cust_type = "Student";
			customer = new Student(name, address, cust_type, age, telephoneNumber, customerNumber);
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

//! Make a withdrawal from a specific account
void Bank::make_withdrawal(int& accountNumber, double& amt, string &dt) 
{       
	    //! Parse the date and create a Date object
		month = stoi(dt.substr(5, 2));
		day = stoi(dt.substr(8, 2));
		year = stoi(dt.substr(0, 4));
		Date date(day, month, year);

		//! Check if the account number is valid
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

//! Gets an account based on user inputted account number
Account* Bank::get_account(int& accountNumber) 
{       
	    //! Checks if the account number is valid
		if (accountNumber >= 0 and accountNumber <= (int)accounts.size() - 1) {
			time_t now = time(0);
			Date date(now);
			double chk_chg = (accounts[accountNumber]->get_customer()->get_chec_chrg()) / 100.0;
			double balance = accounts[accountNumber]->get_balance();
			balance -= chk_chg;
			accounts[accountNumber]->set_balance(balance);
			accounts[accountNumber]->add_trans(new Transaction("CHK CHG", chk_chg, balance, date));

			return accounts[accountNumber];
		}
		else {
			cout << "Account not found ! Please try entering a valid account number." << endl;
			return nullptr;
		}
}


//! Make a deposit into a specific account
void Bank::make_deposit(int &accountNumber, double &amt,string &dt) 
{

	    //! Parse the date and create a Date object
		month = stoi(dt.substr(5, 2));
		day = stoi(dt.substr(8, 2));
		year = stoi(dt.substr(0, 4));
		Date date(day,month,year);

		//! Check if the account number is valid
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


//! Application class constructor
Application::Application() 
{
	    //! Initialize application properties
		accountNumber = -1;
		choice = -1;
		cust_type = -1;
		accountType = -1;
		amount = 0.0;
		bank = new Bank();
		account = nullptr;
		customer = nullptr;
		age = 0;
		telephoneNumber = "";
		
		
}

//! Runs the application
void Application::action() 
{
		while (true)
        {
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
				cin >> cust_type;
				if (cust_type > 2 or cust_type < 0) {
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
				cout << "Account Number : " << bank->add_account(name, address, telephoneNumber, age, accountType, cust_type) << " Added" << endl;
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
					trans = account->get_trans();
                    cout << account->to_string() ;
					if (!trans.empty()) {
						cout << "                        ----------------------------------------------------------" << endl;
						cout << "                        |    Type    |    Date    |    Amount    |    Balance    |" << endl;
						for (Transaction* tr : trans) {
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
