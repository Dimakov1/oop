#include "include/Money.h"

int main() {
    Money m1("123.45");
    m1.print();
    
    Money m2("76.55");
    m2.print();

    Money m3("123.4");
    m3.print();

    Money m4("123");
    m4.print();

    Money m5("123.456");
    m5.print();
    return 0;
}