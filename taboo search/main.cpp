#include "worker.h"
#include "problem.h"
#include "problem_instance.h"
#include "consts.h"
#include <time.h> 
void show_workers(Worker *workers);
void show_problems(Problem *problems);

int main()
{
    srand (time(NULL));
    Worker *workers;
    Problem *problems;

    time_t my_time, start;

    workers = new Worker[workers_amount];
    problems = new Problem[problems_amount];

    for (int i = 0; i < workers_amount; i++)
    { // tworze tablice pracownikow
        workers[i].ID = i;
    }

    for (int i = 0; i < problems_amount; i++)
    { // tworze tablice problemow
        problems[i].problem_ID = i;
    }

    ProblemInstance BigProblem = ProblemInstance(workers, workers_amount, problems, problems_amount);
    show_workers((BigProblem.employees));
    show_problems(problems);

    // vector<vector<int>> example_solution = vector<vector<int>>(workers_amount, vector<int>(problems_amount, 0));

    // if (!read_solution_data(example_solution, workers_amount, problems_amount))
    // {
    //     return -1;
    // }
    
    // BigProblem.solution = example_solution;
    BigProblem.show_workers();
    
    BigProblem.build_first_solution();

    if (BigProblem.analyze_solution())
    {
        cout << "obliczono koszt rozwiazania!" << endl;
    }
    else
    {
        cout << "rozwiazanie zabronione!";
    }

    BigProblem.show_solution();

    time(&start);
    time(&my_time);
    while(difftime(my_time,start) < 3){
    BigProblem.search_randomly(10);
    time(&my_time);
    }

    BigProblem.show_solution();  
    cout << endl << "after all iterations final cost : " << BigProblem.get_cost();
    BigProblem.analyze_solution();
    BigProblem.log_gantt_chart();

    return 0;
}

void show_workers(Worker *workers)
{
    if (!read_worker_data(workers))
        cout << "Wystapil blad podczas pobierania danych " << endl;
    else
    {
        // for (int i = 0; i < workers_amount; i++)
        // {
        //     workers[i].print_worker_data();
        // }
        // cout << endl;
    }
}

void show_problems(Problem *problems)
{
    if (!read_problem_data(problems) || !(read_penalties(problems)))
        cout << "Wystapil blad podczas pobierania danych " << endl;
    else
    {
        for (int i = 0; i < problems_amount; i++)
        {
            // problems[i].print_problem();
        }
    }
}
