#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <fstream>

//te stale zmienic w momencie modyfikacji pliku z danymi wejsciowymi
#define amount_of_skills 4 //liczba umiejetnosci jednego pracownika
#define workers_amount 3 //ilosc pracownikow

using namespace std;

class Worker
{
public:
    int ID;
    int skills[amount_of_skills];

    Worker(int ID_=0, int A = 0, int B = 0, int C = 0);
    void print_worker_data();
};


bool read_worker_data(Worker **workers);

#endif