#include <SkyrimScripting/Plugin.h>
#include <SkyrimScripting/Services.h>

#include "example_plugin1_service.h"
#include "example_plugin2_service.h"

class PluginTwoService : public IPluginTwoService {
    std::uint32_t value = 0;

public:
    static PluginTwoService* instance() {
        static PluginTwoService instance;
        return &instance;
    }

    ~PluginTwoService() override = default;
    std::uint32_t get_int() const override { return value; }
    void          set_int(std::uint32_t value) override { this->value = value; }
};

SKSEPlugin_Entrypoint { SkyrimScripting::Services::Initialize(); }

// Everyone should share their services at PostLoad
SKSEPlugin_OnPostLoad {
    RegisterService(
        PluginTwoService::instance(), "PluginTwoService", "A service provided by example_plugin2."
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
