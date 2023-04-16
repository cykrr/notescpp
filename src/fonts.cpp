#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "fonts.h"

int font_init(font_t *font, FcChar8  *family,  FcChar8 *style,
        FcChar8 *filename) {
    font->family = strdup((char*)family);
    font->style = strdup((char*)style);
    font->filename = strdup((char*)filename);
    return 0;
}
int font_destroy(font_t *font) {
    free(font->family);
    free(font->style);
    free(font->filename);
    return 0;
}

void fonts_show(font_t *fonts, unsigned int fonts_length) {
    printf("%10s\t\t%10s\t\t%10s\n", "Family", "Style", "Filename");
    for (unsigned int i = 0; i < fonts_length; i++)
    {
        printf("%10s\t\t%10s\t\t%10s\n", fonts[i].family, fonts[i].style,
                fonts[i].filename);
    }
}

font_t *fonts;
unsigned int fonts_length;

void init_fontconfig() {

    FcConfig* config = FcInitLoadConfigAndFonts();
    FcPattern* pat = FcPatternCreate();
    FcObjectSet* os = FcObjectSetBuild (FC_FAMILY, FC_STYLE, FC_LANG, FC_FILE,
            (char *) 0);

    FcFontSet* fs = FcFontList(config, pat, os);
    fonts_length = fs->nfont;

    // TODO: Store all fonts in a map to access them later.
    // Meanwhile we will use a default hardcoded font.
    void *tmp = malloc(fs->nfont * sizeof(font_t));
    if (!tmp) return;
    fonts=(font_t*)tmp;


    for (int i=0; fs && i < fs->nfont; ++i) {
        FcPattern* font = fs->fonts[i];
        FcChar8 *file, *style, *family;
        if (FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch     &&
            FcPatternGetString(font, FC_FAMILY, 0, &family) == FcResultMatch &&
            FcPatternGetString(font, FC_STYLE, 0, &style) == FcResultMatch)
        {
            font_t font = {};
            font_init(&font, family, style, file);
            fonts[i]=font;
        }
   }
    if (fs) FcFontSetDestroy(fs);
}
