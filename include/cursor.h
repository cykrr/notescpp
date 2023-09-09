#ifndef CURSOR_H
#define CURSOR_H
#include "nanovg.h"
class Cursor {
    private:
        NVGcontext *vg;
        bool   show_cursor = true;
        /* double last_cursor_tooggle_time = 0.0; */
        /* const double cursor_blink_interval = 0.5; */
    public:
        Cursor(NVGcontext *nvg) : vg(nvg) {

        }
        void render();

};

void Cursor::render()
{
    if (show_cursor)
    {
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
        nvgBeginPath(vg);
        nvgRect(vg, 10, 10, 10, 10);
        nvgFill(vg);
    }
}
#endif
