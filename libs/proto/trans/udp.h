#pragma once

#include <proto/proto.h>

#define UDP_HDR_LEN 8

struct UDPhdr{
    uint16_t srcPort;
    uint16_t dstPort;
    uint16_t length;    //udp报文总长度(udp头+数据)，最小为8
    uint16_t checkSum;  //校验和
    uint16_t getSPort(){return swap_bytes<uint16_t>(srcPort);}
    uint16_t getDPort(){return swap_bytes<uint16_t>(dstPort);}
    uint16_t getLength(){return swap_bytes<uint16_t>(length);}
    uint16_t getCheckSum(){return swap_bytes<uint16_t>(checkSum);}
    void printInfo();
};

bool decode_udp(uint8_t *pkt, LayerNode *pnode);



