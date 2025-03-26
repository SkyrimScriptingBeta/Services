#pragma once

namespace SkyrimScripting::Services {

    struct ServiceInfo {
        const char* name;
        const char* description;
        void*       service_pointer;

        template <typename T>
        T* service() {
            return static_cast<T*>(service_pointer);
        }
    };
}
