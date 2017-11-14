#include "worker.h"


const char * file_name_worker = "worker_data.txt";


Worker :: Worker(int ID_, int A, int B, int C)
{
    ID = ID_;
    skills[0] = A;
    skills[1] = B;
    skills[2] = C;
}

void Worker :: print_worker_data()
{
    cout << "Pracownik " << ID << endl;
    for (int i = 0; i < amount_of_skills; i++)
    {
        cout << skills[i] << " ";
    }
    cout << endl << "....." << endl;
}

bool read_worker_data(Worker **workers)
{
    ifstream file;
    int k = amount_of_skills*workers_amount;
    int n = 0, m = 0;
    int skill_tab[k];
    
    file.open(file_name_worker);
    if(!file.good())
    {
        cout << "Nie mozna wczytac pliku worker_data.txt" << endl;
        return false;
    }
 
    for (int i = 0; i < k; i++)
    {
        file >> skill_tab[i];
        //cout << skill_tab[i];
    }
    
    for(int j = 0; j < workers_amount; j++)
    {
        for(n = m; n < amount_of_skills*(j+1); n++)
        {
            for(int l = 0; l < amount_of_skills; l++)
            {
                workers[j] -> skills[l] = skill_tab[n];
            }
            m += amount_of_skills;
            cout<<m<<endl;
        }
        
    }
    //
    /*for(int i = 0; i < amount_of_skills; i++)
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
    */
    return true;
    
    //
}