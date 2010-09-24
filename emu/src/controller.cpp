#include "controller.h"

#include <ISceneCollisionManager.h>
#include <ISceneNode.h>
#include <line3d.h>
#include <iostream>

namespace environment
{
using namespace irr;
  
controller::controller(scene::ISceneCollisionManager * collision_manager) :
  collision_manager_(collision_manager)
{
}

controller::~controller()
{
}

double controller::ray_traverse(vector3 const & direction) const
{
    core::line3d<f32> ray;
    ray.start = position_;
    ray.end = direction_ * 1000.0f;

    core::vector3df intersection;
    core::triangle3df hitTriangle;
    
    scene::ISceneNode * selectedSceneNode =
      collision_manager_->getSceneNodeAndCollisionPointFromRay(
        ray,
        intersection, // This will be the position of the collision
        hitTriangle, // This will be the triangle hit in the collision
        0, //IDFlag_IsPickable, // This ensures that only nodes that we have
                // set up to be pickable are considered
        0); // Check 
   return (intersection - position_).getLength();
}

double controller::cone_traverse(vector3 const & direction, 
                      double angle) const
{
    std::cerr << 
      "WARNING: double environment::controller::cone_traverse"
      "(vector3 const &, vector3 const &) not implemented yet" 
      << std::endl;
    return 0;
}

double controller::ray_traverse() const
{
    return ray_traverse(direction_);
}

double controller::cone_traverse(double angle) const
{
    return cone_traverse(direction_, angle);
}

void controller::set_speed(double left, 
                double right)
{
    std::cerr << 
      "WARNING: void environment::controller::set_speed"
      "(double, double) not implemented yet" 
      << std::endl;
}

void controller::draw()
{
    
}

}

