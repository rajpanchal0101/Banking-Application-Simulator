/**
1) Module Name: a3_header.h
2) Author: Raj Panchal (rjp659@uregina.ca)
3) Date of creation: 2023-10-22
4) Purpose:This is a header file which consists of all the required libraries, global variables and function's declaration of various classes.
*/
# pragma once  
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "Date.h"  //! Importing "Date.h" file for date related operation
 
using namespace std;

//! Defining the Transaction class for managing banking transactions.
class Transaction
{
private:

	Date date;
	double amount, balance;
	string tran_type;
	

public:
    /**
	1) Purpose: Constructor to initialize a transaction
	2) Parameters: type(string), amt(double), dt(Date)
	3) Return type: None
	4) Side Effect: None
	*/
	Transaction(string type, double& amt, double& bal, Date& dt);
	
    /**
	1) Purpose: It signifies transaction type.
	2) Parameters: None
	3) Return type: string
	4) Side Effect: None
	*/
	string get_tran_type();
	
	/**
	1) Purpose: Default constructor for a transaction..
	2) Parameters: None
	3) Return type: None
	4) Side Effect: None
	*/
	Transaction();
    
	/**
	1) Purpose: gets and returns the date from the user for a transaction.
	2) Parameters: None
	3) Return type: Date
	4) Side Effect: None
	*/
	Date get_date();

    /**
	1) Purpose: gets and returns the amount from the user for a transaction.
	2) Parameters: None
	3) Return type: double
	4) Side Effect: None
	*/
	double get_amount();
    
	/**
	1) Purpose: gets and returns the balance from the user for a transaction.
	2) Parameters: None
	3) Return type: double
	4) Side Effect: None
	*/
	double get_balance();
    
	/**
	1) Purpose: converts the data into string.
	2) Parameters: None
	3) Return type: string
	4) Side Effect: None
	*/
	string to_string();
};

//! Defining the Customer class as a base class for different customer types.
class Customer
{
    private:

		string name, address,customer_type, telephone_number;
		int age, customer_number;

	public:

	    /**
		1) Purpose: Constructor to create a customer with relevant information.
		2) Parameters: name_(string), address_(string), customer_type_(string), age(int), telephone_number_(string), customer_number_(int)
		3) Return type: None
		4) Side Effect: None
		*/
		Customer(string& name_, string& address_, string& customer_type_ ,int& age_, string& telephone_number_, int& customer_number_);
        
		/**
		1) Purpose: Virtual function to be implemented by derived classes for getting savings interest.
		2) Parameters: None
		3) Return type: double
		4) Side Effect: None
		*/
		virtual double get_sav_int() = 0;

		/**
		1) Purpose: Virtual function to be implemented by derived classes for getting checking interest.
		2) Parameters: None
		3) Return type: double
		4) Side Effect: None
		*/
		virtual double get_chec_int() = 0;

		/**
		1) Purpose: Virtual function to be implemented by derived classes for getting checking charge.
		2) Parameters: None
		3) Return type: double
		4) Side Effect: None
		*/
		virtual double get_chec_chrg() = 0;

		/**
		1) Purpose: Virtual function to be implemented by derived classes for getting overdraft penalty.
		2) Parameters: None
		3) Return type: int
		4) Side Effect: None
		*/
		virtual int get_od_plty() = 0;
        

	    /**
		1) Purpose: Sets customer type.
		2) Parameters: customer_type(string)
		3) Return type: void
		4) Side Effect: None
		*/
		void set_customer_type(string& customer_type);
        
		/**
		1) Purpose: Gets customer name.
		2) Parameters: None
		3) Return type: string
		4) Side Effect: None
		*/
		string get_name();
        
		/**
		1) Purpose: Gets customer address.
		2) Parameters: None
		3) Return type: string
		4) Side Effect: None
		*/
		string get_address();
        
		/**
		1) Purpose: Gets customer type.
		2) Parameters: None
		3) Return type: string
		4) Side Effect: None
		*/
		string get_customer_type();
        
		/**
		1) Purpose: Gets customer age.
		2) Parameters: None
		3) Return type: int
		4) Side Effect: None
		*/
		int get_age();
        
		/**
		1) Purpose: Gets customer telephone number in string format.
		2) Parameters: None
		3) Return type: string
		4) Side Effect: None
		*/
		string get_telephone_number();
        
		/**
		1) Purpose: Gets customer number.
		2) Parameters: None
		3) Return type: int
		4) Side Effect: None
		*/
		int get_customer_number();
};


//! Defining a derived class for Senior customers.
class Senior :public Customer
{
public:

    /**
	1) Purpose: Constructor to create a customer of type senior with relevant information.
	2) Parameters: name_(string), address_(string), customer_type_(string), age(int), telephone_number_(string), customer_number_(int)
	3) Return type: None
	4) Side Effect: None
	*/
	Senior(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_);
	
	const double SAVINGS_INTEREST = 4; //! setting savings interest rate
	const double CHECK_INTEREST = 1;   //! setting checking interest rate
	const double CHECK_CHARGE = 1;     //! setting checking charge
	const int OVERDRAFT_PENALTY = 25;  //! setting overdraft penalty
    
	/**
	1) Purpose: function for getting savings interest.
	2) Parameters: None
	3) Return type: double
	4) Side Effect: None
	*/
	double get_sav_int();

	/**
	1) Purpose: function for getting checking interest.
	2) Parameters: None
	3) Return type: double
	4) Side Effect: None
	*/
	double get_chec_int();

	/**
	1) Purpose: function for getting checking charge.
	2) Parameters: None
	3) Return type: double
	4) Side Effect: None
	*/
	double get_chec_chrg();

	/**
	1) Purpose: function for getting overdraft penalty.
	2) Parameters: None
	3) Return type: int
	4) Side Effect: None
	*/
	int get_od_plty();
};



class Adult : public Customer 
{

public:
    
	/**
	1) Purpose: Constructor to create a customer of type Adult with relevant information.
	2) Parameters: name_(string), address_(string), customer_type_(string), age(int), telephone_number_(string), customer_number_(int)
	3) Return type: None
	4) Side Effect: None
	*/
	Adult(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_);

	const double SAVINGS_INTEREST = 3; //! setting savings interest rate
	const double CHECK_INTEREST = 1;   //! setting checking interest rate
	const double CHECK_CHARGE = 3;     //! setting checking charge
	const int OVERDRAFT_PENALTY = 25;  //! setting overdraft penalty
    
	/**
	1) Purpose: function for getting savings interest.
	2) Parameters: None
	3) Return type: double
	4) Side Effect: None
	*/
	double get_sav_int();

	/**
	1) Purpose: function for getting checking interest.
	2) Parameters: None
	3) Return type: double
	4) Side Effect: None
	*/
	double get_chec_int();

	/**
	1) Purpose: function for getting checking charge.
	2) Parameters: None
	3) Return type: double
	4) Side Effect: None
	*/
	double get_chec_chrg();

	/**
	1) Purpose: function for getting overdraft penalty.
	2) Parameters: None
	3) Return type: int
	4) Side Effect: None
	*/
	int get_od_plty();
};

class Student :public Customer 
{

public:

    /**
	1) Purpose: Constructor to create a customer of type Student with relevant information.
	2) Parameters: name_(string), address_(string), customer_type_(string), age(int), telephone_number_(string), customer_number_(int)
	3) Return type: None
	4) Side Effect: None
	*/
	Student(string& name_, string& address_, string& customer_type_, int& age_, string& telephone_number_, int& customer_number_);

	const double SAVINGS_INTEREST = 4;  //! setting savings interest rate
	const double CHECK_INTEREST = 1;    //! setting checking interest rate
	const double CHECK_CHARGE = 2;      //! setting checking charge
	const int OVERDRAFT_PENALTY = 25;   //! setting overdraft penalty

	double get_sav_int();
	double get_chec_int();
	double get_chec_chrg();
	int get_od_plty();
};

class Account {
private:

	double balance;
	Customer *customer;
	string account_type;
	vector<Transaction*> trans;
	int transac_count;
	int account_number;
	


public:
	Account(int &acc_num,string &acc_type);

	string get_account_type();


	void set_balance(double& bal);


	int get_account_number();

	double get_balance();

	void set_customer(Customer *customer_);

	virtual void add_interest()= 0;
	virtual double deposit(double amt, Date date) = 0;
	virtual double withdrawal(double amt, Date date) = 0;

	Customer* get_customer();

	void add_trans(Transaction *tran);

	vector<Transaction*> get_trans();

	string to_string() const;

};

class Savings_Account :public Account {
private:
    Date l_date;
	double balance;
	Transaction* l_trans_date;

public:
	Savings_Account(int& acc_num, string& acc_type);

	double deposit(double amt, Date date);
    
	void add_interest();


	double withdrawal(double amt,Date date);
};

class Checking_Account :public Account {
private:

	Date l_date;
	double balance;
	Transaction* l_trans_date;
	

public:
	Checking_Account( int& acc_num, string& acc_type);


	double deposit(double amt, Date date);

	void add_interest();

	double withdrawal(double amt, Date date);
};

class Bank {
private:
	vector<Account*> accounts;
	int customerNumber;
	Customer* customer;
	int day, month, year;
	int accountNumber;

public:
	Bank();

	int add_account(string& name, string& address, string& telephoneNumber, int& age, int& accType, int& custType);


	void make_withdrawal(int& accountNumber, double& amt, string &dt);

	Account* get_account(int& accountNumber);

	void make_deposit(int &accountNumber, double &amt,string &dt);

};

class Application 
{
private:
    Account* account;
	Customer* customer;
	int choice,cust_type,accountType,accountNumber;
	int age;
	Bank * bank;
	vector<Transaction*> trans;
	string name, address,date, telephoneNumber;
	double amount;
	
	

public:
	Application();

	void action();
};