#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Drink {

    string name; //Mustn't be empty
    double price; //Mustn't be negative

public:
    Drink() {
        name = "";
        price = 0;
    }

    friend istream &operator>>(istream &in, Drink &drink) {
        string buffer;
        getline(in, buffer);

        cout << buffer << endl;
        buffer = buffer.substr(1, buffer.size()-2);
        cout << buffer << endl;
        
        stringstream ss(buffer);

        string strName, strPrice;

        getline(ss, strName, ',');
        getline(ss, strPrice, ',');

        cout << strName << endl;
        cout << strPrice << endl;
        stringstream ssName(strName), ssPrice(strPrice);

        string name;
        double price;

        ssName >> name;
        ssPrice >> price;

        if(name.empty())
            throw invalid_argument("(Drink Operator>>) Name is empty!");
        drink.name = name;

        if(price < 0)
            throw invalid_argument("(Drink Operator>>) Price is invalid!");
        drink.price = price;

        in >> name;
        in >> price;
        return in;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }
};

class Receipt {

    int id; //Must be positive
    double amount; //Mustn't be negative
    vector<Drink> drinks; //Size must be positive

public:
    Receipt() {
        id = 1;
        amount = 0;
        drinks.resize(1);
    }
    
    virtual ~Receipt();
    
    double calculateReceiptAmount () const {
        double cash = 0;
        for(auto drink: drinks) {
            cash += drink.getPrice();
        }
        return cash;
    }
    
    virtual double calculateTipAmount () const = 0;

    bool hasReceiptBeenPaid() const {
        if(amount >= calculateReceiptAmount()) return true;
        else return false;
    }

    friend istream &operator>>(istream &in, Receipt *slip) {
        string line;
        getline(in, line);

        stringstream ss(line);

        string strId, strAmount, strDrinks;
        getline(ss, strId, ',');
        getline(ss, strAmount, ',');
        getline(ss, strDrinks, ',');

        stringstream ssId(strId), ssAmount(strAmount), ssDrinks(strDrinks);

        int id;
        double amount;
        vector<Drink> drinks;

        if(id < 1)
            throw invalid_argument("Id is invalid!");
        if(amount < 0)
            throw invalid_argument("Amount is invalid!");
        if(drinks.size() < 1)
            throw invalid_argument("Drinks Size is invalid!");

        // ssId >> id;
        // ssAmount >> amount;
        // ssDrinks >> drinks;

        slip->id = id;
        slip->amount = amount;
        slip->drinks = drinks;

        return in;
    }
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