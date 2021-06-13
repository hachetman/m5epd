#ifndef SENSOR_VIEW_H
#define SENSOR_VIEW_H

#include "M5EPD_Canvas.h"
#include "basic_view.h"
#include "gui_table.h"
#include <list>

struct sensor_entry {
    int pos_x, pos_y;
    String name;
};

class sensor_view : public basic_view {
public:
    sensor_view() = default;
    ~sensor_view() = default;
    virtual void update(M5EPD_Canvas& canvas);
    virtual void init(M5EPD_Canvas& canvas, view_controller* controller);

private:
    static const int item_height = 80;
    float temperature;
    float humidity;
    int point[2][2];
    gui_table temp_entry;
    gui_table hum_entry;
};
#endif // SENSOR_VIEW_H_
