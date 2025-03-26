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
    auto* pluginOneService = GetService<IPluginOneService>("PluginOneService");
    if (pluginOneService) {
        SKSE::log::info("PluginOneService: {}", pluginOneService->get_string());
    } else {
        SKSE::log::warn("PluginOneService not found.");
    }
}
