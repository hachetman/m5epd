#include "view_controller.h"
#include "basic_view.h"

void view_controller::run()
{
    view_canvas.createCanvas(width, height - status_height);
    view_canvas.setTextSize(3);
    status_canvas.createCanvas(width, status_height);
    status_canvas.setTextSize(3);
    view_list.back()->init(view_canvas, this);
    while (true) {
        Serial.println("update status");
        status.update(status_canvas);
        Serial.println("update view");
        view_list.back()->update(view_canvas);
    }
}
void view_controller::add_view(basic_view* view)
{
    Serial.println("Adding View");
    view_list.emplace_back(view);
    Serial.println("Added View");
}
