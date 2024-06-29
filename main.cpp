#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <map>

using namespace std;

class Transaction {
public:
string accountName;
double amount;
char entryType;
string transactionDate;

Transaction(const string& name, double amt, char type, const string& date)
: accountName(name), amount(amt), entryType(type), transactionDate(date) {}
};

class Ledger {
private:
map<string, double> accountBalances;

public:
void updateLedger(const string& name, double amount, char entryType) {
if (entryType == 'D') {
accountBalances[name] += amount;
} else if (entryType == 'C') {
accountBalances[name] -= amount;
}
}

void printLedgerToFile(const string& fileName) const {
ofstream outFile(fileName);

if (outFile.is_open()) {
outFile << "\nAccount Ledger:\n";
outFile << left << setw(20) << "Account Name" << setw(15) << "Balance" << endl;
outFile << string(35, '-') << endl;
for (const auto& entry : accountBalances) {
outFile << left << setw(20) << entry.first << setw(15) << entry.second << endl;
}
outFile.close();
cout << "Ledger printed to " << fileName << " successfully.\n";
} else {
cerr << "Unable to open the file " << fileName << " for writing.\n";
}
}
};

class FinancialJournal {
private:
vector<Transaction> transactions;
Ledger ledger;

public:
void addTransaction(const string& name, double amt, char type, const string& date) {
transactions.push_back(Transaction(name, amt, type, date));
ledger.updateLedger(name, amt, type);
sort(transactions.begin(), transactions.end(),
[](const Transaction& a, const Transaction& b) { return a.transactionDate <
b.transactionDate; });
}

void printJournalToFile(const string& fileName) const {
ofstream outFile(fileName);

if (outFile.is_open()) {
outFile << left << setw(12) << "Date" << setw(20) << "Particular" << setw(12) <<
"Debit" << "Credit\n";
string currentDate;
for (const auto& transaction : transactions) {
if (transaction.transactionDate != currentDate) {
outFile << left << setw(12) << transaction.transactionDate;
currentDate = transaction.transactionDate;
} else {

outFile << setw(12) << "";
}

outFile << setw(20) << transaction.accountName;

if (transaction.entryType == 'D') {
outFile << setw(12) << transaction.amount << setw(12) << "" << endl;
} else {
outFile << setw(12) << "" << setw(12) << transaction.amount << endl;
}
}

outFile.close();
cout << "Journal printed to " << fileName << " successfully.\n";
} else {
cerr << "Unable to open the file " << fileName << " for writing.\n";
}
}

void printLedgerToFile(const string& fileName) const {
ledger.printLedgerToFile(fileName);
}
};

int getMin(int arr[], int N) {
int minInd = 0;

for (int i = 1; i < N; i++)
if (arr[i] < arr[minInd])
minInd = i;
return minInd;
}

int getMax(int arr[], int N) {
int maxInd = 0;
for (int i = 1; i < N; i++)
if (arr[i] > arr[maxInd])
maxInd = i;
return maxInd;
}

int minOf2(int x, int y) { return (x < y) ? x : y; }

void minCashFlowRec(int amount[], int N) {
int mxCredit = getMax(amount, N), mxDebit = getMin(amount, N);

if (amount[mxCredit] == 0 && amount[mxDebit] == 0)
return;

int min = minOf2(-amount[mxDebit], amount[mxCredit]);
amount[mxCredit] -= min;
amount[mxDebit] += min;

cout << "Person " << mxDebit << " pays " << min
<< " to "
<< "Person " << mxCredit << endl;

minCashFlowRec(amount, N);
}

void minCashFlow(int graph[][3], int N) {
int amount[N] = { 0 };

for (int p = 0; p < N; p++)
for (int i = 0; i < N; i++)
amount[p] += (graph[i][p] - graph[p][i]);

minCashFlowRec(amount, N);
}

struct StockData {
int buyDay;
int sellDay;
int profit;
};

StockData findMaxProfit(int prices[], int start, int end) {
if (start == end) {
return {start, start, 0};

}

int mid = (start + end) / 2;

StockData leftProfit = findMaxProfit(prices, start, mid);
StockData rightProfit = findMaxProfit(prices, mid + 1, end);

int minPrice = prices[start];
int maxPrice = prices[mid + 1];
int maxCrossingProfit = 0;
int buyDay = start;
int sellDay = mid + 1;

for (int i = mid + 1; i <= end; i++) {
if (prices[i] > maxPrice) {
maxPrice = prices[i];
sellDay = i;
}
}

for (int i = mid; i >= start; i--) {
if (prices[i] < minPrice) {
minPrice = prices[i];
buyDay = i;
}
}

maxCrossingProfit = maxPrice - minPrice;

if (leftProfit.profit >= rightProfit.profit && leftProfit.profit >= maxCrossingProfit) {
return leftProfit;
} else if (rightProfit.profit >= leftProfit.profit && rightProfit.profit >=
maxCrossingProfit) {
return rightProfit;
} else {
return {buyDay, sellDay, maxCrossingProfit};
}
}

int main() {
int choice;
do {
cout<<setw(35)<<" --------------------------------------"<<endl;
cout <<setw(34)<< "MUNEEM\n";
cout<<setw(35)<<" --------------------------------------"<<endl;
cout << "Choose an option:\n";
cout << "1. Financial Journal\n";
cout << "2. Minimum Cash Flow\n";
cout << "3. Stock Price Profit Calculation\n";
cout << "4. Exit\n";
cout << "Enter your choice: ";
cin >> choice;

switch (choice) {
case 1: {
cout << "Financial Journal\n";

FinancialJournal journal;

string account1, account2, transactionDate;
double amount;
char entryType1, entryType2, continueInput;

do {
cout << "Enter Transaction Date (YYYY-MM-DD): ";
cin >> transactionDate;

cout << "Enter First Account Name (e.g., Cash): ";
cin.ignore();
getline(cin, account1);

cout << "Is this account Debit or Credit? (D for Debit, C for Credit): ";
cin >> entryType1;
// Validate entry type for account 1
while (entryType1 != 'D' && entryType1 != 'C') {
cout << "Invalid entry type. Please enter 'D' for Debit or 'C' for Credit: ";
cin >> entryType1;
}

cout << "Enter Second Account Name (e.g., Capital): ";
cin.ignore();
getline(cin, account2);

cout << "Is this account Debit or Credit? (D for Debit, C for Credit): ";
cin >> entryType2;
// Validate entry type for account 2
while (entryType2 != 'D' && entryType2 != 'C') {
cout << "Invalid entry type. Please enter 'D' for Debit or 'C' for Credit: ";
cin >> entryType2;
}

cout << "Enter Amount: ";
cin >> amount;

// Add the transactions based on the user's inputs
journal.addTransaction(account1, amount, entryType1, transactionDate);
journal.addTransaction(account2, amount, entryType2, transactionDate);

cout << "Do you want to add another transaction? (y/n): ";
cin >> continueInput;

} while (continueInput == 'y' || continueInput == 'Y');

journal.printJournalToFile("FinancialJournal.txt");
journal.printLedgerToFile("Ledger.txt");

break;
}

case 2: {
cout << "Minimum Cash Flow\n";

int cashflow_arr[3][3] = {
{ 0, 1000, 2000 },
{ 0, 0, 5000 },
{ 0, 0, 0 },
};

minCashFlow(cashflow_arr, 3);
break;
}

case 3: {
cout << "Stock Price Profit Calculation\n";

int n;
cout << "Enter the number of days: ";
cin >> n;

int prices[n];
cout << "Enter the stock prices for each day:\n";
for (int i = 0; i < n; i++) {

cin >> prices[i];
}

StockData result = findMaxProfit(prices, 0, n - 1);

cout << "Buy on day " << result.buyDay + 1 << ", sell on day " << result.sellDay +
1

<< " for a maximum profit of " << result.profit << endl;
break;
}

case 4:
cout << "Exiting...\n";
break;

default:
cout << "Invalid choice. Please try again.\n";
}
} while (choice != 4);

return 0;
}