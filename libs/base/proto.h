#pragma once

#include "debug.h"

enum TRANS_PROTO{
    TRANS_ICMP = 1,
    TRANS_IGMP = 2,
    TRANS_TCP = 6,
    TRANS_UDP = 17,
    TRANS_OSPF = 89,
};


enum Layer {
    Layer_TOP,
    Layer_ETH,
    Layer_IP,
    Layer_TRANS,
    Layer_APP,
};

struct LayerNode {
    Layer layer;
    uint16_t proto;
    void *pkt;
    LayerNode *next;
    LayerNode *prev;
    LayerNode(Layer layer, uint16_t proto, void *pkt, LayerNode *prev=nullptr)
        : layer(layer), proto(proto), pkt(pkt), prev(prev), next(nullptr) {
    }
    LayerNode(void *pkt)
        : layer(Layer_TOP), pkt(pkt), prev(nullptr), next(nullptr) {
    }
    ~LayerNode() {
    }
};
