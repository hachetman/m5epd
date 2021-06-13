#ifndef BASIC_VIEW_H
#define BASIC_VIEW_H

#include "M5EPD_Canvas.h"
#include <M5EPD.h>
#include <array>
#include <list>
#include <memory>
class view_controller;
class basic_view {
public:
    basic_view() = default;
    ~basic_view() = default;
    virtual void update(M5EPD_Canvas& canvas) = 0;
    virtual void init(M5EPD_Canvas& canvas, view_controller* controller) = 0;

protected:
    const static int height = 916;
    const static int width = 540;
    const static int canvas_start = 44;
    view_controller* view_ctrl;
};
#endif // BASIC_VIEW_H_
