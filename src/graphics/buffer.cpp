#include "../../include/graphics/buffer.hpp"

Buffer::Buffer() {}

void Buffer::init(const std::string &name) {
    InitWindow(default_buffer::width, default_buffer::height, name.c_str());

    _monitor.id = GetCurrentMonitor();
    _monitor.dimensions.width = GetMonitorWidth(_monitor.id);
    _monitor.dimensions.height = GetMonitorHeight(_monitor.id);

    _dimensions.width = _monitor.dimensions.width / 2;
    _dimensions.height = _monitor.dimensions.height / 2;

    SetWindowSize(_dimensions.width, _dimensions.height);
    SetTargetFPS(GetMonitorRefreshRate(_monitor.id));
}

void Buffer::deinit() { CloseWindow(); }

const std::tuple<int32_t, int32_t> Buffer::getDimensions() const {
    return std::make_tuple(_dimensions.width, _dimensions.height);
}
