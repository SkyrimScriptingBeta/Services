#include <SkyrimScripting/Services/IServicesService.h>
#include <collections.h>

namespace SkyrimScripting::Services {
    // class ServicesService : public IServicesService {
    //     collections_map<const char*, void*> _services;

    // public:
    //     static IServicesService* instance() {
    //         static ServicesService instance;
    //         return &instance;
    //     }

    //     void* register_service(const char* name, void* service) override {
    //         auto it = _services.find(name);
    //         if (it != _services.end()) {
    //             void* existingService = it->second;
    //             it->second            = service;
    //             return existingService;
    //         }
    //         _services.insert({name, service});
    //         return nullptr;
    //     }

    //     void* get_service(const char* name) const override {
    //         auto it = _services.find(name);
    //         if (it != _services.end()) return it->second;
    //         return nullptr;
    //     }

    //     void* unregister_service(const char* name) override {
    //         auto it = _services.find(name);
    //         if (it != _services.end()) {
    //             void* service = it->second;
    //             _services.erase(it);
    //             return service;
    //         }
    //         return nullptr;
    //     }
    // };
}
