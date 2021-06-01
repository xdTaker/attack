#include "eth.h"
#include <proto/net/net-layer.h>

void decode_ether(uint8_t* pkt, LayerNode *pnode) {
    EthII_hdr *hdr = (EthII_hdr*)pkt;
    // hdr->printInfo();
    uint8_t *next = pkt + ETHII_HDR_LEN;
    pnode->next = new LayerNode(Layer_LINK, ETHII, pkt, pnode);
    decode_net_layer(hdr->type, next, pnode->next);
}