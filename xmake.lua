add_rules("mode.debug", "mode.release", "mode.releasedbg")

set_languages("c++23")

option("commonlib")
    -- Options:
    -- - skyrim-commonlib-ae
    -- - skyrim-commonlib-se
    -- - skyrim-commonlib-ng
    -- - skyrim-commonlib-vr
    --
    -- At this time, this template ONLY supports these ^ packages (from SkyrimScripting)
    set_default("skyrim-commonlib-ae")
option_end()

option("build_plugin")
    set_default(true)
option_end()

option("build_example")
    set_default(true)
option_end()

if not has_config("commonlib") then
    return
end

includes("xmake/*.lua")

if get_config("build_plugin") or get_config("build_example") then
    -- For the commonlib package dependency:
    add_repositories("SkyrimScripting     https://github.com/SkyrimScripting/Packages.git")
    add_repositories("SkyrimScriptingBeta https://github.com/SkyrimScriptingBeta/Packages.git")
    add_repositories("MrowrLib            https://github.com/MrowrLib/Packages.git")

    add_requires("collections")
    add_requires("unordered_dense")
    add_requires("virtual_collections")
    add_requires("SkyrimScripting.Plugin", { configs = { commonlib = get_config("commonlib") }})
end

add_requires(get_config("commonlib"))

library_name = "SkyrimScripting.Services"

includes("SkyrimScripting.Services/xmake.lua")

if get_config("build_plugin") then
    includes("SkyrimScripting.Services.SksePlugin/xmake.lua")
end

if get_config("build_example") then
    skse_plugin({
        name = "Test plugin for " .. library_name,
        mod_files = {"Scripts"},
        build_papyrus = true,
        src = {"example.cpp"},
        deps = {library_name}
    })
end
