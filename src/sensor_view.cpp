#include "sensor_view.h"
#include "M5EPD_Canvas.h"
#include "gui_table.h"
#include "view_controller.h"
#include <memory>
void sensor_view::init(M5EPD_Canvas& canvas, view_controller* controller)
{
    temp_entry.set_position(20, 0);
    hum_entry.set_position(20, 100);

    view_ctrl = controller;
    if (M5.TP.avaliable()) {
        if (!M5.TP.isFingerUp()) {
            M5.TP.update();
            for (int i = 0; i < 2; i++) {
                tp_finger_t FingerItem = M5.TP.readFinger(i);
                point[i][0] = FingerItem.x;
                point[i][1] = FingerItem.y;
            }
        }
    }
}
void sensor_view::update(M5EPD_Canvas& canvas)
{
    M5.SHT30.UpdateData();
    temperature = M5.SHT30.GetTemperature();
    humidity = M5.SHT30.GetRelHumidity();
    temp_entry.draw(canvas, "Temperature:" + String(temperature) + " C");
    hum_entry.draw(canvas, "Humidity:" + String(humidity) + "%C");

    canvas.pushCanvas(0, canvas_start, UPDATE_MODE_DU4);
    if (M5.TP.avaliable()) {
        if (!M5.TP.isFingerUp()) {
            M5.TP.update();
            for (int i = 0; i < 2; i++) {
                tp_finger_t FingerItem = M5.TP.readFinger(i);
                if ((point[i][0] != FingerItem.x) ||
                    (point[i][1] != FingerItem.y)) {
                    point[i][0] = FingerItem.x;
                    point[i][1] = FingerItem.y;
                    Serial.printf("Finger ID:%d-->X: %d*C  Y: %d  Size: %d\r\n",
                                  FingerItem.id, FingerItem.x, FingerItem.y,
                                  FingerItem.size);
                }
            }
        }
    }
}
