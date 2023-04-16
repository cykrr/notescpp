#ifndef fonts_h
#define fonts_h
#include <fontconfig/fontconfig.h>
typedef struct font_t {
    char *family;
    char *style;
    char *filename;
} font_t;

int font_init(font_t *font, FcChar8  *family,  FcChar8 *style,
        FcChar8 *filename);
int font_destroy(font_t *font);

void fonts_show(font_t *fonts);
#endif
