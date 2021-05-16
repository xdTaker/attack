#pragma once

#include <base/common.h>
#include <stdint.h>
#include <stdio.h>

#define PCAP_DEBUG  1
#define PCAP_PKT_MSG 0

#define PCAP_MAGIC                  0xa1b2c3d4
#define PCAP_SWAPPED_MAGIC          0xd4c3b2a1
#define PCAP_MODIFIED_MAGIC         0xa1b2cd34
#define PCAP_SWAPPED_MODIFIED_MAGIC 0x34cdb2a1
#define PCAP_IXIAHW_MAGIC           0x1c0001ac
#define PCAP_SWAPPED_IXIAHW_MAGIC   0xac01001c
#define PCAP_IXIASW_MAGIC           0x1c0001ab
#define PCAP_SWAPPED_IXIASW_MAGIC   0xab01001c
#define PCAP_NSEC_MAGIC             0xa1b23c4d
#define PCAP_SWAPPED_NSEC_MAGIC     0x4d3cb2a1

struct pcap_file_hdr {
    uint32_t magic;
    uint16_t version_major;
    uint16_t version_minor;
    int32_t  thiszone;
    uint32_t sigfigs;
    uint32_t snaplen;
    uint32_t network;
};

struct pcaprec_hdr {
    uint32_t ts_sec;
    uint32_t ts_usec;
    uint32_t incl_len;
    uint32_t orig_len;
    void printInfo();
};

// Alexey's patched version
struct pcaprec_modified_hdr {
    pcaprec_hdr hdr;
    uint32_t    ifindex;    // 网卡id
    uint16_t    protocol;   // Ethernet packet type
    uint8_t     pkt_type;   // broadcast/multicast/etc.
    uint8_t     pad;        // 填充
};

// Alexey's patched version in its ss990915 incarnation, show up in SUSE Linux 6.3
struct pcaprec_ss990915_hdr {
    pcaprec_hdr hdr;
    uint32_t    ifindex;    // 网卡id
    uint16_t    protocol;   // Ethernet packet type
    uint8_t     pkt_type;   // broadcast/multicast/etc.
    uint8_t     cpu1, cpu2; // SMP debugging gunk?
    uint8_t     pad[3];
};

struct pcaprec_nokia_hdr {
    pcaprec_hdr hdr;
    uint8_t     stuff[4];   // mysterious stuff
};

#define MAX_PCAP_SIZE 65536

struct wtap {
    pcap_file_hdr   file_hdr;
    char            buf[MAX_PCAP_SIZE];
    FILE            *fp;
    bool            byte_swapped;
    int             skip_size;
};

enum open_pcap_code {
    OK = 0,
    OPEN_FILE_FAIL,
    PCAP_FILE_HDR_ERR,
    READ_FILE_FAIL,
    NOT_SUPPORTED,
};

open_pcap_code pcap_open(const char *file, wtap *wth);
int pcap_read(wtap *wth, char *buf);
void pcap_close(wtap *wth);