#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Drink {

public:
    Drink();
    friend istream &operator>>(istream &in, Drink &drink);
};

class Receipt {

public:
    Receipt();
    
    virtual ~Receipt();
    
    double calculateReceiptAmount () const;
    
    virtual double calculateTipAmount () const = 0;

    bool hasReceiptBeenPaid() const;

    friend istream &operator>>(istream &in, Receipt *slip);
};

class PubReceipt;

class ClubReceipt;

class Client {
    vector<Receipt *> receipts;

public:
    Client(vector<Receipt *> receipts);
    ~Client();

    double calculateTotalSuccessfullySpentMoney() const;
};

int main()
{
    vector<Receipt *> receipts;
    return 0;
}