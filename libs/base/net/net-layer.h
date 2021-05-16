#pragma once

#include <base/eth/eth.h>
#include <base/net/vlan.h>
#include <base/net/ip.h>

bool decode_net_layer(eth_proto proto, uint8_t *pkt, LayerNode *pnode);