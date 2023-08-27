#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

using std::cout, std::string, std::cin, std::ifstream, std::ofstream;

bool isNumeric(const string);
/* Return whether a value is numeric or not */
bool isNumeric(const string s) {
    bool res = true;
    for(int i = 0; i < s.length(); i++) {
        if(isdigit(s[i]) == false && s[i] != '.') {
            res = false;
        }
    }
    return res;
}

class Product {
    protected:
        int code;
        double price;
        string name;
        std::time_t created_at;

    public:

        Product(const int code, const double price, const string &name): code(code), price(price), name(name), created_at(std::time(nullptr)) {}

        Product(): code(0), price(0), name("No name"), created_at(std::time(nullptr)) {}

        int getCode() const {
            return code;
        }

        double getPrice() const {
            return price;
        }

        void setCode(const int code) {
            this->code = code;
        }

        void setPrice(const double price) {
            this->price = price;
        }

        friend std::ostream &operator<<(std::ostream &os, const Product &product) {
            os << "\nProduct " << product.code << " info:\n";
            os << "Code: " << product.code << "\n";
            os << "Name: " << product.name << "\n";
            os << "Price: " << product.price << "€\n";
            os << "Created at: " << product.created_at << "\n";
            return os;
        }

        friend bool operator==(const Product &a, const Product &b) {
            return a.code == b.code;
        }

        void read() {
            string input;
            askforproductcode:
            cout << "Insert the product's code:";
            cin >> input;
            if(isNumeric(input)) {
                code = stoi(input);
            } else {
                cout << "The product's code must contain only numerical digits\n";
                goto askforproductcode;
            }
            cout << "Insert the product's name:";
            cin >> name;
            askforproductprice:
            cout << "Insert the product's price:";
            cin >> input;
            if(isNumeric(input)) {
                price = stod(input);
            } else {
                cout << "The product's price must contain only numerical digits\n";
                goto askforproductprice;
            }
            created_at = std::time(nullptr);
        }

        virtual ~Product() {}
};

class FoodProduct : public Product {
    protected:
        time_t expiry;
    
    public:

        void read() {
            Product::read();
            askforexpiry:
            cout << "Insert a valid expiry timestamp:\n";
            string input;
            cin >> input;
            if(isNumeric(input))
                expiry = stoi(input);
            else 
                goto askforexpiry;
        }

        /* Return true if product is not expired */
        bool verify() const {
            return std::time(nullptr) < expiry;
        }
};

class BabyProduct : public Product {
    protected:
        string age_range;
    
    public:

        BabyProduct() : Product(), age_range("0-3") {}

        BabyProduct(const int code, const double price, const string &name, const string &age_range) : Product(code, price, name), age_range(age_range) {}

        string getAgeRange() const {
            return age_range;
        }

        void setAgeRange(const string age_range) {
            this->age_range = age_range;
        }

        void read() {
            Product::read();
            cout << "Insert a valid product age range (0-3, 3-6, 6-9, 9-12): ";
            cin >> age_range;
        }

        friend std::ostream &operator<<(std::ostream &os, const BabyProduct &p) {
            os << static_cast<const Product &>(p) << "Age Range: " << p.age_range << "\n";
            return os;
        }
};

class Seller {
    protected:
        int code;
        std::vector<Product *> sold_products;
        int sold_products_total;
        string name;
    
    public:

        Seller() : code(0), sold_products_total(0), name("No name") {}

        Seller(const int code, const string &name) : code(code), sold_products_total(0), name(name) {}

        Seller(const Seller &s) : code(s.code), sold_products(s.sold_products), sold_products_total(s.sold_products_total), name(s.name) {}

        string getName() {
            return name;
        }

        int getCode() {
            return code;
        }

        /* Add all prices of sold products and return the sum */
        double getTotalPrice() {
            double total = 0;
            for(const Product *p : sold_products)
                total += p->getPrice();                
            return total;
        }

        /* Add all prices of sold products that has not expired yet and return the sum */
        double getTotalActivePrice() {
            double total = 0;
            for(const Product *p : sold_products) {
                const FoodProduct *foodp = dynamic_cast<const FoodProduct *>(p);
                if (foodp) {
                    if (foodp->verify()) {
                        total += foodp->getPrice();
                    }
                } else {
                    total += p->getPrice();
                }
            }
            return total;
        }

        void addProduct(Product *p) {
            sold_products.push_back(p);
        }

        void read() {
            string input;
            askforusercode:
            cout << "Insert the user's code: ";
            cin >> input;
            if(isNumeric(input)) {
                code = stoi(input);
            } else {
                cout << "The user's code must contain only numerical digits\n";
                goto askforusercode;
            }
            cout << "Insert the user's name: ";
            cin >> name;
        }

        friend std::ostream &operator<<(std::ostream &os, const Seller &seller) {
            os << "\nSeller " << seller.code << " info:\n";
            os << "Code: " << seller.code << "\n";
            os << "Name: " << seller.name << "\n";
            if(seller.sold_products.size() > 0) {
                os << "Sold products:\n";
                for(const Product *p : seller.sold_products) {
                    os << *p;
                }
            } else {
                os << "Sold products: none\n";
            }
            return os;
        }

        ~Seller() {
            for (Product *p : sold_products) {
                delete p;
            }
        }
};

void readData(std::vector<Seller> *sellers);
/* Load all the saved sellers and products data from the disk */
void readData(std::vector<Seller> *sellers) {
    string delimiter = ";"; // separator char
    string line;
    ifstream sellersF("13_ex_sellers.txt");
    if (sellersF.is_open()) {
        while ( getline (sellersF,line) ) {
            if(line.length() > 0) {
                string code = line.substr(0, line.find(delimiter));
                string name = line.substr(line.find(delimiter)+1, line.length());
                Seller *s = new Seller(stoi(code), name);
                sellers->push_back(*s);
            }
        }
        sellersF.close();
    } else {
        // create sellers file
        ofstream sellersF;
        sellersF.open("13_ex_sellers.txt");
        sellersF.close();
    }
    ifstream productsF("13_ex_products.txt");
    if (productsF.is_open()) {
        while ( getline (productsF,line) ) {
            string code = line.substr(0, line.find(delimiter));
            line = line.substr(line.find(delimiter)+1, line.length());
            string name = line.substr(0, line.find(delimiter));
            line = line.substr(line.find(delimiter)+1, line.length());
            string price = line.substr(0, line.find(delimiter));
            string seller_code = line.substr(line.find(delimiter)+1, line.length());
            cout << "selelr nme" << (*sellers)[0].getName();
            for(int i = 0; i < sellers->size(); i++) {
                if((*sellers)[i].getCode() == stoi(seller_code)) {
                    Product *p = new Product(stoi(code), stod(price), name);
                    (*sellers)[i].addProduct(p);
                }
            }
        }
        productsF.close();
    } else {
        // create products file
        ofstream productsF;
        productsF.open("13_ex_products.txt");
        productsF.close();
    }
}

int main() {
    std::vector<Seller> sellers;
    readData(&sellers);
    string input;
    askforoption:
    cout << "\n1 - Add a seller\n";
    cout << "2 - Add a product\n";
    cout << "3 - Print sellers info\n";
    cout << "4 - Print the total of sold products ascending\n";
    cout << "5 - Print the total of sold products descending\n";
    cout << "\n0 - Exit from program\n";
    cin >> input;
    if(isNumeric(input)) {
        switch (stoi(input)) {
            case 0:
                /* Exit */
                exit(0);
                break;
            case 1: {
                /* Add a seller */
                string name;
                cout << "Insert the seller's name: ";
                cin >> name;
                Seller s(sellers.size()+1, name);
                sellers.push_back(s);
                cout << "New seller added!\n";
                break;
            }
            case 2: {
                /* Add a product */
                if(sellers.size() == 0) {
                    cout << "Add at least a seller before.\n";
                    break;
                }
                cout << "Who do you want to add a product to? (enter a number)\n";
                for(int i = 0; i < sellers.size(); i++) {
                    cout << i << " - " << sellers[i].getName() << "[" << sellers[i].getCode() << "]\n";
                }
                string seller;
                cin >> seller;
                if(isNumeric(seller)) {
                    Product *p = new Product();
                    p->read();
                    sellers[stoi(seller)].addProduct(p);
                } else {
                    cout << "Invalid number.\n";
                }
                break;
            }
            case 3: {
                /* Print sellers info */
                for(const Seller &s : sellers) {
                    cout << s << "\n\n";
                }
                break;
            }
            case 4: {
                /* Print sellers total ascending */
                std::vector<int> indexes;
                for(int i = 0; i < sellers.size(); i++)
                    indexes.push_back(i);
                for(int i = 0; i < sellers.size(); i++) {
                    for(int j = 0; j < sellers.size() - 1 - i; j++) {
                        if(sellers[indexes[j]].getTotalPrice() > sellers[indexes[j+1]].getTotalPrice()) {
                            int temp = indexes[j];
                            indexes[j] = indexes[j+1];
                            indexes[j+1] = temp;
                        }
                    }
                }
                cout << "Total of sold products ascending:\n";
                for(int i = 0; i < indexes.size(); i++) {
                    cout << i+1 << " - " << sellers[indexes[i]].getName() << " (" << sellers[indexes[i]].getTotalPrice() << "€)\n";
                }
                break;
            }
            case 5: {
                /* Print sellers total descending */
                std::vector<int> indexes;
                for(int i = 0; i < sellers.size(); i++)
                    indexes.push_back(i);
                for(int i = 0; i < sellers.size(); i++) {
                    for(int j = 0; j < sellers.size() - 1 - i; j++) {
                        if(sellers[indexes[j]].getTotalPrice() < sellers[indexes[j+1]].getTotalPrice()) {
                            int temp = indexes[j];
                            indexes[j] = indexes[j+1];
                            indexes[j+1] = temp;
                        }
                    }
                }
                cout << "Total of sold products descending:\n";
                for(int i = 0; i < indexes.size(); i++) {
                    cout << i+1 << " - " << sellers[indexes[i]].getName() << " (" << sellers[indexes[i]].getTotalPrice() << "€)\n";
                }
                break;
            }
            default:
                break;
        }
        goto askforoption;
    } else {
        cout << "Invalid option\n";
        goto askforoption;
    }
    
    return 0;
}