#include "udp.h"
#include "trans-layer.h"

void UDPhdr::printInfo(){
    printf("UDP info:\n");
    printf(" src port: %u\n", getSPort());
    printf(" dst port: %u\n", getDPort());
    printf(" udp len: %u\n", getLength());
    printf(" check sum: %#hx\n", getCheckSum());
}


void decode_udp(uint8_t *pkt, LayerNode *pnode){
    //UDPhdr *hdr = (UDPhdr*)pkt;
    //uint8_t *next = pkt + UDP_HDR_LEN;
    pnode->next = new LayerNode(Layer_TRANS, UDP, pkt, pnode);
}
