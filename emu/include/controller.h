#ifndef _H_CONTROLLER_
#define _H_CONTROLLER_

#include "types.h"

//forward declarations
namespace irr
{
namespace scene
{
  class ISceneCollisionManager;
}
}

namespace environment
{
class controller
{
  public:
    controller(irr::scene::ISceneCollisionManager * collision_manager);
    ~controller();
    double ray_traverse(vector3 const & direction) const;
    double cone_traverse(vector3 const & direction, 
                         double angle) const;
    double ray_traverse() const;
    double cone_traverse(double angle) const;
                         
    void set_speed(double left, 
                   double right);
    void draw();
    
  private:
    irr::scene::ISceneCollisionManager * collision_manager_;
    vector3 position_;
    vector3 direction_;
};
}


#endif //_H_CONTROLLER_