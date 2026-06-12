# Banking Application Simulator

A simple banking application for managing bank accounts and transactions. Supports creating savings and checking accounts, making deposits and withdrawals, and viewing account details with transaction history.

## Tech Used

- C++

## Files

| File | Description |
|------|-------------|
| `a3_header.h` | Header file with class declarations (`Transaction`, `Customer`, `Account`, `Savings_Account`, `Checking_Account`, `Bank`, `Application`). Included in `a3_class_methods.cpp`. |
| `a3_main.cpp` | Entry point — creates an `Application` instance and starts the program. |
| `a3_class_methods.cpp` | Implements all class member functions declared in the header. Included in `a3_main.cpp`. |
| `Date.h` | Utility header for date-related operations. Included in `a3_header.h`. |
| `a3_executable.exe` | Pre-built executable binary. |

## Class Overview

- **Transaction** — Represents a bank transaction (type, amount, balance, date).
- **Customer** — Stores customer details (name, address, age, telephone, customer number).
- **Account** — Base class for bank accounts with deposit, withdrawal, and interest calculation.
- **Savings_Account / Checking_Account** — Derived account types.
- **Bank** — Manages customer accounts and provides methods for deposits and withdrawals.
- **Application** — Interactive menu for the user to add accounts, make deposits/withdrawals, and check details.

## How to Build & Run

```bash
g++ a3_main.cpp -o banking && ./banking
```

Or run `a3_executable.exe` directly on Windows.
