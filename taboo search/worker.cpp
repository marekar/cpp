#include "worker.h"

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