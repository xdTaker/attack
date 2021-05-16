#include <base/net/vlan.h>
#include <base/net/net-layer.h>
#include <base/eth/eth.h>

bool decode_vlan(uint8_t *pkt, LayerNode *pnode) {
    cout<<"vlan"<<endl;
    vlan_hdr *hdr = (vlan_hdr*)pkt;
    uint8_t *next = pkt + VLAN_HDR_LEN;
    pnode->next = new LayerNode(Layer_ETH, ETH_VLAN, next, pnode);
    decode_net_layer(hdr->encap_proto, next, pnode->next);
}