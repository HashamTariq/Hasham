#include <iostream>
#include <vector>
#include <iomanip>
#include<windows.h>

using namespace std;

// Structure to represent an item
struct Item {
    string code;
    string description;
    double price;
};

// Function to display items and get user choice
string getUserChoice(const vector<Item>& items, const string& category) {
    cout << "\nChoose a " << category << ":" << endl;
    for (const auto& item : items) {
        cout << item.code << " - " << item.description << ": $" << item.price << endl;
    }

    string userChoice;
    cout << "Enter the code of your chosen " << category << ": ";
    cin >> userChoice;

    // Validate user input
    for (const auto& item : items) {
        if (userChoice == item.code) {
            return userChoice;
        }
    }

    cout << "Invalid choice. Please try again." << endl;
    return getUserChoice(items, category);
}

int main() {
	
		HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,11);	
    // Arrays to store items
    vector<Item> cases = {{"A1", "Compact", 75.00}, {"A2", "Tower", 150.00}};
    vector<Item> ram = {{"B1", "8 GB", 79.99}, {"B2", "16 GB", 149.99}, {"B3", "32 GB", 299.99}};
    vector<Item> hdd = {{"C1", "1 TB HDD", 49.99}, {"C2", "2 TB HDD", 89.99}, {"C3", "4 TB HDD", 129.99}};

    // Basic set of components cost
    const double basicComponentsCost = 200.00;

    // Task 1 - Setting up the system and ordering main items
    cout << "Welcome to the Online Computer Shop!" << endl;
    string caseChoice = getUserChoice(cases, "case");
    string ramChoice = getUserChoice(ram, "RAM");
    string hddChoice = getUserChoice(hdd, "Main Hard Disk Drive");

    // Calculate the total cost of main items
    double totalCost = basicComponentsCost;

    // Output the chosen items and total cost
    cout << "\nChosen Items:" << endl;
    cout << "Case: " << caseChoice << " - " << cases[0].description << endl;
    cout << "RAM: " << ramChoice << " - " << ram[0].description << endl;
    cout << "Main Hard Disk Drive: " << hddChoice << " - " << hdd[0].description << endl;

    // Add the prices of chosen main items to the total cost
    for (const auto& item : {cases, ram, hdd}) {
        for (const auto& i : item) {
            if (i.code == caseChoice || i.code == ramChoice || i.code == hddChoice) {
                totalCost += i.price;
                break;
            }
        }
    }

    cout << fixed << setprecision(2);
    cout << "Total Cost: $" << totalCost << endl;

    // Task 2 - Ordering additional items
    double additionalItemsCost = 0.00;
    vector<Item> additionalItems;

    while (true) {
        cout << "\nDo you want to purchase additional items?" << endl;
        cout << "Enter 'Y' for Yes, 'N' for No: ";
        char choice;
        cin >> choice;

        if (toupper(choice) != 'Y') {
            break;
        }

        cout << "\nAdditional Item Categories:" << endl;
        cout << "D - Solid State Drive" << endl;
        cout << "E - Second Hard Disk Drive" << endl;

        string categoryChoice;
        cout << "Enter the category code (D, E): ";
        cin >> categoryChoice;

        // Handle each additional item category
        if (categoryChoice == "D") {
            const vector<Item> ssd = {{"D1", "240 GB SSD", 59.99}, {"D2", "480 GB SSD", 119.99}};
            string ssdChoice = getUserChoice(ssd, "Solid State Drive");
            additionalItems.push_back(ssd[0]);
            additionalItemsCost += ssd[0].price;
        } else if (categoryChoice == "E") {
            const vector<Item> secondHdd = {{"E1", "1 TB HDD", 49.99}, {"E2", "2 TB HDD", 89.99}, {"E3", "4 TB HDD", 129.99}};
            string secondHddChoice = getUserChoice(secondHdd, "Second Hard Disk Drive");
            additionalItems.push_back(secondHdd[0]);
            additionalItemsCost += secondHdd[0].price;
        } else {
            cout << "Invalid category code. Please try again." << endl;
        }
    }

    // Calculate the updated total cost
    totalCost += additionalItemsCost;

    // Task 3 - Offering discounts
    double discount = 0.0;

    if (additionalItems.size() == 1) {
        discount = 0.05;
    } else if (additionalItems.size() >= 2) {
        discount = 0.1;
    }

    // Apply the discount
    double discountAmount = totalCost * discount;
    totalCost -= discountAmount;

    // Output the chosen additional items, discount, and final cost
    cout << "\nChosen Additional Items:" << endl;
    for (const auto& item : additionalItems) {
        cout << item.description << endl;
    }

    cout << "Additional Items Cost: $" << additionalItemsCost << endl;
    cout << "Discount Applied: " << discount * 100 << "%" << endl;
    cout << "Discount Amount: $" << discountAmount << endl;
    cout << "Final Cost after Discount: $" << totalCost << endl;

    return 0;
}

