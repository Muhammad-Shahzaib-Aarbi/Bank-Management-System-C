# Bank Account Management System 🏦

A robust, terminal-based Bank Management System developed entirely in C. This project was designed to demonstrate advanced programming concepts including dynamic memory management, persistent data structures, and secure file I/O operations.

## 🚀 Key Features

*   **Dual-Tier Authorization:**
    *   **Admin Mode:** Secure portal for banking staff to view account details, monitor global transactions, and update system records.
    *   **User Mode:** Personal portal for account holders to perform withdrawals, deposits, and fund transfers.
*   **Dynamic Memory Allocation:** Utilizes `malloc` and `realloc` to dynamically scale the account array at runtime, ensuring memory is efficiently managed regardless of the number of registered users.
*   **Individualized Transaction Ledgers:** Instead of a single messy log, the system automatically generates and updates separate `.txt` transaction history files for *every individual user*.
*   **Persistent State:** Reads from and writes to `accounts.txt` to ensure all user data (passwords, emails, balances) is saved across terminal sessions.
*   **Enhanced Terminal UI:** Features colored text outputs (`windows.h`), loading animations, and a clean, structured CLI menu system.

## 🛠️ Technical Stack & Concepts Demonstrated

*   **Language:** C
*   **Libraries:** `stdio.h`, `stdlib.h`, `string.h`, `windows.h`, `time.h`
*   **Core Engineering Concepts:** 
    *   Dynamic Memory (`malloc`/`realloc`)
    *   Structs & Pointers
    *   Multi-file Data Handling
    *   Console UI/UX design

## ⚙️ How to Run

1.  **Compile the Code:**
    Ensure you have a C compiler (like GCC) installed. Open your terminal in the project directory:
    ```bash
    gcc bank.c -o bank_system
    ```
2.  **Execute:**
    *   *Windows:* `.\bank_system.exe`
3.  **Usage:**
    Ensure `accounts.txt` is in the same directory. Follow the on-screen prompts to navigate the system.

## 📄 Documentation
For a complete breakdown of the system architecture, logic flow, and edge-case handling, please refer to the included `Project Report.pdf`.
