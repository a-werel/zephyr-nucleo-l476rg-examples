#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);
int main() {
  int ret;

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
  if (ret < 0)
    return 1;

  ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
  if (ret < 0)
    return 1;

  while (1) {
    int val = gpio_pin_get_dt(&button);
    gpio_pin_set_dt(&led, val);
    k_msleep(10);
  }

  return 0;
}