#include "start_view.h"
#include "special_view.h"
#include "view_controller.h"

void start_view::init(M5EPD_Canvas& canvas, view_controller* controller)
{
    add_entry("test");
    add_entry("item2");
    add_entry("item3");
    int counter = 0;
    view_ctrl = controller;
    for (auto const& i : menu_list) {
        canvas.fillRect(5, counter * item_height + 5, width - 10,
                        item_height - 10, 15);
        canvas.fillRect(10, counter * item_height + 10, width - 20,
                        item_height - 20, 0);
        canvas.drawString(i.name, 20,
                          counter * item_height - 5 + item_height / 2);
        counter++;
    }
    canvas.pushCanvas(0, canvas_start, UPDATE_MODE_DU4);
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
void start_view::update(M5EPD_Canvas& canvas)
{ // handling of the touches
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
                    view_ctrl->add_view(new special_view());
                }
            }
        }
    }
}

void start_view::add_entry(String name)
{
    menu_entry entry;
    entry.name = name;
    menu_list.emplace_back(entry);
}
