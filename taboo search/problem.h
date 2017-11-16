#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <fstream>

#define problem_size 4
#define problems_amount 6

using namespace std;

class Problem
{
public:
    int problem_ID;
    int requirements[problem_size];
    int penalty;
    int penalty_per_hour;

    void print_problem();

};

bool read_problem_data(Problem ** problems);
bool read_penalties(Problem ** problems);
#endif