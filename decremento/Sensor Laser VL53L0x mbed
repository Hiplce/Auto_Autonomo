/*
 * Mbed Application program
 *   Time-of-Flight ranging and gesture detection sensor / STMicro VL53L0X
 *      http://www.st.com/ja/imaging-and-photonics-solutions/vl53l0x.html
 *
 *    1) AKIZUKI AE-VL53L0X
 *      http://akizukidenshi.com/catalog/g/gM-12590/
 *    2) SWITCH SCIENCE  Pololu VL53L0X (POLOLU-2490)
 *      https://www.switch-science.com/catalog/2869/
 *    3) SWITCH SCIENCE  VL53L0X (SSCI-028943)
 *      https://www.switch-science.com/catalog/2894/
 *    4) Strawberry Linux
 *      https://strawberry-linux.com/catalog/items?code=15310
 *
 *    ---- Tested AE-VL53L0X BOARD and handmade circuit ----
 *      Tested on below Mbed boards and works fine on mbed 2.0
 *          Nucleo-F303K8
 *          Nucleo-F334R8, -F401RE, -F411RE, -F446RE
 *          Nucleo-L053R8, -L073RZ, -L152RE, -L476RG
 *          FRDM-K64F
 *          TY51822r3
 *      Run also on mbed-os5 (Tested on Nucleo-F446RE)
 *
 * Copyright (c) 2018 Kenji Arai / JH1PJL
 *  http://www.page.sannet.ne.jp/kenjia/index.html
 *  http://mbed.org/users/kenjiArai/
 *      Created:    January   21st, 2018
 *      Revised:    Feburary   6th, 2018 (with updated VL53L0X_simple library)
 */

//  Include --------------------------------------------------------------------
#include "mbed.h"
#include "VL53L0X.h"

//  Definition -----------------------------------------------------------------
#define USE_LCD     0
#define USE_XSHUT   0

//  Constructor ----------------------------------------------------------------
DigitalOut  myled(LED1);
Serial      pc(USBTX, USBRX);
//I2C         i2c(P0_30, P0_7);     // only for TY51822r3
I2C         i2c(I2C_SDA, I2C_SCL);
#if USE_XSHUT
VL53L0X     sensor(i2c, D8);        // XSHUT = D8
#else
VL53L0X     sensor(i2c, NC);        // XSHUT = NC
#endif
#if USE_LCD
TextLCD_I2C_N lcd(&i2c, 0x7c, TextLCD::LCD8x2);  // LCD(Akizuki  AQM0802A)
#endif
Timer       t;

//  RAM ------------------------------------------------------------------------

//  ROM / Constant data --------------------------------------------------------
char *const msg0  = "VL53L0X is running correctly!!\r\n";
char *const msg1  = "VL53L0X -> something is wrong!!\r\n";
char *const msg2  = "#,";
char *const msg3  = "d[mm]=,";
char *const msg4  = "d[mm]=,error,";
char *const msg5  = "VL53[mS]=, ";
char *const msg6  = "all[mS]=, ";

//  Function prototypes --------------------------------------------------------

//------------------------------------------------------------------------------
//  Control Program
//------------------------------------------------------------------------------
int main()
{
    int status = VL53L0X_ERROR_NONE;
    uint32_t data;
    uint32_t count = 0;
    uint32_t tm_sensor;
    uint32_t tm_all_work;

#if USE_LCD
    lcd.locate(0, 0);
    //        12345678
    lcd.puts("12345678");
    lcd.locate(0, 1);
    //        12345678
    lcd.puts(" JH1PJL ");
    lcd.setCursor(TextLCD_Base::CurOff_BlkOff);
    lcd.setContrast(0x19);
    wait(2.0f);
#endif
#if USE_XSHUT
    status = sensor.init_sensor(0x33);  // set new I2C address
#else
    // no control XSHUT then set default address (no other way)
    status = sensor.init_sensor(VL53L0X_DEFAULT_ADDRESS);
#endif
    if (status == VL53L0X_ERROR_NONE) {
        pc.printf(msg0);
    } else {
        pc.printf(msg1);
    }
    status = sensor.set_mode(range_long_distance_33ms_200cm);
    //status = sensor.set_mode(range_hi_accurate_200ms_120cm);
    //status = sensor.set_mode(range_hi_speed_20ms_120cm);
    if (status == VL53L0X_ERROR_NONE) {
        pc.printf(msg0);
    } else {
        pc.printf(msg1);
    }
    while(true) {
        t.reset();
        t.start();
        //myled = !myled;
        status = sensor.get_distance(&data);
        tm_sensor = t.read_ms();
        if (status == VL53L0X_ERROR_NONE) {
            pc.printf("%s%5d,%s%5d,", msg2, count++, msg3, data);
        } else {
            pc.printf("%s%5d,%s", msg2, count++, msg4);
        }
#if USE_LCD
        if ((count % 4) == 0){
            lcd.locate(0, 0);
            lcd.printf(" %5d  ", data);
            lcd.locate(0, 1);
            lcd.printf(" %5d  ", count);
        }
#endif
        pc.printf("%s%d,%s%d\r\n", msg5, tm_sensor, msg6, tm_all_work);
        tm_all_work = t.read_ms();
        if (tm_all_work < 99){
            wait_ms(100 - tm_all_work);
        }
    }
}
