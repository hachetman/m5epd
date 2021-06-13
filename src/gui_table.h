#ifndef GUI_TABLE_H
#define GUI_TABLE_H

#include "M5EPD_Canvas.h"
#include <list>
#include <memory>

class gui_table {
public:
    gui_table() = default;
    ~gui_table() = default;
    virtual void draw(M5EPD_Canvas& canvas, String data);
    void set_position(int x, int y);

private:
    int pos_x;
    int pos_y;
};
#endif // GUI_TABLE_H_
