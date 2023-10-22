#include "a3_header.h"


Transaction::Transaction(string type, double& amt, double& bal, Date& dt) 
{
		tran_type = type;
		amount = amt;
		balance = bal;
		date = dt;
}

string Transaction::get_tran_type() 
{
		return tran_type;
}
	
Transaction::Transaction() 
{
		tran_type = "";
		amount = 0.0;
		balance = 0.0;
}


Date Transaction::get_date() 
{
		return date;
}


double Transaction::get_amount()
 {
		return amount;
 }

double Transaction::get_balance() 
{
		return balance;
}

string Transaction::to_string() 
{
		stringstream t;
		t << "                        | " << left << setw(10) << setfill(' ') << tran_type
			<< " | " << setw(10) << setfill(' ') << date.to_string()
			<< " | " << right << setw(12) << fixed << setprecision(3) << setfill(' ') << amount
			<< " | " << right << setw(13) << fixed << setprecision(3) << setfill(' ') << balance << " |" << endl;
		return t.str();
}


Customer::Customer(string& name_, string& address_, string& customer_type_ ,int& age_, string& telephone_number_, int& customer_number_) 
{
			name = name_;
			address = address_;
			customer_type = customer_type_; 
			age = age_;
			telephone_number = telephone_number_;
			customer_number = customer_number_;
}

	

void Customer::set_customer_type(string& customer_type)
{
			this->customer_type = customer_type;
}

string Customer::get_name()
{
			return name;
}
string Customer::get_address()
{
			return address;
}
string Customer::get_customer_type()
{
			return customer_type;
}
int Customer::get_age()
{
			return age;
}
string Customer::get_telephone_number() 
{
			return telephone_number;
}
int Customer::get_customer_number()
{
			return customer_number;
}


Senior::Senior(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_) : Customer(name_, address_, customer_type_, age_, telephone_number_, customer_number_)
 {}
	

double Senior::get_sav_int()
 { return SAVINGS_INTEREST; }
double Senior::get_chec_int() 
{ return CHECK_INTEREST; }
double Senior::get_chec_chrg() 
{ return CHECK_CHARGE; }
int Senior::get_od_plty() 
{ return OVERDRAFT_PENALTY; }


Adult::Adult(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_) : Customer(name_, address_, customer_type_, age_, telephone_number_, customer_number_) 
{}
	

double Adult::get_sav_int() 
{ return SAVINGS_INTEREST; }
double Adult::get_chec_int()
 { return CHECK_INTEREST; }
double Adult::get_chec_chrg() 
{ return CHECK_CHARGE; }
int Adult::get_od_plty()
 { return OVERDRAFT_PENALTY; }


Student::Student(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_) : Customer(name_, address_, customer_type_, age_, telephone_number_, customer_number_) 
{}


double Student::get_sav_int() 
{ return SAVINGS_INTEREST; }
double Student::get_chec_int()
 { return CHECK_INTEREST; }
double Student::get_chec_chrg() 
{ return CHECK_CHARGE; }
int Student::get_od_plty()
 { return OVERDRAFT_PENALTY; }


Account::Account(int &acc_num,string &acc_type) {
		balance = 0.0;
		account_number = acc_num;
		account_type = acc_type;
		transac_count = 0;
	}

string Account::get_account_type() {
		return account_type;
	}

void Account::set_balance(double& bal) {
		balance = bal;
	}


int Account::get_account_number() {
		return account_number;
	}

double Account::get_balance() {
		return balance;
	}

void Account::set_customer(Customer *customer_) {
		customer = customer_;
	}



Customer* Account::get_customer() {
		return customer;
	}

void Account::add_trans(Transaction *tran) {
		trans.push_back(tran);
	}

vector<Transaction*> Account::get_trans() {
		return trans;
	}

string Account::to_string() const
	{   stringstream str;
        str << "Account : " << account_number << endl
		 << "Owner : " << customer->get_name() << endl
		 << "Type of customer : " << customer->get_customer_type() << endl
		 << "Balance : " << fixed << setprecision(3) << balance << endl;

		 return str.str();
	}



Savings_Account::Savings_Account(int& acc_num, string& acc_type) : Account(acc_num, acc_type) 
{
		balance = 0;
		l_trans_date = nullptr;
}


double Savings_Account::deposit(double amt, Date date) 
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


double Savings_Account::withdrawal(double amt,Date date) 
{
		balance = get_balance();
		if (!get_trans().empty()) {
			l_trans_date = get_trans().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Past or future dates are not allowed." << endl;
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


Checking_Account::Checking_Account( int& acc_num, string& acc_type) : Account( acc_num, acc_type)
{
		balance = 0;
		l_trans_date = nullptr;
		/*interest_rate = get_customer()->get_chec_int();
		chk_chg_rate = get_customer()->get_chec_chrg();*/
}


double Checking_Account::deposit(double amt, Date date) 
{
		if (!get_trans().empty()) {
			l_trans_date = get_trans().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Past or future dates are not allowed." << endl;
				return -1;
			}
		}
		balance = get_balance();
		balance += amt;
		set_balance(balance);
		add_trans(new Transaction("DEP", amt, balance, date));
		return balance;
}

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

double Checking_Account::withdrawal(double amt, Date date) 
{
		balance = get_balance();
		if (!get_trans().empty()) {
			l_trans_date = get_trans().back();
			l_date = l_trans_date->get_date();
			if (date < l_date or date > l_date) {
				cout << "Past or future dates are not allowed." << endl;
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


Bank::Bank() 
{   
		accountNumber = -1;
		customerNumber = -1;
		day = 0;
		month = 0;
		year = 0;
		customer = nullptr;
		
}

int Bank::add_account(string& name, string& address, string& telephoneNumber, int& age, int& accType, int& custType)
{

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


void Bank::make_withdrawal(int& accountNumber, double& amt, string &dt) 
{
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

Account* Bank::get_account(int& accountNumber) 
{
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

void Bank::make_deposit(int &accountNumber, double &amt,string &dt) 
{
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



Application::Application() 
{
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
