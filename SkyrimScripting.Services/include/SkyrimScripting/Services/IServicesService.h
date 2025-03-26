#pragma once

#include <cstdint>

#include "ServiceInfo.h"

namespace SkyrimScripting::Services {

    struct IServicesService {
        static IServicesService* get();
        static void              set(IServicesService* service);

        virtual bool register_service(void* service, const char* name, const char* description) = 0;
        virtual bool unregister_service(const char* name)                                       = 0;
        virtual bool service_exists(const char* name) const                                     = 0;
        virtual void*         get_service(const char* name) const                               = 0;
        virtual ServiceInfo   get_service_info(const char* name) const                          = 0;
        virtual std::uint32_t get_service_count() const                                         = 0;
        virtual ServiceInfo   get_service_info_by_index(std::uint32_t index) const              = 0;

    protected:
        virtual ~IServicesService() = default;

    private:
        static IServicesService* instance;
    };
}
