#include "newton_utils.h"
#include <Newton.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

//Function to create a NewtonCollision from irrlicht mesh
NewtonCollision * CreateCollisionFromMesh(NewtonWorld *nWorld, irr::scene::IMesh *irr_mesh )
{
    int nMeshBuffer = 0; //Mesh Buffer count
    IMeshBuffer *mesh_buffer = NULL;
    float *vertices; //Array to store vertices

    u32 nVertices = 0;

    //Get number of vertices
    for( nMeshBuffer=0 ; nMeshBuffer < irr_mesh->getMeshBufferCount() ; nMeshBuffer++ )
    {
        nVertices += irr_mesh->getMeshBuffer(nMeshBuffer)->getVertexCount();
    }

    //create buffer for vertices
    vertices = new float[nVertices * 3];
    u32 tmpCounter = 0;
    //Get (irr_)mesh buffers and copy face vertices
    for( nMeshBuffer=0 ; nMeshBuffer < irr_mesh->getMeshBufferCount() ; nMeshBuffer++ )
    {
        mesh_buffer = irr_mesh->getMeshBuffer(nMeshBuffer);

        //Get pointer to vertices and indices
        S3DVertex *S3vertices = (S3DVertex*)mesh_buffer->getVertices();

        //copy vertices from mesh to buffer
        for(int i=0; i<mesh_buffer->getVertexCount(); i++)
        {
            vertices[tmpCounter++] = S3vertices[i].Pos.X;
            vertices[tmpCounter++] = S3vertices[i].Pos.Y;
            vertices[tmpCounter++] = S3vertices[i].Pos.Z;
        }
    }

    //Create Newton collision object
    NewtonCollision *collision_obj = NewtonCreateConvexHull(nWorld,nVertices,vertices,sizeof(float)*3, 0, NULL);

    //delete vertices
    delete [] vertices;

    return collision_obj;
}

//Function to create a NewtonCollision from irrlicht mesh with tree optimization
NewtonCollision * CreateTreeCollisionFromMesh(NewtonWorld *nWorld, irr::scene::IMesh *irr_mesh )
{
    //Create new (tree optimized) collision mesh
    NewtonCollision *collision_obj = NewtonCreateTreeCollision(nWorld);

    //Begin collision mesh construction
    NewtonTreeCollisionBeginBuild(collision_obj);

    int nMeshBuffer = 0; //Mesh Buffer count
    int v_index[3] = {0,0,0}; //vertex indices
    IMeshBuffer *mesh_buffer = NULL;
    float array[9]; //Array to store 3 vertices

    //Get (irr_)mesh buffers and copy face by face to collision mesh
    for( nMeshBuffer=0 ; nMeshBuffer < irr_mesh->getMeshBufferCount() ; nMeshBuffer++ )
    {
        mesh_buffer = irr_mesh->getMeshBuffer(nMeshBuffer);

        //Get pointer to vertices and indices
        S3DVertex *vertices = (S3DVertex*)mesh_buffer->getVertices();
        u16 *indices = mesh_buffer->getIndices();

        //Fill collision mesh
        for(int i=0; i<mesh_buffer->getIndexCount(); i+=3)
        {
            v_index[0] = indices[ i ];
            v_index[1] = indices[i+1];
            v_index[2] = indices[i+2];

            // 1st position vertex
            array[0] = vertices[ v_index[0] ].Pos.X;
            array[1] = vertices[ v_index[0] ].Pos.Y;
            array[2] = vertices[ v_index[0] ].Pos.Z;

            // 2nd position vertex
            array[3] = vertices[ v_index[1] ].Pos.X;
            array[4] = vertices[ v_index[1] ].Pos.Y;
            array[5] = vertices[ v_index[1] ].Pos.Z;

            // 3rd position vertex
            array[6] = vertices[ v_index[2] ].Pos.X;
            array[7] = vertices[ v_index[2] ].Pos.Y;
            array[8] = vertices[ v_index[2] ].Pos.Z;

            //Add new face to collision mesh
            NewtonTreeCollisionAddFace(collision_obj, //collision mesh to add face to
                3, //number of vertices in array
                (float*)array, //pointer to vertex array
                3*sizeof(float),//size of each vertex
                1); //ID of the face
        }
    }
    //End collision contruction , set 1 as 2dn param for optimization
    NewtonTreeCollisionEndBuild(collision_obj,0);

    return collision_obj;
}

//Check for collision between two SObjects
bool CheckForCollision(NewtonWorld *nWorld, SObject *obj_A, SObject *obj_B)
{
    //Matrix to store irr_node position
    matrix4 mat_A,mat_B;

    //Copy position
    mat_A.makeIdentity();
    mat_B.makeIdentity();

    mat_A.setTranslation(obj_A->irr_node->getPosition());
    mat_B.setTranslation(obj_B->irr_node->getPosition());

    const int nContacts = 2;
    float contacts[3 * nContacts];
    float normals[3 * nContacts];
    float penetration[ nContacts ];

    //Check for collision between collision meshes,
    // returns number of contact points
    int nHits = NewtonCollisionCollide( nWorld,nContacts,
        obj_A->nwtn_collision, (float*)&mat_A[0],
        obj_B->nwtn_collision, (float*)&mat_B[0],
        contacts,
        normals,
        penetration, 0);
    //Collision detected if nHits > 0
    if( nHits > 0)
        return true;
    return false;
}

