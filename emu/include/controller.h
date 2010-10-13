#ifndef _H_CONTROLLER_
#define _H_CONTROLLER_

#include "types.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#include "newton_utils.h"

//forward declarations
namespace irr
{
namespace scene
{
  class ISceneCollisionManager;
  class ICameraSceneNode;
  class IAnimatedMeshSceneNode;
}
class IrrlichtDevice;
}
class NewtonCollision;

namespace environment
{
class controller
{
  public:
    controller(irr::IrrlichtDevice * device, SObject * land, NewtonWorld *nWorld);
    ~controller();
    double ray_traverse(vector3 const & direction) const;
    double cone_traverse(vector3 const & direction, 
                         double angle) const;
    double ray_traverse() const;
    double cone_traverse(double angle) const;
                         
    void set_speed(double left, 
                   double right);
    void draw();
    vector3 destination(double x, double y, double z);
    
  private:
    irr::scene::ISceneCollisionManager * collision_manager_;
    irr::scene::ICameraSceneNode * camera_;
    irr::scene::IAnimatedMeshSceneNode* node_;
    NewtonCollision * nwtn_collision_;
    NewtonWorld *nWorld_;
    SObject * land_;
    vector3 position_;
    vector3 direction_;
    double lspeed_, rspeed_;
    double rotation;
    mutable boost::mutex mutex_; 
};
}


#endif //_H_CONTROLLER_