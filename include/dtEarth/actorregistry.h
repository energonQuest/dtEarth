#include <dtCore/actorpluginregistry.h>
#include <dtEarth/export.h>

class DT_EARTH_EXPORT EarthActorRegistry : public dtCore::ActorPluginRegistry
{
public:
   static dtCore::RefPtr<dtCore::ActorType> EARTH_ACTOR_TYPE; 
   // @TODO remove.
   //static dtCore::RefPtr<dtCore::ActorType> EARTH_CONFIG_ACTOR_TYPE; 

   EarthActorRegistry();
   void RegisterActorTypes();
};
