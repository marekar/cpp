#include "problem_instance.h"


vector < vector < int > > ProblemInstance::null_sol = vector < vector < int > >();
ProblemInstance ::ProblemInstance(Worker *workers_list, int workers_size, Problem *tasks_list, int tasks_size)
{
    this->employees = workers_list;
    this->tasks = tasks_list;
    this->tasks_size = tasks_size;
    this->employees_amount = workers_amount;
    this->solution = vector< vector<int> >(employees_amount, vector<int>(tasks_size, 0));
}

ProblemInstance ::~ProblemInstance()
{
    delete[] this->employees;
    delete[] this->tasks;
}

void ProblemInstance::show_solution(vector < vector < int > > & sol){
    if( sol == null_sol){
        sol = solution;
    }
    cout << endl << "Solution" ;
    for(int i = 0; i < workers_amount ; i++){
        cout << endl << "worker " << i << "__\t ";
        for(auto it = sol.at(i).begin(); it != sol.at(i).end() ; it++)
            cout << *it <<"\t";
    }

}
void ProblemInstance::show_workers(){
    for(int i = 0 ; i < employees_amount ;i++){
        employees[i].print_worker_data();
    }
}

void ProblemInstance::build_first_solution(){
    float total_cost = 0;
    float one_task_cost = 0;
    float* workers_current_time = new float[workers_amount];
    int best_worker_for_task = 0;
    for( int i = 0 ; i < workers_amount ; i++)
        workers_current_time[i] = 0;

    solution = vector<vector<int>>(employees_amount, vector<int>());
    for(int i = 0 ; i < tasks_size ; i++){
        one_task_cost = 9999999999.0;
        best_worker_for_task = 0;
        for(int j = 0 ; j < workers_amount ; j ++){
            if(get_penalty(i + 1,get_time_for_one(j, i + 1) + workers_current_time[j]) < one_task_cost){
                best_worker_for_task = j;
                // cout << endl << "task " << i + 1 << " best worker " << j;

                one_task_cost = get_penalty(i + 1,get_time_for_one(j, i + 1) + workers_current_time[j]);
                // cout << endl << "task " << i + 1 << " best worker " << j << "cost " << one_task_cost;                
            }

        }
        solution.at(best_worker_for_task).push_back(i + 1);
        workers_current_time[best_worker_for_task] += get_time_for_one(best_worker_for_task, i + 1);
        total_cost += one_task_cost;
    }
    delete[] workers_current_time;
    cost = total_cost;

}



bool ProblemInstance::analyze_solution()
{

    vector<vector<int>> shared_job_vector = vector<vector<int>>(tasks_size + 1, vector<int>());
    float total_cost = 0;
    bool is_ready_to_shared_job;
    vector<vector<int>> gantt_worker_jobs = vector<vector<int>>(employees_amount, vector<int>());
    vector<vector<float>> gantt_worker_time =  vector<vector<float>>(employees_amount, vector<float>()); 
    vector<float> worker_time = vector<float>(employees_amount, 0.0);
    int j = 0;
    for (auto it = solution.begin(); it != solution.end(); it++)
    {

        for (auto it_ins = (*it).begin(); it_ins != (*it).end(); it_ins++)
        {
            if (*it_ins != 0)
            {
                if (count((*it).begin(), (*it).end(), *it_ins) > 1) //same job assigned to one worker many times
                    return false;

                shared_job_vector.at(*it_ins).push_back(j);
            }
        }

        j++;
    }

    shared_job_vector.at(0).insert(shared_job_vector.at(0).begin(), 0);

    for(auto it = shared_job_vector.begin() ; it != shared_job_vector.end() ; it++){
        if((*it).size() == 0)
            return false; //not all jobs are assigned
    }

    auto shared_job_vector_copy = shared_job_vector;
    auto solution_copy = solution;
    int job_number;
    bool changes_appeared;

    int not_resolved_jobs = 1;
    while (not_resolved_jobs > 0)
    {
        changes_appeared = false;
        for (auto it = solution_copy.begin(); it != solution_copy.end(); it++)
        {
            while ((*it).size() > 0 and shared_job_vector.at((*it).at(0)).size() == 1)
            { //check if is this job for one person
                gantt_worker_time[shared_job_vector.at((*it).at(0)).at(0)].push_back(get_time_for_one(shared_job_vector.at((*it).at(0)).at(0), (*it).at(0)));
                gantt_worker_jobs[shared_job_vector.at((*it).at(0)).at(0)].push_back((*it).at(0));

                worker_time.at(shared_job_vector.at((*it).at(0)).at(0)) += get_time_for_one(shared_job_vector.at((*it).at(0)).at(0), (*it).at(0));
                total_cost += get_penalty((*it).at(0), worker_time.at(shared_job_vector.at((*it).at(0)).at(0)));
                (*it).erase((*it).begin()); //remove job from job list, TODO increment time

                changes_appeared = true;
            }

            if ((*it).size() != 0)
            {
                is_ready_to_shared_job = true;

                for (auto job_it = shared_job_vector.at((*it)[0]).begin(); job_it != shared_job_vector.at((*it)[0]).end(); job_it++)
                {

                    if (solution_copy[*job_it][0] != (*it)[0])
                    { //skip, other workers are still working
                        is_ready_to_shared_job = false;
                        break;
                    }
                }
                if (is_ready_to_shared_job)
                {
                    job_number = ((*it)[0]);
                    changes_appeared = true;
                    float max_starting_time = 0, waiting_time = 0;
                    float job_finish_time = 0, job_time = 0;
                    for (auto job_it = shared_job_vector.at((*it)[0]).begin(); job_it != shared_job_vector.at(job_number).end(); job_it++)
                    {
                        if (max_starting_time < worker_time.at(*job_it)) //wait for all workers to be ready
                            max_starting_time = worker_time.at(*job_it);
                    }
                    job_time = get_time_for_many(shared_job_vector.at((*it)[0]), job_number);
                    job_finish_time = job_time + max_starting_time;
                    total_cost += get_penalty(job_number, job_finish_time);

                    for (auto job_it = shared_job_vector.at((*it)[0]).begin(); job_it != shared_job_vector.at(job_number).end(); job_it++)
                    {   
                        waiting_time = job_finish_time - job_time - worker_time.at(*job_it);
                        if(waiting_time > 0.001){
                        gantt_worker_time[*job_it].push_back(waiting_time);
                        gantt_worker_jobs[*job_it].push_back(0);
                            
                        }
                        gantt_worker_time[*job_it].push_back(job_time);
                        gantt_worker_jobs[*job_it].push_back(job_number);
                            
                        worker_time.at(*job_it) = job_finish_time;
                        solution_copy.at(*job_it).erase(solution_copy.at(*job_it).begin()); 
                    }
                }
            }
        }
        if (!changes_appeared)
        { // deadlock detected
            return false;
        }

        not_resolved_jobs = 0;
        for (auto debug_it = solution_copy.begin(); debug_it != solution_copy.end(); debug_it++)
        {

            for (auto debug2_it = (*debug_it).begin(); debug2_it != (*debug_it).end(); debug2_it++)
            {
                not_resolved_jobs++;
            }
        }
    }
    // cout << endl
    //      << "total cost: " << total_cost << endl;
    cost = total_cost;
    return true;
}

float ProblemInstance::get_time_for_one(int worker_number, int task_number)
{

    if (task_number == 0)
        return 0.0;
    task_number = task_number - 1; // task are indexed from 0
    float time = 0;

    for (int i = 0; i < amount_of_skills; i++)
    {
        time += tasks[task_number].requirements[i] / (float)(employees[worker_number].skills[i]);
    }

    return time;
}

float ProblemInstance::get_time_for_many(vector<int> worker_list, int task_number)
{
    float time = 0;
    float *summary_skills = new float[amount_of_skills];
    for (int i = 0; i < amount_of_skills; i++)
    {
        summary_skills[i] = 0.0;
    }

    for (int i = 0; i < amount_of_skills; i++)
    {

        for (auto it = worker_list.begin(); it != worker_list.end(); it++)
        {
            summary_skills[i] += (employees[*it].skills[i]) * employees[*it].teamwork;
        }

        time += tasks[task_number].requirements[i] / summary_skills[i];
    }
    delete[] summary_skills;

    return time;
}

float ProblemInstance::get_penalty(int task_number, float finish_time)
{
    if(task_number < 1)
        return 0;
    else
        task_number--;

    if (tasks[task_number].deadline > finish_time) //task 0 means free time
        return 0;
    else
        return tasks[task_number].penalty * 1.0 + tasks[task_number].penalty_per_hour * (finish_time - tasks[task_number].deadline);
}
bool read_solution_data(vector<vector<int>> &solution, int w_number, int t_number)
{
    ifstream file;

    int data;
    file.open("solution_data.txt");
    if (!file.good())
    {
        cout << "Nie mozna wczytac pliku solution_data.txt" << endl;
        return false;
    }

    for (int i = 0; i < w_number; i++)
    {
        for (int j = 0; j < t_number; j++)
        {
            file >> data;

            solution.at(i).at(j) = data;
        }
    }

    return true;
}

vector < vector < int > >ProblemInstance:: swap_workers(){
    auto swapped = solution;
    int v1 = 0, v2 = 0;
    auto temp = solution[0];
    while(v1 == v2){
        v1 = rand() % solution.size();
        v2 = rand() % solution.size();
    }

    temp = swapped[v1];
    swapped[v1] = swapped[v2];
    swapped[v2] = temp;

    return swapped;
}

vector < vector < int > >ProblemInstance::add_jobs(int jobs_number){
    auto new_sol = solution;
    int job, worker, place, tries;

    while(jobs_number > 0){
        
        tries = 0;
        do{

            worker = rand() % solution.size();
        }while(tries++ < MAX_TRIES && new_sol[worker].size() >= tasks_size);
        tries = 0;
        do{

            job = rand() % tasks_size;
        }while(tries++ < MAX_TRIES && find(new_sol[worker].begin(), new_sol[worker].end(), job) != new_sol[worker].end());//dont add job that actually is in worker list

        place = rand() % (new_sol[worker].size() + 1);

        new_sol[worker].insert(new_sol[worker].begin() + place, job); 
        jobs_number--;

    }

    return new_sol;
}

vector < vector < int > >ProblemInstance::remove_jobs(int jobs_number){
    auto new_sol = solution;
    int  worker, place, tries;

    while(jobs_number > 0){

        tries = 0;

        do{
            worker = rand() % solution.size();
        }while(tries++ < MAX_TRIES && new_sol[worker].size() == 0);



        if( tries > MAX_TRIES){
            jobs_number--;
            continue;
        }

        place = rand() % (new_sol[worker].size());
        new_sol[worker].erase(new_sol[worker].begin() + place); 
        jobs_number--;
    
    }

    return new_sol;


}

vector < vector < int > >ProblemInstance::add_and_remove_jobs(int jobs_add, int jobs_remove){
    auto new_sol = solution;
    int  worker, place, tries, job;

    while(jobs_remove > 0){

        tries = 0;

        do{
            worker = rand() % solution.size();
        }while(tries++ < MAX_TRIES && new_sol[worker].size() == 0);



        if( tries >= MAX_TRIES){
            jobs_remove--;
            continue;
        }

        place = rand() % (new_sol[worker].size());
        new_sol[worker].erase(new_sol[worker].begin() + place); 
        jobs_remove--;
    }

    while(jobs_add > 0){
        
        tries = 0;
        do{

            worker = rand() % solution.size();
        }while(tries++ < MAX_TRIES && new_sol[worker].size() >= tasks_size);
        tries = 0;
        do{

            job = rand() % tasks_size;
        }while(tries++ < MAX_TRIES && find(new_sol[worker].begin(), new_sol[worker].end(), job) != new_sol[worker].end());//dont add job that actually is in worker list
        if( tries >= MAX_TRIES){
            jobs_add--;
            continue;
        }
        place = rand() % (new_sol[worker].size() + 1);

        new_sol[worker].insert(new_sol[worker].begin() + place, job); 
        jobs_add--;

    }



    return new_sol;


}





void ProblemInstance:: get_neighbours(){
     neighbours.clear();
    for(int i = 0 ; i < 50 ; i++){
        neighbours.push_back(swap_workers());
        neighbours.push_back(add_jobs( 1 + rand() % 8));
        neighbours.push_back(remove_jobs( 1 + rand() % 5));
        neighbours.push_back(add_and_remove_jobs( 1 + rand() % 10, 1 + rand() % 10));                
    }

}

    void ProblemInstance:: search_randomly(int how_many){
        while(how_many-- > 0){
        get_neighbours();
        auto temp = solution;
        float temp_cost = cost;
        for(auto it = neighbours.begin() ; it != neighbours.end() ; it++){
            temp = solution;
            temp_cost = cost;
            solution = *it;
            //show_solution();
            if(analyze_solution() && temp_cost > cost){// new better found

                continue;
            }

            else{
                solution = temp; // return to previous;
                cost =temp_cost;
            }


        }



        }

    }