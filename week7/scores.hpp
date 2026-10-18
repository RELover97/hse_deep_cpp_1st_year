#pragma once

class Scores {
public:

    Scores(int a, int b, int c);
    
    int total() const;

private:

    int values_[3];
};

