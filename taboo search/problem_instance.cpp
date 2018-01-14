#include "problem_instance.h"

vector<vector<int>> ProblemInstance::null_sol = vector<vector<int>>();
ProblemInstance ::ProblemInstance(Worker *workers_list, int workers_size, Problem *tasks_list, int tasks_size)
{
    this->employees = workers_list;
    this->tasks = tasks_list;
    this->tasks_size = tasks_size;
    this->employees_amount = workers_amount;
    this->solution = vector<vector<int>>(employees_amount, vector<int>(tasks_size, 0));
    cost = BIG_NUMBER;
    best_cost_ever = BIG_NUMBER;
    correct_generated = 0;
    incorrect_generated = 0;
    aspiration_used = 0;
    gantt_worker_jobs = vector<vector<int>>(employees_amount, vector<int>());
    gantt_worker_time = vector<vector<float>>(employees_amount, vector<float>());
    cost_data_for_plot = vector<float>();
    taboo_list = TabooList(TABOO_SIZE);
}

ProblemInstance ::~ProblemInstance()
{
    delete[] this->employees;
    delete[] this->tasks;
}

void ProblemInstance::show_solution(vector<vector<int>> &sol)
{
    if (sol == null_sol)
    {
        sol = solution;
    }
    cout << endl
         << "Solution";
    for (int i = 0; i < workers_amount; i++)
    {
        cout << endl
             << "worker " << i << "__\t ";
        for (auto it = sol.at(i).begin(); it != sol.at(i).end(); it++)
            if(*it > 0)
                cout << *it << "\t";
    }
    if (correct_generated != 0)
    {
        cout << endl
             << "correct generated: " << correct_generated << " it's "
             << 100.0 * correct_generated / (correct_generated + incorrect_generated) << "% of all " << endl;
    }
}
void ProblemInstance::show_workers()
{
    for (int i = 0; i < employees_amount; i++)
    {
        employees[i].print_worker_data();
    }
}

void ProblemInstance::build_first_solution(bool override)
{
    float total_cost = 0;
    float one_task_cost = 0;
    float *workers_current_time = new float[workers_amount];
    int best_worker_for_task = 0;
    for (int i = 0; i < workers_amount; i++)
        workers_current_time[i] = 0;

    solution = vector<vector<int>>(employees_amount, vector<int>());
    for (int i = 0; i < tasks_size; i++)
    {
        one_task_cost = BIG_NUMBER;
        best_worker_for_task = 0;
        for (int j = 0; j < workers_amount; j++)
        {
            if (get_penalty(i + 1, get_time_for_one(j, i + 1) + workers_current_time[j]) < one_task_cost)
            {
                best_worker_for_task = j;
                one_task_cost = get_penalty(i + 1, get_time_for_one(j, i + 1) + workers_current_time[j]);
            }
        }
        solution.at(best_worker_for_task).push_back(i + 1);
        workers_current_time[best_worker_for_task] += get_time_for_one(best_worker_for_task, i + 1);
        total_cost += one_task_cost;
    }
    delete[] workers_current_time;
    if(override){
        best_cost_ever = cost;
    }
    cost = total_cost;

    cout << cost;
}

bool ProblemInstance::analyze_solution(vector<vector<int>> &sol)
{

    vector<vector<int>> shared_job_vector = vector<vector<int>>(tasks_size + 1, vector<int>());
    float total_cost = 0;
    bool is_ready_to_shared_job;
    gantt_worker_jobs = vector<vector<int>>(employees_amount, vector<int>());
    gantt_worker_time = vector<vector<float>>(employees_amount, vector<float>());
    vector<float> worker_time = vector<float>(employees_amount, 0.0);
    int j = 0;
    for (auto it = sol.begin(); it != sol.end(); it++)
    {

        for (auto it_ins = (*it).begin(); it_ins != (*it).end(); it_ins++)
        {
            if (*it_ins != 0)
            {
                if (count((*it).begin(), (*it).end(), *it_ins) > 1)
                {
                    cost = BIG_NUMBER;
                    return false;
                } //same job assigned to one worker many times

                shared_job_vector.at(*it_ins).push_back(j);
            }
        }

        j++;
    }

    shared_job_vector.at(0).insert(shared_job_vector.at(0).begin(), 0);

    for (auto it = shared_job_vector.begin(); it != shared_job_vector.end(); it++)
    {
        if ((*it).size() == 0)
        {
            cost = BIG_NUMBER;
            return false; //not all jobs are assigned
        }
    }

    auto shared_job_vector_copy = shared_job_vector;
    auto sol_copy = sol;
    int job_number;
    bool changes_appeared;

    int not_resolved_jobs = 1;
    while (not_resolved_jobs > 0)
    {
        changes_appeared = false;
        for (auto it = sol_copy.begin(); it != sol_copy.end(); it++)
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

                    if (sol_copy[*job_it][0] != (*it)[0])
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
                        if (waiting_time > 0.001)
                        {
                            gantt_worker_time[*job_it].push_back(waiting_time);
                            gantt_worker_jobs[*job_it].push_back(0);
                        }
                        gantt_worker_time[*job_it].push_back(job_time);
                        gantt_worker_jobs[*job_it].push_back(job_number);

                        worker_time.at(*job_it) = job_finish_time;
                        sol_copy.at(*job_it).erase(sol_copy.at(*job_it).begin());
                    }
                }
            }
        }
        if (!changes_appeared)
        { // deadlock detected
            cost = BIG_NUMBER;
            return false;
        }

        not_resolved_jobs = 0;
        for (auto debug_it = sol_copy.begin(); debug_it != sol_copy.end(); debug_it++)
        {

            for (auto debug2_it = (*debug_it).begin(); debug2_it != (*debug_it).end(); debug2_it++)
            {
                not_resolved_jobs++;
            }
        }
    }

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
    if (task_number < 1)
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

vector<vector<int>> ProblemInstance::swap_workers()
{
    auto swapped = solution;
    int v1 = 0, v2 = 0;
    auto temp = solution[0];
    TabooMove new_move;
    while (v1 == v2)
    {
        v1 = rand() % solution.size();
        v2 = rand() % solution.size();
    }

    temp = swapped[v1];
    swapped[v1] = swapped[v2];
    swapped[v2] = temp;
    new_move.swapped.push_back(make_pair(v1 < v2 ? v1 : v2, v1 < v2 ? v2 : v1));
    last_move = new_move;
    return swapped;
}

vector<vector<int>> ProblemInstance::add_jobs(int jobs_number)
{
    auto new_sol = solution;
    int job, worker, place, tries;
    TabooMove new_move;
    while (jobs_number > 0)
    {

        tries = 0;
        do
        {

            worker = rand() % solution.size();
        } while (tries++ < MAX_TRIES && new_sol[worker].size() >= tasks_size);

        if (tries > MAX_TRIES)
        {
            last_move = new_move;
            return new_sol;
        }

        tries = 0;
        do
        {

            job = rand() % tasks_size;
        } while (tries++ < MAX_TRIES && find(new_sol[worker].begin(), new_sol[worker].end(), job) != new_sol[worker].end()); //dont add job that actually is in worker list

        if (tries > MAX_TRIES)
        {
            last_move = new_move;
            return new_sol;
        }

        place = rand() % (new_sol[worker].size() + 1);

        new_sol[worker].insert(new_sol[worker].begin() + place, job);
        new_move.added.push_back(make_pair(worker, job));
        jobs_number--;
    }
    last_move = new_move;
    return new_sol;
}

vector<vector<int>> ProblemInstance::take_from_another_worker(int jobs_number)
{
    auto new_sol = solution;
    int job, worker1, worker2, place, tries;
    TabooMove new_move;
    while (jobs_number > 0)
    {

        tries = 0;
        do
        {
            worker1 = rand() % solution.size();
            worker2 = rand() % solution.size();
        } while (tries++ < MAX_TRIES && ((worker1 == worker2) || new_sol[worker1].size() == 0));

        if (tries > MAX_TRIES)
        {
            last_move = new_move;
            return new_sol;
        }

        job = new_sol[worker1][rand() % (new_sol[worker1]).size()];

        place = rand() % (new_sol[worker2].size() + 1);

        new_sol[worker2].insert(new_sol[worker2].begin() + place, job);

        new_move.added.push_back(make_pair(worker2, job));
        new_move.deleted.push_back(make_pair(worker1, job));
        jobs_number--;
    }

    last_move = new_move;
    return new_sol;
}
vector<vector<int>> ProblemInstance::remove_jobs(int jobs_number)
{
    auto new_sol = solution;
    int worker, place, tries;
    TabooMove new_move;
    while (jobs_number > 0)
    {

        tries = 0;

        do
        {
            worker = rand() % solution.size();
        } while (tries++ < MAX_TRIES && new_sol[worker].size() == 0);
        if (tries > MAX_TRIES)
        {
            last_move = new_move;
            return new_sol;
        }

        place = rand() % (new_sol[worker].size());

        new_sol[worker].erase(new_sol[worker].begin() + place);
        new_move.deleted.push_back(make_pair(worker, new_sol[worker][place]));
        jobs_number--;
    }
    last_move = new_move;
    return new_sol;
}

vector<vector<int>> ProblemInstance::give_job_to_lazy_worker()
{
    auto new_sol = solution;
    int laziest_worker, hardest_working_worker, job;
    int biggest_task_amount = 0;
    int smallest_task_amount = BIG_NUMBER;
    TabooMove new_move;

    laziest_worker = -1;
    for (auto it = new_sol.begin(); it != new_sol.end(); it++)
    {
        if ((*it).size() < smallest_task_amount)
        {
            laziest_worker = distance(new_sol.begin(), it);
            smallest_task_amount = (*it).size();
        }
        if ((*it).size() > biggest_task_amount)
        {
            hardest_working_worker = distance(new_sol.begin(), it);
            biggest_task_amount = (*it).size();
        }
    }
    if (laziest_worker != -1 && biggest_task_amount > 0)
    {
        job = *(new_sol[hardest_working_worker].end() - 1);
        new_sol[laziest_worker].push_back(job);
        new_sol[hardest_working_worker].erase(new_sol[hardest_working_worker].end() - 1);
        last_move.added.push_back(make_pair(hardest_working_worker, job));
        last_move.deleted.push_back(make_pair(laziest_worker, job));
    }

    last_move = new_move;
    return new_sol;
}
vector<vector<int>> ProblemInstance::add_and_remove_jobs(int jobs_add, int jobs_remove)
{
    auto new_sol = solution;
    int worker, place, tries, job;
    TabooMove new_move;
    while (jobs_remove > 0)
    {

        tries = 0;

        do
        {
            worker = rand() % solution.size();
        } while (tries++ < MAX_TRIES && new_sol[worker].size() == 0);

        if (tries > MAX_TRIES)
        {
            last_move = new_move;
            return new_sol;
        }

        place = rand() % (new_sol[worker].size());
        new_sol[worker].erase(new_sol[worker].begin() + place);
        jobs_remove--;
        new_move.deleted.push_back(make_pair(worker, job));
    }

    while (jobs_add > 0)
    {

        tries = 0;
        do
        {
            worker = rand() % solution.size();
        } while (tries++ < MAX_TRIES && new_sol[worker].size() >= tasks_size);

        tries = 0;
        do
        {
            job = rand() % tasks_size;
        } while (tries++ < MAX_TRIES && find(new_sol[worker].begin(), new_sol[worker].end(), job) != new_sol[worker].end()); //dont add job that actually is in worker list
        if (tries > MAX_TRIES)
        {
            last_move = new_move;
            return new_sol;
        }
        place = rand() % (new_sol[worker].size() + 1);

        new_sol[worker].insert(new_sol[worker].begin() + place, job);
        new_move.added.push_back(make_pair(worker, job));
        jobs_add--;
    }
    last_move = new_move;
    return new_sol;
}

void ProblemInstance::log_gantt_chart()
{
    ofstream myfile("output.csv");
    ofstream statisticfile("statistic.csv");
    if (myfile.is_open())
    {
        myfile << "data from algorithm" << endl;
        auto it_time = gantt_worker_time.begin();
        auto it_job = gantt_worker_jobs.begin();
        while (it_time != gantt_worker_time.end())
        {

            for (auto it_time_ins = (*it_time).begin(); it_time_ins != (*it_time).end(); it_time_ins++)
            {
                myfile << *it_time_ins << " ; ";
            }
            myfile << endl;

            it_time++;
        }

        while (it_job != gantt_worker_jobs.end())
        {

            for (auto it_job_ins = (*it_job).begin(); it_job_ins != (*it_job).end(); it_job_ins++)
            {
                myfile << *it_job_ins << " ; ";
            }

            myfile << endl;
            it_job++;
        }
    }
    if (statisticfile.is_open())
    {

        statisticfile << "Best cost ; " << best_cost_ever << endl;
        statisticfile << "Neighbours generated ; " << correct_generated + incorrect_generated << endl;
        statisticfile << "Part of correct neighbours generated ; " << 1.0 * correct_generated / (correct_generated + incorrect_generated) << endl;
        statisticfile << "Steps done ; " << (correct_generated + incorrect_generated) / NEIGHBOUR_SIZE << endl;
        statisticfile << "Working time in seconds ; " << WORKING_TIME << endl;
        statisticfile << "Solutions allowed by taboo list ; " << taboo_list.allowed << endl;
        statisticfile << "Solutions blocked by taboo list ; " << taboo_list.blocked << endl;
        statisticfile << "Aspirations ; " << aspiration_used << endl;
        statisticfile << "taboo hitlist ; " << endl;
        for (auto it = taboo_list.hitlist.begin(); it != taboo_list.hitlist.end(); it++)
            statisticfile << *it << " ; ";

        statisticfile << endl
                      << "Best cost history" << endl;

        for (auto it = iteration_data_for_plot.begin(); it != iteration_data_for_plot.end(); it++)
            statisticfile << *it << " ; ";  
        statisticfile << (correct_generated + incorrect_generated) / NEIGHBOUR_SIZE << endl ;     
        
        for (auto it = cost_data_for_plot.begin(); it != cost_data_for_plot.end(); it++)
            statisticfile << *it << " ; ";

        statisticfile << best_cost_ever << endl;
  
  
    }

    myfile.close();
}

void ProblemInstance::log_consts()
{
    ofstream consts_file("consts.csv");
    if(consts_file.is_open())
    {
        consts_file << "amount od skills ; " << amount_of_skills << endl;
        consts_file << "workers_amount ; " << workers_amount << endl;
        consts_file << "problems_amount ; " << problems_amount << endl;
        consts_file << "taboo_size ; " << TABOO_SIZE;
        consts_file << "neighbour_size ; " << NEIGHBOUR_SIZE;
        consts_file << "ADD_THRESHOLD ; " << ADD_THRESHOLD << endl;
        consts_file << "REMOVE_THRESHOLD ; " << REMOVE_THRESHOLD << endl;
        consts_file << "ADD_AND_REMOVE_THRESHOLD ; " << ADD_AND_REMOVE_THRESHOLD << endl;
        consts_file << "SWAP_THRESHOLD ; " << SWAP_THRESHOLD << endl;
        consts_file << "TAKE_THRESHOLD ; " << TAKE_THRESHOLD << endl;
        consts_file << "TO_LAZY_THRESHOLD ; " << TO_LAZY_THRESHOLD << endl;   
    }
    consts_file.close();
}

void ProblemInstance::get_neighbours(int how_many)
{
    neighbours.clear();
    for (int i = 0; i < how_many; i++)
    {
        neighbours.push_back(swap_workers());
        neighbours.push_back(add_jobs(1 + rand() % 4));
        neighbours.push_back(remove_jobs(1 + rand() % 3));
        neighbours.push_back(add_and_remove_jobs(1 + rand() % 3, 1 + rand() % 3));
    }
}
void ProblemInstance ::get_one_neighbour()
{
    float probability = (rand() % 1000) / 1000.0;

    neighbours.clear();
    if (probability < ADD_THRESHOLD)
    {

        neighbours.push_back(add_jobs(1 + rand() % MAX_ADDED_TASK));

    }
    else if (probability < REMOVE_THRESHOLD)
    {

        neighbours.push_back(remove_jobs(1 + rand() % MAX_REMOVED_TASK));

    }
    else if (probability < ADD_AND_REMOVE_THRESHOLD)
    {

        neighbours.push_back(add_and_remove_jobs(1 + rand() % MAX_ADDED_TASK, 1 + rand() % MAX_REMOVED_TASK));

    }
    else if (probability < SWAP_THRESHOLD)
    {
        neighbours.push_back(swap_workers());
    }
    else if (probability < TAKE_THRESHOLD)
    {

        neighbours.push_back(take_from_another_worker(1 + rand() % MAX_TAKE_FROM_ANOTHER));
    }

    else if (probability < TO_LAZY_THRESHOLD)
    {

        neighbours.push_back(give_job_to_lazy_worker());

    }
    else
    cout << "no return!";
}

void ProblemInstance::search_randomly(int how_many)
{
    while (how_many-- > 0)
    {
        get_neighbours();
        auto temp = solution;
        float temp_cost = cost;
        for (auto it = neighbours.begin(); it != neighbours.end(); it++)
        {
            temp = solution;
            temp_cost = cost;
            solution = *it;
            //show_solution();
            if (analyze_solution(solution) && temp_cost > cost)
            { // new better found

                continue;
            }

            else
            {
                solution = temp; // return to previous;
                cost = temp_cost;
            }
        }
    }
}

void ProblemInstance ::step()
{
    float this_step_best_cost;
    int i = 0;
    bool acceptable;
    this_step_best_cost = BIG_NUMBER;

    while (i++ < NEIGHBOUR_SIZE)
    {

        try{

            get_one_neighbour();

        }catch(...){
            cout << "catch activated" << endl;
        }


        acceptable = analyze_solution(neighbours[0]);

        if (acceptable)
        {
            correct_generated++;
            if (taboo_list.is_on_list(last_move))
            {
                if (cost < best_cost_ever)
                { //kryterium aspiracji
                    cout << endl
                         << "kryterium aspiracji! " << cost;
                    aspiration_used++;
                    iteration_data_for_plot.push_back( ( incorrect_generated + correct_generated )/NEIGHBOUR_SIZE );
                    cost_data_for_plot.push_back(cost);
                    show_solution();
                    if (cost < taboo_list.last_medium_cost * MEDIUM_APPEND_THRESHOLD)
                    {
                        taboo_list.mediumList.push_back(neighbours[0]);
                        taboo_list.last_medium_cost = cost;
                        cout << endl
                             << "appending to medium-term memory";
                    }
                    iterations_since_new_value_found = 0;
                    this_step_best_cost = cost;
                    solution = neighbours[0];
                    taboo_list.add(last_move);

                    best_solution = solution;
                    best_cost_ever = this_step_best_cost;
                }
            }
            else
            {
                if (cost < this_step_best_cost)
                {                                       
                    this_step_best_cost = cost;
                    solution = neighbours[0];
                    taboo_list.add(last_move);
                }
            }
        }
        else
        {
            incorrect_generated++;
            //not acceptable
        }
    }

    // if (this_step_best_cost < 100000)
    //     cost_data_for_plot.push_back(this_step_best_cost);
    // else
    //     cost_data_for_plot.push_back(0.0);

    if (this_step_best_cost < best_cost_ever)
    {

        iteration_data_for_plot.push_back( ( incorrect_generated + correct_generated )/NEIGHBOUR_SIZE );
        cost_data_for_plot.push_back(this_step_best_cost); 
        iterations_since_new_value_found = 0;
        if (this_step_best_cost < taboo_list.last_medium_cost * MEDIUM_APPEND_THRESHOLD)
        {
            taboo_list.mediumList.push_back(best_solution);
            taboo_list.last_medium_cost = this_step_best_cost;
            cout << endl
                 << "appending to medium-term memory";
        }
        best_solution = solution;
        best_cost_ever = this_step_best_cost;
        cout << endl
             << "new cost: " << best_cost_ever;
             show_solution();
    }
    iterations_since_new_value_found++;

    if (iterations_since_new_value_found > MEDIUM_MEMORY_ITERATIONS_THRESHOLD && taboo_list.mediumList.size() > 0)
    {
        iterations_since_new_value_found = 0;
        solution = taboo_list.get_solution_from_medium_memory();
        cout << endl
             << "getting solution from medium memory";
             if(solution.size() == 0){
                 build_first_solution(false);
                 cout << "BFS";
             }
    }
}
