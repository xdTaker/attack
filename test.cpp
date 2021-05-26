#include <iostream>
#include "libs/base/link/eth.h"
#include "libs/pcap/pcap.h"
#include <base/net/ip.h>
// #include <base/common.h>
using namespace std;

// int pcap_size_check_main(int argc, char**argv){
//     if (argc < 2) return 0;
//     const char *pcap_file = argv[1];
//     wtap wth;
//     pcap_open(pcap_file, &wth);
//     int cnt = 10;
//     char buf[MAX_PCAP_SIZE];
//     int64_t sum_len = sizeof(pcap_file_hdr) + wth.skip_size;
//     cout<<"file hdr len: "<<sum_len<<endl;
//     int len;
//     while((len = pcap_read(&wth, buf)) > 0) {
//         sum_len += len;
//     }
//     pcap_close(&wth);
//     cout<<"sum_len: "<<sum_len<<endl;
//     return 0;
// }

int parse_pcap(int argc, char**argv) {
    if (argc < 2) {
        printf("%s <pkt_file>\n", argv[0]);
        return 0;
    }
    const char* pcap_file = argv[1];
    wtap wth;
    pcap_code code;
    if (OK != (code = pcap_open(pcap_file, &wth))) {
        printf("open %s fail, code: %d\n", pcap_file, code);
        return code;
    }
    int cnt = 10;
    uint8_t buf[MAX_PCAP_SIZE];
    int64_t sum_len = sizeof(pcap_file_hdr) + wth.skip_size;
    int len;
    while((len = pcap_read(&wth, buf)) > 0) {
        pcaprec_hdr *hdr = (pcaprec_hdr *)buf;
        hdr->printInfo();
        uint8_t *pkt = buf + sizeof(pcaprec_hdr);
        // print_hex(buf, len);
        // printf("ftell: %ld\n", ftell(wth.fp));
        LayerNode *node = new LayerNode(pkt);
        decode_ether(pkt, node);
        LayerNode *tnode;
        while (node) {
            node->printInfo();
            tnode = node;
            node = node->next;
            delete tnode;
        }
        break;
    }
    return 0;
}

int main(int argc, char**argv) {
    parse_pcap(argc, argv);
    return 0;
}