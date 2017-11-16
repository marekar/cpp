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

//Funkcja odczytujaca z pliku wydajnosci pracownikow
//wypelnia tablice skills[] dla kazdego pracownika
bool read_worker_data(Worker **workers)
{
    ifstream file;
    int k = amount_of_skills*workers_amount;
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
        for(int i = j*amount_of_skills; i < amount_of_skills*(j+1); i++)
        {
            workers[j] -> skills[i - j*amount_of_skills] = skill_tab[i];
        }
    }

    return true; 
}