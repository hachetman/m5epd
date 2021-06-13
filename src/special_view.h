#ifndef SPECIAL_VIEW_H
#define SPECIAL_VIEW_H

#include "M5EPD_Canvas.h"
#include "basic_view.h"
#include "view_controller.h"
#include <M5EPD.h>
#include <array>
#include <memory>
class special_view : public basic_view {
public:
    special_view() = default;
    ~special_view() = default;
    virtual void update(M5EPD_Canvas& canvas);
    virtual void init(M5EPD_Canvas& canvas, view_controller* controller);

private:
    int position = 0;
};
#endif // SPECIAL_VIEW_H_
