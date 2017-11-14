#include "worker.h"

int main ()
{
    //Worker pierwszy = Worker(1, 4, 5, 6);
    //pierwszy.print_worker_data();
    //cout << pierwszy.skills[2] <<endl;

    Worker* workers[workers_amount];
    for(int i = 0; i < workers_amount; i++)
    {
        workers[i] = new Worker();
        workers[i] -> ID = i+1;
    }

    if(!read_worker_data(workers))
        cout << "Wystapil blad podczas pobierania danych " << endl;


    workers[0] -> print_worker_data();
    workers[1] -> print_worker_data();
    workers[2] -> print_worker_data();
    return 0;
}


