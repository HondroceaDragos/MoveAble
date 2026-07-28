#pragma once

#include <raylib.h>
#include <stdint.h>
#include <string>
#include <tuple>

namespace default_buffer {
    constexpr int32_t width = 720;
    constexpr int32_t height = 480;
}

class Buffer {
public:
    Buffer();
    void init(const std::string& name);
    void deinit();

    const std::tuple<int32_t, int32_t> getDimensions() const;
private:
    class Monitor {
    public:
        inline static int32_t id = 0;
        struct {
            int32_t width;
            int32_t height;
        } dimensions;
    } _monitor;

    struct {
        int32_t width;
        int32_t height;
    } _dimensions;
};