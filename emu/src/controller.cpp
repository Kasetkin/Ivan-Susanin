const double PI = 3.14;

#include "controller.h"

#include <irrlicht.h>
#include <Newton.h>

#include <iostream>


namespace environment
{
using namespace irr;
  
controller::controller(irr::IrrlichtDevice *device, SObject * land, NewtonWorld *nWorld) :
  collision_manager_(device->getSceneManager()->getSceneCollisionManager()),
  land_(land),
  nWorld_(nWorld)
{
    boost::lock_guard<boost::mutex> lock(mutex_);
    position_ = vector3(-70,-66,-60);
    direction_ = vector3(0, 0, 1);
    
    camera_ = device->getSceneManager()->addCameraSceneNode(0, position_, direction_, 1);
    camera_->setPosition(position_ - 20 * direction_ + vector3(0, 20, 0));
    camera_->setTarget(position_);
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
    nwtn_collision_ = CreateTreeCollisionFromMesh(nWorld_, smgr->getMesh("../../media/dwarf.x"));
}

controller::~controller()
{
}

double controller::ray_traverse(vector3 const & direction) const
{
    float coords[4];
    direction.getAs4Values(coords);
    vector3 dir(coords[0] * cos(-rotation) - coords[2] * sin(-rotation),
                coords[1], 
                coords[0] * sin(-rotation) + coords[2] * cos(-rotation));
    boost::lock_guard<boost::mutex> lock(mutex_);
    core::line3d<f32> ray;
    ray.start = position_ + vector3(0, 5, 0);
    ray.end = position_  + vector3(0, 5, 0) + dir * 1000.0f;

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
    boost::lock_guard<boost::mutex> lock(mutex_);
    std::cerr << 
      "WARNING: double environment::controller::cone_traverse"
      "(vector3 const &, vector3 const &) not implemented yet" 
      << std::endl;
    return 0;
}

double controller::ray_traverse() const
{
    boost::lock_guard<boost::mutex> lock(mutex_);
    return ray_traverse(direction_);
}

double controller::cone_traverse(double angle) const
{
    boost::lock_guard<boost::mutex> lock(mutex_);
    return cone_traverse(direction_, angle);
}

void controller::set_speed(double left, 
                double right)
{
    boost::lock_guard<boost::mutex> lock(mutex_);
    /*std::cerr << 
      "WARNING: void environment::controller::set_speed"
      "(double, double) not implemented yet" 
      << std::endl;*/
    lspeed_ = left;
    rspeed_ = right;
}

void controller::draw()
{
    boost::lock_guard<boost::mutex> lock(mutex_);
    
    //lspeed_ = 0;
    //rspeed_ = 0;
    
    double l = 20;  
    double omega = (lspeed_ - rspeed_) / l;
    double alpha = omega;
    double beta = alpha / 2;
    float coords[4];
    direction_.getAs4Values(coords);
    direction_ = vector3(coords[0] * cos(alpha)
        - coords[2] * sin(alpha), 
        coords[1], 
        coords[0] * sin(alpha)
        + coords[2] * cos(alpha));
    
    direction_ = direction_.normalize();
    vector3 ppos = position_;
    position_ += (lspeed_ + rspeed_) / 2 * vector3(coords[0] * cos(beta)
        - coords[2] * sin(beta), 
        coords[1], 
        coords[0] * sin(beta)
        + coords[2] * cos(beta));
    direction_.getAs4Values(coords);
    //std::cout << "POSITION: " << coords[0] << " " << coords[1] << " " << coords[2] << std::endl;
    node_->setPosition(position_);

    /*if (CheckForCollision(nWorld_, land_, SObject(node_, nwtn_collision_)))
    {
        position_ = ppos;
        node_->setPosition(position_);
    }*/
    
    rotation = -atan2(coords[2], coords[0]);
    //std::cout << rotation << std::endl;
    node_->setRotation(vector3(0, -90 + rotation * 180 / PI, 0));
    camera_->setPosition(position_ - 100 * direction_ + vector3(0, 100, 0));
    camera_->setTarget(position_);
    
    //camera_->setPosition(position_);
    //camera_->setTarget(position_ + direction_);
}

}

