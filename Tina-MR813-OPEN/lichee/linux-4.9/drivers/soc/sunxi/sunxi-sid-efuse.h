/*
 * The key define in SUNXI Efuse.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * Matteo <duanmintao@allwinnertech.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __SUNXI_SID_EFUSE_H__
#define __SUNXI_SID_EFUSE_H__

#include <linux/sunxi-sid.h>

typedef struct {
	char name[64];
	uint32_t len;
	uint32_t offset;
	uint64_t key_data;
} sunxi_efuse_key_info_t;

struct efuse_crypt {
	sunxi_efuse_key_info_t key_store;
	struct work_struct work;
	struct completion work_end;
	struct mutex mutex;
	unsigned char *temp_data;
	unsigned int cmd;
	unsigned int ret;
};

typedef struct efuse_crypt efuse_cry_st;
typedef struct efuse_crypt *efuse_cry_pt;

#define SECBLK_READ							_IO('V', 20)
#define SECBLK_WRITE						_IO('V', 21)
#define SECBLK_IOCTL						_IO('V', 22)

struct secblc_op_t{
	int item;
	unsigned char *buf;
	unsigned int len;
};



struct efuse_key_map {
	char name[SUNXI_KEY_NAME_LEN];
	int offset;
	int size;	 /* the number of key in bits */
	int read_flag_shift;
	int burn_flag_shift;
	int public;
	int reserve[3];
};

#if defined(CONFIG_ARCH_SUN8IW6)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128, -1,      2,       1,     {0} },
{EFUSE_OEM_NAME,         0x10,  32,  -1,      -1,      1,     {0} },
{EFUSE_NV1_NAME,	 0x14,	32,  -1,      18,      0,     {0} },
{EFUSE_NV2_NAME,	 0x18,	224, -1,      19,      0,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x34,	64,  -1,      -1,      1,     {0} },
{EFUSE_RENEW_NAME,	 0x3C,	64,  -1,      -1,      0,     {0} },
{EFUSE_IN_NAME,          0x44,  256, 13,      2,       0,     {0} },
{EFUSE_ROTPK_NAME,	 0x64,	256, 14,      3,       0,     {0} },
{EFUSE_SSK_NAME,	 0x84,	128, 15,      4,       0,     {0} },
{EFUSE_RSSK_NAME,	 0x94,	256, 16,      5,       0,     {0} },
{EFUSE_HDCP_HASH_NAME,	 0xB4,	128, -1,      6,       0,     {0} },
{EFUSE_EK_HASH_NAME,	 0xC4,	128, -1,      7,       0,     {0} },
{EFUSE_RESERVED_NAME,	 0xD4,	256, 17,      8,       0,     {0} },
{"",                     0,     0,   0,       0,       0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0xFC,  32,  -1,      -1,      1,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0xFC,  32,  -1,      -1,      1,     {0} };

#elif defined(CONFIG_ARCH_SUN8IW7)
static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,	 0x0,	128, -1,       -1,       1,     {0} },
{EFUSE_OEM_NAME,	 0x10,	32,  -1,       -1,       1,     {0} },
{EFUSE_NV1_NAME,	 0x14,	32,  -1,       -1,       0,     {0} },
{EFUSE_NV2_NAME,	 0x18,	64,  -1,       -1,       0,     {0} },
{EFUSE_RSAKEY_HASH_NAME, 0x20,	160, -1,       -1,       0,     {0} },
{EFUSE_THM_SENSOR_NAME,	 0x34,	64,  -1,       8,        1,     {0} },
{EFUSE_RENEW_NAME,	 0x3c,	64,  -1,       -1,      -1,     {0} },
{EFUSE_IN_NAME,		 0x44,	192, 17,       9,        0,     {0} },
{EFUSE_OPT_ID_NAME,	 0x5c,	32,  18,       10,       0,     {0} },
{EFUSE_ID_NAME,		 0x60,	32,  19,       11,       0,     {0} },
{EFUSE_ROTPK_NAME,	 0x64,	256, 14,       3,        0,     {0} },
{EFUSE_SSK_NAME,	 0x84,	128, 15,       4,        0,     {0} },
{EFUSE_RSSK_NAME,	 0x94,	256, 16,       5,        0,     {0} },
{EFUSE_HDCP_HASH_NAME,	 0xb4,	128, -1,       6,        0,     {0} },
{EFUSE_EK_HASH_NAME,	 0xc4,	128, -1,       7,        0,     {0} },
{EFUSE_SN_NAME,		 0xd4,	192, 20,       8,       12,     {0} },
{EFUSE_BACKUP_KEY_NAME,	 0xec,	64,  21,       22,       0,     {0} },
{EFUSE_JTAG_SECU_NAME,	 0xf4,	32,  -1,       -1,       0,     {0} },
{EFUSE_JTAG_ATTR_NAME,	 0xf8,	32,  -1,       -1,       0,     {0} },
{EFUSE_CHIP_CONF_NAME,	 0xfC,	32,  -1,       -1,       0,     {0} },
{"",			 0,	0,    0,        0,       0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0xF8,   32,   -1,      9,      1,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0xF8,   32,   -1,      9,      1,     {0} };

#elif defined(CONFIG_ARCH_SUN8IW11)

#define EFUSE_IS_PUBLIC

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128, -1,      -1,      1,     {0} },
{EFUSE_IN_NAME,          0x10,  256, 23,      11,      0,     {0} },
{EFUSE_SSK_NAME,         0x30,  128, 22,      10,      0,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x40,  32,  -1,      -1,      1,     {0} },
{EFUSE_FT_ZONE_NAME,     0x44,  64,  -1,      -1,      1,     {0} },
{EFUSE_TV_OUT_NAME,      0x4C,  128, -1,      -1,      0,     {0} },
{EFUSE_RSSK_NAME,        0x5C,  256, 20,      8,       0,     {0} },
{EFUSE_HDCP_HASH_NAME,   0x7C,  128, -1,      9,       0,     {0} },
{EFUSE_RESERVED_NAME,    0x90,  896, -1,      -1,      0,     {0} },
{"",                     0,     0,   0,       0,       0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0x8C,   32,  -1,      -1,      1,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0x8C,   32,  -1,      -1,      1,     {0} };

#elif defined(CONFIG_ARCH_SUN8IW12)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,	 0x0,	128, 16,       0,       1,     {0} },
{EFUSE_BROM_CONF_NAME,	 0x10,	16,  17,       1,       1,     {0} },
{EFUSE_BROM_TRY_NAME,	 0x12,	16,  17,       1,       1,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,  96,  18,       2,       1,     {0} },
{EFUSE_FT_ZONE_NAME,	 0x20,	128, 19,       3,       1,     {0} },
{EFUSE_ROTPK_NAME,	 0x30,	256, 20,       4,       0,     {0} },
{EFUSE_NV1_NAME,	 0x50,	32,  21,       5,       0,     {0} },
{EFUSE_TVE_NAME,	 0x54,	32,  22,       6,       0,     {0} },
{EFUSE_ANTI_BLUSH_NAME,  0x58,  32,  23,       7,       0,     {0} },
{EFUSE_RESERVED_NAME,	 0x5C,	768, 24,       8,       0,     {0} },
{"",			 0,	0,   0,        0,       0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0xBC,   32,   25,      9,      1,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0xBC,   32,   25,      9,      1,     {0} };

#elif defined(CONFIG_ARCH_SUN8IW15)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128,  0,      0,      1,     {0} },
{EFUSE_BROM_CONF_NAME,   0x10,  16,   1,      1,      1,     {0} },
{EFUSE_BROM_TRY_NAME,    0x12,  16,   1,      1,      1,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,  64,   2,      2,      1,     {0} },
{EFUSE_FT_ZONE_NAME,     0x1C,  128,  3,      3,      1,     {0} },
{EFUSE_OEM_NAME,         0x2C,  160,  4,      4,      1,     {0} },
{"",                     0,     0,    0,      0,      0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0x43,   32,   6,      6,      0,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0x40,   32,   5,      5,      0,     {0} };

#elif defined(CONFIG_ARCH_SUN8IW16)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,	 0x0,	128, 16,       0,       0,     {0} },
{EFUSE_BROM_CONF_NAME,	 0x10,	16,  17,       1,       0,     {0} },
{EFUSE_BROM_TRY_NAME,	 0x12,	16,  17,       1,       0,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,	96,  18,       2,       0,     {0} },
{EFUSE_FT_ZONE_NAME,	 0x20,	128, 19,       3,       0,     {0} },
{EFUSE_ROTPK_NAME,	 0x30,	256, 20,       4,       0,     {0} },
{EFUSE_NV1_NAME,	 0x50,	32,  21,       5,       0,     {0} },
{EFUSE_TVE_NAME,	 0x54,	32,  22,       6,       0,     {0} },
{EFUSE_ANTI_BLUSH_NAME,  0x58,	32,  23,       7,       0,     {0} },
{EFUSE_GAMMA_NAME,	 0x5C,	64,  24,       8,       0,     {0} },
{EFUSE_RESERVED_NAME,	 0x64,	736, 24,       8,       0,     {0} },
{EFUSE_RESERVED2_NAME,	 0xC0,	512, 26,       10,      0,     {0} },
{"",			 0,	0,   0,        0,       0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0xBC,   32,   25,      9,      1,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0xBC,   32,   25,      9,      1,     {0} };

#elif defined(CONFIG_ARCH_SUN8IW19)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,	 0x0,	128, 16,       0,       0,     {0} },
{EFUSE_BROM_CONF_NAME,	 0x10,	16,  17,       1,       0,     {0} },
{EFUSE_BROM_TRY_NAME,	 0x12,	16,  17,       1,       0,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,	64,  18,       2,       0,     {0} },
{EFUSE_AUDIO_BIAS_NAME,  0x1C,	8,   18,       2,       0,     {0} },
{EFUSE_LDOA_NAME,        0x1D,	8,   18,       2,       0,     {0} },
{EFUSE_LDOB_NAME,        0x1E,	8,   18,       2,       0,     {0} },
{EFUSE_DDR_CFG_NAME,     0x1F,	8,   18,       2,       0,     {0} },
{EFUSE_FT_ZONE_NAME,	 0x20,	128, 19,       3,       0,     {0} },
{EFUSE_ROTPK_NAME,	 0x30,	256, 20,       4,       0,     {0} },
{EFUSE_NV1_NAME,	 0x50,	32,  21,       5,       0,     {0} },
{EFUSE_PSENSOR_NAME,	 0x54,	32,  22,       6,       0,     {0} },
{EFUSE_ANTI_BLUSH_NAME,  0x58,	32,  23,       7,       0,     {0} },
{EFUSE_RESERVED_NAME,	 0x5C,	256, 24,       8,       0,     {0} },
{"",			 0,	0,   0,        0,       0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0x7C,   32,   25,      9,      1,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0x7C,   32,   25,      9,      1,     {0} };

#elif defined(CONFIG_ARCH_SUN8IW18)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128,  0,      0,      1,     {0} },
{EFUSE_BROM_CONF_NAME,   0x10,  16,   1,      1,      1,     {0} },
{EFUSE_BROM_TRY_NAME,    0x12,  16,   1,      1,      1,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,  64,   2,      2,      1,     {0} },
{EFUSE_FT_ZONE_NAME,     0x1C,  128,  3,      3,      1,     {0} },
{EFUSE_OEM_NAME,         0x2C,  32,   4,      4,      1,     {0} },
{"",                     0,     0,    0,      0,      0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0x34,   32,   6,      6,      0,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0x30,   32,   5,      5,      0,     {0} };
#elif defined(CONFIG_ARCH_SUN8IW17)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128,  0,      0,      1,     {0} },
{EFUSE_BROM_CONF_NAME,   0x10,  16,   1,      1,      1,     {0} },
{EFUSE_BROM_TRY_NAME,    0x12,  16,   1,      1,      1,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,  96,   2,      2,      1,     {0} },
{EFUSE_FT_ZONE_NAME,     0x20,  128,  3,      3,      1,     {0} },
{EFUSE_OEM_NAME,         0x30,  128,  4,      4,      1,     {0} },
{"",                     0,     0,    0,      0,      0,     {0} },
};

static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0x40,  32,  5,       5,       0,     {0} };
static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0x44,  32,  6,       6,       0,     {0} };

#elif defined(CONFIG_ARCH_SUN50IW1) || defined(CONFIG_ARCH_SUN50IW2)
#define EFUSE_IS_PUBLIC
static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128, -1,      2,       1,     {0} },
{EFUSE_OEM_NAME,         0x10,  32,  -1,      -1,      1,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x34,  64,  -1,      -1,      1,     {0} },
{"",                     0,     0,   0,       0,       0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0xFC,  32,  -1,      -1,      1,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0xFC,  32,  -1,      -1,      1,     {0} };

#elif defined(CONFIG_ARCH_SUN50IW3) || defined(CONFIG_ARCH_SUN50IW6)
#define EFUSE_IS_PUBLIC
#define EFUSE_VERDOR_ID_OFFSET (0x32)
static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128, 0,       0,       1,     {0} },
{EFUSE_BROM_CONF_NAME,   0x10,  16,  1,       1,       1,     {0} },
{EFUSE_BROM_TRY_NAME,    0x12,  16,  1,       1,       1,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,  64,  2,       2,       1,     {0} },
{EFUSE_FT_ZONE_NAME,     0x1C,  128, 3,       3,       1,     {0} },
{EFUSE_OEM_NAME,         0x2C,  160, 4,       4,       1,     {0} },
{"",                     0,     0,   0,       0,       0,     {0} }
};

static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0x40,  32,  5,       5,       0,     {0} };
static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0x44,  32,  6,       6,       0,     {0} };

#elif defined(CONFIG_ARCH_SUN50IW9)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128,  0,      0,      1,     {0} },
{EFUSE_BROM_CONF_NAME,   0x10,  16,   1,      1,      1,     {0} },
{EFUSE_BROM_TRY_NAME,    0x12,  16,   1,      1,      1,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,  64,   2,      2,      1,     {0} },
{EFUSE_FT_ZONE_NAME,     0x1C,  128,  3,      3,      1,     {0} },
{EFUSE_OEM_NAME,         0x2C,  160,  4,      4,      1,     {0} },
{"",                     0,     0,    0,      0,      0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0x44,   32,   6,      6,      0,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0x40,   32,   5,      5,      0,     {0} };

#elif defined(CONFIG_ARCH_SUN50IW10)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128,  0,      0,      1,     {0} },
{EFUSE_BROM_CONF_NAME,   0x10,  16,   1,      1,      1,     {0} },
{EFUSE_BROM_TRY_NAME,    0x12,  16,   1,      1,      1,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,  64,   2,      2,      1,     {0} },
{EFUSE_FT_ZONE_NAME,     0x1C,  128,  3,      3,      1,     {0} },
{EFUSE_OEM_NAME,         0x2C,  160,  4,      4,      1,     {0} },
{"",                     0,     0,    0,      0,      0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0x44,   32,   6,      6,      0,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0x40,   32,   5,      5,      0,     {0} };

#elif defined(CONFIG_ARCH_SUN50IW11)

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128,  0,      0,      1,     {0} },
{EFUSE_BROM_CONF_NAME,   0x10,  16,   1,      1,      1,     {0} },
{EFUSE_BROM_TRY_NAME,    0x12,  16,   1,      1,      1,     {0} },
{EFUSE_THM_SENSOR_NAME,  0x14,  32,   2,      2,      1,     {0} },
{EFUSE_FT_ZONE_NAME,     0x18,  96,   3,      3,      1,     {0} },
{EFUSE_OEM_NAME,         0x24,  32,   4,      4,      1,     {0} },
{"",                     0,     0,    0,      0,      0,     {0} },
};

static struct efuse_key_map key_map_rd_pro = {
EFUSE_RD_PROTECT_NAME,  0x2C,   32,   6,      6,      0,     {0} };
static struct efuse_key_map key_map_wr_pro = {
EFUSE_WR_PROTECT_NAME,  0x28,   32,   5,      5,      0,     {0} };

#else

#define EFUSE_IS_PUBLIC
#define EFUSE_HAS_NO_RW_PROTECT

static struct efuse_key_map key_maps[] = {
/* Name                  Offset Size ReadFlag BurnFlag Public Reserve */
{EFUSE_CHIPID_NAME,      0x0,   128, -1,      -1,      1,     {0} },
{"",                     0,     0,   0,       0,       0,     {0} }
};

#endif

#endif /* end of __SUNXI_SID_EFUSE_H__ */

