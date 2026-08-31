    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <conio.h>
    #include <windows.h>
    #include <ctype.h>
    #include <time.h>
                
    #define RED   "\x1B[31m" // ChatGPT
    #define GREEN "\x1B[32m"
    #define RESET "\x1B[0m"

    // Bank account structure
    typedef struct {
        char username[40];
        char password[9];
        float balance;   
        char email[40];
        char contact[20]; 
    } BankAccount;

    // Global variables
    BankAccount *accounts = NULL;      // Dynamic array of all accounts
    int account_count = 0;             // Number of accounts
    FILE **transaction_files = NULL;   // Stores transaction history files

    // Display functions
    void displayHeader(const char *title);
    void displayMenu();
    void accountHolderLogin();
    void adminLogin();
    void adminMenu();
    void createAccount();
    void viewAccountDetails(int index);
    void makeTransactions(int account_index);
    void withdraw(int account_index);
    void deposit(int account_index);
    void transferFunds(int account_index);
    void showTransactionHistory(int account_index);
    void updateRecords();
    void exitProgram();
    void rotateDashAnimation(int durationMs, int frameDelayMs);

    int main() {
        system("cls");
        system("COLOR 1F");     

        FILE *file = fopen("accounts.txt", "r");
        if (!file) {
            printf("\n\n\t\t\t%sError: Cannot open accounts file.%s\n", RED, RESET);
            return 1;
        }

        int capacity = 5;
        accounts = malloc(capacity * sizeof(BankAccount));

        while (fscanf(file, "%39s\t%8s\t%f\t%39s\t%19s", 
            accounts[account_count].username,
            accounts[account_count].password,
            &accounts[account_count].balance,
            accounts[account_count].email,
            accounts[account_count].contact) == 5) {

            account_count++;

            if (account_count == capacity) {
                capacity *= 2;
                BankAccount *temp = realloc(accounts, capacity * sizeof(BankAccount));
                if (!temp) {
                    printf("\n\t\t\t%sError: Memory full!%s\n", RED, RESET);
                    free(accounts);
                    fclose(file);
                    return 1;
                }
                accounts = temp;
            }
        }
        fclose(file);

        transaction_files = calloc(account_count, sizeof(FILE *));

        int choice;
        do {
            system("cls");
            system("COLOR 1F");
            printf("\n\t\t\tLoading Main Menu...");
            rotateDashAnimation(1000, 150);
            system("cls");
            displayHeader("Welcome to Banking System");
            displayMenu();
            
            printf("\n\t\t\tEnter choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: adminLogin(); break;
                case 2: accountHolderLogin(); break;
                case 3: createAccount(); break;
                case 4: exitProgram();
                default: 
                    printf("\n\t\t\t%sInvalid choice!%s", RED, RESET);
                    Sleep(1000);
                    system("cls");
            }
        } while (1);

        return 0;
    }
    // Display a centered header with border
    void displayHeader(const char *title){
        printf("\n\n");
        printf("\t\t\t\311\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\273\n");
        printf("\t\t\t\t %s\n", title);
        printf("\t\t\t\310\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\274\n");
    }
    // Display the main menu options
    void displayMenu(){
        printf("\n\t\t\t1. Admin Login");
        printf("\n\t\t\t2. Account Holder Login");
        printf("\n\t\t\t3. Create new Account");
        printf("\n\t\t\t4. Exit");
    }
    // Update account details in the file
    void updateRecords(){
        FILE *file = fopen("accounts.txt", "w");
        if (file == NULL)
        {
            printf("\n\t\t\t%sError: Could not update records file.%s\n", RED, RESET);
            return;
        }

        for (int i = 0; i < account_count; i++)
        {
            fprintf(file, "%-39s\t%-8s\t%.2f\t%-39s\t%-19s\n",
                    accounts[i].username,
                    accounts[i].password,
                    accounts[i].balance,
                    accounts[i].email,
                    accounts[i].contact);
        }

        fclose(file);
    }
    // Clean up and exit the program
    void exitProgram(){
        updateRecords();
        free(accounts);
        free(transaction_files);
        printf("\n\t\t\tSaving data and exiting, please wait...");
        rotateDashAnimation(2000, 200);
        exit(0);
    }
    // Account holder login function
    void accountHolderLogin() {
        char username[40], password[9];
        int attempts = 0;
        system("cls");
        system("COLOR 30");
        while (attempts < 3) {
            displayHeader("Account Login");

            printf("\n\t\t\tUsername: ");
            scanf("%39s", username);

            printf("\t\t\tPassword: ");
            scanf("%8s", password);

            printf("\n\t\t\tValidating credentials, please wait...");
            rotateDashAnimation(1500, 200);
            for (int i = 0; i < account_count; i++) {
                if (strcmp(username, accounts[i].username) == 0 && 
                    strcmp(password, accounts[i].password) == 0) {
                    printf("\n\t\t\t%sLogin successful!%s", GREEN, RESET);
                    Sleep(1000);
                    system("cls");
                    viewAccountDetails(i);
                    return;
                }
            }
            printf("\n\t\t\t%sInvalid login! Attempts left: %d %s",RED, 2 - attempts, RESET);
            Sleep(1500);
            system("cls");
            attempts++;
        }

        printf("\n\t\t\t%sToo many failed attempts. Returning to menu...%s", RED, RESET);
        rotateDashAnimation(1500, 200);
        system("cls");
    }
    // Withdraw money from an account
    void withdraw(int account_index) {
        system("cls");
        system("COLOR 70");
        float amount;
        displayHeader("Withdraw Money");
        printf("\n\t\t\tBalance: Rs. %.2f", accounts[account_index].balance);

        printf("\n\t\t\tEnter amount: ");
        scanf("%f", &amount);

        printf("\n\t\t\tProcessing your withdrawal, please wait...");
        rotateDashAnimation(2000, 200);
        if (amount <= 0) {
            printf("\n\t\t\t%sAmount must be positive!%s", RED, RESET);
        } 
        else if (amount > accounts[account_index].balance) {
            printf("\n\t\t\t%sInsufficient funds!%s", RED, RESET);
        } 
        else {
            accounts[account_index].balance -= amount;
            updateRecords();

            // Get the current date and time
            time_t t;
            struct tm *tm_info;
            time(&t);
            tm_info = localtime(&t);
            char date_time[30];
            strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", tm_info);

            char filename[20];
            sprintf(filename, "User%d.txt", account_index + 1);
            FILE *file = fopen(filename, "a");
            fprintf(file, "Withdrawal: Rs. %.2f on %s\n", amount,date_time);
            fclose(file);

            printf("\n\t\t\t%sSuccess! New balance: Rs. %.2f%s", GREEN, accounts[account_index].balance, RESET);
        }

        printf("\n\t\t\tPress any key to continue...");
        getch();
        system("cls");
    }
    // Deposit money into an account
    void deposit(int account_index){
        system("COLOR 70");
        float amount;

        displayHeader("Deposit Money");
        printf("\n\t\t\tCurrent balance: %.2f", accounts[account_index].balance);
        printf("\n\t\t\tEnter amount to deposit: ");
        scanf("%f", &amount);

        printf("\n\t\t\tProcessing your withdrawal, please wait...");
        rotateDashAnimation(2000, 200);
        while (amount <= 0)
        {
            printf("\n\t\t\t%sAmount must be positive! Try again: %s", RED, RESET);
            scanf("%f", &amount);
        }

        accounts[account_index].balance += amount;

        // Get the current date and time
        time_t t;
        struct tm *tm_info;
        time(&t);
        tm_info = localtime(&t);
        char date_time[30];
        strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", tm_info);

        char filename[20];
        sprintf(filename, "User%d.txt", account_index + 1);
        FILE *file = fopen(filename, "a");
        fprintf(file, "Deposit: Rs. %.2f on %s\n", amount,date_time);
        fclose(file);

        printf("\n\t\t\t%sDeposit successful!%s", GREEN, RESET);
        printf("\n\t\t\tNew balance: %.2f", accounts[account_index].balance);
        updateRecords();

        printf("\n\t\t\tPress any key to return...");
        getch();
        system("cls");
    }
    // Transfer funds between accounts
    void transferFunds(int sender_index){
        system("COLOR 70");
        char recipient[40];
        float amount;
        int recipient_index = -1;

        displayHeader("Transfer Funds");
        printf("\n\t\t\tYour current balance: %.2f", accounts[sender_index].balance);

        printf("\n\t\t\tEnter recipient username: ");
        scanf("%39s", recipient);

        for (int i = 0; i < account_count; i++)
        {
            if (strcmp(recipient, accounts[i].username) == 0)
            {
                recipient_index = i;
                break;
            }
        }

        if (recipient_index == -1)
        {
            printf("\n\t\t\t%sRecipient not found!%s", RED, RESET);
            printf("\n\t\t\tPress any key to return...");
            getch();
            system("cls");
            return;
        }

        printf("\n\t\t\tEnter amount to transfer: ");
        scanf("%f", &amount);
        printf("\n\t\t\tProcessing your withdrawal, please wait...");
        rotateDashAnimation(2000, 200);
        if (amount <= 0)
        {
            printf("\n\t\t\t%sAmount must be positive!%s", RED, RESET);
        }
        else if (amount > accounts[sender_index].balance)
        {
            printf("\n\t\t\t%sInsufficient funds!%s", RED, RESET);
        }
        else
        {
            accounts[sender_index].balance -= amount;
            accounts[recipient_index].balance += amount;

            // Get the current date and time
            time_t t;
            struct tm *tm_info;
            time(&t);
            tm_info = localtime(&t);
            char date_time[30];
            strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", tm_info);

            char filename[20];

            sprintf(filename, "User%d.txt", sender_index + 1);
            FILE *file = fopen(filename, "a");
            fprintf(file, "Transfer to %s: Rs. %.2f on %s\n", recipient, amount, date_time);
            fclose(file);

            sprintf(filename, "User%d.txt", recipient_index + 1);
            file = fopen(filename, "a");
            fprintf(file, "Transfer from %s: Rs. %.2f on %s\n", accounts[sender_index].username, amount, date_time);
            fclose(file);

            printf("\n\t\t\t%sTransfer successful!%s", GREEN, RESET);
            printf("\n\t\t\tYour new balance: %.2f", accounts[sender_index].balance);
            updateRecords();
        }

        printf("\n\t\t\tPress any key to return...");
        getch();
        system("cls");
    }
    // Show transaction history for an account
    void showTransactionHistory(int account_index){
        system("COLOR 70");
        char filename[20];
        sprintf(filename, "User%d.txt", account_index + 1);

        displayHeader("Transaction History");
        printf("\n\t\t\tLoading transaction history, please wait...");
        rotateDashAnimation(1500, 200); 
        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("\n\t\t\t%sNo transaction history found.%s", RED, RESET);
        }
        else
        {
            char line[100];
            while (fgets(line, sizeof(line), file))
            {
                printf("\n\t\t\t==========================================");
                printf("\n\t\t\t%s", line);
            }
            fclose(file);
        }

        printf("\n\t\t\tPress any key to return...");
        getch();
        system("cls");
    }
    // Transaction menu for an account
    void makeTransactions(int account_index){
        system("COLOR 70");
        int choice;
        do
        {
            displayHeader("Transaction Menu");
            printf("\n\t\t\t1. Transfer Funds");
            printf("\n\t\t\t2. Deposit Money");
            printf("\n\t\t\t3. Withdraw Money");
            printf("\n\t\t\t4. View Transaction History");
            printf("\n\t\t\t5. Return to Account");
            printf("\n\t\t\tEnter your choice: ");
            scanf("%d", &choice);
            system("cls");
            switch (choice)
            {
            case 1:
                printf("\n\t\t\tProcessing your request, please wait...");
                rotateDashAnimation(1500, 200);
                system("cls");
                transferFunds(account_index);
                break;
            case 2:
                printf("\n\t\t\tProcessing your request, please wait...");
                rotateDashAnimation(1500, 200);
                system("cls");
                deposit(account_index);
                break;
            case 3:
                printf("\n\t\t\tProcessing your request, please wait...");
                rotateDashAnimation(1500, 200);
                withdraw(account_index);
                break;
            case 4:
                printf("\n\t\t\tLoading transaction history, please wait...");
                rotateDashAnimation(1500, 200);
                system("cls");
                showTransactionHistory(account_index);
                break;
            case 5:
                return;
            default:
                printf("\n\t\t\t%sInvalid choice! Try again.%s", RED, RESET);
                Sleep(1000);
                system("cls");
            }
        } while (1);
    }
    // View account details and options
    void viewAccountDetails(int account_index){
        system("COLOR 70");

        printf("\n\t\t\tLoading account details, please wait...");
        rotateDashAnimation(1500, 200);
        system("cls");

        int choice;
        do
        {
            displayHeader("Account Details");
            printf("\n\t\t\tUsername: %s", accounts[account_index].username);
            printf("\n\t\t\tBalance: %.2f", accounts[account_index].balance);
            printf("\n\t\t\tEmail: %s", accounts[account_index].email);
            printf("\n\t\t\tContact: %s", accounts[account_index].contact);

            printf("\n\n\t\t\t1. Make Transactions");
            printf("\n\t\t\t2. View Transaction History");
            printf("\n\t\t\t3. Return to Main Menu");
            printf("\n\t\t\t4. Exit");
            printf("\n\t\t\tEnter your choice: ");
            scanf("%d", &choice);

            system("cls");

            switch (choice)
            {
            case 1:
                makeTransactions(account_index);
                break;
            case 2:
                showTransactionHistory(account_index);
                break;
            case 3:
                return;
            case 4:
                exitProgram();
            default:
                printf("\n\t\t\t%sInvalid choice! Try again.%s", RED, RESET);
                Sleep(1000);
                system("cls");
            }
        } while (1);
    }
    // Create a new bank account
    void createAccount() {
        system("COLOR 70");
        BankAccount new_acc;
        system("cls");
        displayHeader("Create New Account");

        printf("\n\t\t\tUsername: ");
        scanf("%39s", new_acc.username);

        printf("\t\t\tPassword (max 8 chars): ");
        scanf("%8s", new_acc.password);

        printf("\t\t\tEmail: ");
        scanf("%39s", new_acc.email);

        printf("\t\t\tContact: ");
        scanf("%19s", new_acc.contact);

        new_acc.balance = 0.0;

        account_count++;
        accounts = realloc(accounts, account_count * sizeof(BankAccount));
        accounts[account_count - 1] = new_acc;

        updateRecords();

        char filename[20];
        sprintf(filename, "User%d.txt", account_count);
        FILE *file = fopen(filename, "w");
        if (file) fclose(file);
        printf("\n\t\t\tCreating your account, please wait...");
        rotateDashAnimation(2000, 200);
        printf("\n\t\t\t%sAccount created! Your Number is : %d %s", GREEN, account_count, RESET);

        char choice;
        printf("\n\t\t\tWould you like to make an initial deposit? (Y/N): ");
        scanf(" %c", &choice);
        
        if (toupper(choice) == 'Y') {
            system("cls");
            deposit(account_count - 1);
        } else {
            printf("\n\t\t\tPress any key to return to main menu...");
            getch();
            system("cls");
        }
    }
    // Admin login and functions
    void adminLogin(){
        const char admin_username[] = "admin";
        const char admin_password[] = "admin123";
        char username[40], password[40];
        int attempts = 0;

        while (attempts < 3)
        {
            system("cls");
            system("COLOR 30");
            displayHeader("Admin Login");

            printf("\n\t\t\tEnter admin username: ");
            scanf("%39s", username);

            printf("\t\t\tEnter admin password: ");
            scanf("%39s", password);

            printf("\n\t\t\tValidating credentials, please wait...");
            rotateDashAnimation(1500, 200);
            if (strcmp(username, admin_username) == 0 &&
                strcmp(password, admin_password) == 0)
            {
                printf("\n\t\t\t%sAdmin login successful!%s", GREEN, RESET);
                Sleep(1000);
                system("cls");
                adminMenu();
                return;
            }
            printf("\n\t\t\t%sInvalid credentials! Attempts remaining: %d %s",RED, 2 - attempts, RESET);
            Sleep(1500);
            system("cls");
            attempts++;
        }

        printf("\n\t\t\t%sToo many failed attempts. RetAurning to main menu.%s", RED, RESET);
        rotateDashAnimation(1500, 200); // 1.5 seconds animation
        system("cls");
    }
    // Admin menu and functions
    void adminMenu(){
        system("COLOR 08");
        int choice;
        do
        {
            printf("\n\t\t\tLoading Admin Menu...");
            rotateDashAnimation(1000, 150); 
            system("cls");
            displayHeader("Admin Menu");
            printf("\n\t\t\t1. View Account by Index");
            printf("\n\t\t\t2. View Account by Username");
            printf("\n\t\t\t3. View All Accounts");
            printf("\n\t\t\t4. Return to Main Menu");
            printf("\n\t\t\tEnter your choice: ");
            scanf("%d", &choice);

            system("cls");

            switch (choice)
            {
            case 1:
            {
                int index;
                printf("\n\t\t\tEnter account index (0-%d): ", account_count - 1);
                scanf("%d", &index);

                if (index >= 0 && index < account_count)
                {
                    viewAccountDetails(index);
                }
                else
                {
                    printf("\n\t\t\t%sInvalid index!%s", RED, RESET);
                    Sleep(1000);
                }
                break;
            }
            case 2:
            {
                char username[40];
                printf("\n\t\t\tEnter username: ");
                scanf("%39s", username);

                int found = 0;
                for (int i = 0; i < account_count; i++)
                {
                    if (strcmp(username, accounts[i].username) == 0)
                    {
                        viewAccountDetails(i);
                        found = 1;
                        break;
                    }
                }

                if (!found)
                {
                    printf("\n\t\t\t%sAccount not found!%s", RED, RESET);
                    Sleep(1000);
                }
                break;
            }
            case 3:
                printf("\n\t\t\tLoading all accounts, please wait...");
                rotateDashAnimation(1500, 200);
                system("cls");
                displayHeader("All Accounts");
                for (int i = 0; i < account_count; i++)
                {
                    printf("\n\t\t\t%d. %s (Balance: %.2f)", i, accounts[i].username, accounts[i].balance);
                }
                printf("\n\t\t\tPress any key to return...");
                getch();
                system("cls");
                break;
            case 4:
                return;
            default:
                printf("\n\t\t\t%sInvalid choice!%s", RED, RESET);
                Sleep(1000);
                system("cls");
            }
        } while (1);
    }

    void rotateDashAnimation(int durationMs, int frameDelayMs) {
        char dashPositions[] = {'-', '\\', '|', '/'};
        int frames = durationMs / frameDelayMs;

        for (int i = 0; i < frames; i++) {
            printf("\b%c", dashPositions[i % 4]);
            fflush(stdout);
            Sleep(frameDelayMs);
        }
        printf("\b \b");
    }