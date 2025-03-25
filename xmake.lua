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

option("build_example")
    set_default(true)
option_end()

if not has_config("commonlib") then
    return
end

includes("xmake/*.lua")

if get_config("build_example") then
    -- For the commonlib package dependency:
    add_repositories("SkyrimScripting https://github.com/SkyrimScripting/Packages.git")
end

add_requires(get_config("commonlib"))

library_name = "SkyrimScripting.Services"

target(library_name)
    set_kind("static")
    add_files("src/*.cpp")
    add_includedirs("include", { public = true }) -- Your library's own include path
    add_headerfiles("include/(**.h)")
    add_packages(get_config("commonlib"), { public = true })


if get_config("build_example") then
    skse_plugin({
        name = "Test plugin for " .. library_name,
        mod_files = {"Scripts"},
        build_papyrus = true,
        src = {"plugin.cpp"}
    })
end
