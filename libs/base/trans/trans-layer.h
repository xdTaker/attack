#pragma once
#include <base/common.h>
#include <base/net/ip.h>

void decode_trans_layer(TRANS_PROTO proto, uint8_t *pkt, LayerNode *pnode);
ForEth_Proto set_psd_hdr(const void *ip_hdr, void *phdr);

/* 伪IP头 */
struct PsdIP4Hdr {
    uint32_t srcAddr;
    uint32_t dstAddr;
    uint16_t ptcl;       // 协议类型
    uint16_t plen;      // TCP/UDP长度
    void set(uint32_t srcAddr, uint32_t dstAddr, uint8_t ptcl, uint16_t plen) {
        this->srcAddr = srcAddr;
        this->dstAddr = dstAddr;
        this->ptcl = swap_bytes<uint16_t>(ptcl);
        this->plen = swap_bytes<uint16_t>(plen);
    }
    uint16_t getLen() {
        return swap_bytes<uint16_t>(plen);
    }
};
#define IP4_PHDR_LEN 12

struct PsdIP6Hdr {
    uint32_t srcAddr[4];
    uint32_t dstAddr[4];
    uint32_t plen;      // TCP/UDP长度
    uint8_t mbz[3];     // 强制置空
    uint8_t ptcl;       // 协议类型
};
#define IP6_PHDR_LEN 16
