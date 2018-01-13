#ifndef PROBLEM_INSTANCE_H
#define PROBLEM_INSTANCE_H

#include <iostream>
#include <fstream>
#include "problem.h"
#include "worker.h"
#include <vector>
#include <algorithm>
#include "consts.h"
#include "taboo.h"
#include <time.h>

using namespace std;

class ProblemInstance

{
  private:
    int employees_amount;
    long int correct_generated;
    long int incorrect_generated;
    int tasks_size;
    float cost;
    float best_cost_ever;

    vector<vector<int>> gantt_worker_jobs;
    vector<vector<float>> gantt_worker_time;

    TabooMove last_move;

    float get_resolving_time(int worker_number, int task_number);
    float get_time_for_many(vector<int> worker_list, int task_number);
    float get_time_for_one(int worker_number, int task_number);
    float get_penalty(int task_number, float finish_time);
    vector<float> cost_data_for_plot;
    vector<int> iteration_data_for_plot;
    vector<vector<int>> swap_workers();
    vector<vector<int>> add_jobs(int jobs_number = 1);
    vector<vector<int>> remove_jobs(int jobs_number = 1);
    vector<vector<int>> add_and_remove_jobs(int jobs_add, int jobs_remove);
    vector<vector<int>> take_from_another_worker(int jobs_number);
    vector<vector<int>> give_job_to_lazy_worker();
    void get_one_neighbour();
    void get_neighbours(int how_many = 10);
    int iterations_since_new_value_found;
    int aspiration_used;

  public:
    TabooList taboo_list;
    static vector<vector<int>> null_sol;
    Worker *employees;
    Problem *tasks;
    float get_cost() { return cost; }
    float get_best_cost() { return best_cost_ever; }
    vector<vector<int>> solution;
    vector<vector<int>> best_solution;

    vector<vector<vector<int>>> neighbours;

    ProblemInstance(Worker *workers_list, int workers_size, Problem *tasks_list, int tasks_size);

    void search_randomly(int how_many);

    bool analyze_solution(vector<vector<int>> &sol);
    void build_first_solution();

    void show_solution(vector<vector<int>> &sol = null_sol);
    void show_best_solution() { show_solution(best_solution); }
    void show_workers();
    void step();
    void log_gantt_chart();
    void log_consts();

    ~ProblemInstance();
};
bool read_solution_data(vector<vector<int>> &solution, int w_number, int t_number);

#endif