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
#ifndef _HVSI_H
#define _HVSI_H

#define VS_DATA_PACKET_HEADER 0xff
#define VS_CONTROL_PACKET_HEADER 0xfe
#define VS_QUERY_PACKET_HEADER 0xfd
#define VS_QUERY_RESPONSE_PACKET_HEADER 0xfc

#define VSV_SET_MODEM_CTL 1  
#define VSV_MODEM_CTL_UPDATE 2  
#define VSV_CLOSE_PROTOCOL 3

#define VSV_SEND_VERSION_NUMBER 1
#define VSV_SEND_MODEM_CTL_STATUS 2

#define HVSI_TSDTR 0x01
#define HVSI_TSCD 0x20

#define HVSI_MAX_OUTGOING_DATA 12
#define HVSI_VERSION 1

struct hvsi_header {
 uint8_t type;
 uint8_t len;
 uint16_t seqno;
} __attribute__((packed));

struct hvsi_data {
 struct hvsi_header hdr;
 uint8_t data[HVSI_MAX_OUTGOING_DATA];
} __attribute__((packed));

struct hvsi_control {
 struct hvsi_header hdr;
 uint16_t verb;

 uint32_t word;
 uint32_t mask;
} __attribute__((packed));

struct hvsi_query {
 struct hvsi_header hdr;
 uint16_t verb;
} __attribute__((packed));

struct hvsi_query_response {
 struct hvsi_header hdr;
 uint16_t verb;
 uint16_t query_seqno;
 union {
 uint8_t version;
 uint32_t mctrl_word;
 } u;
} __attribute__((packed));

#define HVSI_INBUF_SIZE 255
struct tty_struct;
struct hvsi_priv {
 unsigned int inbuf_len;
 unsigned char inbuf[HVSI_INBUF_SIZE];
 unsigned int inbuf_cur;
 unsigned int inbuf_pktlen;
 atomic_t seqno;
 unsigned int opened:1;
 unsigned int established:1;
 unsigned int is_console:1;
 unsigned int mctrl_update:1;
 unsigned short mctrl;
 struct tty_struct *tty;
 int (*get_chars)(uint32_t termno, char *buf, int count);
 int (*put_chars)(uint32_t termno, const char *buf, int count);
 uint32_t termno;
};

struct hvc_struct;

#endif
