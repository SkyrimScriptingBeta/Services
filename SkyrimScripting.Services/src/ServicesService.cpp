#include <collections.h>

#include "SkyrimScripting/Services/IServicesService.h"

namespace SkyrimScripting::Services {
    class ServicesService : public IServicesService {
        collections_map<const char*, ServiceInfo> services;

    public:
        bool register_service(void* service, const char* name, const char* description) override {
            ServiceInfo info = {name, description, service, nullptr};
            services.insert(std::make_pair(name, info));
            return true;
        }

        bool unregister_service(const char* name) override { return services.erase(name) > 0; }

        bool service_exists(const char* name) const override { return services.contains(name); }

        void* get_service(const char* name) const override {
            auto it = services.find(name);
            return it != services.end() ? it->second.service_pointer : nullptr;
        }

        ServiceInfo get_service_info(const char* name) const override {
            auto it = services.find(name);
            return it != services.end() ? it->second : ServiceInfo{};
        }

        std::uint32_t get_service_count() const override { return services.size(); }

        ServiceInfo get_service_info_by_index(std::uint32_t index) const override {
            auto it = services.begin();
            std::advance(it, index);
            return it != services.end() ? it->second : ServiceInfo{};
        }
    };
}
