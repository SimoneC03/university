#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Pet {

    private:
        string name;

    public:
        Pet(const string &name) {
            this->name = name;
        }

        friend ostream &operator<<(ostream &os, const Pet &pet) {
            os << "Pet's name: " << pet.name;
            return os;
        }
};

class Person {

    private:
        string name;
        std::vector<Pet> pets;

    public:
        Person(const string &name) {
            this->name = name;
        }

        void addPet(const Pet &pet) {
            pets.push_back(pet);
        }
        
        friend ostream &operator<<(ostream &os, const Person &p) {
            os << "Person: " << p.name << endl;
            os << "Pets: " << endl;
            for (const Pet& pet : p.pets) {
                os << pet << "\n";
            }
            return os;
        }      
};


int main() {
    Person person1("Alice");
    Person person2("Bob");
    person1.addPet(Pet("Nando"));
    person1.addPet(Pet("Aron"));
    person2.addPet(Pet("Max"));
    std::cout << person1 << "\n";
    std::cout << person2 << "\n";
    return 0;
}