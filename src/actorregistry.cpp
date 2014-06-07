#include <dtEarth/actorregistry.h>

#include <dtEarth/earthactor.h>

using namespace dtEarth;

dtCore::RefPtr<dtCore::ActorType> EarthActorRegistry::EARTH_ACTOR_TYPE(new dtCore::ActorType("EarthActor", "dtEarth",
                                                                                   "OSGEarth actor"));

// @TODO remove
//dtCore::RefPtr<dtCore::ActorType> EarthActorRegistry::EARTH_CONFIG_ACTOR_TYPE(new dtCore::ActorType("OceanConfigActor", "dtEarth",
                                                                                            //"OSGOceanConfigActor"));

//////////////////////////////////////////////////////////////////////////
extern "C" DT_EARTH_EXPORT dtCore::ActorPluginRegistry* CreatePluginRegistry()
{
   return new EarthActorRegistry;
}

extern "C" DT_EARTH_EXPORT void DestroyPluginRegistry(dtCore::ActorPluginRegistry* registry)
{
   if (registry)
   {
      delete registry;
   }
}

EarthActorRegistry::EarthActorRegistry() : dtCore::ActorPluginRegistry("dtEarth Library")
{
   mDescription = "All game actors for dtEarth";
}

void EarthActorRegistry::RegisterActorTypes()
{   
   //EarthActor/EarthActorProxy
   mActorFactory->RegisterType<dtEarth::EarthActorProxy>(EARTH_ACTOR_TYPE.get());

   // @TODO remove.
   //OceanConfigActor/OceanConfigActorProxy
   //mActorFactory->RegisterType<dtEarth::OceanConfigActorProxy>(OCEAN_CONFIG_ACTOR_TYPE.get());
}
