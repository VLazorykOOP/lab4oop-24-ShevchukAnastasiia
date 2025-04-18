#include <iostream>
#include <string>
#include <vector>

// Клас Person
class Person {
public:
    std::string surname;
    std::string firstName;
    std::string middleName;

    Person() = default;

    Person(const std::string& s, const std::string& f, const std::string& m)
        : surname(s), firstName(f), middleName(m) {}
};

// Оператор виводу для Person
std::ostream& operator<<(std::ostream& os, const Person& person) {
    return os << person.surname << " " << person.firstName << " " << person.middleName;
}

// Оператор вводу для Person
std::istream& operator>>(std::istream& is, Person& person) {
    return is >> person.surname >> person.firstName >> person.middleName;
}

// Клас асоціативного масиву
class AssocArray {
private:
    std::vector<std::string> emails;
    std::vector<Person> people;
    int errorCode = 0;

public:
    void add(const std::string& email, const Person& person) {
        emails.push_back(email);
        people.push_back(person);
    }

    Person& operator[](const std::string& email) {
        for (size_t i = 0; i < emails.size(); ++i) {
            if (emails[i] == email) {
                errorCode = 0;
                return people[i];
            }
        }
        errorCode = 1;
        static Person empty;
        return empty;
    }

    Person& operator()(const std::string& email) {
        return (*this)[email];
    }

    int getErrorCode() const { return errorCode; }

    friend std::ostream& operator<<(std::ostream& os, const AssocArray& assoc);
    friend std::istream& operator>>(std::istream& is, AssocArray& assoc);
};

// Оператор виводу для AssocArray
std::ostream& operator<<(std::ostream& os, const AssocArray& assoc) {
    for (size_t i = 0; i < assoc.emails.size(); ++i) {
        os << assoc.emails[i] << " -> " << assoc.people[i] << "\n";
    }
    return os;
}

// Оператор вводу для AssocArray
std::istream& operator>>(std::istream& is, AssocArray& assoc) {
    std::string email;
    Person person;
    std::cout << "Enter email: ";
    is >> email;
    std::cout << "Enter full name (Surname FirstName MiddleName): ";
    is >> person;
    assoc.add(email, person);
    return is;
}

// Тестування
void testAssocArray() {
    AssocArray assoc;

    assoc.add("john.doe@example.com", Person("Doe", "John", "Michael"));
    assoc.add("jane.smith@example.com", Person("Smith", "Jane", "Elizabeth"));

    Person& p = assoc["john.doe@example.com"];
    if (assoc.getErrorCode() == 0) {
        std::cout << "Found: " << p << "\n";
    } else {
        std::cout << "Email not found.\n";
    }

    Person& p2 = assoc("jane.smith@example.com");
    std::cout << "Lookup using (): " << p2 << "\n";

    Person& p3 = assoc["no.email@example.com"];
    if (assoc.getErrorCode()) {
        std::cout << "Email not found. Error code: " << assoc.getErrorCode() << "\n";
    }

    std::cout << "\nAll entries:\n" << assoc;
}

int main() {
    testAssocArray();

    AssocArray assoc;
    std::cin >> assoc;
    std::cout << assoc;

    return 0;
}
