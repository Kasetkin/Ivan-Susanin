#include "grid.h"
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int main()
{
    freopen("grid.in", "rt", stdin);
    freopen("grid.out", "wt", stdout);
    int size;
    cin >> size >> ws;
    grid g(size * 2 + 1, 1);
    for (int i = 0; i < size; ++i)
    {
        string s;
        cin >> s >> ws;
        for (int j = 0; j < size; ++j)
        {
              if (s[j] == '#')
                  g.add_obstacle(i + 0.5, j + 0.5);
        }
    }  
    std::list<std::pair<double, double> > p = g.make_path(0.5, 0.5, size - 1, size - 1);
    cout << p.size() << "\n";
    for (std::list<std::pair<double, double> >::iterator it = p.begin(); it != p.end(); ++it)
    {
        cout << it->first << " " << it->second << "\n";
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
    
}