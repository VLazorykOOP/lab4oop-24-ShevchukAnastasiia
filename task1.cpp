#include <iostream>
#include <stdexcept>

class VectorLong {
private:
    long* data;
    size_t size;
    int codeError;
    static int objectCount;

public:
    // Конструктори
    VectorLong() : size(1), codeError(0) {
        data = new(std::nothrow) long[1]{0};
        if (!data) codeError = 1;
        objectCount++;
    }

    VectorLong(size_t n) : size(n), codeError(0) {
        data = new(std::nothrow) long[n]{0};
        if (!data) codeError = 1;
        objectCount++;
    }

    VectorLong(size_t n, long value) : size(n), codeError(0) {
        data = new(std::nothrow) long[n];
        if (!data) {
            codeError = 1;
        } else {
            for (size_t i = 0; i < n; ++i) data[i] = value;
        }
        objectCount++;
    }

    // Конструктор копіювання
    VectorLong(const VectorLong& other) : size(other.size), codeError(other.codeError) {
        data = new(std::nothrow) long[size];
        if (!data) {
            codeError = 1;
        } else {
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
        }
        objectCount++;
    }

    // Деструктор
    ~VectorLong() {
        delete[] data;
        objectCount--;
    }

    // Оператор присвоєння
    VectorLong& operator=(const VectorLong& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        codeError = other.codeError;
        data = new(std::nothrow) long[size];
        if (!data) {
            codeError = 1;
        } else {
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
        }
        return *this;
    }

    // Унарні оператори
    VectorLong& operator++() { for (size_t i = 0; i < size; ++i) ++data[i]; return *this; }
    VectorLong operator++(int) { VectorLong temp(*this); ++(*this); return temp; }

    VectorLong& operator--() { for (size_t i = 0; i < size; ++i) --data[i]; return *this; }
    VectorLong operator--(int) { VectorLong temp(*this); --(*this); return temp; }

    bool operator!() const { return size == 0; }

    VectorLong operator~() const {
        VectorLong result(*this);
        for (size_t i = 0; i < size; ++i) result.data[i] = ~data[i];
        return result;
    }

    VectorLong operator-() const {
        VectorLong result(*this);
        for (size_t i = 0; i < size; ++i) result.data[i] = -data[i];
        return result;
    }

    // Оператори +=, -=, *=, /=, %=, |=, ^=, &=
    VectorLong& operator+=(const VectorLong& other) {
        if (size != other.size) return *this;
        for (size_t i = 0; i < size; ++i) data[i] += other.data[i];
        return *this;
    }

    VectorLong& operator-=(const VectorLong& other) {
        if (size != other.size) return *this;
        for (size_t i = 0; i < size; ++i) data[i] -= other.data[i];
        return *this;
    }

    VectorLong& operator*=(long val) {
        for (size_t i = 0; i < size; ++i) data[i] *= val;
        return *this;
    }

    VectorLong& operator/=(long val) {
        for (size_t i = 0; i < size; ++i) data[i] /= val;
        return *this;
    }

    VectorLong& operator%=(long val) {
        for (size_t i = 0; i < size; ++i) data[i] %= val;
        return *this;
    }

    VectorLong& operator|=(const VectorLong& other) {
        if (size != other.size) return *this;
        for (size_t i = 0; i < size; ++i) data[i] |= other.data[i];
        return *this;
    }

    VectorLong& operator^=(const VectorLong& other) {
        if (size != other.size) return *this;
        for (size_t i = 0; i < size; ++i) data[i] ^= other.data[i];
        return *this;
    }

    VectorLong& operator&=(const VectorLong& other) {
        if (size != other.size) return *this;
        for (size_t i = 0; i < size; ++i) data[i] &= other.data[i];
        return *this;
    }

    // Бінарні арифметичні оператори
    friend VectorLong operator+(VectorLong a, const VectorLong& b) { return a += b; }
    friend VectorLong operator-(VectorLong a, const VectorLong& b) { return a -= b; }
    friend VectorLong operator*(VectorLong a, long val) { return a *= val; }
    friend VectorLong operator/(VectorLong a, long val) { return a /= val; }
    friend VectorLong operator%(VectorLong a, long val) { return a %= val; }

    // Бітові оператори
    friend VectorLong operator|(VectorLong a, const VectorLong& b) { return a |= b; }
    friend VectorLong operator^(VectorLong a, const VectorLong& b) { return a ^= b; }
    friend VectorLong operator&(VectorLong a, const VectorLong& b) { return a &= b; }

    // Введення / виведення
    friend std::istream& operator>>(std::istream& in, VectorLong& v) {
        for (size_t i = 0; i < v.size; ++i) in >> v.data[i];
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const VectorLong& v) {
        for (size_t i = 0; i < v.size; ++i) out << v.data[i] << " ";
        return out;
    }

    // Оператори порівняння
    bool operator==(const VectorLong& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i)
            if (data[i] != other.data[i]) return false;
        return true;
    }

    bool operator!=(const VectorLong& other) const { return !(*this == other); }

    bool operator>(const VectorLong& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i)
            if (data[i] <= other.data[i]) return false;
        return true;
    }

    bool operator>=(const VectorLong& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i)
            if (data[i] < other.data[i]) return false;
        return true;
    }

    bool operator<(const VectorLong& other) const { return other > *this; }
    bool operator<=(const VectorLong& other) const { return other >= *this; }

    // Оператор індексації
    long& operator[](size_t index) {
        if (index >= size) {
            codeError = 2;
            return data[size - 1];
        }
        return data[index];
    }

    // Виклик як функції
    void operator()() const {
        for (size_t i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }

    // Доступ до розміру та коду помилки
    size_t getSize() const { return size; }
    int getCodeError() const { return codeError; }
    static int getObjectCount() { return objectCount; }
};

// Ініціалізація статичної змінної
int VectorLong::objectCount = 0;

// --- Тестування ---
int main() {
    VectorLong v1(5, 10);
    VectorLong v2(5, 2);

    v1 += v2;
    v1();

    VectorLong v3 = v1 + v2;
    v3();

    std::cout << "Objects: " << VectorLong::getObjectCount() << std::endl;

    return 0;
}
