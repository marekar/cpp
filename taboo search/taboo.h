#ifndef TABOO_H_
#define TABOO_H_
#include <algorithm>
#include <utility>
#include <vector>
#include "consts.h"
#include <iostream>

using namespace std;

class TabooMove
{
  public:
    vector<pair<int, int>> added;
    vector<pair<int, int>> deleted;
    vector<pair<int, int>> swapped;

    bool is_similar(TabooMove &move);
};

class TabooList
{
    vector<TabooMove> shortList;

    int size;

  public:
    vector<long int> hitlist;

    long int blocked;
    long int allowed;

    vector<vector<vector<int>>> mediumList;
    float last_medium_cost;
    TabooList(int max_size = TABOO_SIZE);
    void add(TabooMove &move);
    bool is_on_list(TabooMove &move);
    void show_hitlist();
    vector<vector<int>> get_solution_from_medium_memory();
};

#endif