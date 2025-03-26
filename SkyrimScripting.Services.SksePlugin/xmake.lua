skse_plugin({
    target = "SKSE Plugin",
    name = library_name,
    mod_files = {"Scripts"},
    src = {"*.cpp"},
    deps = {library_name},
    packages = {"collections", "unordered_dense", "SkyrimScripting.Plugin"}
})
