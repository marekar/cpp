#include "worker.h"
#include "problem.h"
#include "problem_instance.h"
void show_workers(Worker** workers);
void show_problems(Problem** problems);

int main ()
{
    Worker* workers[workers_amount];
    Problem* problems[problems_amount];
    Worker* workersPtr;
    Problem* problemPtr;
    workersPtr = new Worker[workers_amount];
    problemPtr = new Problem[problems_amount];

    for(int i = 0; i < workers_amount; i++)
    { // tworze tablice pracownikow
        workers[i] = new Worker();
        workers[i] -> ID = i;
        workersPtr[i] = *workers[i];
    }

    for(int i = 0; i < problems_amount; i++)
    { // tworze tablice problemow
        problems[i] = new Problem();
        problems[i] -> problem_ID = i;
        problemPtr[i] = problemPtr[i];
    }

    ProblemInstance BigProblem = ProblemInstance(workersPtr, workers_amount, problemPtr, problems_amount);

    vector< vector<int> > example_solution = vector< vector<int> >(workers_amount, vector<int>(problems_amount, 0));


    if(!read_solution_data(example_solution, workers_amount, problems_amount)){
        return -1;
    }

    BigProblem.solution = example_solution;

    cout <<"after check: "<< BigProblem.is_solution_legal() << endl;
    cout << "done";
    // show_workers(workers);
    // show_problems(problems);
   
    return 0;
}









void show_workers(Worker** workers)
{
    if(!read_worker_data(workers))
        cout << "Wystapil blad podczas pobierania danych " << endl;
    else
    {
        for(int i = 0; i < workers_amount; i++)
        {
            workers[i] -> print_worker_data();
        }
        cout << endl;
    }
}

void show_problems(Problem** problems)
{
    if(!read_problem_data(problems) || !(read_penalties(problems)))
        cout << "Wystapil blad podczas pobierania danych " << endl;
    else
    {
        for(int i = 0; i < problems_amount; i++)
        {
            problems[i] -> print_problem();
        }
    } 
}

