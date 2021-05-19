#pragma once

#include <base/common.h>

enum Net_Type {
    Net_IPv4,
    Net_IPv6,
    Net_ICMP,
    Net_IGMP
};

enum ForIP_Proto {
    ICMP = 1,
    IGMP = 2,
    TCP = 6,
    UDP = 17,
};

struct IP4hdr{
    uint8_t hdrLen: 4;  // 4字节为单位
    uint8_t version: 4;
    /* TOS: type of service */
    uint8_t unused: 1;
    uint8_t minCost: 1;
    uint8_t maxReliable: 1;
    uint8_t maxThruput: 1;
    uint8_t minDelay: 1;
    uint8_t priority: 3; // not used
    uint16_t totalLen;

    uint16_t identity;
    uint16_t segOff: 13;    // 片偏移，8字节为单位
    uint16_t MF: 1; // 1: 后面还有分片
    uint16_t DF: 1; // 0: 能够分片
    uint16_t UNUSED: 1;

    uint8_t TTL;    // 生命周期
    uint8_t upProto;    // 上一层协议，1:ICMP 2:IGMP 6:TCP 17:UDP 89:OSPF
    uint16_t checksum;
    
    uint32_t srcAddr;
    uint32_t dstAddr;
    uint8_t option[0];
    
    IP4hdr(uint8_t len=5);
    void setProto(TRANS_PROTO proto);
    void setSrcAddr(uint32_t addr);
    void setDstAddr(uint32_t addr);
    static string IPint2str(uint32_t IPaddr); 
    static uint32_t IPstr2int(const char *IPstr);
    uint16_t getTotalLen() {return swap_bytes<uint16_t>(totalLen);}
    uint16_t getHdrLen() {return hdrLen * 4;}
    void setCheck();
    void subTTL();
    bool check();
    void setTcpPsdHdr();
    void printInfo();
};
#define IP4_HDR_LEN 20

bool decode_IPv4(uint8_t *pkt, LayerNode *pnode);