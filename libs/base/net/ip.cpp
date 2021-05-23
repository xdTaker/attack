#include <base/net/ip.h>
#include <base/trans/trans-layer.h>

bool decode_IPv4(uint8_t *pkt, LayerNode *pnode) {
    IP4hdr *hdr = (IP4hdr*)pkt;
    hdr->printInfo();
    uint8_t *next = pkt + hdr->getHdrLen();
    pnode->next = new LayerNode(Layer_IP, Net_IPv4, pkt, pnode);
    decode_trans_layer((TRANS_PROTO)hdr->upProto, next, pnode->next);
}

IP4hdr::IP4hdr(uint8_t len){
    memset(this, 0, sizeof(IP4hdr));
    hdrLen = len;
    TTL = 128;
    version = 4;
}

string IP4hdr::IPint2str(uint32_t IPaddr) {
    string IPstr;
    int swaped_IP = swap_bytes<uint32_t>(IPaddr);
    // print_hex<uint32_t>(IPaddr);
    for (int i=0; i<4; i++) {
        IPstr += std::to_string(IPaddr & 0xFF);
        IPstr += '.';
        IPaddr >>= 8;
    }
    IPstr.pop_back();
    return IPstr;
}

uint32_t IP4hdr::IPstr2int(const char *IPstr) {
    uint32_t IPaddr = 0;
    int tmp;
    vector<string> parts;
    split_string(IPstr, parts, ".");
    if (parts.size() != 4)
        goto end;
    for (string &str: parts) {
        IPaddr <<= 8;
        tmp = atoi(str.c_str());
        if (tmp < 0 && tmp > 255) {
            IPaddr = 0;
            goto end;
        }
        IPaddr |= tmp;
    }
end:
    return IPaddr;
}

void IP4hdr::setCheck(){
    checksum = 0;
    checksum = getCheckSum((uint16_t*)this, getHdrLen());
}

bool IP4hdr::check(){
    uint16_t t_checksum = getCheckSum((uint16_t*)this, getHdrLen());
    // printf("  checksum: %u\n", t_checksum);
    return t_checksum == 0;
}

void IP4hdr::subTTL(){
    TTL --;
    checksum ++;
}

void IP4hdr::printInfo() {
    printf("IPv4 info:\n");
    printf("  src ip: %s\n", IPint2str(srcAddr).c_str());
    printf("  dst ip: %s\n", IPint2str(dstAddr).c_str());
    printf("  proto: %s\n", getstr_hex<uint8_t>(upProto).c_str());
    printf("  totol len: %u\n", getTotalLen());
    printf("  hdr len: %u\n", getHdrLen());
    printf("  check: %s\n", check()? "OK": "ERROR");
}

void IP4hdr::setProto(TRANS_PROTO proto) {
    upProto = proto;
    setCheck();
}
void IP4hdr::setSrcAddr(uint32_t addr) {
    srcAddr = addr;
    setCheck();
}
void IP4hdr::setDstAddr(uint32_t addr) {
    dstAddr = addr;
    setCheck();
}