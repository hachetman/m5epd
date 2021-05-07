#include "status_bar.h"

void status_bar::update(M5EPD_Canvas& canvas)
{
    M5.RTC.getDate(&RTCDate);
    M5.RTC.getTime(&RTCtime);
    voltage = M5.getBatteryVoltage();
    if (voltage < lipo_low_voltage) {
        voltage = lipo_low_voltage;
    }
    else if (voltage > lipo_high_voltage) {
        voltage = lipo_high_voltage;
    }
    float battery = (float)(voltage - lipo_low_voltage) /
                    (float)(lipo_high_voltage - lipo_low_voltage);

    // uint8_t px = battery * 25;
    sprintf(buffer.data(), "%d%%", (int)(battery * 100));
    canvas.drawString(buffer.data(), 498 - 20, 5);
    // canvas->fillRect(498 + 3, 8 + 10, px, 13, 15);
    sprintf(buffer.data(), "%d/%02d/%02d %02d:%02d:%02d %02d", RTCDate.year,
            RTCDate.mon, RTCDate.day, RTCtime.hour, RTCtime.min, RTCtime.sec,
            M5.getBatteryVoltage());
    canvas.drawString(buffer.data(), 5, 5);
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}
