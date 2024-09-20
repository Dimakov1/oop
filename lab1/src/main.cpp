#include<bits/stdc++.h>
#include "../include/calculator.h"

int main(){
    int length, width, height;
    std::cin >> length >> width >> height;
    std::cout << box_capacity(length, width, height) << '\n';
}