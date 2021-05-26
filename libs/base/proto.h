#pragma once

#include "debug.h"

enum TRANS_PROTO {
    TRANS_ICMP = 1,
    TRANS_IGMP = 2,
    TRANS_TCP = 6,
    TRANS_UDP = 17,
    TRANS_OSPF = 89,
};

enum Port_for_Proto {
    Port_FtpData = 20,
    Port_Ftp = 21,
    Port_Ssh = 22,
    Port_Telent = 23,
    Port_Smtp = 25,
    Port_Dns = 53,
    Port_Tftp = 69,
    Port_Http = 80,
    Port_Pop2 = 109,
    Port_Pop3 = 110,

    Port_Https = 443,

    Port_Mysql = 3306,
};

enum Layer {
    Layer_TOP,
    Layer_LINK,
    Layer_NET,
    Layer_TRANS,
    Layer_APP,
};

struct LayerNode {
    Layer layer;
    uint16_t proto;
    void *pkt;
    void *ext;
    LayerNode *next;
    LayerNode *prev;
    LayerNode(Layer layer, uint16_t proto, void *pkt, LayerNode *prev=nullptr, void *ext=nullptr)
        : layer(layer), proto(proto), pkt(pkt), prev(prev), next(nullptr), ext(ext) {
    }
    LayerNode(void *pkt)
        : layer(Layer_TOP), pkt(pkt), prev(nullptr), next(nullptr), ext(nullptr) {
    }
    ~LayerNode() {
    }
    void printInfo();
};
