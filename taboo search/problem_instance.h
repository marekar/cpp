#ifndef PROBLEM_INSTANCE_H
#define PROBLEM_INSTANCE_H

#include <iostream>
#include <fstream>
#include "problem.h"
#include "worker.h"
#include <vector>
#include <algorithm>
#include "consts.h"

using namespace std;

class ProblemInstance

{
private:

    int employees_amount;
    int tasks_size;
    float cost;
    float get_resolving_time(int worker_number, int task_number);
    float get_time_for_many(vector<int> worker_list, int task_number);
    float get_time_for_one(int worker_number, int task_number);
    float get_penalty(int task_number, float finish_time);  
    vector < vector < int > >swap_workers();
    void get_neighbours();
public:

    Worker * employees;
    Problem * tasks;
    float get_cost(){return cost;}

    vector < vector < int > > solution;
    vector <vector < vector < int > >> neighbours;
    ProblemInstance(Worker * workers_list, int workers_size, Problem * tasks_list, int tasks_size);

    void search_randomly();

    bool analyze_solution();
    void build_first_solution();

    void show_solution();
    void show_workers();

    ~ProblemInstance();
};
bool read_solution_data(vector< vector<int> > &solution, int w_number, int t_number);


#endif