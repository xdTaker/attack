#include <proto/net/net-layer.h>

bool decode_net_layer(eth_proto proto, uint8_t *pkt, LayerNode *pnode) {
    bool ret;
    switch (proto) {
        case VLAN:
            ret = decode_vlan(pkt, pnode);
            break;
        case IPv4:
            ret = decode_IPv4(pkt, pnode);
            break;
        default:
            ret = false;
            print_hex<uint16_t>(proto);
    }
    return ret;
}