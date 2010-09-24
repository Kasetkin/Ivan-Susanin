#include "hardware.h"
namespace environment
{
hardware::hardware(boost::shared_ptr<controller> const & c) :
  robo_(c)
{
}

hardware::~hardware()
{
}

//must exported to python
  //sensors
double hardware::ray_distance(double x, double y, double z) const
{
    return robo_->ray_traverse(vector3(x, y, z));
}

double hardware::ir_distance(double x, double y, double z) const
{
    return robo_->cone_traverse(vector3(x, y, z), 5);
}

double hardware::wave_distance(double x, double y, double z) const
{
    return robo_->cone_traverse(vector3(x, y, z), 5);
}

  //controls
void hardware::set_speed(double left, double right)
{
    robo_->set_speed(left, right);
}
}
