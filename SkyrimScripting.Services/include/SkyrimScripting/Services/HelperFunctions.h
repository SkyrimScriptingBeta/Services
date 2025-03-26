#pragma once

#include <cstdint>
#include <string_view>

#include "ServiceInfo.h"

namespace SkyrimScripting::Services::HelperFunctions {
    /**
     * Register a service with the given name and description.
     *
     * If the service already exists, it will be replaced.
     * Returns true if the service was successfully registered.
     */
    bool RegisterServicePointer(void* service, std::string_view name, std::string_view description);

    /**
     * Register a service with the given name and description (templated version).
     *
     * If the service already exists, it will be replaced.
     * Returns true if the service was successfully registered.
     */
    template <typename T>
    bool RegisterService(T* service, std::string_view name, std::string_view description) {
        return RegisterServicePointer(static_cast<void*>(service), name, description);
    }

    /**
     * Unregister a service by its name.
     *
     * Returns true if the service was successfully unregistered, false otherwise.
     */
    bool UnregisterService(std::string_view name);

    /**
     * Check if a service exists by its name.
     *
     * Returns true if the service exists, false otherwise.
     */
    bool ServiceExists(std::string_view name);

    /**
     * Get a pointer to a service by its name.
     *
     * Returns a pointer to the service if it exists, or nullptr otherwise.
     */
    void* GetServicePointer(std::string_view name);

    /**
     * Get a pointer to a service by its name (templated version).
     *
     * Returns a pointer to the service if it exists, or nullptr otherwise.
     */
    template <typename T>
    T* GetService(std::string_view name) {
        return static_cast<T*>(GetServicePointer(name));
    }

    /**
     * Get information about a service by its name.
     *
     * Returns a `ServiceInfo` struct containing details about the service.
     */
    ServiceInfo GetServiceInfo(std::string_view name);

    /**
     * Get the total number of registered services.
     *
     * Returns the count of registered services.
     */
    std::uint32_t GetServiceCount();

    /**
     * Get information about a service by its index.
     *
     * Returns a `ServiceInfo` struct containing details about the service.
     */
    ServiceInfo GetServiceInfoByIndex(std::uint32_t index);
}