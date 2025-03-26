#pragma once

namespace SkyrimScripting::Services {
    /**
     * The `SkyrimScripting::Services::Initialize` function **MUST** be called during the plugin's
     * initialization.
     *
     * > Must call this BEFORE the `kPostLoad` event.
     */
    void Initialize();
}
