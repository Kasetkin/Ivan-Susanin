#include "world.h"

#include <boost/python.hpp>


#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/make_shared.hpp>
#include <irrlicht.h>
#include <driverChoice.h>


#include "hardware.h"
#include "controller.h"

namespace environment
{
using namespace irr;

struct world::pimpl
{
    boost::shared_ptr<controller> controller_;
    boost::shared_ptr<boost::thread> thread_;
    irr::IrrlichtDevice *device_;
    boost::mutex mutex_; 
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
        
    data_->controller_ = boost::make_shared<controller>(
        data_->device_->getSceneManager()->getSceneCollisionManager());    
    data_->thread_ = boost::make_shared<boost::thread>(
        boost::bind(&world::routine, this));
    Py_Initialize();
    
}

world::~world()
{
    Py_Finalize();
    boost::lock_guard<boost::mutex> lock(data_->mutex_);
    data_->device_->closeDevice();
    data_->device_->drop();
}

void world::run_script(std::string const & script)
{
  using namespace boost::python;
  object main = import("__main__");
  object global(main.attr("__dict__"));
  object result = exec(script.c_str(),
    global, global);
  // Create a reference to it.
  //object greet = global["greet"];

  // Call it.
  //std::string message = extract<std::string>(greet());
  //std::cout << message << std::endl;

}

void world::run_file(std::string const & file)
{
  try
  {
  using namespace boost::python;
  object main = import("__main__");
  object global(main.attr("__dict__"));
  hardware * hw = new hardware(data_->controller_);
  object Tclass = class_<hardware>("hardware", init<hardware>())
      .def("ray_distance", &hardware::ray_distance)/* defs, etc. */;
  object hard = Tclass(*hw);
  global["robo"] = hard;
  //handle<> x(hard);

  
  object result = exec_file(file.c_str(),
    global, global);
  }
  catch (boost::python::error_already_set)
  {
      //std::cerr << "EX: " << e.what() << std::endl;
      PyErr_Print();
      throw;
  }
  
}

void world::stop()
{
}

void world::reset()
{
}

void world::routine()
{
    video::IVideoDriver * driver = data_->device_->getVideoDriver();
    scene::ISceneManager* smgr = data_->device_->getSceneManager();
    scene::ICameraSceneNode* camera =
        smgr->addCameraSceneNodeFPS(0, 100.0f, .3f,
                                    0, 0, 0, true, 3.f);
    camera->setPosition(core::vector3df(50,50,-60));
    camera->setTarget(core::vector3df(-70,30,-60));
    for (;;)
    {
        boost::lock_guard<boost::mutex> lock(data_->mutex_);
        if (!data_->device_->run())
            break;
        
        if (data_->device_->isWindowActive())
        {
            driver->beginScene(true, true, 0);
            smgr->drawAll();
            driver->endScene();
        }
        
    }
}


}
