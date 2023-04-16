#include "args.h"
int main(int argc, char **argv) {
    parse_args(argc, argv);
    init_fontconfig();



    // create buffer and put text in it
    hb_buffer_t *buffer;
    buffer = hb_buffer_create();
    hb_buffer_add_utf8(buffer, "asd", -1, 0, -1);
    // set script, lang, dir of the buffer
    hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);
    hb_buffer_set_script(buffer, HB_SCRIPT_LATIN);
    hb_buffer_set_language(buffer, hb_language_from_string("es", -1));

    // Create face and font from fontfile
    hb_blob_t *blob = hb_blob_create_from_file("/usr/share/fonts/droid/DroidSans.ttf");
    hb_face_t *face = hb_face_create(blob, 0);
    hb_font_t *font = hb_font_create(face);
    // shape!
    hb_shape(font, buffer, NULL, 0);

    // Get the glyph pos. and info.
    unsigned int glyph_count;
    hb_glyph_info_t *glyph_info = hb_buffer_get_glyph_infos(buffer, &glyph_count);
    hb_glyph_position_t *glyph_pos = hb_buffer_get_glyph_positions(buffer, &glyph_count);

    hb_position_t x = 0, y = 0;
    for (unsigned int i=0; i<glyph_count; i++) {
        hb_codepoint_t  glyphid = glyph_info[i].codepoint;
        hb_position_t  xoff = glyph_pos[i].x_offset;
        hb_position_t  yoff = glyph_pos[i].y_offset;
        hb_position_t  xadv = glyph_pos[i].x_advance;
        hb_position_t  yadv = glyph_pos[i].y_advance;
        x+=xadv;
        y+=yadv;
    }

    hb_buffer_destroy(buffer);
    hb_font_destroy(font);
    hb_face_destroy(face);
    hb_blob_destroy(blob);
    return 0;
}
