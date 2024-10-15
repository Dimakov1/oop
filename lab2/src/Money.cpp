#include "../include/Money.h"
#include <stdexcept>
#include <utility>

void Money::fromString(const std::string& str) {
    digits.clear();
    bool hasDecimalPoint = false;
    int decimalCount = 0;
    int digitCountBeforePoint = 0; 

    for (int i = str.size() - 1; i >= 0; --i) {
    
        if (str[i] == '.') {
            if (hasDecimalPoint) {
                throw std::invalid_argument("Неверный формат строки: более одной точки.");
            }
            hasDecimalPoint = true;
            continue;
        }

        if(!hasDecimalPoint){
            ++digitCountBeforePoint;
        }

        if (str[i] >= '0' && str[i] <= '9') {
            digits.push_back(str[i] - '0');
            if (hasDecimalPoint) {
                ++decimalCount; 
            }
        } else {
            throw std::invalid_argument("Неверный символ в строке.");
        }
    }

    if (digitCountBeforePoint > 2 && hasDecimalPoint) {
        throw std::invalid_argument("Неверный формат строки: слишком много знаков после точки.");
    }

    if (hasDecimalPoint && digitCountBeforePoint == 1) {
        digits.insert(digits.begin(), 0); 
    }

    if (!hasDecimalPoint) {
        digits.insert(digits.begin(), 0); 
        digits.insert(digits.begin(), 0);
    }

    while (digits.size() < 3) {
        digits.push_back(0);
    }
}





void Money::removeLeadingZeros() {
    while (digits.size() > 3 && digits.back() == 0) {
        digits.pop_back();
    }
}

Money::Money() : digits{0, 0, 0} {}

Money::Money(const size_t& n, unsigned char t) : digits(n, t) {
    if (n < 3) throw std::invalid_argument("Минимальный размер — 3 (для рублей и копеек).");
}

Money::Money(const std::initializer_list<unsigned char>& t) : digits(t) {
    if (digits.size() < 3) throw std::invalid_argument("Минимум 3 цифры.");
}

Money::Money(const std::string& str) {
    fromString(str);
}

Money::Money(const Money& other) : digits(other.digits) {}

Money::Money(Money&& other) noexcept : digits(std::move(other.digits)) {
    other.digits = {0, 0, 0};
}

Money& Money::operator=(const Money& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

Money& Money::operator=(Money&& other) noexcept {
    if (this != &other) {
        digits = std::move(other.digits);
        other.digits = {0, 0, 0}; 
    }
    return *this;
}

Money::~Money() noexcept = default;

void Money::print() const {
    if (digits.empty()) {
        std::cout << "Сумма: 0.00\n";
        return;
    }
    std::cout << "Сумма: ";
    for (int i = digits.size() - 1; i >= 0; --i) {
        std::cout << static_cast<int>(digits[i]);
        if (i == 2) std::cout << '.';
    }
    std::cout << '\n';
}

Money Money::operator+(const Money& other) const {
    Money result;
    size_t max_size = std::max(this->digits.size(), other.digits.size());
    result.digits.resize(max_size, 0);

    unsigned char carry = 0;
    for (size_t i = 0; i < max_size; ++i) {
        unsigned char a_digit = (i < this->digits.size()) ? this->digits[i] : 0;
        unsigned char b_digit = (i < other.digits.size()) ? other.digits[i] : 0;
        unsigned char sum = a_digit + b_digit + carry;
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry > 0) {
        result.digits.push_back(carry);
    }

    return result;
}

Money Money::operator-(const Money& other) const {
    Money result = *this; 
    if(result.digits.size() >= other.digits.size()){
        for (size_t i = 0; i < result.digits.size(); ++i) {
            if (i >= other.digits.size()) {
                continue;
            }

            if (result.digits[i] < other.digits[i]) {
                size_t borrowIndex = i + 1;
                while (borrowIndex < result.digits.size() && result.digits[borrowIndex] == 0) {
                    result.digits[borrowIndex] = 9;
                    ++borrowIndex;
                }

                if (borrowIndex < result.digits.size()) {
                    result.digits[borrowIndex] -= 1;
                    result.digits[i] += 10; 
                } else {
                    throw std::overflow_error("Результат вычитания меньше нуля.");
                }
            }

            result.digits[i] -= other.digits[i]; 
        }
    } else{
        throw std::overflow_error("Результат вычитания меньше нуля.");
    }

    result.removeLeadingZeros(); 
    return result;
}




Money& Money::operator+=(const Money& other) {
    *this = *this + other;
    return *this;
}

Money& Money::operator-=(const Money& other) {
    *this = *this - other;
    return *this;
}

bool Money::operator==(const Money& other) const {
    for(int i = 0; i < digits.size(); i++){
        if (digits[i] != other.digits[i]){
            return false;
        }
    }
    return true;
}

bool Money::operator<(const Money& other) const {
    if (digits.size() != other.digits.size()) return digits.size() < other.digits.size();
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] < other.digits[i]) return true;
        if (digits[i] > other.digits[i]) return false;
    }
    return false;
}

bool Money::operator>(const Money& other) const {
    return other < *this;
}