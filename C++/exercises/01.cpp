#include <iostream>
#include <ctime>

using std::cout, std::cin, std::string;

bool isNumeric(string &s) {
    for(int i = 0; i < s.length(); i++) {
        if(isdigit(s[i]) == false && s[i] != '.') return false;
    }
    return true;
}

int getRandom(int min, int max) {
    timeval time;
    srand(time.tv_usec + (rand()%10000));
    return (rand() % (max-min)) + min;
}


class Citizen {
    protected:
        string name, lastname, city;
        int salary;

    public:
        Citizen() {}

        Citizen(string &name, string &lastname, string &city, int salary) : name(name), lastname(lastname), city(city), salary(salary) {}

        friend std::ostream &operator<<(std::ostream &os, Citizen *citizen) {
            os << "Name: " << citizen->name << " " << citizen->lastname << "\n"
                << "City: " << citizen->city << "\n"
                << "Salary/pension: " << citizen->salary << "\n"; 
            return os;
        }

        virtual ~Citizen() = default;

};

class Student : public Citizen {
    private:
        int age; 
    public:
        Student() {}

        Student(string &name, string &lastname, string &city, int salary) : Citizen(name,lastname,city,salary), age(getRandom(6,25)) {}

        int getAge() {
            return age;
        }

        friend std::ostream &operator<<(std::ostream &os, Student *student) {
            os << static_cast<Citizen *>(student) << "Age: " << student->getAge() << "\nType: Student.\n";;
            return os;
        }
};

class Worker : public Citizen {
    private:
        int age; 
    public:
        Worker() {}

        Worker(string &name, string &lastname, string &city, int salary) : Citizen(name,lastname,city,salary), age(getRandom(18,70)) {}

        int getAge() {
            return age;
        }

        friend std::ostream &operator<<(std::ostream &os, Worker *worker) {
            os << static_cast<Citizen *>(worker) << "Age: " << worker->getAge() << "\nType: Worker.\n";
            return os;
        }
};

class Pensioner : public Citizen {
    private:
        int age; 
    public:
        Pensioner() {}

        Pensioner(string &name, string &lastname, string &city, int salary) : Citizen(name,lastname,city,salary), age(getRandom(65,90)) {}

        int getAge() {
            return age;
        }

        friend std::ostream &operator<<(std::ostream &os, Pensioner *pensioner) {
            os << static_cast<Citizen *>(pensioner) << "Age: " << pensioner->getAge() << "\nType: Pensioner.\n";
            return os;
        }
};

template<typename T>
struct Node {
    T value;
    Node<T> *next;
};

template <typename T>
class SortedList {
    public:
        Node<T> *head;

        SortedList() : head(nullptr) {}

        /* Push neatly a new node */
        void push(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            if(head == nullptr) {
                head = newNode;
                return;
            }
            // Age compare if `value` is a Citizen's subclass
            Student *s = dynamic_cast<Student *>(value);
            Worker *w = dynamic_cast<Worker *>(value);
            Pensioner *p = dynamic_cast<Pensioner *>(value);
            Student *sTemp = dynamic_cast<Student *>(head->value);
            Worker *wTemp = dynamic_cast<Worker *>(head->value);
            Pensioner *pTemp = dynamic_cast<Pensioner *>(head->value);
            if((s != nullptr || w != nullptr || p != nullptr) && (sTemp != nullptr || wTemp != nullptr || pTemp != nullptr)) {
                int valueAge = (s!=nullptr) ? s->getAge() : (w != nullptr) ? w->getAge() : p->getAge();
                int tempAge = (sTemp!=nullptr) ? sTemp->getAge() : (wTemp != nullptr) ? wTemp->getAge() : pTemp->getAge();
                if(valueAge <= tempAge) {
                    newNode->next = head;
                    head = newNode;
                    return;
                }
            } else {
               if(value <= head->value) {
                    newNode->next = head;
                    head = newNode;
                    return;
                } 
            }
            Node<T> *current = head;
            while(current->next != nullptr) {
                Student *sTemp = dynamic_cast<Student *>(current->next->value);
                Worker *wTemp = dynamic_cast<Worker *>(current->next->value);
                Pensioner *pTemp = dynamic_cast<Pensioner *>(current->next->value);
                if((s != nullptr || w != nullptr || p != nullptr) && (sTemp != nullptr || wTemp != nullptr || pTemp != nullptr)) {
                    int valueAge = (s!=nullptr) ? s->getAge() : (w != nullptr) ? w->getAge() : p->getAge();
                    int tempAge = (sTemp!=nullptr) ? sTemp->getAge() : (wTemp != nullptr) ? wTemp->getAge() : pTemp->getAge();
                    if(valueAge <= tempAge) {
                        newNode->next = current->next;
                        current->next = newNode;
                        return;
                    }
                } else {
                    if(value <= current->next->value) {
                        newNode->next = current->next;
                        current->next = newNode;
                        return;
                    }
                }
                current = current->next;
            }
            current->next = newNode;
        }

        friend std::ostream &operator<<(std::ostream &os, SortedList<T> &l) {
            int i = 0;
            for(Node<T> *current = l.head; current != nullptr; current = current->next) {
                Student *sTemp = dynamic_cast<Student *>(current->value);
                Worker *wTemp = dynamic_cast<Worker *>(current->value);
                Pensioner *pTemp = dynamic_cast<Pensioner *>(current->value);
                if(sTemp != nullptr) {
                    os << (i+1) << " - " << sTemp << "\n";
                } else if(wTemp != nullptr) {
                    os << (i+1) << " - " << wTemp << "\n";
                } else if(pTemp != nullptr) {
                    os << (i+1) << " - " << pTemp << "\n";
                } else {
                    os << (i+1) << " - " << current->value << "\n";
                }
                i++;
            }
            return os;
        }
};

class CitizenManagement {
    public:

        void main() {
            SortedList<Citizen *> citizens;
            // insert citizens
            cout << "How many citizen do you want to create?\n";
            string input;
            cin >> input;
            if(isNumeric(input)) {
                // create citizens
                for(int i = 0; i < abs(stoi(input)); i++) {
                    string names[] = {"Mark", "Liam", "James", "Emma", "Amelia"};
                    string lastnames[] = {"Smith", "Jones", "Davis", "Williams", "Johnson"};
                    string cities[] = {"Washington", "Springfield", "Georgetown", "Centerville"};
                    int type = getRandom(1,3);
                    if(type == 1) {
                        Student *s = new Student(names[getRandom(0,4)], lastnames[getRandom(0,4)], cities[getRandom(0,3)], 0);
                        citizens.push(s);
                    } else if(type == 2) {
                        Worker *s = new Worker(names[getRandom(0,4)], lastnames[getRandom(0,4)], cities[getRandom(0,3)], getRandom(20000, 100000));
                        citizens.push(s);
                    } else {
                        Pensioner *s = new Pensioner(names[getRandom(0,4)], lastnames[getRandom(0,4)], cities[getRandom(0,3)], getRandom(4000, 10000));
                        citizens.push(s);
                    }
                }
                cout << "Citizens created:\n";
                // filter by age
                cout << citizens;
                cout << "\nPlease, enter a numeric value to filter citizens age: ";
                cin >> input;
                if(isNumeric(input)) {
                    int students = 0;
                    int workers = 0;
                    int pensioners = 0;
                    cout << "Citizens under " << input << ":\n";
                    for(Node<Citizen *> *current = citizens.head; current != nullptr; current = current->next) {
                        Student *sTemp = dynamic_cast<Student *>(current->value);
                        Worker *wTemp = dynamic_cast<Worker *>(current->value);
                        Pensioner *pTemp = dynamic_cast<Pensioner *>(current->value);
                         if(sTemp != nullptr && sTemp->getAge() <= stoi(input)) {
                            cout << sTemp << "\n";
                            students++;
                        } else if(wTemp != nullptr && wTemp->getAge() <= stoi(input)) {
                            cout << wTemp << "\n";
                            workers++;
                        } else if(pTemp != nullptr && pTemp->getAge() <= stoi(input)) {
                            cout << pTemp << "\n";
                            pensioners++;
                        }
                    }
                    cout << "Total of students: " << students << "\n";
                    cout << "Total of workers: " << workers << "\n";
                    cout << "Total of pensioners: " << pensioners << "\n";
                } else {
                    cout << "Invalid number.\n";
                }
            } else {
                cout << "Invalid number.\n";
            }
        }
};

int main() {
    CitizenManagement m;
    m.main();
    return 0;
}