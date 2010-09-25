#include "world.h"

#include <boost/python.hpp>


#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/make_shared.hpp>
#include <irrlicht.h>
#include <driverChoice.h>

#include <iostream>

#include "hardware.h"
#include "controller.h"

#include "newton_utils.h"
#include <Newton.h>

namespace environment
{
using namespace irr;

struct world::pimpl
{
    boost::shared_ptr<controller> controller_;
    boost::shared_ptr<boost::thread> thread_;
    irr::IrrlichtDevice *device_;
    boost::mutex mutex_;
    NewtonWorld *nWorld_;
};
  
world::world(std::string const & title, 
      size_t x, 
      size_t y, 
      size_t width, 
      size_t height,
      bool headless) :
      data_(boost::make_shared<pimpl>()),
      headless_(headless)
{
    video::E_DRIVER_TYPE driverType = video::EDT_NULL;
    if (!headless_)
    {
      driverType=driverChoiceConsole(); //FIXME: create GUI
      if (driverType==video::EDT_COUNT)
          return; //FIXME: throw here
    }
    
    data_->device_ =
        createDevice(driverType, core::dimension2d<u32>(640, 480), 16, false);

    if (data_->device_ == 0)
        return; //FIXME: throw here

    //scene::ICameraSceneNode * camera = data_->device_->getSceneManager()->addCameraSceneNodeFPS(0, 100.0f, .3f, 0, 0, 0, true, 3.f);
    //camera->setPosition(core::vector3df(50,50,-60));
    //camera->setTarget(core::vector3df(-70,30,-60));

    data_->device_->getFileSystem()->addZipFileArchive("../../media/map-20kdm2.pk3");

    scene::IAnimatedMesh* q3levelmesh = data_->device_->getSceneManager()->getMesh("20kdm2.bsp");


    scene::IMeshSceneNode* q3node = 0;
    if (q3levelmesh)
        q3node = data_->device_->getSceneManager()->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, 0);

    data_->nWorld_ = NewtonCreate(NULL,NULL);
    SObject * co = new SObject(q3node->getPosition(), CreateTreeCollisionFromMesh(data_->nWorld_, q3levelmesh));
    
    /*
    So far so good, we've loaded the quake 3 level like in tutorial 2. Now,
    here comes something different: We create a triangle selector. A
    triangle selector is a class which can fetch the triangles from scene
    nodes for doing different things with them, for example collision
    detection. There are different triangle selectors, and all can be
    created with the ISceneManager. In this example, we create an
    OctreeTriangleSelector, which optimizes the triangle output a little
    bit by reducing it like an octree. This is very useful for huge meshes
    like quake 3 levels. After we created the triangle selector, we attach
    it to the q3node. This is not necessary, but in this way, we do not
    need to care for the selector, for example dropping it after we do not
    need it anymore.
    */

    scene::ITriangleSelector* selector = 0;

    if (q3node)
    {
        q3node->setPosition(core::vector3df(-1350,-130,-1400));

        selector = data_->device_->getSceneManager()->createOctreeTriangleSelector(
                q3node->getMesh(), q3node, 128);
        q3node->setTriangleSelector(selector);
        // We're not done with this selector yet, so don't drop it.
    }

        
    data_->controller_ = boost::make_shared<controller>(data_->device_, co, data_->nWorld_);    
    //data_->thread_ = boost::make_shared<boost::thread>(
    //    boost::bind(&world::routine, this));
    Py_Initialize();
    
}

world::~world()
{
    std::cout << "~world()" << std::endl;
    int * a = 0;
    *a = 1;
    Py_Finalize();
    
    data_->device_->closeDevice();
    boost::lock_guard<boost::mutex> lock(data_->mutex_);
    data_->device_->drop();
    NewtonDestroy(data_->nWorld_);
}

#define PY_PREPARE(foo, arg)\
    using namespace boost::python;\
    try { \
      object main = import("__main__");\
      object global(main.attr("__dict__"));\
      hardware * hw = new hardware(data_->controller_);\
      object Tclass = class_<hardware>("hardware", init<hardware>())\
          .def("ray_distance", &hardware::ray_distance)\
          .def("set_speed", &hardware::set_speed);\
      object hard = Tclass(*hw);\
      global["robo"] = hard;\
      object result = foo(arg.c_str(),\
      global, global);\
    }\
    catch (boost::python::error_already_set)\
    {\
        PyErr_Print();\
        throw;\
    }


void world::run_script(std::string const & script)
{
    PY_PREPARE(exec, script)
}

void world::run_file(std::string const & file)
{
//  boost::lock_guard<boost::mutex> lock(data_->mutex_);
  PY_PREPARE(exec_file, file)
    
}

void world::start()
{
    data_->thread_ = boost::make_shared<boost::thread>(
        boost::bind(&world::routine, this));
   
}

void world::stop()
{
}

void world::reset()
{
}

void world::routine()
{
    video::IVideoDriver * driver = 0;
    scene::ISceneManager* smgr = 0;
    {
      boost::lock_guard<boost::mutex> lock(data_->mutex_);
      driver = data_->device_->getVideoDriver();
      smgr = data_->device_->getSceneManager();
    }
    for(;;)
    {
        boost::lock_guard<boost::mutex> lock(data_->mutex_);
        if (!data_->device_->run())
            return;
        
        if (data_->device_->isWindowActive())
        {
            data_->controller_->draw();
            driver->beginScene(true, true, 0);
            smgr->drawAll();
            driver->endScene();
        }
        
    }
}


}
