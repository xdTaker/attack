#include "proto.h"
#include <proto/link/eth.h>
#include <proto/net/net-layer.h>
#include <proto/trans/trans-layer.h>

void LayerNode::printInfo() {
    switch (layer)
    {
    case Layer_TOP:
        printf("top layer\n");
        // printf("next layer: %s\n", "");
        break;
    case Layer_LINK:
        switch (proto)
        {
        case ETHII:
            ((EthII_hdr*)pkt)->printInfo();
            break;
        case ETH_VLAN:
            printf("vlan\n");
        default:
            break;
        }
    case Layer_NET:
        switch (proto) {
        case IPv4:
            ((IP4hdr*)pkt)->printInfo();
            break;
        default:
            break;
        }
        break;
    case Layer_TRANS:
        switch (proto) {
        case TCP:
            ((TCPhdr*)pkt)->printInfo(prev->pkt);
            break;
        case UDP:
            ((UDPhdr*)pkt)->printInfo();
            break;
        }
        break;
    default:
        break;
    }
}