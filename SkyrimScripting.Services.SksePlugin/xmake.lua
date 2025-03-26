skse_plugin({
    target = "SKSE Plugin",
    basename = "!!SkyrimScripting.Services",
    name = library_name,
    src = {"*.cpp"},
    deps = {library_name},
    packages = {"collections", "unordered_dense", "SkyrimScripting.Plugin"}
})
