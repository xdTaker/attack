#include "eth.h"
#include <proto/net/net-layer.h>

bool decode_ether(uint8_t* pkt, LayerNode *pnode) {
    EthII_hdr *hdr = (EthII_hdr*)pkt;
    // hdr->printInfo();
    uint8_t *next = pkt + ETHII_HDR_LEN;
    pnode->next = new LayerNode(Layer_LINK, ETHII, pkt, pnode);
    return decode_net_layer(hdr->type, next, pnode->next);
}