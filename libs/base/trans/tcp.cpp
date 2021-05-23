#include "tcp.h"
#include "trans-layer.h"

void decode_tcp(uint8_t *pkt, LayerNode *pnode) {
    TCPhdr *hdr = (TCPhdr*)pkt;
    uint8_t *next = pkt + hdr->getHdrLen();
    pnode->next = new LayerNode(Layer_TRANS, TRANS_TCP, pkt, pnode);
    hdr->printInfo(pnode->pkt);
}

TCPhdr::TCPhdr(uint16_t len){
    memset(this, 0, sizeof(TCPhdr));
    offset = len;
}

void TCPhdr::setSPort(uint16_t port) {
    srcPort = swap_bytes<uint16_t>(port);
}
void TCPhdr::setDPort(uint16_t port) {
    dstPort = swap_bytes<uint16_t>(port);
}

void TCPhdr::setCheck(const void *ip_hdr){
    checksum = 0;
    uint16_t t_checksum = 0;
    uint16_t phdr[IP6_PHDR_LEN / 2];
    switch (set_psd_hdr(ip_hdr, phdr)) {
        case IPv4:
            t_checksum = getCheckSum(phdr, IP4_PHDR_LEN);
            t_checksum = getCheckSum((uint16_t*)this, ((PsdIP4Hdr*)phdr)->getLen(), ~t_checksum);
            break;
        case IPv6:
        default:
            return;
    }
    checksum = t_checksum;
}

bool TCPhdr::check(const void *ip_hdr){
    uint16_t t_checksum = 0;
    uint16_t phdr[IP6_PHDR_LEN / 2];
    switch (set_psd_hdr(ip_hdr, phdr)) {
        case IPv4:
            t_checksum = getCheckSum(phdr, IP4_PHDR_LEN);
            t_checksum = getCheckSum((uint16_t*)this, ((PsdIP4Hdr*)phdr)->getLen(), ~t_checksum);
            break;
        case IPv6:
        default:
            return false;
    }
    return t_checksum == 0;
}

void TCPhdr::printInfo(const void *ip_hdr) {
    printf("TCP info:\n");
    printf("  src port: %u\n", getSPort());
    printf("  dst port: %u\n", getDPort());
    printf("  hdr len: %u\n", getHdrLen());
    printf("  seq num: %u\n", seqNum);
    printf("  ack num: %u\n", ackNum);
    printf("  window: %u\n", window);
    printf("  flags: "); {
        if (URG)
            printf("U ");
        if (PSH)
            printf("P ");
        if (RST)
            printf("R ");
        if (SYN)
            printf("S ");
        if (FIN)
            printf("F ");
        if (ACK)
            printf("A ");
    }printf("\n");
    printf("  check: %s\n", check(ip_hdr)? "OK": "ERROR");
}
