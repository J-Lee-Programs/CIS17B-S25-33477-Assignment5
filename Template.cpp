#include <iostream>
#include <string>
#include <array>
#include <typeinfo>

//developer checklist:
//created template T with package & label [X]
//specialized package [X]
//partial specialization [X]
//box template/class [X]
//function template specializations [X]

template<typename T>
class Package {
private:
    T item;
public:
    Package(T i) : item(i) {}
    void label() {
        std::cout << "Generic package containing: " << typeid(T).name() << "\n";
    }
};

// Specialization for std::string
template<>
class Package<std::string> {
private:
    std::string item;
public:
    Package(std::string i) : item(i) {}
    void label() {
        std::cout << "Book package: \"" << item << "\"\n";
    }
};

// Partial specialization for pointers
template<typename T>
class Package<T*> {
private:
    T* item;
public:
    Package(T* i) : item(i) {}
    void label() {
        std::cout << "Fragile package for pointer to type: " << typeid(T).name() << "\n";
    }
};

template<typename T, int Size>
class Box {
private:
    std::array<T, Size> items;
    int count = 0;
public:
    bool addItem(const T& item) {
        if (count < Size) {
            items[count++] = item;
            std::cout << "Added item to box: \"" << item << "\"\n";
            return true;
        }
        return false;
    }

    void printItems() const {
        std::cout << "Box contents:\n";
        for (int i = 0; i < count; ++i) {
            std::cout << " - " << items[i] << "\n";
        }
    }
};

template<typename T>
void shipItem(const T& item) {
    std::cout << "Shipping item of type: " << typeid(T).name() << "\n";
}

template<>
void shipItem(const double& item) {
    std::cout << "Shipping temperature-controlled item: " << item << "°C\n";
}

int main() {
    Package<int> intData(23);
    Package<std::string> stringData("The programmer's guide");
    Package<double*> doubleData(NULL);

    Box<std::string, 3> Box;


    intData.label();
    stringData.label();
    doubleData.label();

    Box.addItem("The book");
    Box.addItem("Langrange's Bounds");
    Box.addItem("La Circle");

    Box.printItems();

    shipItem(intData);
    shipItem(stringData);
    shipItem(doubleData);

    shipItem(19.7);
    shipItem(23.1);
    shipItem(20.6);


    return 0;
}