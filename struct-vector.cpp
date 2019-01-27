//============================================================================
// Version     : 1.0.190120
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>
#include <iomanip>

// FIXME (1): Reference the CSVParser library
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

struct Bid
{
    string title;
    string fund;
    double amount;
    Bid()
    {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid)
{
    cout << left << setw(52) << bid.title << " | " << left << setw(6) << bid.amount << " | " << left << setw(13) << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid()
{
    Bid bid;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath)
{
    // FIXME (2): Define a vector data structure to hold a collection of bids.
    vector<Bid> collectedBids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // loop to read rows of a CSV file
    for (int i = 0; i < file.rowCount(); ++i)
    {
        // FIXME (3): create a data structure to hold data from each row and add to vector
        collectedBids.push_back(Bid());
        collectedBids.at(i).title = file[i][0];
        collectedBids.at(i).fund = file[i][8];
        collectedBids.at(i).amount = strToDouble(file[i][4], '$');
    }
    return collectedBids;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch)
{
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char *argv[])
{
    // process command line arguments
    string csvPath;
    switch (argc)
    {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // FIXME (4): Define a vector to hold all the bids
    vector<Bid> allBids;

    // FIXME (7a): Define a timer variable
    clock_t start;

    int choice = 0;
    while (choice != 9)
    {
        cout << "\nMenu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\n*** SORRY: Not currently implemented. ***" << endl;
            break;
        case 2:
            // FIXME (7b): Initialize a timer variable before loading bids
            start = clock();
            // FIXME (5): Complete the method call to load the bids
            allBids = loadBids(csvPath);
            cout << "\n"
                 << allBids.size() << " bids read" << endl;
            // FIXME (7c): Calculate elapsed time and display result
            start = clock() - start;
            cout << "time: " << start << " clock ticks." << endl;
            cout << "time: " << start * 1.0 / CLOCKS_PER_SEC << " seconds." << endl;
            break;
        case 3:
            // FIXME (6): Loop and display the bids read
            cout << endl;
            if (allBids.size() == 0)
            {
                cout << "*** SORRY: No bids have been loaded. ***" << endl;
            }
            else
            {
                string str = string(84, '-');
                cout << str << endl;
                cout << setw(5) << left << "BID #"
                     << " | " << left << setw(52) << "TITLE"
                     << " | " << left << setw(6) << "AMOUNT"
                     << " | " << left << setw(13) << "FUND" << endl;
                cout << str << endl;
                for (unsigned int i = 0; i < allBids.size(); ++i)
                {
                    cout << " " << left << setw(4) << i + 1 << " | ";
                    displayBid(allBids.at(i));
                }
                cout << str << endl;
            }
            break;
        }
    }

    cout << "\nGood bye." << endl;

    return 0;
}
