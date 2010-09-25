#ifndef _H_NEWTON_UTILS_
#define _H_NEWTON_UTILS_

class NewtonWorld;
class NewtonCollision;
#include <irrlicht.h>
#include "types.h"
struct SObject
{
  SObject(vector3 const & position, NewtonCollision *nwtn_collision_) :
      pos(position), nwtn_collision(nwtn_collision_)
  {
  }
//Irrlicht scene node
//irr::scene::IMeshSceneNode *irr_node;
vector3 pos;
//Newton collision object
NewtonCollision *nwtn_collision;
};

NewtonCollision * CreateCollisionFromMesh(NewtonWorld *nWorld, irr::scene::IMesh *irr_mesh );
NewtonCollision * CreateTreeCollisionFromMesh(NewtonWorld *nWorld, irr::scene::IMesh *irr_mesh );
bool CheckForCollision(NewtonWorld *nWorld, SObject *obj_A, SObject *obj_B);

#endif