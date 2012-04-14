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
#ifndef _ASM_POWERPC_PS3_H
#define _ASM_POWERPC_PS3_H

#include <linux/init.h>
#include <linux/types.h>
#include <linux/device.h>
#include "cell-pmu.h"

union ps3_firmware_version {
 u64 raw;
 struct {
 u16 pad;
 u16 major;
 u16 minor;
 u16 rev;
 };
};

enum ps3_param_av_multi_out {
 PS3_PARAM_AV_MULTI_OUT_NTSC = 0,
 PS3_PARAM_AV_MULTI_OUT_PAL_RGB = 1,
 PS3_PARAM_AV_MULTI_OUT_PAL_YCBCR = 2,
 PS3_PARAM_AV_MULTI_OUT_SECAM = 3,
};

enum ps3_param_av_multi_out ps3_os_area_get_av_multi_out(void);

struct ps3_os_area_flash_ops {
 ssize_t (*read)(void *buf, size_t count, loff_t pos);
 ssize_t (*write)(const void *buf, size_t count, loff_t pos);
};

enum ps3_dma_page_size {
 PS3_DMA_4K = 12U,
 PS3_DMA_64K = 16U,
 PS3_DMA_1M = 20U,
 PS3_DMA_16M = 24U,
};

enum ps3_dma_region_type {
 PS3_DMA_OTHER = 0,
 PS3_DMA_INTERNAL = 2,
};

struct ps3_dma_region_ops;

struct ps3_dma_region {
 struct ps3_system_bus_device *dev;

 const struct ps3_dma_region_ops *region_ops;
 unsigned char ioid;
 enum ps3_dma_page_size page_size;
 enum ps3_dma_region_type region_type;
 unsigned long len;
 unsigned long offset;

 unsigned long bus_addr;
 struct {
 spinlock_t lock;
 struct list_head head;
 } chunk_list;
};

struct ps3_dma_region_ops {
 int (*create)(struct ps3_dma_region *);
 int (*free)(struct ps3_dma_region *);
 int (*map)(struct ps3_dma_region *,
 unsigned long virt_addr,
 unsigned long len,
 dma_addr_t *bus_addr,
 u64 iopte_pp);
 int (*unmap)(struct ps3_dma_region *,
 dma_addr_t bus_addr,
 unsigned long len);
};

struct ps3_system_bus_device;

enum ps3_mmio_page_size {
 PS3_MMIO_4K = 12U,
 PS3_MMIO_64K = 16U
};

struct ps3_mmio_region_ops;

struct ps3_mmio_region {
 struct ps3_system_bus_device *dev;
 const struct ps3_mmio_region_ops *mmio_ops;
 unsigned long bus_addr;
 unsigned long len;
 enum ps3_mmio_page_size page_size;
 unsigned long lpar_addr;
};

struct ps3_mmio_region_ops {
 int (*create)(struct ps3_mmio_region *);
 int (*free)(struct ps3_mmio_region *);
};

enum ps3_cpu_binding {
 PS3_BINDING_CPU_ANY = -1,
 PS3_BINDING_CPU_0 = 0,
 PS3_BINDING_CPU_1 = 1,
};

enum lv1_result {
 LV1_SUCCESS = 0,

 LV1_RESOURCE_SHORTAGE = -2,
 LV1_NO_PRIVILEGE = -3,
 LV1_DENIED_BY_POLICY = -4,
 LV1_ACCESS_VIOLATION = -5,
 LV1_NO_ENTRY = -6,
 LV1_DUPLICATE_ENTRY = -7,
 LV1_TYPE_MISMATCH = -8,
 LV1_BUSY = -9,
 LV1_EMPTY = -10,
 LV1_WRONG_STATE = -11,

 LV1_NO_MATCH = -13,
 LV1_ALREADY_CONNECTED = -14,
 LV1_UNSUPPORTED_PARAMETER_VALUE = -15,
 LV1_CONDITION_NOT_SATISFIED = -16,
 LV1_ILLEGAL_PARAMETER_VALUE = -17,
 LV1_BAD_OPTION = -18,
 LV1_IMPLEMENTATION_LIMITATION = -19,
 LV1_NOT_IMPLEMENTED = -20,
 LV1_INVALID_CLASS_ID = -21,
 LV1_CONSTRAINT_NOT_SATISFIED = -22,
 LV1_ALIGNMENT_ERROR = -23,
 LV1_HARDWARE_ERROR = -24,
 LV1_INVALID_DATA_FORMAT = -25,
 LV1_INVALID_OPERATION = -26,
 LV1_INTERNAL_ERROR = -32768,
};

#ifdef DEBUG
#else
#endif

enum ps3_match_sub_id {
 PS3_MATCH_SUB_ID_GPU_FB = 1,
 PS3_MATCH_SUB_ID_GPU_RAMDISK = 2,
};

#define PS3_MODULE_ALIAS_EHCI "ps3:1:0"
#define PS3_MODULE_ALIAS_OHCI "ps3:2:0"
#define PS3_MODULE_ALIAS_GELIC "ps3:3:0"
#define PS3_MODULE_ALIAS_AV_SETTINGS "ps3:4:0"
#define PS3_MODULE_ALIAS_SYSTEM_MANAGER "ps3:5:0"
#define PS3_MODULE_ALIAS_STOR_DISK "ps3:6:0"
#define PS3_MODULE_ALIAS_STOR_ROM "ps3:7:0"
#define PS3_MODULE_ALIAS_STOR_FLASH "ps3:8:0"
#define PS3_MODULE_ALIAS_SOUND "ps3:9:0"
#define PS3_MODULE_ALIAS_GPU_FB "ps3:10:1"
#define PS3_MODULE_ALIAS_GPU_RAMDISK "ps3:10:2"
#define PS3_MODULE_ALIAS_LPM "ps3:11:0"

enum ps3_system_bus_device_type {
 PS3_DEVICE_TYPE_IOC0 = 1,
 PS3_DEVICE_TYPE_SB,
 PS3_DEVICE_TYPE_VUART,
 PS3_DEVICE_TYPE_LPM,
};

struct ps3_system_bus_device {
 enum ps3_match_id match_id;
 enum ps3_match_sub_id match_sub_id;
 enum ps3_system_bus_device_type dev_type;

 u64 bus_id;
 u64 dev_id;
 unsigned int interrupt_id;
 struct ps3_dma_region *d_region;
 struct ps3_mmio_region *m_region;
 unsigned int port_number;
 struct {
 u64 node_id;
 u64 pu_id;
 u64 rights;
 } lpm;

 struct device core;
 void *driver_priv;
};

struct ps3_system_bus_driver {
 enum ps3_match_id match_id;
 enum ps3_match_sub_id match_sub_id;
 struct device_driver core;
 int (*probe)(struct ps3_system_bus_device *);
 int (*remove)(struct ps3_system_bus_device *);
 int (*shutdown)(struct ps3_system_bus_device *);

};

struct ps3_sys_manager_ops {
 struct ps3_system_bus_device *dev;
 void (*power_off)(struct ps3_system_bus_device *dev);
 void (*restart)(struct ps3_system_bus_device *dev);
};

struct ps3_prealloc {
 const char *name;
 void *address;
 unsigned long size;
 unsigned long align;
};

enum ps3_lpm_rights {
 PS3_LPM_RIGHTS_USE_LPM = 0x001,
 PS3_LPM_RIGHTS_USE_TB = 0x100,
};

enum ps3_lpm_tb_type {
 PS3_LPM_TB_TYPE_NONE = 0,
 PS3_LPM_TB_TYPE_INTERNAL = 1,
};

#endif
