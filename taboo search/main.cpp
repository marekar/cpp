#include "worker.h"

int main ()
{
    Worker* workers[workers_amount];
    for(int i = 0; i < workers_amount; i++)
    {
        workers[i] = new Worker();
        workers[i] -> ID = i;
    }

    if(!read_worker_data(workers))
        cout << "Wystapil blad podczas pobierania danych " << endl;
    else
    {
        for(int i = 0; i < workers_amount; i++)
        {
            workers[i] -> print_worker_data();
        }
    }
    
    return 0;
}


