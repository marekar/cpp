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
        workers[i] -> ID = i+1;
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
    int k = amount_of_skills*workers_amount;
    int skill_tab[k];
   
    file.open(file_name_worker);
    if(!file.good())
    {
        cout << "Nie mozna wczytac pliku worker_data.txt" << endl;
        return false;
    }
 
    for (int i = 0; i < 9; i++)
    {
        file >> skill_tab[i];
        //cout << skill_tab[i];
    }
    
    for(int i = 0; i < amount_of_skills; i++)
    {
        workers[0] -> skills[i] = skill_tab[i];
    }
     
    for(int i = 3; i < amount_of_skills + 3; i++)
    {
        workers[1] -> skills[i-3] = skill_tab[i];
    }
   
    for(int i = 6; i < amount_of_skills + 6; i++)
    {
        workers[2] -> skills[i-6] = skill_tab[i];
    }
    
    return true;
    //
}
