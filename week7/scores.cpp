#include "scores.hpp"

Scores::Scores(int a, int b, int c) 
    : values_{a, b, c} 
{}

int Scores::total() const {
    return values_[0] + values_[1] + values_[2];
}

