#include "AmbientLightController.h"

namespace e506::ambient_light {
namespace {

constexpr Color kDefaultColor = Color::WarmWhite;

}  // namespace

AmbientLightController::AmbientLightController(
    ILightDriver& driver,
    IPreferenceStore& preferences,
    IDiagnosticSink& diagnostics)
    : driver_(driver),
      preferences_(preferences),
      diagnostics_(diagnostics) {}

bool AmbientLightController::initialize() {
    const auto stored = preferences_.load();
    const bool use_default = !stored || !isSupported(*stored);
    if (stored && !isSupported(*stored)) {
        diagnostics_.report(Diagnostic::UnsupportedValue);
    }
    const auto selected = use_default ? kDefaultColor : *stored;

    if (!driver_.apply(selected)) {
        setDriverFailure(true);
        return false;
    }
    active_color_ = selected;
    setDriverFailure(false);

    if (!use_default) {
        return true;
    }
    if (!preferences_.save(selected)) {
        setPersistenceFailure(true);
        return false;
    }
    setPersistenceFailure(false);
    return true;
}

bool AmbientLightController::setColor(Color color) {
    if (!isSupported(color)) {
        diagnostics_.report(Diagnostic::UnsupportedValue);
        return false;
    }
    if (active_color_ && *active_color_ == color) {
        return true;
    }

    if (!driver_.apply(color)) {
        setDriverFailure(true);
        return false;
    }
    active_color_ = color;
    setDriverFailure(false);

    if (!preferences_.save(color)) {
        setPersistenceFailure(true);
        return false;
    }
    setPersistenceFailure(false);
    return true;
}

std::optional<Color> AmbientLightController::activeColor() const noexcept {
    return active_color_;
}

bool AmbientLightController::isSupported(Color color) noexcept {
    bool supported = false;
    switch (color) {
        case Color::WarmWhite:
        case Color::White:
        case Color::Blue:
        case Color::Red:
            supported = true;
            break;
        default:
            break;
    }
    return supported;
}

void AmbientLightController::setDriverFailure(bool active) {
    if (active == driver_failure_active_) {
        return;
    }
    driver_failure_active_ = active;
    if (active) {
        diagnostics_.report(Diagnostic::DriverFailure);
    } else {
        diagnostics_.clear(Diagnostic::DriverFailure);
    }
}

void AmbientLightController::setPersistenceFailure(bool active) {
    if (active == persistence_failure_active_) {
        return;
    }
    persistence_failure_active_ = active;
    if (active) {
        diagnostics_.report(Diagnostic::PersistenceFailure);
    } else {
        diagnostics_.clear(Diagnostic::PersistenceFailure);
    }
}

}  // namespace e506::ambient_light
