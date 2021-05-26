#pragma once

#include <base/common.h>

struct vlan_hdr {
    uint16_t prior: 3;
    uint16_t DEI: 1;
    uint16_t vlan_ID: 12;
    uint16_t encap_proto;
};
#define VLAN_HDR_LEN 4

bool decode_vlan(uint8_t *pkt, LayerNode *pnode);