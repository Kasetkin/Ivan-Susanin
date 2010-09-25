#ifndef _H_NEWTON_UTILS_
#define _H_NEWTON_UTILS_

class NewtonWorld;
class NewtonCollision;
#include <irrlicht.h>
struct SObject
{
  SObject(irr::scene::IMeshSceneNode *irr_node_, NewtonCollision *nwtn_collision_) :
      irr_node(irr_node_), nwtn_collision(nwtn_collision_)
  {
  }
//Irrlicht scene node
irr::scene::IMeshSceneNode *irr_node;
//Newton collision object
NewtonCollision *nwtn_collision;
};

NewtonCollision * CreateCollisionFromMesh(NewtonWorld *nWorld, irr::scene::IMesh *irr_mesh );
NewtonCollision * CreateTreeCollisionFromMesh(NewtonWorld *nWorld, irr::scene::IMesh *irr_mesh );
bool CheckForCollision(NewtonWorld *nWorld, SObject *obj_A, SObject *obj_B);

#endif