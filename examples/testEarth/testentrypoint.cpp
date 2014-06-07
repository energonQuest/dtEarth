#include "testexport.h"

#include <cassert>

#include <dtCore/orbitmotionmodel.h>
#include <dtCore/camera.h>
#include <dtCore/deltawin.h>
#include <dtCore/system.h>
#include <dtCore/transform.h>
#include <dtGame/baseinputcomponent.h>
#include <dtGame/gamemanager.h>
#include <dtGame/gameapplication.h>
#include <dtABC/baseabc.h>
#include <dtGame/gameentrypoint.h>
#include <dtUtil/datapathutils.h>

static const osg::Vec3 TARGET_XYZ(0, 6, 5);

// for key input handling
class TestInput : public dtGame::BaseInputComponent
{
public:
   TestInput() : dtGame::BaseInputComponent("TestInput") { }

   virtual bool HandleKeyPressed(const dtCore::Keyboard* keyboard, int key)
   {
      switch (key)
      {
      case osgGA::GUIEventAdapter::KEY_Escape:
         {
            GetGameManager()->GetApplication().Quit();
            return true;
         }
      default:
         break;
      }
      return false;
   }
};

//////////////////////////////////////////////////////////////////////////
class TEST_EARTH_EXPORT TestEarthEntryPoint : public dtGame::GameEntryPoint
{
public:
   TestEarthEntryPoint() {}

   virtual void Initialize(dtABC::BaseABC& app, int argc, char** argv)
   {
      std::string dataPath = dtUtil::GetDeltaDataPathList();
      dtUtil::SetDataFilePathList(dataPath + ";"
                                 + dtUtil::GetDeltaRootPath() + "/examples/data/;");

      // add a motion model
      dtCore::OrbitMotionModel* motionModel = new dtCore::OrbitMotionModel(app.GetKeyboard(), app.GetMouse());
      motionModel->SetTarget(app.GetCamera());
      motionModel->SetDistance(20.f);
      motionModel->SetFocalPoint(TARGET_XYZ);
   }

   virtual void OnStartup(dtABC::BaseABC& app, dtGame::GameManager& gamemanager)
   {
      app.GetWindow()->SetWindowTitle("testEarth");

      gamemanager.LoadActorRegistry("dtEarth");

      // add the input handler
      gamemanager.AddComponent(*new TestInput(), dtGame::GameManager::ComponentPriority::NORMAL);

      try
      {
         gamemanager.SetProjectContext("C:/jhuapl/dtOceanProto/resources", true);
         gamemanager.ChangeMap("testEarth");
      }
      catch (const dtUtil::Exception& e)
      {
         LOG_ERROR("Problem getting the Map 'testEarth' loaded.");
         e.LogException(dtUtil::Log::LOG_ERROR);
      }
   }

};

//////////////////////////////////////////////////////////////////////////
extern "C" TEST_EARTH_EXPORT dtGame::GameEntryPoint* CreateGameEntryPoint()
{
   return new TestEarthEntryPoint;
}

//////////////////////////////////////////////////////////////////////////
extern "C" TEST_EARTH_EXPORT void DestroyGameEntryPoint(dtGame::GameEntryPoint* entryPoint)
{
   delete entryPoint;
}
