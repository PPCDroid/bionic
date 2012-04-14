/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef _SMU_H
#define _SMU_H

#include <linux/types.h>

#define SMU_CMD_PARTITION_COMMAND 0x3e
#define SMU_CMD_PARTITION_LATEST 0x01
#define SMU_CMD_PARTITION_BASE 0x02
#define SMU_CMD_PARTITION_UPDATE 0x03

#define SMU_CMD_FAN_COMMAND 0x4a

#define SMU_CMD_BATTERY_COMMAND 0x6f
#define SMU_CMD_GET_BATTERY_INFO 0x00

#define SMU_CMD_RTC_COMMAND 0x8e
#define SMU_CMD_RTC_SET_PWRUP_TIMER 0x00  
#define SMU_CMD_RTC_GET_PWRUP_TIMER 0x01  
#define SMU_CMD_RTC_STOP_PWRUP_TIMER 0x02
#define SMU_CMD_RTC_SET_PRAM_BYTE_ACC 0x20  
#define SMU_CMD_RTC_SET_PRAM_AUTOINC 0x21  
#define SMU_CMD_RTC_SET_PRAM_LO_BYTES 0x22  
#define SMU_CMD_RTC_SET_PRAM_HI_BYTES 0x23  
#define SMU_CMD_RTC_GET_PRAM_BYTE 0x28  
#define SMU_CMD_RTC_GET_PRAM_LO_BYTES 0x29  
#define SMU_CMD_RTC_GET_PRAM_HI_BYTES 0x2a  
#define SMU_CMD_RTC_SET_DATETIME 0x80  
#define SMU_CMD_RTC_GET_DATETIME 0x81  

#define SMU_CMD_I2C_COMMAND 0x9a

#define SMU_I2C_TRANSFER_SIMPLE 0x00
#define SMU_I2C_TRANSFER_STDSUB 0x01
#define SMU_I2C_TRANSFER_COMBINED 0x02

#define SMU_CMD_POWER_COMMAND 0xaa
#define SMU_CMD_POWER_RESTART "RESTART"
#define SMU_CMD_POWER_SHUTDOWN "SHUTDOWN"
#define SMU_CMD_POWER_VOLTAGE_SLEW "VSLEW"

#define SMU_CMD_READ_ADC 0xd8

#define SMU_CMD_MISC_df_COMMAND 0xdf

#define SMU_CMD_MISC_df_SET_DISPLAY_LIT 0x02

#define SMU_CMD_MISC_df_NMI_OPTION 0x04

#define SMU_CMD_MISC_df_DIMM_OFFSET 0x99

#define SMU_CMD_VERSION_COMMAND 0xea
#define SMU_VERSION_RUNNING 0x00
#define SMU_VERSION_BASE 0x01
#define SMU_VERSION_UPDATE 0x02

#define SMU_CMD_SWITCHES 0xdc

#define SMU_SWITCH_CASE_CLOSED 0x01
#define SMU_SWITCH_AC_POWER 0x04
#define SMU_SWITCH_POWER_SWITCH 0x08

#define SMU_CMD_MISC_ee_COMMAND 0xee
#define SMU_CMD_MISC_ee_GET_DATABLOCK_REC 0x02

#define SMU_CMD_MISC_ee_GET_WATTS 0x03

#define SMU_CMD_MISC_ee_LEDS_CTRL 0x04  
#define SMU_CMD_MISC_ee_GET_DATA 0x05  

#define SMU_CMD_POWER_EVENTS_COMMAND 0x8f

enum {
 SMU_PWR_GET_POWERUP_EVENTS = 0x00,
 SMU_PWR_SET_POWERUP_EVENTS = 0x01,
 SMU_PWR_CLR_POWERUP_EVENTS = 0x02,
 SMU_PWR_GET_WAKEUP_EVENTS = 0x03,
 SMU_PWR_SET_WAKEUP_EVENTS = 0x04,
 SMU_PWR_CLR_WAKEUP_EVENTS = 0x05,

 SMU_PWR_LAST_SHUTDOWN_CAUSE = 0x07,

 SMU_PWR_SERVER_ID = 0x08,
};

enum {
 SMU_PWR_WAKEUP_KEY = 0x01,
 SMU_PWR_WAKEUP_AC_INSERT = 0x02,
 SMU_PWR_WAKEUP_AC_CHANGE = 0x04,
 SMU_PWR_WAKEUP_LID_OPEN = 0x08,
 SMU_PWR_WAKEUP_RING = 0x10,
};

struct smu_sdbp_header {
 __u8 id;
 __u8 len;
 __u8 version;
 __u8 flags;
};

#define SMU_U16_MIX(x) le16_to_cpu(x)
#define SMU_U32_MIX(x) ((((x) & 0xff00ff00u) >> 8)|(((x) & 0x00ff00ffu) << 8))

#define SMU_SDB_FVT_ID 0x12

struct smu_sdbp_fvt {
 __u32 sysclk;
 __u8 pad;
 __u8 maxtemp;

 __u16 volts[3];
};

#define SMU_SDB_CPUVCP_ID 0x21

struct smu_sdbp_cpuvcp {
 __u16 volt_scale;
 __s16 volt_offset;
 __u16 curr_scale;
 __s16 curr_offset;
 __s32 power_quads[3];
};

#define SMU_SDB_CPUDIODE_ID 0x18

struct smu_sdbp_cpudiode {
 __u16 m_value;
 __s16 b_value;

};

#define SMU_SDB_SLOTSPOW_ID 0x78

struct smu_sdbp_slotspow {
 __u16 pow_scale;
 __s16 pow_offset;
};

#define SMU_SDB_SENSORTREE_ID 0x25

struct smu_sdbp_sensortree {
 __u8 model_id;
 __u8 unknown[3];
};

#define SMU_SDB_CPUPIDDATA_ID 0x17

struct smu_sdbp_cpupiddata {
 __u8 unknown1;
 __u8 target_temp_delta;
 __u8 unknown2;
 __u8 history_len;
 __s16 power_adj;
 __u16 max_power;
 __s32 gp,gr,gd;
};

#define SMU_SDB_DEBUG_SWITCHES_ID 0x05

struct smu_user_cmd_hdr
{
 __u32 cmdtype;
#define SMU_CMDTYPE_SMU 0  
#define SMU_CMDTYPE_WANTS_EVENTS 1  
#define SMU_CMDTYPE_GET_PARTITION 2  

 __u8 cmd;
 __u8 pad[3];
 __u32 data_len;
};

struct smu_user_reply_hdr
{
 __u32 status;
 __u32 reply_len;
};

#endif
