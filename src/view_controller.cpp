#include "view_controller.h"
#include "basic_view.h"

void view_controller::run()
{
    view_canvas.createCanvas(width, height - status_height);
    view_canvas.setTextSize(3);
    status_canvas.createCanvas(width, status_height);
    status_canvas.setTextSize(3);
    while (true) {
        status.update(status_canvas);
        view_list.back()->update(view_canvas);
    }
}
void view_controller::add_view(basic_view* view)
{
    view_list.emplace_back(view);
}
