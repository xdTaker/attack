#pragma once

#include <proto/link/eth.h>
#include <proto/link/vlan.h>
#include <proto/net/ip.h>

bool decode_net_layer(eth_proto proto, uint8_t *pkt, LayerNode *pnode);