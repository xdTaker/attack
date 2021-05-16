#include <base/net/net-layer.h>

bool decode_net_layer(eth_proto proto, uint8_t *pkt, LayerNode *pnode) {
    switch (proto) {
        case VLAN:
            decode_vlan(pkt, pnode);
            break;
        case IPv4:
            decode_IPv4(pkt, pnode);
            break;
        default:
            print_hex<uint16_t>(proto);
    }
    return true;
}