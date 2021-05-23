#include "eth.h"
#include <base/net/net-layer.h>

void decode_ether(uint8_t* pkt, LayerNode *pnode) {
    EthII_hdr *hdr = (EthII_hdr*)pkt;
    hdr->printInfo();
    // print_hex(pkt, ETHII_HDR_LEN);
    uint8_t *next = pkt + ETHII_HDR_LEN;
    pnode->next = new LayerNode(Layer_ETH, ETHII, pkt, pnode);
    decode_net_layer(hdr->type, next, pnode->next);
}