#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>

extern "C"
{
  extern const lv_image_dsc_t papuga_scalled;
}

int main()
{
  const struct device *display = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

  if (!device_is_ready(display))
  {
    printk("Error: display not ready!\n");
    return 1;
  }

  display_blanking_off(display);

  lv_obj_t *img = lv_image_create(lv_screen_active());
  lv_image_set_src(img, &papuga_scalled);
  lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

  while (1)
  {
    lv_task_handler();
    k_msleep(5);
  }

  return 0;
}
