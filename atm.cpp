#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


struct User {
    string cardNumber;
    string name;
    string address;
    double balance;
    string password;
};


vector<User> readUserDataFromFile(const string& filename) {
    ifstream file(filename);
    vector<User> users;
    if (file.is_open()) {
        User user;
        while (file >> user.cardNumber >> user.name >> user.address >> user.balance >> user.password) {
            users.push_back(user);
        }
        file.close();
    }
    return users;
}

void createAccount(vector<User>& users) {
    User newUser;
    
    cout << "Enter Card Number: ";
    cin >> newUser.cardNumber;

    
    for (const auto& user : users) {
        if (user.cardNumber == newUser.cardNumber) {
            cout << "Card number already exists. Please choose a different card number." << endl;
            return;
        }
    }

    cout << "Enter Name: ";
    cin.ignore(); 
    getline(cin, newUser.name);

    cout << "Enter Address: ";
    getline(cin, newUser.address);

    cout << "Enter Password: ";
    cin >> newUser.password;

    newUser.balance = 0.0; 

    users.push_back(newUser);
    cout << "Account created successfully!" << endl;
}


void writeUserDataToFile(const string& filename, const vector<User>& users) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.cardNumber << " " << user.name << " " << user.address << " " << user.balance << " " << user.password << "\n";
        }
        file.close();
    }
}


void deposit(vector<User>& users, const string& cardNumber, double amount) {
    for (auto& user : users) {
        if (user.cardNumber == cardNumber) {
            user.balance += amount;
            cout << "Deposit successful. Updated balance: " << user.balance << endl;
            break;
        }
    }
}


void withdraw(vector<User>& users, const string& cardNumber, double amount) {
    for (auto& user : users) {
        if (user.cardNumber == cardNumber) {
            if (user.balance >= amount) {
                user.balance -= amount;
                cout << "Withdrawal successful. Updated balance: " << user.balance << endl;
            } else {
                cout << "Insufficient balance." << endl;
            }
            break;
        }
    }
}


void checkAccountDetails(const vector<User>& users, const string& cardNumber) {
    for (const auto& user : users) {
        if (user.cardNumber == cardNumber) {
            cout << "Name: " << user.name << endl;
            cout << "Address: " << user.address << endl;
            cout << "Balance: " << user.balance << endl;
            break;
        }
    }
}


void transfer(vector<User>& users, const string& senderCardNumber, const string& receiverCardNumber, double amount) {
    bool senderFound = false, receiverFound = false;
    for (auto& user : users) {
        if (user.cardNumber == senderCardNumber) {
            senderFound = true;
            if (user.balance >= amount) {
                user.balance -= amount;
                for (auto& receiver : users) {
                    if (receiver.cardNumber == receiverCardNumber) {
                        receiver.balance += amount;
                        cout << "Transfer successful. Updated balance for sender: " << user.balance << endl;
                        cout << "Updated balance for receiver: " << receiver.balance << endl;
                        receiverFound = true;
                        break;
                    }
                }
                break;
            } else {
                cout << "Sender has insufficient balance." << endl;
                break;
            }
        }
    }
    if (!senderFound) {
        cout << "Sender account not found." << endl;
    }
    if (!receiverFound) {
        cout << "Receiver account not found." << endl;
    }
}


bool authenticateUser(const vector<User>& users, const string& cardNumber, const string& password) {
    for (const auto& user : users) {
        if (user.cardNumber == cardNumber && user.password == password) {
            return true;
        }
    }
    return false;
}


int main() {
    const string filename = "userData.txt";
    vector<User> users = readUserDataFromFile(filename);

    int loginOption;
    do {
        cout << "Choose an option:\n";
        cout << "1. Login\n";
        cout << "2. Create an account\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> loginOption;

        if (loginOption == 1) {
            
            
             string cardNumber, password;
    cout << "Enter Card Number: ";
    cin >> cardNumber;
    cout << "Enter Password: ";
    cin >> password;
     if (authenticateUser(users, cardNumber, password)) {
        char choice;
        do {
            cout << "\nChoose an option:\n";
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. Check Account Details\n";
            cout << "4. Transfer\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case '1': {
                    double depositAmount;
                    cout << "Enter amount to deposit: ";
                    cin >> depositAmount;
                    deposit(users, cardNumber, depositAmount);
                    break;
                }
                case '2': {
                    double withdrawAmount;
                    cout << "Enter amount to withdraw: ";
                    cin >> withdrawAmount;
                    withdraw(users, cardNumber, withdrawAmount);
                    break;
                }
                case '3':
                    checkAccountDetails(users, cardNumber);
                    break;
                case '4': {
                    string receiverCardNumber;
                    double transferAmount;
                    cout << "Enter receiver's card number: ";
                    cin >> receiverCardNumber;
                    cout << "Enter amount to transfer: ";
                    cin >> transferAmount;
                    transfer(users, cardNumber, receiverCardNumber, transferAmount);
                    break;
                }
                case '5':
                    cout << "Exiting...";
                    break;
                default:
                    cout << "Invalid choice. Please try again.";
            }
        } while (choice != '5');

        
        writeUserDataToFile(filename, users);
    } else {
        cout << "Authentication failed. Invalid card number or password.";
    }

        } else if (loginOption == 2) {
            createAccount(users);
            writeUserDataToFile(filename, users); 
        } else if (loginOption == 3) {
            cout << "Exiting...";
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (loginOption != 3); 

    return 0;
}
