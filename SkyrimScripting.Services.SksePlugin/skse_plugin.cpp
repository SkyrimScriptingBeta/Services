#include <SkyrimScripting/Plugin.h>
#include <collections.h>

#include <string>

#include "SkyrimScripting/Services/IServicesService.h"

namespace SkyrimScripting::Services {
    class ServicesService : public IServicesService {
        collections_map<std::string, ServiceInfo> services;  // Changed key type to std::string

    public:
        static IServicesService* instance() {
            static ServicesService instance;
            return &instance;
        }

        bool register_service(void* service, const char* name, const char* description) override {
            SKSE::log::info("Registering service: Name='{}', Description='{}'", name, description);
            ServiceInfo info = {name, description, service, nullptr};
            services.insert(std::make_pair(std::string(name), info)
            );  // Convert name to std::string
            SKSE::log::info("Service '{}' registered successfully.", name);
            return true;
        }

        bool unregister_service(const char* name) override {
            SKSE::log::info("Unregistering service: Name='{}'", name);
            bool result = services.erase(std::string(name)) > 0;  // Convert name to std::string
            if (result) {
                SKSE::log::info("Service '{}' unregistered successfully.", name);
            } else {
                SKSE::log::warn("Failed to unregister service '{}': Service not found.", name);
            }
            return result;
        }

        bool service_exists(const char* name) const override {
            SKSE::log::debug("Checking existence of service: Name='{}'", name);
            bool exists = services.contains(std::string(name));  // Convert name to std::string
            SKSE::log::debug("Service '{}' exists: {}", name, exists);
            return exists;
        }

        void* get_service(const char* name) const override {
            SKSE::log::debug("Retrieving service: Name='{}'", name);
            auto it = services.find(std::string(name));  // Convert name to std::string
            if (it != services.end()) {
                SKSE::log::info("Service '{}' retrieved successfully.", name);
                return it->second.service_pointer;
            } else {
                SKSE::log::warn("Service '{}' not found.", name);
                return nullptr;
            }
        }

        ServiceInfo get_service_info(const char* name) const override {
            SKSE::log::debug("Retrieving service info: Name='{}'", name);
            auto it = services.find(std::string(name));  // Convert name to std::string
            if (it != services.end()) {
                SKSE::log::info("Service info for '{}' retrieved successfully.", name);
                return it->second;
            } else {
                SKSE::log::warn("Service info for '{}' not found.", name);
                return ServiceInfo{};
            }
        }

        std::uint32_t get_service_count() const override {
            std::uint32_t count = services.size();
            SKSE::log::info("Total number of registered services: {}", count);
            return count;
        }

        ServiceInfo get_service_info_by_index(std::uint32_t index) const override {
            SKSE::log::debug("Retrieving service info by index: Index={}", index);
            auto it = services.begin();
            std::advance(it, index);
            if (it != services.end()) {
                SKSE::log::info("Service info at index {} retrieved successfully.", index);
                return it->second;
            } else {
                SKSE::log::warn("No service found at index {}.", index);
                return ServiceInfo{};
            }
        }
    };
}

// PostLoad, send a message to EVERYONE passing a reference to the ServicesService.
SKSEPlugin_OnPostLoad {
    if (auto* servicesService = SkyrimScripting::Services::ServicesService::instance()) {
        servicesService->register_service(
            servicesService, "SkyrimScripting.Services.ServicesService", "The Services Service."
        );
        SKSE::log::info("Sending ServicesService message.");
        SKSE::GetMessagingInterface()->Dispatch(
            69, (void*)servicesService, sizeof(std::uintptr_t), nullptr
        );
        SKSE::log::info("ServicesService message sent.");
    } else {
        SKSE::log::warn("Failed to send IServicesService message: ServicesService is not available."
        );
    }
}
