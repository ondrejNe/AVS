
#include "rp2040-bmp-demo.h"

int main(void)
{
    // Pi pico SDK initialization
    stdio_init_all();
    while (getchar() != 10) {
        /* busy wait */
    }

    printf("Stdio Pico initialized\n");
    printf("Press enter to continue\n");
    while (getchar() != 10) {
        /* busy wait */
    }

    struct bmp3_dev bmp388;
    struct bmp3_data bmpData;

    int ret;
    // BMP388 initialization
    ret = bmp388_setup(&bmp388);

    printf("BMP388 setup done %d\n", ret);

    while (true) {
        uint32_t loop_start = millis();

        // BMP388 data reading
        ret = bmp3_get_sensor_data(BMP3_PRESS_TEMP, &bmpData, &bmp388);

        printf("Pressure: %f Pa, Temperature: %f C\n", bmpData.pressure, bmpData.temperature);

        while (millis() - loop_start < FREQUENCY_MILLIS)
        {
            /* busy wait */
        }
    }
}

int bmp388_setup(struct bmp3_dev *bmp388)
{
    /* I2C setup*/
    i2c_init(BMP_I2C, 100000);
    gpio_set_function(BMP_SCK_PIN, GPIO_FUNC_I2C);
    gpio_set_function(BMP_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(BMP_SCK_PIN);
    gpio_pull_up(BMP_SDA_PIN);

    int8_t rslt = bmp3_interface_init(bmp388, BMP3_I2C_INTF);
    bmp3_check_rslt("bmp3_interface_init", rslt);

    rslt = bmp3_init(bmp388);
    bmp3_check_rslt("bmp3_init", rslt);

    struct bmp3_settings bmpSettings = {0};
    bmpSettings.int_settings.drdy_en = BMP3_ENABLE;
    bmpSettings.press_en = BMP3_ENABLE;
    bmpSettings.temp_en = BMP3_ENABLE;

    bmpSettings.odr_filter.press_os = BMP3_OVERSAMPLING_2X;
    bmpSettings.odr_filter.temp_os = BMP3_OVERSAMPLING_2X;
    bmpSettings.odr_filter.odr = BMP3_ODR_100_HZ;

    uint16_t settings_sel = BMP3_SEL_PRESS_EN | BMP3_SEL_TEMP_EN | BMP3_SEL_PRESS_OS | BMP3_SEL_TEMP_OS | BMP3_SEL_ODR |
                            BMP3_SEL_DRDY_EN;

    rslt = bmp3_set_sensor_settings(settings_sel, &bmpSettings, bmp388);
    bmp3_check_rslt("bmp3_set_sensor_settings", rslt);

    bmpSettings.op_mode = BMP3_MODE_NORMAL;
    rslt = bmp3_set_op_mode(&bmpSettings, bmp388);
    bmp3_check_rslt("bmp3_set_op_mode", rslt);

    sleep_ms(100);

    struct bmp3_status bmpStatus;
    rslt = bmp3_get_status(&bmpStatus, bmp388);
    bmp3_check_rslt("bmp3_get_status", rslt);

    return rslt;
}
