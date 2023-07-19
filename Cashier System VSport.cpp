// This program will be used as a cashier receipt system for a food store.
// 16026792
#include <iostream> // For the use of standard input and output objects (Cin, Cout...)
#include <iomanip> // For the spacing between displayed text (Setw)
#include <fstream> // For the use of a file system.
#include <vector> // Vectors are needed to save the information in files.
#include <sstream> // This is used to create a stream library, to convert object into string.


using namespace std;

const int n = 10; // Declaration for n, that is a needed variable for loops and arrays as it represents an n value.

const string products[n] = { "Milk", "Bread", "Chocolate", "Towel", "Toothpaste", "Soap", "Pen", "Biscuits", "Lamp", "Battery" }; // Array for the name of products currently on sale
double prices[n] = { 10.50, 5.50, 8.00, 12.10, 6.75, 5.20, 2.00, 4.25, 20.50, 10.00 };// Array for the prices of the products currently on sale
string barcodes[n]{ "0120001", "0120002", "0120003", "0120004", "0120005", "0120006", "0120007", "0120008", "0120009", "0120010" };// Barcodes for the products currently on sale

int customer_counter = 0;




void welcome_message()// Custom Function for welcome message.
{
    cout << setw(2) << "****************************************************" << endl; // The Welcome message itself
    cout << setw(2) << "*   WELCOME TO HERTS SUPERMARKET CHECKOUT SYSTEM   *" << endl;
    cout << setw(2) << "* Scan the barcode or manually type the barcode ID *" << endl;
    cout << setw(2) << "****************************************************" << endl;
}

void welcome_message(ofstream& file)// Custom Function for welcome message to be printed in receipt file.
{
    file << setw(2) << "****************************************************" << endl; // The Welcome message itself
    file << setw(2) << "*   WELCOME TO HERTS SUPERMARKET CHECKOUT SYSTEM   *" << endl;
    file << setw(2) << "* Scan the barcode or manually type the barcode ID *" << endl;
    file << setw(2) << "****************************************************" << endl;
}
void reciept(double sum, vector <string> barcodes_pull) // This function is used to print a receipt out on screen as well as to save a text file of customers receipts; to show a history.
{
    double total_price = 0; // Declaration of total price for the transaction.

    cout << endl;
    cout << setfill('-') << setw(27) << "RECEIPT" << setw(28) << '\n' << setfill(' ');

    for (int i = 0; i < barcodes_pull.size(); i++)
        for (int j = 0; j < n; j++)
            if (barcodes_pull[i] == barcodes[j]) // if the user barcodes match the ones in the array they are saved to be displayed in the receipts.
            {
                cout << setw(20) << "Items" << setw(15) << "Barcodes" << setw(10) << "Price" << endl; // This is a general arrangment of the receipt, total price, cash sum and change due are shown.
                cout << setw(20) << products[j] << setw(15) << barcodes[j] << setw(10) << prices[j] << endl;
                total_price += prices[j];
            }
    cout << endl;
    cout << setw(20) << "Total transaction: " << total_price << endl; // Other section of receipt layout
    cout << setw(20) << "Total cash paid: " << sum << endl;
    cout << setw(20) << "Change: " << sum - total_price << endl;
    cout << setw(15) << "------------------------------------------------------" << endl;
    cout << setw(15) << "Thank you for using our service!" << endl;

    stringstream ss; // Start of the receipt file system.
    ss << ++customer_counter;
    string customer_number;
    ss >> customer_number;
    ofstream file;
    string filename = "Receipt " + customer_number + ".txt";
    file.open("Receipt.txt");
    welcome_message(file);

    total_price = 0;

    file << endl;
    file << setfill('-') << setw(27) << "RECEIPT" << setw(28) << '\n' << setfill(' ');

    for (int i = 0; i < barcodes_pull.size(); i++)
        for (int j = 0; j < n; j++)
            if (barcodes_pull[i] == barcodes[j])
            {
                file << setw(20) << "Items" << setw(15) << "Barcodes" << setw(10) << "Price" << endl;
                file << setw(20) << products[j] << setw(15) << barcodes[j] << setw(10) << prices[j] << endl;
                total_price += prices[j];
            }
    file << endl;
    file << setw(20) << "Total transaction: " << total_price << endl; // Receipt to be printed in file.
    file << setw(20) << "Total cash paid: " << sum << endl;
    file << setw(20) << "Change: " << sum - total_price << endl;
    file << setw(15) << "------------------------------------------------------" << endl;
    file << setw(15) << "Thank you for using our service!" << endl;

    file.close(); // Attempt to making multiple receipts be saved.

}
void customer_payment(double price, vector <string> barcodes_pull)
{
    double sum = 0; // Sum of the user cash to be taken away from total price
    double user_cash = 0; // User inputted cash


    do // Start of do-while loop that processes entered cash of the user against the price. Returns change if need be.
    {
        if (price == 0)
            break;

        cout << "Please enter cash: "; // user prompt to start entering cash.
        cin >> user_cash; // where user enters cash input.
        if (user_cash <= 0) // if user cash is less than or equal to 0
            continue;
        sum += user_cash;

        if (sum < price) // If the user sum of cash is less than price will start a promt asking for more money.
            cout << "Cash amount needed: " << price - sum << endl; // promt asking for more money from the user if needed.
        else  cout << "Change due: " << sum - price << endl; // if the user enters more cash than the required amount then change to be received will be shown here.

    } while (sum < price);

    reciept(sum, barcodes_pull);
}


void barcode_search()
{
    vector <string> barcodes_pull;


    double price = 0; // Declaration for the price variable to be used in loops.
    string barcode = ""; // For the user inputted Barcode

    bool barcode_match = false;

    do // Start of a "do while" loop that asks the user to input a barcode.
    {
        barcode_match = false;
        cout << "Please enter Barcode (Type 'F' to finish):";// user prompt to start inputting barcodes.
        cin >> barcode;
        for (int i = 0; i < n; i++) // A for loop
            if (barcode == barcodes[i]) // If statement that links the inputted barcode/s with the ones stored in the array.

            {
                price += prices[i]; // This links the prices with the prices stored in the arrays.
                barcode_match = true;
                barcodes_pull.push_back(barcode);
                break; // Break from loop to progress to error tolerance.
            }
        if (barcode_match == false && barcode != "F") // If a correct barcode or "F" is not entered, error message will be printed below.
            cout << "Error, Barcode not found. Please try again!" << endl; // Error message if wrong input is detected.
    } while (barcode != "F");// Exit statement that when "F" is typed the loop is broken and a receipt is shown.

    cout << endl;// empty space to separate the total transaction price and the enter Barcode.
    cout << "Total transaction price: " << price << endl; // Total price of selected items is shown here.


    customer_payment(price, barcodes_pull);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool New_customer()
{


    char user_answer = ' ';

    do // Beginning of do_while loops to ask the user to move onto the next customer or not.
    {
        cout << "Continue(Y/N): "; // prompt asking the user to continue yes or no (Y/N)
        cin >> user_answer; // accepting user answer for conditions.
        if (user_answer != 'Y' && user_answer != 'N' && // Here, if the wrong character is used an error prompt will show.
            user_answer != 'y' && user_answer != 'n')
            cout << "Wrong answer. Please try again." << endl; // Error prompt.
    } while (user_answer != 'Y' && user_answer != 'N' &&
        user_answer != 'y' && user_answer != 'n');

    if (user_answer == 'Y' || user_answer == 'y')
        return true;
    else return false;


}

int main()
{
    do // Do while loop, used to take bool value from (New customer) to determine system ready for new customer.
    {
        welcome_message(); // Calling on the welcome message function
        barcode_search(); // calling on the barcode search function

    } while (New_customer()); // Calling on New customer function while taking value that is either True/false.
    // If true system loops back to start. If not program ends.

    return 0;
}