#include "gui_table.h"
#include "HardwareSerial.h"
#include <memory>
using std::shared_ptr;

void gui_table::draw(M5EPD_Canvas& canvas, String data)
{
    canvas.drawString(data, pos_x, pos_y);
}
void gui_table::set_position(int x, int y)
{
    pos_x = x;
    pos_y = y;
}
