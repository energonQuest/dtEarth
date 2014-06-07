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
        GetGameActorProxy().GetGameManager()->GetApplication().GetCompositeViewer()->getView(0)->apply(new osgViewer::SingleWindow(100,100,1024,800));


    // Tell the database pager to not modify the unref settings
    //viewer->getViewWithFocus()->getDatabasePager()->setUnrefImageDataAfterApplyPolicy( false, false );

    // install our default manipulator (do this before calling load)
    GetGameActorProxy().GetGameManager()->GetApplication().GetCompositeViewer()->getView(0)->setCameraManipulator( new osgEarth::Util::EarthManipulator() );

    // load an earth file, and support all or our example command-line options
    // and earth file <external> tags    
    osg::Node* node = osgEarth::Util::MapNodeHelper().load( arguments, GetGameActorProxy().GetGameManager()->GetApplication().GetCompositeViewer()->getView(0));
    if ( node )
    {
        GetGameActorProxy().GetGameManager()->GetApplication().GetCompositeViewer()->getView(0)->setSceneData( node );
        //GetGameActorProxy().GetGameManager()->GetApplication().GetCompositeViewer()->addView(viewer);
        //viewer.run();
    }

   //if (mLightSource != NULL)
   //{
   //   GetOSGNode()->asGroup()->removeChild(mLightSource);
   //}
   //if (mOceanScene != NULL)
   //{
   //   GetOSGNode()->asGroup()->removeChild(mOceanScene.get());
   //}

   //mOceanSurface = new osgOcean::FFTOceanSurface(
   //   mConfig->GetFFTGridSize(),
   //   mConfig->GetResolution(),
   //   mConfig->GetNumTiles() ,
   //   mConfig->GetWindDirection(),
   //   mConfig->GetWindSpeed(),
   //   mConfig->GetDepth(),
   //   mConfig->GetReflectionDamping(),
   //   mConfig->GetWaveScale(),
   //   mConfig->GetIsChoppy(),
   //   mConfig->GetChoppyFactor(),
   //   mConfig->GetAnimLoopTime(),
   //   mConfig->GetNumFrames());


   //osg::ref_ptr<osg::TextureCubeMap> cubeMap = new osg::TextureCubeMap;
   //cubeMap->setInternalFormat(GL_RGBA);

   //cubeMap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
   //cubeMap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
   //cubeMap->setWrap  (osg::Texture::WRAP_S,     osg::Texture::CLAMP_TO_EDGE);
   //cubeMap->setWrap  (osg::Texture::WRAP_T,     osg::Texture::CLAMP_TO_EDGE);

   //cubeMap->setImage(osg::TextureCubeMap::NEGATIVE_X, osgDB::readImageFile(mConfig->GetSkyBoxLeft()));
   //cubeMap->setImage(osg::TextureCubeMap::POSITIVE_X, osgDB::readImageFile(mConfig->GetSkyBoxRight()));
   //cubeMap->setImage(osg::TextureCubeMap::NEGATIVE_Z, osgDB::readImageFile(mConfig->GetSkyBoxBack()));
   //cubeMap->setImage(osg::TextureCubeMap::POSITIVE_Z, osgDB::readImageFile(mConfig->GetSkyBoxFront()));
   //cubeMap->setImage(osg::TextureCubeMap::POSITIVE_Y, osgDB::readImageFile(mConfig->GetSkyBoxDown()));
   //cubeMap->setImage(osg::TextureCubeMap::NEGATIVE_Y, osgDB::readImageFile(mConfig->GetSkyBoxUp()));
   //mOceanSurface->setEnvironmentMap(cubeMap.get());

   //mOceanSurface->setFoamBottomHeight(mConfig->GetFoamBottomHeight());
   //mOceanSurface->setFoamTopHeight(mConfig->GetFoamTopHeight());
   //mOceanSurface->enableCrestFoam(mConfig->GetEnableCrestFoam());
   //mOceanSurface->setLightColor(mConfig->GetLightColor());
   //mOceanSurface->enableEndlessOcean(mConfig->GetEnableEndlessOcean());

   //mOceanScene = new osgOcean::OceanScene(mOceanSurface.get());
   //mOceanScene->setUseDefaultSceneShader(mConfig->GetUseDefaultSceneShader());
   //// set scene size to window size
   //dtCore::Camera* cam =  GetGameActorProxy().GetGameManager()->GetApplication().GetCamera();
   //dtCore::DeltaWin::PositionSize size = cam->GetWindow()->GetPosition();
   //mOceanScene->setScreenDims(osg::Vec2s(size.mWidth, size.mHeight));

   //mOceanScene->setLightID(0);
   //mOceanScene->enableReflections(mConfig->GetEnableReflections());
   //mOceanScene->enableRefractions(mConfig->GetEnableRefractions());

   //mOceanScene->setAboveWaterFog(mConfig->GetAboveWaterFogHeight(), mConfig->GetAboveWaterFogColor());
   //mOceanScene->setUnderwaterFog(mConfig->GetUnderWaterFogHeight(),  mConfig->GetUnderWaterFogColor());
   //mOceanScene->setUnderwaterDiffuse(mConfig->GetUnderWaterDiffuseColor());
   //mOceanScene->setUnderwaterAttenuation(mConfig->GetUnderWaterAttentuation());


   //mOceanScene->setSunDirection(-mConfig->GetSunDirection());
   //mOceanScene->enableGodRays(mConfig->GetEnableGodRays());
   //mOceanScene->enableSilt(mConfig->GetEnableSilt());
   //mOceanScene->enableUnderwaterDOF(mConfig->GetEnableUnderwaterDOF());
   //mOceanScene->enableGlare(mConfig->GetEnableGlare());
   //mOceanScene->setGlareAttenuation(mConfig->GetGlareAttentuation());

   //mSkyDome = new SkyDome(
   //   mConfig->GetSkyBoxRadius(),
   //   mConfig->GetSkyBoxLongSteps(),
   //   mConfig->GetSkyBoxLatSteps(),
   //   cubeMap.get()
   //);

   //mSkyDome->setNodeMask(mOceanScene->getReflectedSceneMask() | mOceanScene->getNormalSceneMask());

   //mOceanCylinder = new Cylinder(mConfig->GetSkyBoxRadius(), 999.8f, 16, false, true);
   //mOceanCylinder->setColor(mConfig->GetUnderWaterFogColor());
   //mOceanCylinder->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
   //mOceanCylinder->getOrCreateStateSet()->setMode(GL_FOG, osg::StateAttribute::OFF);


   //osg::Geode* oceanCylinderGeode = new osg::Geode;
   //oceanCylinderGeode->addDrawable(mOceanCylinder.get());
   //oceanCylinderGeode->setNodeMask(mOceanScene->getNormalSceneMask());

   //osg::PositionAttitudeTransform* cylinderPat = new osg::PositionAttitudeTransform;
   //cylinderPat->setPosition(osg::Vec3f(0.f, 0.f, -1000.f));
   //cylinderPat->addChild(oceanCylinderGeode);

   //// add a pat to track the camera
   //mSkyTransform = new osg::PositionAttitudeTransform;
   //mSkyTransform->setDataVariance(osg::Object::DYNAMIC);
   //mSkyTransform->setPosition(osg::Vec3f(0.f, 0.f, 0.f));
   //mSkyTransform->setUserData(new CameraTrackDataType(*mSkyTransform));
   //mSkyTransform->setUpdateCallback(new CameraTrackCallback);
   //mSkyTransform->setCullCallback(new CameraTrackCallback);

   //mSkyTransform->addChild(mSkyDome.get());
   //mSkyTransform->addChild(cylinderPat);

   //mOceanScene->addChild(mSkyTransform);

   //{
   //   // Create and add fake texture for use with nodes without any texture
   //   // since the OceanScene default scene shader assumes that texture unit
   //   // 0 is used as a base texture map.
   //   osg::Image* image = new osg::Image;
   //   image->allocateImage(1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE);
   //   *(osg::Vec4ub*)image->data() = osg::Vec4ub(0xFF, 0xFF, 0xFF, 0xFF);

   //   osg::Texture2D* fakeTex = new osg::Texture2D(image);
   //   fakeTex->setWrap(osg::Texture2D::WRAP_S,osg::Texture2D::REPEAT);
   //   fakeTex->setWrap(osg::Texture2D::WRAP_T,osg::Texture2D::REPEAT);
   //   fakeTex->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::NEAREST);
   //   fakeTex->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::NEAREST);

   //   osg::StateSet* stateset = mOceanScene->getOrCreateStateSet();
   //   stateset->setTextureAttribute(0,fakeTex,osg::StateAttribute::ON);
   //   stateset->setTextureMode(0,GL_TEXTURE_1D,osg::StateAttribute::OFF);
   //   stateset->setTextureMode(0,GL_TEXTURE_2D,osg::StateAttribute::ON);
   //   stateset->setTextureMode(0,GL_TEXTURE_3D,osg::StateAttribute::OFF);
   //}

   //mLightSource = new osg::LightSource;
   //mLightSource->setLocalStateSetModes();

   //osg::Light* light = mLightSource->getLight();
   //light->setLightNum(0);
   //light->setAmbient(osg::Vec4d(0.3f, 0.3f, 0.3f, 1.0f));
   //light->setDiffuse(mConfig->GetSunDiffuseColor());
   //light->setSpecular(osg::Vec4d(0.1f, 0.1f, 0.1f, 1.0f));
   //light->setPosition(osg::Vec4f(mConfig->GetSunDirection(), 1.f)); // point light

   //mOceanScene->setOceanSurfaceHeight(mConfig->GetOceanHeight());

   //GetOSGNode()->asGroup()->addChild(mLightSource);

   //GetOSGNode()->asGroup()->addChild(mOceanScene.get());

   //mOceanScene->addChild(mEnv->GetOSGNode());
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
