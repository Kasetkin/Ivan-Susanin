#include "grid.h"

#include <queue>
#include <set>
#include <cmath>
#include <numeric>
#include <cstdlib>
#include <iostream>

grid::grid(int size, double resolution) :
    map(size, std::vector<bool>(size, 0)), resolution_(resolution)
{
}

grid::~grid()
{
}

void grid::add_obstacle(double x, double y)
{
      std::cout << "WALL" << (int)(x / resolution_) + map.size() / 2 << (int)(y / resolution_) + map.size() / 2 << std::endl;
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
    node & operator =(node const & n);
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

node & node::operator =(node const & n)
{
    if (ptr)
    {
        --(ptr->ref);
        if (!(ptr->ref))
          delete ptr;
    }
    ptr = n.ptr;
    if (ptr)
        ++(ptr->ref);
}

node::node (int x, int y, double cost, node const & parent) :
    ptr(new body)
{
    if (!parent.valid())
      std::cout << "WTF PARENT INVALID" << std::endl;
    ptr->ref = 1;
    ptr->x = x;
    ptr->y = y;
    ptr->cost = cost;
    ptr->parent = parent;
    if (!ptr->parent.valid())
      std::cout << "WTF PARENT INVALID" << std::endl;
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
    return ptr->cost > n.ptr->cost;
}

bool node::valid() const
{
    return (ptr != 0);
}

node node::get_parent() const
{
    if (ptr)
    {
        std::cout << "PARENT " << ptr->parent.valid() << std::endl;
        return ptr->parent;
    }
    else
    {
        std::cout << "INVALID" << std::endl;
        return node();
    }
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

std::list<std::pair<double, double> > grid::make_path(double x, double y, double px, double py) const
{
      int tx = (int)(px / resolution_) + map.size() / 2;
      int ty = (int)(py / resolution_) + map.size() / 2;
      std::priority_queue<node> q;
      q.push(node((int)(x / resolution_) + map.size() / 2, 
                  (int)(y / resolution_) + map.size() / 2, 
                  (x - tx) * (x - tx) +
                  (y - ty) * (y - ty)));
      
      std::set<std::pair<int, int> > marked;
      marked.insert(std::make_pair(q.top().x(), q.top().y()));
      node end;
      
      while (!q.empty())
      {
            node n = q.top();
            //std::cout << "V " << n.x() << " " << n.y() << std::endl;
            q.pop();
            for (int i = -1; i <= 1; ++i)
              for (int j = -1; j <= 1; ++j)
              {
                  if (n.x() + i < 0 || n.x() + i >= map.size() || n.y() + j < 0 || n.y() + j >= map.size())
                      continue;
                  if (i || j)//(std::abs(i) + std::abs(j) == 1)
                  {
                        if (!has_obstacle(n.x() + i, n.y() + j) && marked.count(std::make_pair(n.x() + i, n.y() + j)) <= 0)
                        {
                              node ne(n.x() + i, n.y() + j, 
                                      n.cost() - 
                                      (n.x() - tx) * (n.x() - tx) + 
                                      (n.y() - ty) * (n.y() - ty) + 
                                      (n.x() - tx + i) * (n.x() - tx + i) + 
                                      (n.y() - ty + j) * (n.y() - ty + j), n);
                              //std::cout << "V " << ne.x() << " " << ne.y() << std::endl;
                              if (n.x() + i == tx && n.y() + j == ty)
                              {
                                  end = ne;
                                  goto finish;
                              }
                              q.push(ne);
                              marked.insert(std::make_pair(ne.x(), ne.y()));
                              
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
              //std::cout << "TRACE" << std::endl;
              path.push_front(std::make_pair((end.x() - map.size() / 2) * resolution_ + resolution_ / 2, (end.y() - map.size() / 2) * resolution_ + resolution_ / 2));
              end = end.get_parent();
          }
          return path;
      }
      else
      {
        std::cout << "NO PATH" << std::endl;
        return std::list<std::pair<double, double> >();
      }
}

bool grid::has_obstacle(int x, int y) const
{
      return map[x][y];
}