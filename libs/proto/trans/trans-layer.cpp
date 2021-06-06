#include "trans-layer.h"

bool decode_trans_layer(TRANS_PROTO proto, uint8_t *pkt, LayerNode *pnode) {
    bool ret;
    switch (proto)
    {
    case TRANS_TCP:
        ret = decode_tcp(pkt, pnode);
        break;

    case TRANS_UDP:
        ret = decode_udp(pkt, pnode);
        break;
    
    default:
        ret = false;
        cout<<"协议: "<<getstr_hex(proto)<<endl;
        break;
    }

    return ret;
}


ForEth_Proto set_psd_hdr(const void *ip_hdr, void *phdr) {
    IP4hdr *ip4;
    switch (*((uint8_t*)ip_hdr) >> 4) {
        case 4:
            ip4 = (IP4hdr*)ip_hdr;
            ((PsdIP4Hdr*)phdr)->set(ip4->srcAddr, ip4->dstAddr, ip4->upProto, ip4->getTotalLen()-ip4->getHdrLen());
            return IPv4;
        case 6:
            return IPv6;
        default:
            return FORETH_UNKNOW;
    }
}
