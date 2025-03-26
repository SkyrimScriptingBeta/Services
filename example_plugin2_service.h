#include <cstdint>

struct IPluginTwoService {
    virtual std::uint32_t get_int() const              = 0;
    virtual void          set_int(std::uint32_t value) = 0;

protected:
    virtual ~IPluginTwoService() = default;
};
