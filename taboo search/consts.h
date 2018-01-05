
#ifndef MY_CONST_H
#define MY_CONST_H


//te stale zmienic w momencie modyfikacji pliku z danymi wejsciowymi
#define amount_of_skills 4 //liczba umiejetnosci jednego pracownika
#define workers_amount 9 //ilosc pracownikow
#define problems_amount 12
#define MAX_TRIES 10
#define TABOO_SIZE 200
#define NEIGHBOUR_SIZE 30

#define NEIGHBOUR_ADD_FACTOR 100.0
#define NEIGHBOUR_REMOVE_FACTOR 100.0
#define NEIGHBOUR_ADD_AND_REMOVE_FACTOR 100.0
#define NEIGHBOUR_SWAP_FACTOR 100.0

#define SUMM ( NEIGHBOUR_ADD_FACTOR + NEIGHBOUR_REMOVE_FACTOR + NEIGHBOUR_ADD_AND_REMOVE_FACTOR + NEIGHBOUR_SWAP_FACTOR )

#define ADD_THRESHOLD ( NEIGHBOUR_ADD_FACTOR /  SUMM  ) 
#define REMOVE_THRESHOLD (ADD_THRESHOLD + (NEIGHBOUR_REMOVE_FACTOR/SUMM))
#define ADD_AND_REMOVE_THRESHOLD (REMOVE_THRESHOLD + (NEIGHBOUR_ADD_AND_REMOVE_FACTOR/SUMM))
#define SWAP_THRESHOLD (ADD_AND_REMOVE_THRESHOLD + (NEIGHBOUR_SWAP_FACTOR/SUMM))
#define problem_size amount_of_skills

#endif