#include "special_view.h"
#include "view_controller.h"
void special_view::init(M5EPD_Canvas& canvas, view_controller* controller)
{
    view_ctrl = controller;
}

void special_view::update(M5EPD_Canvas& canvas)

{
    std::array<char, 60> buffer;
    canvas.fillRect(200, position, 10, 10, 0);
    position += 20;
    Serial.println("update 2");
    canvas.fillRect(200, position, 10, 10, 15);

    canvas.drawString(buffer.data(), 498 - 20, 5);
    canvas.pushCanvas(0, 44, UPDATE_MODE_DU4);
    if (position > 916) {
        canvas.fillRect(200, 900, 10, 40, 0);
        position = 0;
    }
}
