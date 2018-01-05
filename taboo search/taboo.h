#ifndef TABOO_H_
#define TABOO_H_
#include <algorithm>
#include <utility>
#include <vector>
#include "consts.h"
#include <iostream>

using namespace std;

class TabooMove{
    public:

    vector<pair<int,int>> added;
    vector<pair<int,int>> deleted;
    vector<pair<int,int>> swapped;   

    bool is_similar(TabooMove & move);
};


class TabooList{
    vector<TabooMove> shortList;
    vector<long int> hitlist;
    int size;
    long int blocked;
    long int allowed;
    public:
    TabooList(int max_size = TABOO_SIZE);
    void add(TabooMove& move);
    bool is_on_list(TabooMove& move);
    void show_hitlist();
};

#endif