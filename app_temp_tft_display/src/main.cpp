#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/sys/printk.h>

int main()
{
  const struct device *const dev = DEVICE_DT_GET(DT_NODELABEL(tmp102));

  if (!device_is_ready(dev))
  {
    printk("Sensor is not ready!\n");
    return 1;
  }

  int ret;
  struct sensor_value temp_value;
  struct sensor_value attr;

  attr.val1 = 1;
  attr.val2 = 0;
  ret = sensor_attr_set(dev, SENSOR_CHAN_AMBIENT_TEMP, SENSOR_ATTR_SAMPLING_FREQUENCY, &attr);

  if (ret)
  {
    printk("sensor_attr_set failed: %d\n", ret);
    return 1;
  }
  while (1)
  {
    sensor_sample_fetch(dev);
    sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp_value);
    double temperature = sensor_value_to_double(&temp_value);
    printf("Actual temperature is : %.2f\n", temperature);
    k_msleep(1000);
  }

  return 0;
}