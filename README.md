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

Example of what this looks like when using `SkyrimScripting/Plugin.h`

```cpp
#include <SkyrimScripting/Plugin.h>
#include <SkyrimScripting/Services.h>

#include "example_plugin1_service.h"
#include "example_plugin2_service.h"

class PluginOneService : public IPluginOneService {
public:
    static PluginOneService* instance() {
        static PluginOneService instance;
        return &instance;
    }

    ~PluginOneService() override = default;
    const char* get_string() const override { return "Hello, world!"; }
};

SKSEPlugin_Entrypoint { SkyrimScripting::Services::Initialize(); }

// Everyone should share their services at PostLoad
SKSEPlugin_OnPostLoad {
    RegisterService(
        PluginOneService::instance(), "PluginOneService", "A service provided by example_plugin1."
    );
}

// Services should all be ready to consume at PostPostLoad
SKSEPlugin_OnPostPostLoad {
    auto* pluginTwoService = GetService<IPluginTwoService>("PluginTwoService");
    if (pluginTwoService) {
        SKSE::log::info("PluginTwoService: {}", pluginTwoService->get_int());
        pluginTwoService->set_int(42);
        SKSE::log::info("PluginTwoService: {}", pluginTwoService->get_int());
    } else {
        SKSE::log::warn("PluginTwoService not found.");
    }
}
```

# Available Functions

```cpp
bool RegisterServicePointer(
    void* service, std::string_view name, std::string_view description
) {
    if (auto* servicesService = IServicesService::get()) {
        return servicesService->register_service(service, name.data(), description.data());
    }
    SKSE::log::warn("Failed to register service: IServicesService is not available.");
    return false;
}

bool UnregisterService(std::string_view name) {
    if (auto* servicesService = IServicesService::get()) {
        return servicesService->unregister_service(name.data());
    }
    SKSE::log::warn("Failed to unregister service: IServicesService is not available.");
    return false;
}

bool ServiceExists(std::string_view name) {
    if (auto* servicesService = IServicesService::get()) {
        return servicesService->service_exists(name.data());
    }
    SKSE::log::warn("Failed to check if service exists: IServicesService is not available.");
    return false;
}

void* GetServicePointer(std::string_view name) {
    if (auto* servicesService = IServicesService::get()) {
        return servicesService->get_service(name.data());
    }
    SKSE::log::warn("Failed to get service pointer: IServicesService is not available.");
    return nullptr;
}

ServiceInfo GetServiceInfo(std::string_view name) {
    if (auto* servicesService = IServicesService::get()) {
        return servicesService->get_service_info(name.data());
    }
    SKSE::log::warn("Failed to get service info: IServicesService is not available.");
    return {};
}

std::uint32_t GetServiceCount() {
    if (auto* servicesService = IServicesService::get()) {
        return servicesService->get_service_count();
    }
    SKSE::log::warn("Failed to get service count: IServicesService is not available.");
    return 0;
}

ServiceInfo GetServiceInfoByIndex(std::uint32_t index) {
    if (auto* servicesService = IServicesService::get()) {
        return servicesService->get_service_info_by_index(index);
    }
    SKSE::log::warn("Failed to get service info by index: IServicesService is not available.");
    return {};
}

struct ServiceInfo {
    const char* name;
    const char* description;
    void*       service_pointer;

    template <typename T>
    T* service() {
        return static_cast<T*>(service_pointer);
    }
};
```
