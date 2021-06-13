#include "NTP.h"
#include "secrets.h"
#include "view_controller.h"
#include <M5EPD.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <array>
#include <string>

const int default_rotation = 90;
const int delay_500ms = 500;
void setup()
{
    WiFiUDP wifiUdp;
    NTP ntp(wifiUdp);
    rtc_time_t RTCtime;
    rtc_date_t RTCDate;
    view_controller controller;
    M5.begin(true, false, true, true, false);
    M5.EPD.SetRotation(default_rotation);
    M5.TP.SetRotation(default_rotation);
    M5.EPD.Clear(true);
    ntp.ruleDST("CEST", Last, Sun, Mar, 2,
                120); // last sunday in march 2:00, timezone +120min (+1 GMT +
    // 1h summertime offset)
    ntp.ruleSTD("CET", Last, Sun, Oct, 3,
                60); // last sunday in october 3:00, timezone +60min (+1 GMT)
                     // ntp.isDST(false);
                     // ntp.timeZone(1);
                     // ntp.offset(0, 0, 0, 0);
    WiFi.begin(ssid, password);
    for (int i = 0; i < 20; i++) {
        Serial.println("Connecting ...");
        delay(delay_500ms);
        if (WiFiClass::status() == WL_CONNECTED) {
            Serial.println("connected ...");
            ntp.begin();
            Serial.println("start NTP");
            delay(delay_500ms);
            ntp.update();
            RTCtime.hour = ntp.hours();
            RTCtime.min = ntp.minutes();
            RTCtime.sec = ntp.seconds();
            RTCDate.day = ntp.day();
            RTCDate.mon = ntp.month();
            RTCDate.year = ntp.year();
            M5.RTC.setTime(&RTCtime);
            M5.RTC.setDate(&RTCDate);
            break;
        }
    }

    WiFi.disconnect(true, false);
    sensor_view view;
    controller.add_view(&view);
    controller.run();
}

void loop() {}
