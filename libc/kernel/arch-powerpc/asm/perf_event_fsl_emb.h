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
#include <linux/types.h>
#include <asm/hw_irq.h>

#define MAX_HWEVENTS 4

#define FSL_EMB_EVENT_VALID 1
#define FSL_EMB_EVENT_RESTRICTED 2

#define FSL_EMB_EVENT_THRESHMUL 0x0000070000000000ULL
#define FSL_EMB_EVENT_THRESH 0x0000003f00000000ULL

struct fsl_emb_pmu {
 const char *name;
 int n_counter;

 int n_restricted;

 u64 (*xlate_event)(u64 event_id);

 int n_generic;
 int *generic_events;
 int (*cache_events)[PERF_COUNT_HW_CACHE_MAX]
 [PERF_COUNT_HW_CACHE_OP_MAX]
 [PERF_COUNT_HW_CACHE_RESULT_MAX];
};

