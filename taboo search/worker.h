#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <fstream>

#define amount_of_skills 3
#define workers_amount 3

using namespace std;

class Worker
{
public:
    int ID;
    int skills[amount_of_skills];
    int groupwork;

    Worker(int ID_=0, int A = 0, int B = 0, int C = 0);
    void print_worker_data();
};


bool read_worker_data(Worker **workers);

#endif