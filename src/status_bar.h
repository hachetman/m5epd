#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include "M5EPD_Canvas.h"
#include <M5EPD.h>
#include <array>
#include <memory>
class status_bar {
public:
    status_bar() = default;
    ~status_bar() = default;
    void update(M5EPD_Canvas& canvas);

private:
    uint32_t voltage = 0;
    rtc_time_t RTCtime;
    rtc_date_t RTCDate;
    static const int buffer_size = 64;
    const int lipo_low_voltage = 3300;
    const int lipo_high_voltage = 4250;
    std::array<char, buffer_size> buffer{};
};
#endif // STATUS_BAR_H_
