#include "special_view.h"

void special_view::update(M5EPD_Canvas& canvas)
{
    std::array<char, 60> buffer;
    canvas.fillRect(200, position, 10, 10, 0);
    position += 20;
    canvas.fillRect(200, position, 10, 10, 15);

    sprintf(buffer.data(), "%d", (int)(position));
    canvas.drawString(buffer.data(), 498 - 20, 5);
    canvas.pushCanvas(0, 44, UPDATE_MODE_DU4);
    if (position > 916) {
        canvas.fillRect(200, 900, 10, 40, 0);
        position = 0;
    }
}
