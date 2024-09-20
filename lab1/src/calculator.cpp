
#include<bits/stdc++.h>
#include "../include/calculator.h"

int box_capacity(int length, int width, int height){
    return (length * 12 / 16) * (width * 12 / 16) * (height * 12 / 16);
}