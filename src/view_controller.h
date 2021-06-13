#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H

#include "M5EPD_Canvas.h"
#include "basic_view.h"
#include "sensor_view.h"
#include "special_view.h"
#include "start_view.h"
#include "status_bar.h"
#include <list>

class view_controller {
public:
    view_controller() = default;
    void run();
    void add_view(basic_view* view);

private:
    std::list<basic_view*> view_list;
    status_bar status;
    M5EPD_Canvas view_canvas = M5EPD_Canvas(&M5.EPD);
    M5EPD_Canvas status_canvas = M5EPD_Canvas(&M5.EPD);
    static const int width = 540;
    static const int height = 960;
    static const int status_height = 44;
};
#endif // STATUS_BAR_H_
