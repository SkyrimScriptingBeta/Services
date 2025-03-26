#include "SkyrimScripting/Services/HelperFunctions.h"

#include <SKSE/SKSE.h>

#include "SkyrimScripting/Services/IServicesService.h"

namespace SkyrimScripting::Services::HelperFunctions {

    bool RegisterServicePointer(
        void* service, std::string_view name, std::string_view description
    ) {
        if (auto* servicesService = IServicesService::get()) {
            return servicesService->register_service(service, name.data(), description.data());
        }
        SKSE::log::warn("Failed to register service: IServicesService is not available.");
        return false;
    }

    bool UnregisterService(std::string_view name) {
        if (auto* servicesService = IServicesService::get()) {
            return servicesService->unregister_service(name.data());
        }
        SKSE::log::warn("Failed to unregister service: IServicesService is not available.");
        return false;
    }

    bool ServiceExists(std::string_view name) {
        if (auto* servicesService = IServicesService::get()) {
            return servicesService->service_exists(name.data());
        }
        SKSE::log::warn("Failed to check if service exists: IServicesService is not available.");
        return false;
    }

    void* GetServicePointer(std::string_view name) {
        if (auto* servicesService = IServicesService::get()) {
            return servicesService->get_service(name.data());
        }
        SKSE::log::warn("Failed to get service pointer: IServicesService is not available.");
        return nullptr;
    }

    ServiceInfo GetServiceInfo(std::string_view name) {
        if (auto* servicesService = IServicesService::get()) {
            return servicesService->get_service_info(name.data());
        }
        SKSE::log::warn("Failed to get service info: IServicesService is not available.");
        return {};
    }

    std::uint32_t GetServiceCount() {
        if (auto* servicesService = IServicesService::get()) {
            return servicesService->get_service_count();
        }
        SKSE::log::warn("Failed to get service count: IServicesService is not available.");
        return 0;
    }

    ServiceInfo GetServiceInfoByIndex(std::uint32_t index) {
        if (auto* servicesService = IServicesService::get()) {
            return servicesService->get_service_info_by_index(index);
        }
        SKSE::log::warn("Failed to get service info by index: IServicesService is not available.");
        return {};
    }

}
