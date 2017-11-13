#include "worker.h"
#include <fstream>

//const char * file_name_worker = "worker_data.txt";

bool read_worker_data();
ifstream file;

int main ()
{
    Worker pierwszy = Worker(1, 4, 5, 6);
    pierwszy.print_worker_data();
    cout << pierwszy.skills[2] <<endl;
    
    if(!read_worker_data())
        cout << "Wystapil blad podczas pobierania danych " << endl;
    

    pierwszy.print_worker_data();
    return 0;
}

bool read_worker_data()
{
    file.open("worker_data.txt");
    if(!file.good())
    {
        cout << "Nie mozna wczytac pliku worker_data.txt" << endl;
        return false;
    }
  
    while(true)
    {
        int skill_tab[3];
        file >> skill_tab[0] >> skill_tab[1] >> skill_tab[2];
        if(file.good())
        {
            for(int i = 0; i < amount_of_skills; i++)
            {
                cout << skill_tab[i] << endl;
                pierwszy.skills[i] = skill_tab[i];
            }
        }
        else
            break;
    }
    return true;
    //
}