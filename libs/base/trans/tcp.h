#pragma once

#include <base/net/ip.h>

struct Psd_TCPhdr {
    uint32_t srcAddr;
    uint32_t dstAddr;
    char mbz; //强制置空
    char ptcl; //协议类型
    unsigned short tcpl; //TCP长度
};

struct TCPhdr {
    uint16_t srcPort;
    uint16_t dstPort;
    uint32_t seqNum;
    uint32_t ackNum;
    uint16_t reserved: 4;
    uint16_t offset: 4;   // 报文长度，单位4字节
    uint16_t reserved2: 2;
    uint16_t URG: 1;  // 紧急指针是否有效
    uint16_t ACK: 1;  // 确认号是否有效（确认报文段）
    uint16_t PSH: 1;  // 提示应用程序立即读取（比如多段的最后一个报文）
    uint16_t RST: 1;  // 要求对方重新建立连接（复位报文段）
    uint16_t SYN: 1;  // 请求建立一个连接（同步报文段）
    uint16_t FIN: 1;  // 通知关闭（结束报文段）
    uint16_t window;  // 接收窗口，告诉对方本端tcp接收缓冲区还能容纳多少数据，单位B
    uint16_t checksum;  // 伪首部+tcp首部+tcp数据
    uint16_t urgent;  // 紧急偏移
    uint8_t  options[0];

    TCPhdr(uint16_t len=5);
    void setSPort(uint16_t port);
    void setDPort(uint16_t port);
    uint16_t getSPort() {return swap_bytes<uint16_t>(srcPort);}
    uint16_t getDPort() {return swap_bytes<uint16_t>(dstPort);}
    uint16_t getHdrLen() {return offset * 4;}
    void setCheck(void *iphdr);
    bool check();
    void printInfo();
};
#define TCP_HDR_LEN 20

void decode_tcp(uint8_t *pkt, LayerNode *pnode);
uint32_t encode_tcp(uint8_t *pkt, )