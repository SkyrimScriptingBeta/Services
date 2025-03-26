#include "SkyrimScripting/Services/IServicesService.h"

namespace SkyrimScripting::Services {
    IServicesService* IServicesService::instance = nullptr;

    IServicesService* IServicesService::get() { return instance; }

    void IServicesService::set(IServicesService* service) { instance = service; }
}
