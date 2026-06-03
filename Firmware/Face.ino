#include "../../lv_examples.h"

// Define the paths to your individual animation frames
static const char * anim_paths[] = {
    "Face:Untitled222_20260522153223.JPG",
    "Face:Untitled222_20260522153214.JPG",
    "Face:Untitled222_20260522153223.JPG",
    "Face:Untitled222_20260522153223.JPG",
    "Face:Untitled222_20260522153223.JPG"
};

// Apply the path array to your animated image widget
lv_animimg_set_src(animimg, (const void **)anim_paths, 5);

#if LV_USE_ANIMIMG && LV_BUILD_EXAMPLES
LV_IMAGE_DECLARE(animimg001);
LV_IMAGE_DECLARE(animimg002);
LV_IMAGE_DECLARE(animimg003);
LV_IMAGE_DECLARE(animimg004);
LV_IMAGE_DECLARE(animimg005);
static const lv_image_dsc_t * anim_imgs[5] = {
    &animimg001,
    & animimg002,
    & animimg003,
    & animimg004,
    & animimg005,

};
/**
 * @title Three-frame animated image
 * @brief Cycle three frames on a centered animated image widget.
 *
 * An `lv_animimg` is centered on the active screen and receives an
 * array of three `lv_image_dsc_t` descriptors through
 * `lv_animimg_set_src`. `lv_animimg_set_duration` sets one full cycle
 * to 1000 ms, `lv_animimg_set_repeat_count` uses
 * `LV_ANIM_REPEAT_INFINITE`, and `lv_animimg_start` kicks the
 * animation off.
 */


void lv_example_animimg_play(void)
{
    tft.startWrite();
    tft.setAddrWindow(0, 0, camera_width, camera_height);
    lv_obj_t * animimg0 = lv_animimg_create(lv_screen_active());
    lv_obj_center(animimg0);
    lv_animimg_set_src(animimg0, (const void **) anim_imgs, 5);
    lv_animimg_set_duration(animimg0, 500);
    lv_animimg_set_repeat_count(animimg0, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(animimg0);
    tft.endWrite();
}
#endif

