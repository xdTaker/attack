#include "trans-layer.h"
#include "tcp.h"

void decode_trans_layer(TRANS_PROTO proto, uint8_t *pkt, LayerNode *pnode) {
    cout<<"协议: "<<getstr_hex(proto)<<endl;
    switch (proto)
    {
    case TRANS_TCP:
        decode_tcp(pkt, pnode);
        break;
    
    default:
        break;
    }
}