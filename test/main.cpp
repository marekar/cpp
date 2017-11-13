#include <iostream>
#include <vector> //vector class-template
#include <set>
#include <map>

#include <algorithm>
#include <numeric>

using namespace std;

typedef multimap <int, string, less<int> > mp_type;
int main()
{
    cout << "Marek Piekarz, AGH AiR II rok" << endl << endl;
    cout << "ZADANIE A - VECTOR" << endl << endl;
   
    vector<int> v;
    // add integers at the end of the vector
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(7);
    v.push_back(5);
    
    v.insert(++v.begin(), 7);
    v[0] = 9;
    v.push_back(v[0]);
    v.push_back(v[1]);
    cout <<"Pierwszy element o wartosci 3 to: " << *find(v.begin(), v.end(),3) << endl;
    v.erase(find(v.begin(), v.end(), 3));
    cout <<"Element o najmniejszej wartosci: " << *min_element(v.begin(), v.end()) << endl;
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    cout << "Ilosc dziewiatek: " << count(v.begin(), v.end(), 9) <<endl;
    cout << "Suma 4 pierwszych elementow: " << accumulate(v.begin(), v.begin()+4, 0)<<endl;

    // display info about v
    cout << "The size of v is: " << v.size() << "\nThe capacity of v is: " << v.capacity();
    vector<int>::const_iterator it;
    cout << "\nThe content of v is: ";

    for (it = v.begin(); it != v.end(); it++)
    {
    cout << *it << " ";
    }
    cout << endl << "==================================" << endl << endl;
    //====================================================

    cout << "ZADANIE B SET" << endl << endl;

    set<int, less <int> > s;
    
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(7);
    s.insert(5);

    s.insert(7);
    s.erase(s.begin());
    s.insert(s.begin(), 9);
    cout <<"Pierwszy element o wartosci 3 to: " << *find(s.begin(), s.end(),3) << endl;
    s.erase(find(s.begin(), s.end(), 3));
    cout <<"Element o najmniejszej wartosci: " << *min_element(s.begin(), s.end()) << endl;
    cout << "Ilosc dziewiatek: " << count(s.begin(), s.end(), 9) <<endl;
    cout << "Suma wszystkich elementow: " << accumulate(s.begin(), s.end(), 0)<<endl;
    
    cout <<"\nThe content of s is: ";
    set<int, less <int> > ::iterator it_s;
    for (it_s = s.begin(); it_s != s.end(); it_s++)
    {
        cout << *it_s << " ";
    }
    cout << endl << "==================================" << endl << endl;
    //====================================================

    cout << "Zadanie C MULTIMAP" << endl << endl;

    mp_type mp;
    mp_type::iterator it_mp;

    mp.insert(pair<int, string>(2, "dwa"));
    mp.insert(pair<int, string>(3, "trzy"));
    mp.insert(pair<int, string>(4, "cztery"));
    mp.insert(pair<int, string>(7, "siedem"));
    mp.insert(pair<int, string>(5, "piec"));

    mp.insert(pair<int, string>(7, "siedem"));
    mp.erase(mp.begin());
    mp.insert(pair<int, string>(9, "dziewiec"));

    pair <int, string> temp = *mp.begin();
    it_mp = ++mp.begin();
    mp.insert(temp);
    mp.insert(*it_mp);

    pair <mp_type::iterator, mp_type::iterator> three;
    three = mp.equal_range(3);
    cout << "Elementy o wartosci 3: " << endl;
    mp_type::iterator ite;
    for (ite = three.first; ite != three.second; ++ite)
    {
        cout << "[" << ite->first << " - " << ite->second << "]" << endl;
    }

    mp.erase(3);
	cout << "\nElement o najmniejszej wartosci: "<< endl << "[" << (*min_element(mp.begin(), mp.end())).first << " - " << (*min_element(mp.begin(), mp.end())).second << "]" << endl;
    cout << "\nIlosc dziewiatek: " << mp.count(9) << endl;
    cout << "Suma 4 pierwszych elementow: ";
    int sum = 0;
    it_mp = mp.begin();
    for (int i = 0; i<4; i++)
    {
        sum += (*it_mp).first;
        it_mp++;
    }
    cout << sum << endl;
    
    //
    cout << "\nThe content of mp is: " << endl;
    for (it_mp = mp.begin(); it_mp != mp.end(); it_mp++)
    {
        cout << "[" << (*it_mp).first << " - " << (*it_mp).second << "]" << endl;
    }
    return 0;
}