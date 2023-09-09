#include <string>
#include "cursor.h"
#include <sstream>

class EditView {

    private:
        float font_size = 32.f;
        std::string buffer = "This is a sample buffer\nSaying hello now.";

    private:
        NVGcontext *vg;
        Cursor c;

        void draw_slice_buffer() {

            std::string token = "\n";
            //split str with strtok with \n and store it in token
            std::istringstream iss(this->buffer);
            std::string line;
            float y = 30.0f;
            while (std::getline(iss, line, '\n')) {
                nvgText(vg, 10.0f, y, line.c_str(), nullptr);
                y+=font_size;
            }

        }
    public:
        EditView(NVGcontext *vgc): vg(vgc), c(vgc) {

        }

        void draw_text() {
            nvgBeginPath(vg);


            // draw Hello world at left upper corner with white color
            nvgFontFace(vg, "sans");
            nvgFontSize(vg, font_size);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));

            draw_slice_buffer();

        }
        void putc(char c) {
            this->buffer.push_back(c);
        }

        void delete_char() {
            this->buffer.pop_back();
        }
};
