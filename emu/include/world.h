#ifndef _H_WORLD_
#define _H_WORLD_

#include <boost/shared_ptr.hpp>
#include <string>

namespace environment
{
class world
{
  public:
    world(std::string const & title, 
          size_t x = 0, 
          size_t y = 0, 
          size_t width = 640, 
          size_t height = 480,
          bool headless = false);
    ~world();
    void run_script(std::string const & script);
    void run_file(std::string const & file);
    void stop();
    void start();
    void reset();
  private:
    void python_prepare();
    void routine();
    struct pimpl;
    boost::shared_ptr<pimpl> data_;
    bool headless_;
    
};
}
#endif //_H_WORLD_
