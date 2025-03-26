struct IPluginOneService {
    virtual const char* get_string() const = 0;

protected:
    virtual ~IPluginOneService() = default;
};
