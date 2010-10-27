#include "grid.h"

#include <queue>
#include <set>
#include <cmath>

grid::grid(int size, double resolution) :
    map(size, std::vector<bool>(size, 0)), resolution_(resolution)
{
}

grid::~grid()
{
}

void grid::add_obstacle(double x, double y)
{
      map[(int)(x / resolution_) + map.size() / 2][(int)(y / resolution_) + map.size() / 2] = 1;
}

struct node
{
    struct body;
    body * ptr;
    
    node(node const & n);
    node (int x, int y, double cost, node const & parent);
    node (int x, int y, double cost) ;
    node();
    ~node();
    bool operator < (node const & n) const;
    bool valid() const;
    node get_parent() const;
    int & x() const;
    int & y() const;
    double & cost() const;
};

struct node::body
{
    int x, y;
    double cost;
    node parent;
    int ref;
};

node::node()  :
    ptr(0)
{
}

node::node(node const & n)
{
    ptr = n.ptr;
    if (ptr)
        ++(ptr->ref);
}

node::node (int x, int y, double cost, node const & parent) :
    ptr(new body)
{
    ptr->ref = 1;
    ptr->x = x;
    ptr->y = y;
    ptr->cost = cost;
    ptr->parent = parent;
}

node::node (int x, int y, double cost) :
    ptr(new body)
{
    ptr->ref = 1;
    ptr->x = x;
    ptr->y = y;
    ptr->cost = cost;
}

node::~node()
{
    if (!ptr)
      return;
    --(ptr->ref);
    if (!(ptr->ref))
      delete ptr;
}

bool node::operator < (node const & n) const
{
    return ptr->cost < n.ptr->cost;
}

bool node::valid() const
{
    return ptr != 0;
}

node node::get_parent() const
{
    if (ptr)
        return ptr->parent;
    else
        return node();
}

int & node::x() const
{
    return ptr->x;
}

int & node::y() const
{
    return ptr->y;
}

double & node::cost() const
{
    return ptr->cost;
}

bool operator < (std::pair<int, int> const & a, std::pair<int, int> const & b)
{
    if (a.first != b.first)
      return a.first < b.first;
    return a.second < b.second;
}
#include <iostream>
std::list<std::pair<double, double> > grid::make_path(double x, double y, double px, double py) const
{
      int tx = (int)(px / resolution_);
      int ty = (int)(py / resolution_);
      std::cout << tx << " = " << ty  << std::endl;
      std::priority_queue<node> q;
      q.push(node((int)(x / resolution_), (int)(y / resolution_), x * x + y * y));
      
      std::set<std::pair<int, int> > marked;
      marked.insert(std::make_pair(q.top().x(), q.top().y()));
      node end;
      std::cout << "ADD" << std::endl;
      while (!q.empty())
      {
            node n = q.top();
            q.pop();
            std::cout << "POP" << std::endl;
            for (int i = -1; i <= 1; ++i)
              for (int j = -1; j <= 1; ++j)
              {
                  if (n.x() + i < 0 || n.x() + i >= map.size() || n.y() + j < 0 || n.y() + j >= map.size())
                      continue;
                  if (std::abs(i) + std::abs(j) == 1)
                  {
                        std::cout << (n.x() + i) << " " <<  (n.y() + j) << std::endl;
                        if (!has_obstacle(n.x() + i, n.y() + j) && marked.count(std::make_pair(n.x() + i, n.y() + j)) <= 0)
                        {
                              std::cout << "GO " << (n.x() + i) << " " <<  (n.y() + j) << std::endl;
                              if (n.x() + i == tx && n.y() + j == ty)
                              {
                                  end = n;
                                  std::cout << "FOUND" << std::endl;
                                  goto finish;
                              }
                              node ne(n.x() + i, n.y() + j, n.cost() - n.x() * n.x() + n.y() * n.y() + (n.x() + i) * (n.x() + i) + (n.y() + j) * (n.y() + j), n);\
                              std::cout << "ADD" << std::endl;
                              q.push(ne);
                              marked.insert(std::make_pair(ne.x(), n.y()));
                        }
                  }
              }      
      }
      finish:
      if (end.valid())
      {
          std::list<std::pair<double, double> > path;
          while (end.valid())
          {
              path.push_front(std::make_pair(end.x() * resolution_ + resolution_ / 2, end.y() * resolution_ + resolution_ / 2));
              end = end.get_parent();
          }
          return path;
      }
      else
        return std::list<std::pair<double, double> >();
}

bool grid::has_obstacle(int x, int y) const
{
      return map[x][y] == 1;
}