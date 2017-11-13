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

    Worker* workers[workers_amount];
    for(int i = 0; i < workers_amount; i++)
    {
        workers[i] = new Worker();
    }

    if(!read_worker_data(workers))
        cout << "Wystapil blad podczas pobierania danych " << endl;
    

    workers[0] -> print_worker_data();
    workers[1] -> print_worker_data();
    workers[2] -> print_worker_data();
    return 0;
}

bool read_worker_data(Worker **workers)
{
    int n = 0;
    int k = amount_of_skills*workers_amount;
    int skill_tab[k];
    cout << "k" << k << endl;
    file.open(file_name_worker);
    if(!file.good())
    {
        cout << "Nie mozna wczytac pliku worker_data.txt" << endl;
        return false;
    }

    while(true)
    {   
        for (int i = 0; i < 9; i++)
        {
            file >> skill_tab[i];
            cout << "lala" << skill_tab[i] << endl;
        }
        
        if(file.good())
        {
            for(int i = 0; i < amount_of_skills; i++)
            {
                workers[0] -> skills[i] = skill_tab[i];
            }

            for(int i = 3; i < amount_of_skills + 3; i++)
            {
                workers[1] -> skills[i] = skill_tab[i];
            }

        //    for(int i = 6; i < amount_of_skills + 6; i++)
       //     {
       //         workers[2] -> skills[i] = skill_tab[i];
      //      }
        }
        else
            break;
    }
    return true;
    //
}