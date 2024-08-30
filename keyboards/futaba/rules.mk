# This file intentionally left blank

POINTING_DEVICE_ENABLE = yes
# MOUSEKEY_ENABLE = yes
POINTING_DEVICE_DRIVER = custom

ENCODER_MAP_ENABLE = yes
I2C_DRIVER_REQUIRED = yes
SRC += drivers/sensors/azoteq_iqs5xx.c
SRC += futaba_azoteq_iqs5xx_driver.c
