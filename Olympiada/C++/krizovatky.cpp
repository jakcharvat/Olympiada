//
//  main.cpp
//  Olympiada
//
//  Created by Jakub Charvat on 31.10.2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;


//MARK: - Krizovatka
class Krizovatka
{
public:
    int id;
    bool podVodou = false;
    vector<Krizovatka> pripojeneKrizovatky;
};


ostream &operator<<(std::ostream &os, Krizovatka const &krizovatka) {
    string pripojeneKrizovatky = "";
    for (Krizovatka const& pripojka : krizovatka.pripojeneKrizovatky)
    {
        if (pripojeneKrizovatky.empty())
        {
            pripojeneKrizovatky.append(to_string(pripojka.id));
        }
        else
        {
            pripojeneKrizovatky.append(" " + to_string(pripojka.id));
        }
    }
    
    return os << krizovatka.id << ": " << krizovatka.podVodou << " - " << pripojeneKrizovatky << "\n";
}


//MARK: BFSKrizovatka
class BFSKrizovatka
{
public:
    Krizovatka current;
    vector<Krizovatka> routeToCurrent;
    int distance = 0;
};


//MARK: - Run
void runPrivalovyDest()
{
    int n; int m; int k;
    cin >> n >> m >> k;
    
    Krizovatka krizovatky[n];
    for (int i = 0; i < n; i ++)
    {
        int potopena;
        cin >> potopena;
        
        Krizovatka krizovatka;
        krizovatka.id = i;
        krizovatka.podVodou = potopena == 1;
        krizovatky[i] = krizovatka;
    }
    
    for (int i = 0; i < m; i ++)
    {
        int krizovatka1, krizovatka2;
        cin >> krizovatka1 >> krizovatka2;
        
        krizovatky[krizovatka1].pripojeneKrizovatky.push_back(krizovatky[krizovatka2]);
        krizovatky[krizovatka2].pripojeneKrizovatky.push_back(krizovatky[krizovatka1]);
    }
    
    
    //MARK: BFS
    queue<BFSKrizovatka> queue;
    BFSKrizovatka homeKrizovatka;
    homeKrizovatka.current = krizovatky[n - 1];
    queue.push(homeKrizovatka);
    
    set<int> visitedKrizovatkas;
    visitedKrizovatkas.insert(n - 1);
    
    while (!queue.empty())
    {
        BFSKrizovatka krizovatka = queue.front();
        queue.pop();
        
        int newDistance = krizovatka.distance + 1;
        vector<Krizovatka> newRoute = krizovatka.routeToCurrent;
        newRoute.push_back(krizovatka.current);
        
        for (Krizovatka pripojka : krizovatka.current.pripojeneKrizovatky)
        {
            if (pripojka.id == 0)
            {
                cout << "\n" << krizovatka.distance << "\n";
                return;
            }
            
            if (visitedKrizovatkas.find(pripojka.id) != visitedKrizovatkas.end()) continue;
            
            if (!pripojka.podVodou || newDistance <= k)
            {
                visitedKrizovatkas.insert(pripojka.id);
                BFSKrizovatka newKrizovatka;
                newKrizovatka.current = pripojka;
                newKrizovatka.distance = newDistance;
                newKrizovatka.routeToCurrent = newRoute;
                queue.push(newKrizovatka);
            }
        }
    }
    
    cout << "\n-1\n";
}
