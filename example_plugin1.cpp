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
