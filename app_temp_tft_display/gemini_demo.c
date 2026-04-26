#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>

int main(void) {
  /* Pobieramy wskaźnik do naszego czujnika używając etykiety z overlay'a */
  const struct device *const temp_sensor = DEVICE_DT_GET(DT_NODELABEL(tmp102));

  /* Sprawdzamy, czy system widzi urządzenie na magistrali I2C */
  if (!device_is_ready(temp_sensor)) {
    printf("Błąd: Czujnik TMP102 nie jest gotowy!\n");
    return 0;
  }

  printf("TMP102 znaleziony. Rozpoczynam pomiary...\n");

  while (1) {
    struct sensor_value temp;

    /* Krok 1: Wymuszenie pomiaru w czujniku */
    sensor_sample_fetch(temp_sensor);

    /* Krok 2: Pobranie wartości temperatury otoczenia */
    sensor_channel_get(temp_sensor, SENSOR_CHAN_AMBIENT_TEMP, &temp);

    /* Złożenie wyniku w jedną liczbę zmiennoprzecinkową (tzw. float) */
    double temperature = sensor_value_to_double(&temp);

    printf("Aktualna temperatura: %.2f st. C\n", temperature);

    /* Usypiamy na 1 sekundę */
    k_msleep(1000);
  }
  return 0;
}