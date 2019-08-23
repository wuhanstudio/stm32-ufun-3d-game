extern const struct fal_flash_dev stm32_onchip_flash;
	
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash,                                           \
}

#define FAL_PART_TABLE                                                          \
{                                                                               \
    {FAL_PART_MAGIC_WROD,       "app", "onchip_flash",         0,   128*1024, 0}, \
    {FAL_PART_MAGIC_WROD,      "flash0", "onchip_flash",   128*1024,  128*1024, 0}, \
}
