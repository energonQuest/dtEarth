#pragma once

#include <dtGame/gameactor.h>
#include <dtEarth/export.h>
// @TODO remove references to old dtOcean code. thanx dtOcean.
//#include <osg/Fog>
//#include <osg/TextureCubeMap>
//#include "cylinder.h"
//#include <dtCore/skybox.h>
//#include <dtGame/environmentactor.h>

//namespace dtCore
//{
//   class Environment;
//}

//namespace osgEarth
//{
//// @TODO remove references to old dtOcean code. thanx dtOcean.
//   //class OceanScene;
//   //class FFTOceanSurface;
//}

namespace dtEarth
{
// @TODO remove references to old dtOcean code. thanx dtOcean.
   class DT_EARTH_EXPORT EarthActor : public dtGame::GameActor // dtGame::IEnvGameActor
   {
   public:
      typedef dtGame::GameActor BaseClass;

      /** CTor */
      EarthActor(dtGame::GameActorProxy& proxy);
      ~EarthActor();

      void OnEnteredWorld();
      void ProcessMessage(const dtGame::Message& msg);

   private:
      bool mConfig;

      void OnMapLoaded();
      void Build();
   };

   // -----------------------------------------------

// @TODO remove references to old dtOcean code. thanx dtOcean.
   class DT_EARTH_EXPORT EarthActorProxy : public dtGame::GameActorProxy //dtGame::IEnvGameActorProxy
   {
      typedef dtGame::GameActorProxy BaseClass;

   public:
      EarthActorProxy();
      virtual void CreateDrawable();
      virtual void BuildPropertyMap();

   protected:
      virtual ~EarthActorProxy();
   };

} // namespace dtEarth
