https://community.st.com/t5/stm32-mcus-touchgfx-and-gui/new-stm32h747-disco-example-problems/td-p/65106
LCD based on FGRIDA FRD400B25025-A-CTK

new lib NT35510

The fix is available on GitHub :

https://github.com/STMicroelectronics/STM32CubeH7/commit/1c84713102f8509deb79ae14db8dbb104c17c45e#diff-8a5b12f7040dfb560c495dc0a1213725ba939bf19d531dd1e97067b6a1a79ec0

In fact , LCD DSI MB1166-A9 delivered with latest version of STM32H747I-DISCO/ boards come based on LCD FGRIDA FRD400B25025-A-CTK instead of FRD397B25009-D-CTK.

Now the firmware is updated , you just need to enable the right hardware component as defined in stm32h747i_discovery_conf.h file and add the new component library (NT35510) in your project .

/* IMPORTANT: One of the following flags must be enabled in stm32h747i_discovery_conf.h file */

/* options in order to select the target daughter board revision connected on STM32H747I DISCOVERY : !!!!!!!!!! */

/* USE_LCD_CTRL_OTM8009A */ /* Applicable for all LCD daughter boards (MB1166) except for Rev -A09 */

/* USE_LCD_CTRL_NT35510 */ /* Applicable only for LCD daughter boards (MB1166) Rev -A09 */