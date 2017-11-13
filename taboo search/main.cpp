#include "worker.h"
#include <fstream>

#define workers_amount 3

const char * file_name_worker = "worker_data.txt";

bool read_worker_data(Worker **workers);
ifstream file;

int main ()
{
    //Worker pierwszy = Worker(1, 4, 5, 6);
    //pierwszy.print_worker_data();
    //cout << pierwszy.skills[2] <<endl;

    Worker **workers;
    workers = new *Worker[workers_amount];
    for(int i = 0; i < workers_amount; i++)
    {
        workers[i] = new Worker();
    }

    if(!read_worker_data(workers))
        cout << "Wystapil blad podczas pobierania danych " << endl;
    

    workers[0] -> print_worker_data();
    return 0;
}

bool read_worker_data(Worker **workers)
{
    file.open(file_name_worker);
    if(!file.good())
    {
        cout << "Nie mozna wczytac pliku worker_data.txt" << endl;
        return false;
    }
  
    while(true)
    {
        int k = amount_of_skills;
        int i = 0;
        int skill_tab[9];
        file >> skill_tab[0] >> skill_tab[1] >> skill_tab[2];
        if(file.good())
        {
            for(int j = 0; j < workers_amount; j++)
            {
                for(int i; i < k; i++)
                {
                    workers[j] -> skills[i] = skill_tab[i];
                }
                i += amount_of_skills;
                k += k;
            }
        }
        else
            break;
    }
    return true;
    //
}