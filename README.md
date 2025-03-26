# SkyrimScripting Services

> Share Services between SKSE plugins

```cpp
// A shared header which you provide to other SKSE plugin authors

#pragma once

struct ICoolService {
    virtual void do_something() = 0;
    
protected:
    // Recommended: disallow destruction through this interface
    virtual ~ICoolService() = default;
}
```

```cpp
// For SkyrimScripting Services functions:
#include <SkyrimScripting/Services.h>

// Example of how you might include headers for services from other plugins
#include <AnotherPlugin/IServiceFromAnotherPlugin.h>

// Example of how you might include headers for services for your plugin
#include "ICoolService.h"

// Provide the implementation of your plugin's service(s) in your SKSE plugin
class TheCoolServiceImplementation : public ICoolService {
public:
    void do_something() override {
        // Do something cool
    }
};

// You'll need persistent pointers to your services. Store them wherever you like.
std::unique_ptr<ICoolService> coolService = std::make_unique<TheCoolServiceImplementation>();

extern "C" __declspec(dllexport) bool SKSEPlugin_Load(const SKSE::LoadInterface* skse) {
    // Initialize SkyrimScripting Services
    // (it registers a listener for receiving the service manager)
    SkyrimScripting::Services::Initialize();
    
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* msg) {

        // In the kPostLoad message, register your plugin's shared services, if any.
        if (msg->type == SKSE::MessagingInterface::kPostLoad) {
          
            // Register your services
            RegisterService(
                coolService.get(), "CoolService", "A cool service for doing cool things."
            );
            
        // In the kPostPostLoad message, get services from other plugins.
        // You can store the services in your plugin's global state, or use them directly.
        } else if (msg->type == SKSE::MessagingInterface::kPostPostLoad) {
          
            // Get services from other plugins
            auto* anotherService = GetService<IServiceFromAnotherPlugin>("AnotherService");
            if (anotherService) {
                anotherService->do_something();
            }
        }
    });

    SKSE::Init(skse);
    
    return true;
}
```