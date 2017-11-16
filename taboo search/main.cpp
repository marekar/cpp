#include "worker.h"
#include "problem.h"

int main ()
{
    Worker* workers[workers_amount];
    Problem* problems[problems_amount];

    for(int i = 0; i < workers_amount; i++)
    { // tworze tablice pracownikow
        workers[i] = new Worker();
        workers[i] -> ID = i;
    }

    for(int i = 0; i < problems_amount; i++)
    { // tworze tablice problemow
        problems[i] = new Problem();
        problems[i] -> problem_ID = i;
    }

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

     if(!read_problem_data(problems))
        cout << "Wystapil blad podczas pobierania danych " << endl;
    else
    {
        for(int i = 0; i < problems_amount; i++)
        {
            problems[i] -> print_problem();
        }
    }
    
    return 0;
}


