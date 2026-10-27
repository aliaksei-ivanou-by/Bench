#pragma once

#include <optional>

namespace e506::ambient_light {

enum class Color {
    WarmWhite,
    White,
    Blue,
    Red
};

enum class Diagnostic {
    UnsupportedValue,
    DriverFailure,
    PersistenceFailure
};

class ILightDriver {
public:
    virtual ~ILightDriver() = default;
    virtual bool apply(Color color) = 0;
};

class IPreferenceStore {
public:
    virtual ~IPreferenceStore() = default;
    virtual std::optional<Color> load() = 0;
    virtual bool save(Color color) = 0;
};

class IDiagnosticSink {
public:
    virtual ~IDiagnosticSink() = default;
    virtual void report(Diagnostic diagnostic) = 0;
    virtual void clear(Diagnostic diagnostic) = 0;
};

class AmbientLightController {
public:
    AmbientLightController(ILightDriver& driver,
                           IPreferenceStore& preferences,
                           IDiagnosticSink& diagnostics);

    bool initialize();
    bool setColor(Color color);
    std::optional<Color> activeColor() const noexcept;

private:
    static bool isSupported(Color color) noexcept;
    void setDriverFailure(bool active);
    void setPersistenceFailure(bool active);

    ILightDriver& driver_;
    IPreferenceStore& preferences_;
    IDiagnosticSink& diagnostics_;
    std::optional<Color> active_color_;
    bool driver_failure_active_{false};
    bool persistence_failure_active_{false};
};

}  // namespace e506::ambient_light
