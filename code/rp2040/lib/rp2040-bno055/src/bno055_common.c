#include "bno055_common.h"
#include "bno055_config.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

s8 BNO055_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    int ret = i2c_write_blocking(BNO_I2C, dev_addr, &reg_addr, 1, true);
    ret += i2c_read_blocking(BNO_I2C, dev_addr, reg_data, cnt, false);

    if (ret > 0)
        ret = 0; // compatibility with a BNO driver
    return ret;
}

s8 BNO055_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    uint8_t buf[cnt + 1];
    buf[0] = reg_addr; // first written byte is register address to write to (start writing from)
    memcpy(buf + 1, reg_data, cnt);
    int ret = i2c_write_blocking(BNO_I2C, dev_addr, buf, cnt + 1, false);
    if (ret > 0)
        ret = 0; // compatibility with a BNO driver
    return ret;
}
void BNO055_delay_msek(u32 msek)
{
    sleep_ms(msek); // Delay using millisecond sleep
}

int bno055_interface_init(struct bno055_t* bno055) {
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

    return 0;
}
