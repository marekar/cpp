#include "problem.h"

const char * file_name_problem = "problem_data.txt";

void Problem :: print_problem()
{
    cout << "Problem " << problem_ID << endl;
    for(int i = 0; i < problem_size; i++)
    {
        cout << requirements[i] << " ";
    }
    cout << endl << "Kara za niedotrzymanie terminu: " << penalty << "PLN" << endl;
}

bool read_problem_data(Problem ** problems)
{
    ifstream file;
    int k = (problem_size+1)*problems_amount;
    int requirements_tab[k];
    int temp = 0;

    file.open(file_name_problem);
    if(!file.good())
    {
        cout << "Nie mozna wczytac pliku problem_data.txt" << endl;
        return false;
    }
 
    for (int i = 0; i < k; i++)
    {
        file >> requirements_tab[i];
        //cout << requirements_tab[i];
    }
    //czesc niedzialajaca
    /*
    for(int j = 0; j < problems_amount; j++)
    {
        for(int i = temp; i < (j+1)*problem_size+1; i++)
        {
            problems[j] -> requirements[i - j*problem_size-1] = requirements_tab[i+1];
            //problems[j] -> penalty = requirements_tab[5];
        }
        temp = j*problem_size + 1;
    }
    */
    return true; 
}