# CS700 - Assignment 3 - Banking Application Simulator

*Description - This assignment consists of building a simplified version of banking application for managing bank accounts and transactions. Below is the detailed description of  each and every file:

Files:

1. **a3_header.h** :
      - Description: It is the header file.
      - Functionality: This header file contains the declarations of various classes used in the application, such as `Transaction`, `Customer`, `Account`, `Savings_Account`, `Checking_Account`, and `Bank`. It is included in "a3_class_methods.cpp".

2. **a3_main.cpp** :
      - Description: It is the main program file.
      - Functionality: This is the main entry point of the application. It creates an instance of the `Application` class and starts the application.

3. **a3_class_methods.cpp** : 
      - Description: It is the implementation file.
      - Functionality: This file contains the implementation of the classes declared in `a3_header.h`. It includes member function definitions for these classes. It is included in the "a3_main.cpp".

4. **a3_executable.exe** : 
      - Description: Executable binary for "a3_main.cpp".

5. **a3_screenshot_console_output_using_terminal.JPG** : 
      - Description: Screenshot of console output and program execution using terminal.
     
6. **a3_screenshot_console_output_1.JPG** : 
      - Description: Screenshot of the console output consisting of the functionality of adding the account, making deposit, making withdrawal and checking the account and few validations as well for transaction dates.

7. **a3_screenshot_console_output_2.JPG** :
     - Description: Screenshot of the console output consisting of the functionality of adding the account, making deposit, making withdrawal and checking the account and few validations as well for transaction dates.

8. **a3_screenshot_IDE_integrated_version_control.JPG** : 
      - Description: Screenshot of IDE integrated version control simulation for the assignment  .

9. **a3_screenshot_terminal_git_commands_.JPG** : Screenshot of terminal with Git commands for this program.
       - Description: Screenshot of terminal with Git commands for adding, commiting and pushing various files of  assignment 3 to github.

10. **Date.h** :
      - Description: It is a file already included in the assignment for any date related operation.
      - Functionality: It has various functions for fetching current dates and for performing any date related operation. It is included in the "a3_header.h".


## Class Descriptions

- **Transaction**: Represents a bank transaction with details such as transaction type, amount, balance, and date.

- **Customer**: Represents a bank customer with details like name, address, age, customer type, telephone number, and customer number.

- **Account**: Base class for different types of bank accounts, such as savings and checking accounts. It includes functions for deposit, withdrawal, and calculating interest.

- **Savings_Account**: Derived from `Account`, represents a savings account.

- **Checking_Account**: Derived from `Account`, represents a checking account.

- **Bank**: Manages customer accounts and provides methods for adding accounts, making deposits, and withdrawals.

- **Application**: The main application class that interacts with the user. It provides a menu to add accounts, make deposits, withdrawals, and check account details.


>Note : For Doxygen to extract the comments, * and ! have been appended after standard comment syntax.


>GitHub Repository Link (CS700_Assignment 3): https://github.com/rajpanchal0101/CS700_Assignment3