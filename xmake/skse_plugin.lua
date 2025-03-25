function skse_plugin(mod_info)
    local commonlib_version = get_config("commonlib"):match("skyrim%-commonlib%-(.*)")
    local mods_folders = os.getenv("SKYRIM_MODS_FOLDERS")

    if mods_folders then
        mod_info.mods_folders = mods_folders
    else
        print("SKYRIM_MODS_FOLDERS environment variable not set")
    end
    
    target(mod_info.name)
        add_deps(library_name)
        set_basename(mod_info.name .. "-" .. commonlib_version:upper())
        add_rules("@skyrim-commonlib-" .. commonlib_version .. "/plugin", {
            mod_name     = mod_info.name .. " (" .. commonlib_version:upper() .. ")",
            mods_folders = mod_info.mods_folders or "",
            mod_files    = mod_info.mod_files,
            name         = mod_info.name,
            version      = mod_info.version,
            author       = mod_info.author,
            email        = mod_info.email
        })
        for _, src in ipairs(mod_info.src or {}) do
            add_files(src)
        end
        for _, include in ipairs(mod_info.include or {}) do
            add_includedirs(include, { public = true })
        end
        for _, dep in ipairs(mod_info.deps or {}) do
            add_deps(dep, { public = true })
        end
        for _, package in ipairs(mod_info.packages or {}) do
            add_packages(package, { public = true })
        end
        if mod_info.build_papyrus then
            compile_papyrus_scripts()
        end
end
