#pragma once

#include <SKSE/SKSE.h>

#include <atomic>

#include "IServicesService.h"

namespace SkyrimScripting::Services {

    namespace {
        std::atomic<bool> _initialized = false;
    }

    /**
     * The `SkyrimScripting::Services::Initialize` function **MUST** be called during the plugin's
     * initialization.
     *
     * > Must call this BEFORE the `kPostLoad` event.
     */
    inline void Initialize() {
        if (_initialized.exchange(true)) return;

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
