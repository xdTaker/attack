#pragma once

#include <base/common.h>

enum Eth_Type {
    ETH_VLAN,
    ETHII,
    ETH802_2,
    ETH802_3,
    ETHSNAP,
};

enum ForEth_Proto {
    IPv4 = 0x0008,
    IPv6 = 0xDD86,
    ARP = 0x0608,
    RARP = 0x3580,
    VLAN = 0x0081,
};

typedef uint16_t eth_proto;

#pragma pack(push)
#pragma pack(1)
struct EthII_hdr {
    uint8_t dstMac[6];
    uint8_t srcMac[6];
    uint16_t type;
    void printInfo() {
        printf("ETHII info:\n");
        printf("  src mac: %s\n", getstr_hex(srcMac, 6).c_str());
        printf("  dst mac: %s\n", getstr_hex(dstMac, 6).c_str());
        printf("  proto: %s\n", getstr_hex<uint16_t>(type).c_str());
    }
};
#define ETHII_HDR_LEN 14

struct Eth802_2_hdr {
    uint8_t dstMac[6];
    uint8_t srcMac[6];
    uint16_t len;
    uint8_t DSAP;   // Destination Service Access Point
    uint8_t SSAP;   // Source Service Access Point
    uint8_t CTL;    // 无连接或面向连接的LLC
};

struct Eth802_3_hdr {
    uint8_t dstMac[6];
    uint8_t srcMac[6];
    uint16_t len;
};

struct EthSNAP_hdr {
    uint8_t dstMac[6];
    uint8_t srcMac[6];
    uint16_t len;
    uint8_t DSAP;   // Destination Service Access Point
    uint8_t SSAP;   // Source Service Access Point
    uint8_t CTL;
    uint8_t code[3];    // 厂商代码
    uint16_t type;      // 协议类型
};
#pragma pack(pop)

void decode_ether(uint8_t* pkt, LayerNode *pnode);
int encode_ether(uint8_t *pkt, eth_proto proto, uint8_t *srcMac, uint8_t *dstMac);