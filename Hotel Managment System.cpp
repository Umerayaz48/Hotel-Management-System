#include <iostream>
#include <string>
using namespace std;

struct Room {
    int roomNumber;
    string type;
    float price;
    bool isBooked;
    string guestName;
    string checkIn;
    string checkOut;
    float foodBill;
};

struct FoodOrder {
    string itemName;
    float itemPrice;
    int quantity;
};

Room rooms[10];
int totalRooms = 10;
FoodOrder orders[50];
int totalOrders = 0;

// ========== INITIALIZE ROOMS ==========

void initializeRooms() {
    for (int i = 0; i < totalRooms; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = false;
        rooms[i].guestName = "";
        rooms[i].checkIn = "";
        rooms[i].checkOut = "";
        rooms[i].foodBill = 0.0;

        if (i < 4) {
            rooms[i].type = "Single";
            rooms[i].price = 50.0;
        } else if (i < 8) {
            rooms[i].type = "Double";
            rooms[i].price = 100.0;
        } else {
            rooms[i].type = "Suite";
            rooms[i].price = 200.0;
        }
    }
}

// ========== DISPLAY FOOD MENU ==========

void displayFoodMenu() {
    cout << "\n=============================" << endl;
    cout << "        FOOD MENU            " << endl;
    cout << "=============================" << endl;
    cout << "--- BREAKFAST ---" << endl;
    cout << "1.  Bread & Butter     $3" << endl;
    cout << "2.  Egg & Toast        $5" << endl;
    cout << "3.  Pancakes           $6" << endl;
    cout << "4.  Omelette           $7" << endl;
    cout << endl;
    cout << "--- LUNCH ---" << endl;
    cout << "5.  Grilled Chicken    $12" << endl;
    cout << "6.  Pasta              $10" << endl;
    cout << "7.  Burger             $8" << endl;
    cout << "8.  Club Sandwich      $9" << endl;
    cout << endl;
    cout << "--- DINNER ---" << endl;
    cout << "9.  Steak              $20" << endl;
    cout << "10. Grilled Fish       $18" << endl;
    cout << "11. Chicken Curry      $15" << endl;
    cout << "12. Vegetable Rice     $10" << endl;
    cout << endl;
    cout << "--- DRINKS ---" << endl;
    cout << "13. Water              $1" << endl;
    cout << "14. Juice              $3" << endl;
    cout << "15. Coffee             $4" << endl;
    cout << "16. Tea                $2" << endl;
    cout << "=============================" << endl;
}

// ========== ORDER FOOD ==========

void orderFood() {
    int roomNo;
    cout << "\nEnter Your Room Number: ";
    cin >> roomNo;

    if (roomNo < 1 || roomNo > totalRooms) {
        cout << "Invalid room number!" << endl;
        return;
    }

    int index = roomNo - 1;

    if (!rooms[index].isBooked) {
        cout << "Room " << roomNo << " is not booked! Please book a room first." << endl;
        return;
    }

    displayFoodMenu();

    string itemNames[] = {
        "Bread & Butter", "Egg & Toast", "Pancakes", "Omelette",
        "Grilled Chicken", "Pasta", "Burger", "Club Sandwich",
        "Steak", "Grilled Fish", "Chicken Curry", "Vegetable Rice",
        "Water", "Juice", "Coffee", "Tea"
    };

    float itemPrices[] = {
        3, 5, 6, 7,
        12, 10, 8, 9,
        20, 18, 15, 10,
        1, 3, 4, 2
    };

    int itemChoice;
    int quantity;
    char more;

    do {
        cout << "\nEnter Item Number (1-16): ";
        cin >> itemChoice;

        if (itemChoice < 1 || itemChoice > 16) {
            cout << "Invalid item! Try again." << endl;
            continue;
        }

        cout << "Enter Quantity: ";
        cin >> quantity;

        float total = itemPrices[itemChoice - 1] * quantity;
        rooms[index].foodBill += total;

        // Save order
        orders[totalOrders].itemName = itemNames[itemChoice - 1];
        orders[totalOrders].itemPrice = itemPrices[itemChoice - 1];
        orders[totalOrders].quantity = quantity;
        totalOrders++;

        cout << itemNames[itemChoice - 1] << " x" << quantity
             << " = $" << total << " added!" << endl;

        cout << "Order more? (y/n): ";
        cin >> more;

    } while (more == 'y' || more == 'Y');

    cout << "\nTotal Food Bill for Room " << roomNo
         << ": $" << rooms[index].foodBill << endl;
}

// ========== VIEW FOOD BILL ==========

void viewFoodBill() {
    int roomNo;
    cout << "\nEnter Room Number: ";
    cin >> roomNo;

    if (roomNo < 1 || roomNo > totalRooms) {
        cout << "Invalid room number!" << endl;
        return;
    }

    int index = roomNo - 1;

    if (!rooms[index].isBooked) {
        cout << "Room " << roomNo << " is not booked!" << endl;
        return;
    }

    cout << "\n===== FOOD BILL - ROOM " << roomNo << " =====" << endl;
    cout << "Guest Name : " << rooms[index].guestName << endl;
    cout << "Total Food Bill : $" << rooms[index].foodBill << endl;
}

// ========== DISPLAY ALL ROOMS ==========

void displayRooms() {
    cout << "\n===== ALL ROOMS =====" << endl;
    cout << "Room No | Type   | Price/Night | Status" << endl;
    cout << "--------|--------|-------------|--------" << endl;

    for (int i = 0; i < totalRooms; i++) {
        string status;
        if (rooms[i].isBooked) {
            status = "Booked";
        } else {
            status = "Available";
        }
        cout << "   " << rooms[i].roomNumber
             << "    | " << rooms[i].type
             << "   | $" << rooms[i].price
             << "      | " << status << endl;
    }
}

// ========== AVAILABLE ROOMS ==========

void availableRooms() {
    cout << "\n===== AVAILABLE ROOMS =====" << endl;
    bool anyAvailable = false;

    for (int i = 0; i < totalRooms; i++) {
        if (!rooms[i].isBooked) {
            cout << "Room " << rooms[i].roomNumber
                 << " | " << rooms[i].type
                 << " | $" << rooms[i].price << "/night" << endl;
            anyAvailable = true;
        }
    }

    if (!anyAvailable) {
        cout << "No rooms available at the moment." << endl;
    }
}

// ========== BOOK ROOM ==========

void bookRoom() {
    int roomNo;
    cout << "\nEnter Room Number to Book: ";
    cin >> roomNo;

    if (roomNo < 1 || roomNo > totalRooms) {
        cout << "Invalid room number!" << endl;
        return;
    }

    int index = roomNo - 1;

    if (rooms[index].isBooked) {
        cout << "Sorry, Room " << roomNo << " is already booked!" << endl;
        return;
    }

    cin.ignore();

    cout << "Enter Guest Name: ";
    getline(cin, rooms[index].guestName);

    cout << "Enter Check-in Date (DD/MM/YYYY): ";
    getline(cin, rooms[index].checkIn);

    cout << "Enter Check-out Date (DD/MM/YYYY): ";
    getline(cin, rooms[index].checkOut);

    rooms[index].isBooked = true;
    rooms[index].foodBill = 0.0;

    cout << "\nRoom " << roomNo << " booked successfully!" << endl;
    cout << "Guest : " << rooms[index].guestName << endl;
    cout << "Type  : " << rooms[index].type << endl;
    cout << "Price : $" << rooms[index].price << " per night" << endl;
}

// ========== CHECKOUT ==========

void checkOut() {
    int roomNo;
    cout << "\nEnter Room Number to Check Out: ";
    cin >> roomNo;

    if (roomNo < 1 || roomNo > totalRooms) {
        cout << "Invalid room number!" << endl;
        return;
    }

    int index = roomNo - 1;

    if (!rooms[index].isBooked) {
        cout << "Room " << roomNo << " is not booked!" << endl;
        return;
    }

    float totalBill = rooms[index].price + rooms[index].foodBill;

    cout << "\n===== FINAL BILL =====" << endl;
    cout << "Room Number  : " << roomNo << endl;
    cout << "Guest Name   : " << rooms[index].guestName << endl;
    cout << "Room Type    : " << rooms[index].type << endl;
    cout << "Check-in     : " << rooms[index].checkIn << endl;
    cout << "Check-out    : " << rooms[index].checkOut << endl;
    cout << "Room Charge  : $" << rooms[index].price << endl;
    cout << "Food Bill    : $" << rooms[index].foodBill << endl;
    cout << "--------------------" << endl;
    cout << "TOTAL BILL   : $" << totalBill << endl;
    cout << "====================" << endl;

    rooms[index].isBooked = false;
    rooms[index].guestName = "";
    rooms[index].checkIn = "";
    rooms[index].checkOut = "";
    rooms[index].foodBill = 0.0;

    cout << "\nGuest checked out successfully!" << endl;
}

// ========== SEARCH GUEST ==========

void searchGuest() {
    string name;
    cin.ignore();
    cout << "\nEnter Guest Name to Search: ";
    getline(cin, name);

    bool found = false;
    for (int i = 0; i < totalRooms; i++) {
        if (rooms[i].guestName == name && rooms[i].isBooked) {
            cout << "\n===== GUEST FOUND =====" << endl;
            cout << "Room Number : " << rooms[i].roomNumber << endl;
            cout << "Room Type   : " << rooms[i].type << endl;
            cout << "Check-in    : " << rooms[i].checkIn << endl;
            cout << "Check-out   : " << rooms[i].checkOut << endl;
            cout << "Room Price  : $" << rooms[i].price << endl;
            cout << "Food Bill   : $" << rooms[i].foodBill << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No guest found with name: " << name << endl;
    }
}

// ========== MAIN ==========

int main() {
    initializeRooms();

    int choice;

    cout << "======================================" << endl;
    cout << "  WELCOME TO HOTEL MANAGEMENT SYSTEM  " << endl;
    cout << "======================================" << endl;

    do {
        cout << "\n===== MAIN MENU =====" << endl;
        cout << "1. View All Rooms" << endl;
        cout << "2. View Available Rooms" << endl;
        cout << "3. Book a Room" << endl;
        cout << "4. Order Food" << endl;
        cout << "5. View Food Bill" << endl;
        cout << "6. Check Out (With Full Bill)" << endl;
        cout << "7. Search Guest" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayRooms();   break;
            case 2: availableRooms(); break;
            case 3: bookRoom();       break;
            case 4: orderFood();      break;
            case 5: viewFoodBill();   break;
            case 6: checkOut();       break;
            case 7: searchGuest();    break;
            case 0: cout << "\nThank you! Goodbye!" << endl; break;
            default: cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
