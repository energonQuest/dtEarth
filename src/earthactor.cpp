#include <dtEarth/earthactor.h>

// @TODO remove references to old dtOcean code. thanx dtOcean.
//#include <osgOcean/OceanScene>
//#include <osgOcean/FFTOceanSurface>
//#include <dtOcean/oceanconfigactor.h>
//#include <dtOcean/skydome.h>
//#include <dtOcean/spheresegment.h>
#include <dtCore/scene.h>

#include <dtABC/application.h>
#include <dtCore/enginepropertytypes.h>
//#include <dtCore/deltawin.h>
//#include <dtCore/environment.h>
#include <dtGame/gamemanager.h>
#include <dtGame/messagetype.h>
#include <dtGame/message.h>
#include <dtUtil/exception.h>
//#include <osg/LightSource>
//#include <osg/PositionAttitudeTransform>
#include <osg/ArgumentParser>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/config/SingleWindow>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/ExampleResources>

using namespace dtEarth;

EarthActor::EarthActor(dtGame::GameActorProxy& proxy)
   : BaseClass(proxy)
   , mConfig(false)
{
    SetName("EarthActor");
}


EarthActor::~EarthActor()
{
}


void EarthActor::OnEnteredWorld()
{
    Build();
   // get informed about enabled debug drawing
   //GetGameActorProxy().RegisterForMessages(dtGame::MessageType::INFO_MAP_LOADED,
   //   dtGame::GameActorProxy::PROCESS_MSG_INVOKABLE);
}


void EarthActor::ProcessMessage(const dtGame::Message& msg)
{
   if (msg.GetMessageType() == dtGame::MessageType::INFO_MAP_LOADED)
   {
      OnMapLoaded();
   }
}


void EarthActor::OnMapLoaded()
{
   if (EarthActor::mConfig == false)
   {
        if (&GetGameActorProxy() != NULL)
        {
            Build();
            mConfig = true;
        }
   }
}


void EarthActor::Build()
{
    int argc = 7;
    char** argv = new char*[10];
    argv[0] = new char[32];
    argv[0] = "test";
    argv[1] = new char[32];
    argv[1] = "--window";
    argv[2] = new char[32];
    argv[2] = "100";
    argv[3] = new char[32];
    argv[3] = "100";
    argv[4] = new char[32];
    argv[4] = "800";
    argv[5] = new char[32];
    argv[5] = "800";
    argv[6] = new char[32];
    argv[6] = "./tests/ocean.earth";
    
    osg::ArgumentParser arguments(&argc,argv);

    // help?
    if ( arguments.read("--help") )
        return;

    if ( arguments.read("--stencil") )
        osg::DisplaySettings::instance()->setMinimumNumStencilBits( 8 );

    // create a viewer:
    //osgViewer::CompositeViewer* viewer = new osgViewer::Viewer(arguments);//  = NULL;    
    osgViewer::Viewer* viewer = new osgViewer::Viewer(arguments);//  = NULL;    
    //viewer = GetGameActorProxy().GetGameManager()->GetApplication().GetCompositeViewer();
        //GetGameActorProxy().GetGameManager()->GetApplication().GetCompositeViewer()->getView(0)->apply(new osgViewer::SingleWindow(100,100,1024,800));


    // Tell the database pager to not modify the unref settings
    viewer->getDatabasePager()->setUnrefImageDataAfterApplyPolicy( false, false );

    // install our default manipulator (do this before calling load)
    //GetGameActorProxy().GetGameManager()->GetApplication().GetCompositeViewer()->getView(0)->setCameraManipulator( new osgEarth::Util::EarthManipulator() );
    viewer->setCameraManipulator( new osgEarth::Util::EarthManipulator() );

    // load an earth file, and support all or our example command-line options
    // and earth file <external> tags    
    osg::Node* node = osgEarth::Util::MapNodeHelper().load( arguments, viewer);
    if ( node )
    {
        viewer->setSceneData( node );
        GetGameActorProxy().GetGameManager()->GetApplication().GetCompositeViewer()->addView(viewer);
        //viewer.run();
    }
}

// --------------------------------------------

EarthActorProxy::EarthActorProxy()
   : BaseClass()
{
   SetClassName("dtEarth::EarthActor");
}


EarthActorProxy::~EarthActorProxy()
{
}


void EarthActorProxy::CreateDrawable()
{
   EarthActor* actor = new EarthActor(*this);
   SetActor(*actor);
}


void EarthActorProxy::BuildPropertyMap()
{
   BaseClass::BuildPropertyMap();
   static const std::string GROUPNAME = "dtEarth";

   using namespace dtCore;

   EarthActor* actor;
   GetActor(actor);
}

//////////////////////////////////////////////////////////////////////////////////
//float dtEarth::EarthActor::GetOceanSurfaceHeightAt(float x, float y, osg::Vec3* normal) const
//{
//   return mOceanScene->getOceanSurfaceHeightAt(x, y, normal);
//}
//
//////////////////////////////////////////////////////////////////////////////////
//void dtEarth::EarthActor::SetWindowSize(const osg::Vec2s size)
//{
//   if (mOceanScene.valid())
//   {
//      mOceanScene->setScreenDims(size);
//   }
//}
