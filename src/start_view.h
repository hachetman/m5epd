#ifndef START_VIEW_H
#define START_VIEW_H

#include "M5EPD_Canvas.h"
#include "basic_view.h"
#include <list>

struct menu_entry {
    int pos_x, pos_y;
    String name;
};

class start_view : public basic_view {
public:
    start_view() = default;
    ~start_view() = default;
    virtual void update(M5EPD_Canvas& canvas);
    virtual void init(M5EPD_Canvas& canvas, view_controller* controller);

private:
    static const int item_height = 80;
    int point[2][2];
    void add_entry(String name);
    std::list<menu_entry> menu_list;
};
#endif // START_VIEW_H_
