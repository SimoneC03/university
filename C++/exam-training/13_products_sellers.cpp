#include <iostream>
#include <ctime>
#include <vector>

using std::cout, std::string, std::cin;

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
                price = stoi(input);
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

        Seller() : code(0), sold_products_total(0) {}

        Seller(const int code) : code(code), sold_products_total(0) {}

        Seller(const Seller &s) : code(s.code), sold_products(s.sold_products), sold_products_total(s.sold_products_total) {}

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
            os << "Sold products:\n";
            for(const Product *p : seller.sold_products) {
                os << *p;
            }
            return os;
        }

        ~Seller() {
            for (Product *p : sold_products) {
                delete p;
            }
        }
};

int main() {
    Seller s1, s2;
    s1.read();
    Product p1;
    FoodProduct p2;
    p1.read();
    p2.read();
    s1.addProduct(&p1);
    s1.addProduct(&p2);
    cout << "Seller 1 info" << s1;
    s2.read();
    FoodProduct p3;
    BabyProduct p4;
    p3.read();
    p4.read();
    s2.addProduct(&p3);
    s2.addProduct(&p4);
    cout << "Seller 2 info" << s2;

    return 0;
}