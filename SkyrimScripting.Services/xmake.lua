target(library_name)
    set_kind("static")
    add_files("src/*.cpp")
    add_includedirs("include", { public = true }) -- Your library's own include path
    add_headerfiles("include/(**.h)")
    add_packages(get_config("commonlib"), { public = true })
    add_packages("collections", { public = true })
    add_packages("unordered_dense", { public = true })
