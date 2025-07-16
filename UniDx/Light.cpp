#include "Light.h"

#include "LightManager.h"
#include "Debug.h"


namespace UniDx{

void Light::OnEnable()
{
    LightManager::instance->registerLight(this);
}


void Light::OnDisable()
{
    LightManager::instance->unregisterLight(this);
}

}
