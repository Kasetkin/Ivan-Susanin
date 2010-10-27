#ifndef _H_GRID_
#define _H_GRID_

#include <list>
#include <vector>

class grid
{
  public:
    grid(int size, double resolution);
    ~grid();
    void add_obstacle(double x, double y);
    std::list<std::pair<double, double> > make_path(double x, double y, double px, double py) const;

  private:
    bool has_obstacle(int x, int y) const;
    //FIXME: it's ugly
    std::vector<std::vector<bool> > map;
    double resolution_;
    
};

#endif //_H_GRID_