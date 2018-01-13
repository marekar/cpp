
#ifndef MY_CONST_H
#define MY_CONST_H

#define BIG_NUMBER 10e20

//te stale zmienic w momencie modyfikacji pliku z danymi wejsciowymi
#define amount_of_skills 4 //liczba umiejetnosci jednego pracownika
#define workers_amount 9*2 //ilosc pracownikow
#define problems_amount 20 
#define MAX_TRIES 10
#define TABOO_SIZE 17
#define NEIGHBOUR_SIZE 30
#define WORKING_TIME 30

#define MAX_ADDED_TASK 7
#define MAX_REMOVED_TASK 8
#define MAX_TAKE_FROM_ANOTHER 6


#define NEIGHBOUR_ADD_FACTOR 100.0

#define amount_of_skills 4  //liczba umiejetnosci jednego pracownika
#define workers_amount 9*2  //ilosc pracownikow
#define problems_amount 20  //rozmiar problemu
#define MAX_TRIES 10        
#define TABOO_SIZE 17       
#define NEIGHBOUR_SIZE 30   
#define WORKING_TIME 60    //maksymalny czas

#define MAX_ADDED_TASK 7   //max zmian sąsiedztwa 
#define MAX_REMOVED_TASK 8  
#define MAX_TAKE_FROM_ANOTHER 6 //przełożenie zadań do innego pracowniak

#define NEIGHBOUR_ADD_FACTOR 100.0  //dodawanie sąsiedztwa
#define NEIGHBOUR_REMOVE_FACTOR 100.0
#define NEIGHBOUR_ADD_AND_REMOVE_FACTOR 120.0
#define NEIGHBOUR_SWAP_FACTOR 60.0
#define NEIGHBOUR_TAKE_FACTOR 150.0
#define NEIGHBOUR_TO_LAZY_FACTOR 60.0
#define MEDIUM_APPEND_THRESHOLD 0.9
#define MEDIUM_MEMORY_ITERATIONS_THRESHOLD 10000


#define SUMM ( NEIGHBOUR_ADD_FACTOR + NEIGHBOUR_REMOVE_FACTOR + NEIGHBOUR_ADD_AND_REMOVE_FACTOR + NEIGHBOUR_SWAP_FACTOR + NEIGHBOUR_TAKE_FACTOR)

#define ADD_THRESHOLD ( NEIGHBOUR_ADD_FACTOR /  SUMM  ) 
#define REMOVE_THRESHOLD (ADD_THRESHOLD + (NEIGHBOUR_REMOVE_FACTOR/SUMM))
#define ADD_AND_REMOVE_THRESHOLD (REMOVE_THRESHOLD + (NEIGHBOUR_ADD_AND_REMOVE_FACTOR/SUMM))
#define SWAP_THRESHOLD (ADD_AND_REMOVE_THRESHOLD + (NEIGHBOUR_SWAP_FACTOR/SUMM))
#define TAKE_THRESHOLD (SWAP_THRESHOLD + (NEIGHBOUR_TAKE_FACTOR/SUMM))
#define TO_LAZY_THRESHOLD (TAKE_THRESHOLD + (NEIGHBOUR_TO_LAZY_FACTOR/SUMM))
#define problem_size amount_of_skills

#endif