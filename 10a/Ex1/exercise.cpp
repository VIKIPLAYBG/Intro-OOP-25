#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Drink {

    string name; //Mustn't be empty (Unless Default Constructor)
    double price; //Mustn't be negative

public:
    Drink() {
        this->name = "";
        this->price = 0;
    }
    
    friend istream &operator>>(istream &in, Drink &drink) {
        string line;
        getline(in, line);

        stringstream ss(line);

        string strName, strPrice;
        getline(ss, strName);
        getline(ss, strPrice);

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

        return in;
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

};

class Receipt {

    int id; //Must be positive
    double amount; //Mustn't be negative
    vector<Drink> drinks; //Size must be positive

public:
    Receipt() {
        this->id = 1;
        this->amount = 0;
        Drink drink;
        drinks.push_back(drink);
    }
    
    virtual ~Receipt() = default;
    
    double calculateReceiptAmount () const {
        double sum = 0;
        for(const auto d : drinks) {
            sum += d.getPrice();
        }
        return sum;
    }
    
    virtual double calculateTipAmount () const = 0;

    bool hasReceiptBeenPaid() const {
        double check = calculateReceiptAmount() + calculateTipAmount();
        return amount >= check;
    }

    friend istream &operator>>(istream &in, Receipt &slip) {
        string line;
        getline(in, line);

        stringstream ss(line);
        string strId, strAmount;

        getline(ss, strId);
        getline(ss, strAmount);

        stringstream ssId(strId), ssAmount(strAmount);

        int id, drinksAmount;
        double amount;
        vector<Drink> drinks;

        ssId >> id;
        ssAmount >> amount;

        if(id < 1)
            throw invalid_argument("(Receipt Operator>>) Id is invalid!");
        slip.id = id;

        if(amount < 0)
            throw invalid_argument("(Receipt Operator>>) Amount is invalid!");
        slip.amount = amount;

        in >> drinksAmount;
        if(drinksAmount <= 0)
            throw invalid_argument("(Receipt Operator>>) Drinks Amount is invalid!");
        slip.drinks.clear();
        
        for(size_t i = 0; i < drinksAmount; i++) {
            Drink d;
            in >> d;
            slip.drinks.push_back(d);
        }

        return in;
    }

    int getId() const {
        return id;
    }

    double getAmount() const {
        return amount;
    }

    vector<Drink> getDrinks() const {
        return drinks;
    }
};

class PubReceipt : public Receipt{
    double calculateTipAmount() const override {
        return 0.15 * calculateReceiptAmount();
    }
};

class ClubReceipt : public Receipt{
    double calculateTipAmount() const override {
        return 0.25 * calculateReceiptAmount();
    }
};

class Client {

    vector<Receipt *> receipts;

public:

    Client(vector<Receipt *> receipts) {
        this->receipts = receipts;
    }

    ~Client() {
        for(const auto r : receipts) {
            delete r;
        }
    }

    double calculateTotalSuccessfullySpentMoney() const {
        double totalMoney = 0;
        for(auto r : receipts) {
            if(r->hasReceiptBeenPaid()) {
                totalMoney += r->getAmount();
            }
        }
        return totalMoney;
    }
};

int main()
{
   
    vector<Receipt *> receipts;
    ifstream in("receipts.txt");
    if(!in.is_open()) 
        throw runtime_error("(Main) Cannot Open Input File!");
    
    string line;

    while(getline(in, line)) {
        if(line == "Pub" || line == "Club") {
            Receipt* r = nullptr;
            if(line == "Pub")
                r = new PubReceipt();
            else r = new ClubReceipt();
            try {
                in >> *r;
                receipts.push_back(r);
            } catch (exception &ex) {
                cerr << "Error! - " << ex.what() << endl;
                delete r;
            }
        }
    }

    in.close();

    Client me(receipts);

    cout << "Total successfully spent money: " << me.calculateTotalSuccessfullySpentMoney() << "BGN" << endl;

    return 0;
}