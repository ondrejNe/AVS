
#include "rp2040-bno-demo.h"

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

    struct bno055_t bno055;
    struct bno055_all_float_s bnoData;

    int ret;
    // BNO055 initialization
    ret = bno055_setup(&bno055);

    printf("BNO055 setup done %d\n", ret);

    while (true) {
        uint32_t loop_start = millis();

        // BNO Accel
        ret = bno055_convert_float_accel_xyz_mg(&bnoData.accel);
        // BNO gyro
        ret = bno055_convert_float_gyro_xyz_rps(&bnoData.gyro);
        // BNO euler
        ret = bno055_convert_float_euler_h_deg(&bnoData.euler.h);
        ret = bno055_convert_float_euler_p_deg(&bnoData.euler.p);
        ret = bno055_convert_float_euler_r_deg(&bnoData.euler.r);

        printf("Ret: %d Loop %u\n", ret, loop_start);
        printf("BNO055 data:\n");
        printf("Accel: x=%f, y=%f, z=%f\n", bnoData.accel.x, bnoData.accel.y, bnoData.accel.z);
        printf("Gyro: x=%f, y=%f, z=%f\n", bnoData.gyro.x, bnoData.gyro.y, bnoData.gyro.z);
        printf("Euler: h=%f, p=%f, r=%f\n", bnoData.euler.h, bnoData.euler.p, bnoData.euler.r);

        while (millis() - loop_start < FREQUENCY_MILLIS)
        {
            /* busy wait */
        }
    }
}

int bno055_setup(struct bno055_t *bno055)
{
    // GPIO setup
    gpio_init(BNO_INT_PIN);
    gpio_init(BNO_RST_PIN);

    gpio_set_dir(BNO_INT_PIN, GPIO_IN);
    gpio_set_dir(BNO_RST_PIN, GPIO_OUT);

    gpio_put(BNO_RST_PIN, 0);
    sleep_ms(1);
    gpio_put(BNO_RST_PIN, 1);

    /* I2C setup*/
    i2c_init(BNO_I2C, 100000);
    gpio_set_function(BNO_SCK_PIN, GPIO_FUNC_I2C);
    gpio_set_function(BNO_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(BNO_SCK_PIN);
    gpio_pull_up(BNO_SDA_PIN);

    /* Sensor setup */
    bno055->bus_write = BNO055_I2C_bus_write;
    bno055->bus_read = BNO055_I2C_bus_read;
    bno055->delay_msec = BNO055_delay_msek;
    bno055->dev_addr = BNO055_I2C_ADDR1;

    sleep_ms(500);

    // Initialize BNO055 sensor
    int ret = bno055_init(bno055);
    if (ret != BNO055_SUCCESS)
    {
        printf("BNO init failed\n");
        return -1;
    }

    // Set power mode to normal
    ret = bno055_set_power_mode(BNO055_POWER_MODE_NORMAL);
    if (ret != BNO055_SUCCESS)
    {
        return -2;
    }
    // Set operation mode to config
    ret = bno055_set_operation_mode(BNO055_OPERATION_MODE_CONFIG);
    if (ret != BNO055_SUCCESS)
    {
        return -3;
    }

    // Set accelerometer power mode to normal
    ret = bno055_set_accel_power_mode(BNO055_ACCEL_NORMAL);
    if (ret != BNO055_SUCCESS)
    {
        return -4;
    }

    // Set gyro power mode to normal
    ret = bno055_set_gyro_power_mode(BNO055_GYRO_POWER_MODE_NORMAL);
    if (ret != BNO055_SUCCESS)
    {
        return -5;
    }

    // Set magnetometer power mode to normal
    ret = bno055_set_mag_power_mode(BNO055_MAG_POWER_MODE_NORMAL);
    if (ret != BNO055_SUCCESS)
    {
        return -6;
    }

    // Set operation mode to NDOF
    ret = bno055_set_operation_mode(BNO055_OPERATION_MODE_NDOF);
    if (ret != BNO055_SUCCESS)
    {
        return -7;
    }
    return 0;
}