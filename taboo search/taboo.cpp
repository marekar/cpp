#include "taboo.h"

using namespace std;

TabooList::TabooList(int max_size){
    blocked = 0;
    allowed = 0;
    if(max_size > 0){
        size = max_size;
    }
    else
        size = 0;
    
    last_medium_cost = BIG_NUMBER;
    hitlist = vector<long int>(size, 0);

}

bool TabooList::is_on_list(TabooMove& move){
    bool onlist = false;

    int i = 0;

    for(auto it = shortList.begin() ; it != shortList.end() ; it++){

        if(it -> is_similar(move) ){
            ( hitlist[i] )++;
            onlist = true;
            break;
        }
        i++;
    }
    if(onlist){
       blocked++;
    }

    else{
       allowed++;
    }

        
    return onlist;
}

void TabooList::add(TabooMove& move){
    auto temp = move.added;
    move.added = move.deleted;
    move.deleted = temp;

    shortList.push_back(move);
    if (shortList.size() > size){
        shortList.erase(shortList.begin());
    }
}


bool TabooMove::is_similar(TabooMove & move){
    
    if(added.size() != 0 && move.added.size() != 0)
    for(auto it = added.begin() ; it != added.end() ; it++){
        for(auto it2 = move.added.begin() ; it2 != move.added.end() ; it2++){
            if( ( (*it).first == (*it2).first) && ( (*it).second == (*it2).second) )
                return true;
        }
    }

    if(deleted.size() != 0 && move.deleted.size() != 0)
    for(auto it = deleted.begin() ; it != deleted.end() ; it++){
        for(auto it2 = move.deleted.begin() ; it2 != move.deleted.end() ; it2++){
            if( ( (*it).first == (*it2).first) && ( (*it).second == (*it2).second) )
                return true;
        }
    }

    if(swapped.size() != 0 && move.swapped.size() != 0)
    for(auto it = swapped.begin() ; it != swapped.end() ; it++){
        for(auto it2 = move.swapped.begin() ; it2 != move.swapped.end() ; it2++){
            if( ( (*it).first == (*it2).first) && ( (*it).second == (*it2).second) )
                return true;
        }
    }


    return false;
}

void TabooList::show_hitlist(){
    cout << endl << "taboo hitlist:  " << "blocked: " << blocked << "  allowed: "<<allowed << "   " <<  100.0*allowed/ (blocked+ allowed)  << "% of all"
     <<endl;
    for (auto it = hitlist.begin() ; it != hitlist.end() ; it++){
        cout << *it << " ";
    }
    cout << endl;

}

vector< vector < int > > TabooList::get_solution_from_medium_memory(){
    float probability;
    probability = rand() % mediumList.size();
    probability = probability * probability * probability / float(mediumList.size() * mediumList.size() );
    return ( mediumList[mediumList.size() - 1  - int(probability)]);
}