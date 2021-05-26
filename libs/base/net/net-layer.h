#pragma once

#include <base/link/eth.h>
#include <base/link/vlan.h>
#include <base/net/ip.h>

bool decode_net_layer(eth_proto proto, uint8_t *pkt, LayerNode *pnode);