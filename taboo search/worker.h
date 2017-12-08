#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <fstream>
#include "consts.h"


using namespace std;

class Worker
{
public:
    int ID;
    int skills[amount_of_skills];
    float teamwork;
    Worker(int ID_=0);
    void print_worker_data();
};

//Funkcja odczytujaca z pliku wydajnosci pracownikow
//wypelnia tablice skills[] dla kazdego pracownika
bool read_worker_data(Worker *workers);

#endif