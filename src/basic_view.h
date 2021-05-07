#ifndef BASIC_VIEW_H
#define BASIC_VIEW_H

#include "M5EPD_Canvas.h"
#include <M5EPD.h>
#include <array>
#include <memory>
class basic_view {
public:
    basic_view() = default;
    ~basic_view() = default;
    virtual void update(M5EPD_Canvas& canvas) = 0;
};
#endif // BASIC_VIEW_H_
