#include "tcp.h"

void decode_tcp(uint8_t *pkt, LayerNode *pnode) {
    TCPhdr *hdr = (TCPhdr*)pkt;
    uint8_t *next = pkt + hdr->getHdrLen();
    pnode->next = new LayerNode(Layer_TRANS, TRANS_TCP, pkt, pnode);
    hdr->printInfo();
    hdr->check();
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

void TCPhdr::setCheck(){
    checksum = 0;
    uint32_t t_checksum = 0;
    uint16_t *ptr = (uint16_t*)this;
    for(int i=0; i<2*offset; i++){
        t_checksum += *ptr;
        ptr ++;
    }
    t_checksum = ~((t_checksum & 0xffff) + (t_checksum >> 16));
    checksum = t_checksum & 0xffff;
}

bool TCPhdr::check(){
    uint32_t t_checksum = 0;
    uint16_t *ptr = (uint16_t*)this;
    for(int i=0; i<2*offset; i++){
        t_checksum += (*ptr);
        ptr ++;
    }
    t_checksum = ~((t_checksum & 0xffff) + (t_checksum >> 16));
    t_checksum &= 0xffff;
    printf("check: %u   checksum: %u\n", t_checksum, checksum);
    return t_checksum == 0;
}

void TCPhdr::printInfo() {
    printf("TCP info:\n");
    printf("  src port: %u\n", getSPort());
    printf("  dst port: %u\n", getDPort());
    printf("  hdr len: %u\n", getHdrLen());
    printf("  seq num: %u\n", seqNum);
    printf("  ack num: %u\n", ackNum);
    printf("  window: %u\n", window);
}
