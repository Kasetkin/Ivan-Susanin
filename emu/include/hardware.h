#ifndef _H_HARDWARE_
#define _H_HARDWARE_

#include <boost/shared_ptr.hpp>

#include "types.h"
#include "controller.h"


namespace environment
{
class hardware
{
  public:
    hardware(boost::shared_ptr<controller> const & c);
    ~hardware();
    
    //must exported to python
      //sensors
    double ray_distance(double x, double y, double z) const;
    double ir_distance(double x, double y, double z) const;
    double wave_distance(double x, double y, double z) const;
      //controls
    void set_speed(double left, double right);
    
  private:
    boost::shared_ptr<controller> robo_;
};
}


#endif //_H_HARDWARE_