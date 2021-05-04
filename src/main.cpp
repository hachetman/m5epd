#include "NTP.h"
#include <WiFi.h>
//#include "status_bar.h"
#include "secrets.h"
#include <M5EPD.h>
#include <WiFiUdp.h>
int point[2][2];
M5EPD_Canvas canvas(&M5.EPD);
M5EPD_Canvas canvas2(&M5.EPD);
WiFiUDP wifiUdp;
NTP ntp(wifiUdp);
rtc_time_t RTCtime;
rtc_date_t RTCDate;
int wifi_timeout;
char timeStrbuff[64];
const int width = 540;
const int status_height = 40;
const int view_height = 920;
const int default_rotation = 90;
const int delay_500ms = 500;
void setup()
{
    M5.begin(true, true, true, true, false);
    M5.EPD.SetRotation(default_rotation);
    M5.TP.SetRotation(default_rotation);
    M5.EPD.Clear(true);
    // status_bar statusbar(width, width);
    canvas.createCanvas(width, view_height, 1);
    canvas2.createCanvas(width, status_height, 1);
    canvas.setTextSize(3);
    canvas2.setTextSize(3);
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
    ntp.ruleDST("CEST", Last, Sun, Mar, 2,
                120); // last sunday in march 2:00, timetone +120min (+1 GMT +
    // 1h summertime offset)
    ntp.ruleSTD("CET", Last, Sun, Oct, 3,
                60); // last sunday in october 3:00, timezone +60min (+1 GMT)
                     // ntp.isDST(false);
                     // ntp.timeZone(1);
                     // ntp.offset(0, 0, 0, 0);
}

void loop()
{
    M5.RTC.getDate(&RTCDate);
    M5.RTC.getTime(&RTCtime);
    sprintf(timeStrbuff, "%d/%02d/%02d %02d:%02d:%02d", RTCDate.year,
            RTCDate.mon, RTCDate.day, RTCtime.hour, RTCtime.min, RTCtime.sec);

    canvas.drawString(timeStrbuff, 0, 0);
    canvas2.drawString(timeStrbuff, 0, 0);
    canvas.pushCanvas(0, 80, UPDATE_MODE_DU4);
    canvas2.pushCanvas(0, 0, UPDATE_MODE_DU4);
    if (M5.TP.avaliable()) {
        if (!M5.TP.isFingerUp()) {
            M5.TP.update();
            canvas.fillCanvas(0);
            bool is_upadte = false;
            for (int i = 0; i < 2; i++) {
                tp_finger_t FingerItem = M5.TP.readFinger(i);
                if ((point[i][0] != FingerItem.x) ||
                    (point[i][1] != FingerItem.y)) {
                    is_upadte = true;
                    point[i][0] = FingerItem.x;
                    point[i][1] = FingerItem.y;
                    canvas.fillRect(FingerItem.x - 50, FingerItem.y - 50, 100,
                                    100, 15);
                }
            }
            if (is_upadte) {
                canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
            }
        }
    }
}
