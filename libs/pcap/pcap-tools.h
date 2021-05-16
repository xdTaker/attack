#pragma once

#include <pcap/pcap.h>
#include <base/eth/eth.h>
#include <base/net/net-layer.h>

void edit_pkt(uint8_t *pkt) {
    LayerNode *node = new LayerNode(pkt);
    decode_ether(pkt, node);
    char input[64];
    vector<string> opts;
    vector<string>::iterator opt;
    while (1) {
        switch (node->layer)
        {
        case Layer_TOP:
            printf("top layer\n");
            // printf("next layer: %s\n", "");
            break;
        case Layer_IP:
            IP4hdr *hdr = (IP4hdr*)node->pkt;
            hdr->printInfo();
            break;
        default:
            break;
        }
        printf(">");
        scanf("%s", input);
        split_string(input, opts, " ", false);
        opt = opts.begin();
        if (0 == strcmp(opt->c_str(), "next")) {
            if (node->next)
                node = node->next;
            else {
                printf("last layer yet.\n");
            }
        } else if (0 == strcmp(opt->c_str(), "prev")) {
            if (node->prev)
                node = node->prev;
            else {
                printf("top layer yet.\n");
            }
        } else if (0 == strcmp(opt->c_str(), "set")) {
            opt ++;
            if (0 == strcmp(opt->c_str(), "sip") || 0 == strcmp(opt->c_str(), "dip")) {
                opt ++;
                if (node->layer != Layer_IP) {
                    printf("go to net layer to set ip.\n");
                } else {
                    uint32_t tmp = IP4hdr::IPstr2int(opt->c_str());
                    if (tmp == 0) {
                        printf("ip is invaild\n");
                    } else {
                        IP4hdr *hdr = (IP4hdr*)node->pkt;
                        if (0 == strcmp(opt->c_str(), "sip"))
                            hdr->setSrcAddr(tmp);
                        else
                            hdr->setDstAddr(tmp);
                    }
                }
            } else if (0 == strcmp(opt->c_str(), "sport") || 0 == strcmp(opt->c_str(), "dport")) {
                opt ++;
                if (node->layer != Layer_TRANS) {
                    printf("go to trans layer to set port.\n");
                }
            }
        }
        
    }
}
