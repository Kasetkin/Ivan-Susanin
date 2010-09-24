const double PI = 3.14;

#include "controller.h"

#include <irrlicht.h>

#include <iostream>

namespace environment
{
using namespace irr;
  
controller::controller(irr::IrrlichtDevice *device) :
  collision_manager_(device->getSceneManager()->getSceneCollisionManager())
{
    position_ = vector3(-70,-66,-60);
    direction_ = vector3(0, 0, 1);
    
    //camera_ = device->getSceneManager()->addCameraSceneNodeFPS(0, position_, direction_, 1);
    //camera_->setPosition(position_);
    //camera_->setTarget(direction_);
    lspeed_ = 0;
    rspeed_ = 0;
    

    scene::ISceneManager* smgr = device->getSceneManager();
    
    node_ = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../../media/dwarf.x"),
                        0, 0);
    node_->setPosition(position_);
    node_->setRotation(core::vector3df(0,90,0));
    rotation = PI / 2;
    node_->setAnimationSpeed(10.f);
    node_->getMaterial(0).NormalizeNormals = true;
    // Just do the same as we did above.
    //selector = smgr->createTriangleSelector(node);
    //node->setTriangleSelector(selector);
    //selector->drop();

    //material.setTexture(0, 0);
    //material.Lighting = false;
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
    /*std::cerr << 
      "WARNING: void environment::controller::set_speed"
      "(double, double) not implemented yet" 
      << std::endl;*/
    lspeed_ = left;
    rspeed_ = right;
}

void controller::draw()
{
      
    //position_ += direction_ * std::min(lspeed, rspeed);
    rotation = 0;
    node_->setPosition(position_);
    node_->setRotation(vector3(0, rotation * 180 / PI, 0));
    
    //camera_->setPosition(position_);
    //camera_->setTarget(position_ + direction_);
}

}

