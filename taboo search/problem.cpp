#include "problem.h"

const char *file_name_problem = "problem_data.txt";
const char *file_name_penalty = "penalty_data.txt";

void Problem ::print_problem()
{
    cout << endl
         << "----Problem " << problem_ID << endl;
    for (int i = 0; i < problem_size; i++)
    {
        cout << requirements[i] << " ";
    }
    cout << endl
         << "Kara za niedotrzymanie terminu: " << penalty << " PLN" << endl;
    cout << "Kara na godzine: " << penalty_per_hour << " PLN/GODZ" << endl;
}

//Funkcja do wczytywania zadan
bool read_problem_data(Problem *problems)
{
    ifstream file;
    int k = (problem_size + 1) * problems_amount;
    int requirements_tab[k];

    file.open(file_name_problem);
    if (!file.good())
    {
        cout << "Nie mozna wczytac pliku problem_data.txt" << endl;
        return false;
    }

    for (int i = 0; i < k; i++)
    {
        file >> requirements_tab[i];
        // cout << requirements_tab[i];
    }

    for (int j = 0; j < problems_amount; j++)
    {
        for (int i = j * problem_size; i < (j + 1) * problem_size; i++)
        {
            problems[j].requirements[i - j * problem_size] = requirements_tab[i];
        }
        problems[j].deadline = j + 0.5;
    }

    return true;
}

//Funkcja wczytujaca kary dla zadan
bool read_penalties(Problem *problems)
{
    ifstream file;
    int k = 2 * problems_amount;
    int penalties_tab[k];

    file.open(file_name_penalty);
    if (!file.good())
    {
        cout << "Nie mozna wczytac pliku penalty_data.txt" << endl;
        return false;
    }

    for (int i = 0; i < k; i++)
    {
        file >> penalties_tab[i];
        //cout << penalties_tab[i];
    }

    for (int j = 0; j < problems_amount; j++)
    { // wczytywanie kary za niedotrzymanie terminu
        for (int i = 2 * j; i < 2 * (j + 1); i += 2)
        {
            problems[j].penalty = penalties_tab[i];
            problems[j].penalty_per_hour = penalties_tab[i];
        }
    }

    for (int j = 0; j < problems_amount; j++)
    { // wczytywanie kary za godzine
        for (int i = 2 * j; i < 2 * (j + 1); i++)
        {
            problems[j].penalty_per_hour = penalties_tab[i];
        }
    }

    return true;
}