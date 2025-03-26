#include "SkyrimScripting/Services/Initialize.h"

#include <SKSE/SKSE.h>

#include "SkyrimScripting/Services/IServicesService.h"

namespace SkyrimScripting::Services {

    void Initialize() {
        SKSE::GetMessagingInterface()->RegisterListener(
            "SkyrimScripting.Services",
            [](SKSE::MessagingInterface::Message* message) {
                if (message->type == 69) {
                    if (message->data != nullptr) {
                        auto servicesService = static_cast<IServicesService*>(message->data);
                        IServicesService::set(servicesService);
                    }
                }
            }
        );
    }
}
