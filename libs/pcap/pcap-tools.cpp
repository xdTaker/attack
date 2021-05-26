#include "pcap-tools.h"

int main(int argc, char **argv) {
    if (argc == 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("%s <file> --edit -s <file-offset>\n", argv[0]);
        printf("%s <file> --edit -n <packet-no.>\n", argv[0]);
    }
    pcap_code code;
    const char *file = argv[1];
    wtap wth;
    if (OK != (code = pcap_open(file, &wth))) {
        printf("open %s fail, code: %d\n", file, code);
        return code;
    }
    if (strcmp(argv[2], "--edit") == 0) {
        int64_t file_off = -1;
        uint8_t *pkt = nullptr;
        uint8_t buf[MAX_PCAP_SIZE];
        if (strcmp(argv[3], "-s") == 0) {
            int64_t off = atol(argv[4]);
            file_off = off;
            fseek(wth.fp, off, SEEK_SET);
            if (0 != pcap_read(&wth, buf)) {
                pkt = buf + sizeof(pcaprec_hdr);
            }
        } else if (strcmp(argv[3], "-n") == 0) {
            int n = atoi(argv[4]);
            int cnt = 0;
            while (cnt <= n) {
                if (cnt == n) {
                    file_off = ftell(wth.fp);
                }
                cnt ++;
                pcap_read(&wth, buf);
            }
            pkt = buf + sizeof(pcaprec_hdr);
        }
        if (pkt) {
            edit_pkt(pkt);
            if (file_off != -1) {
                fseek(wth.fp, file_off + sizeof(pcaprec_hdr), SEEK_SET);
                fwrite(pkt, 1, ((pcaprec_hdr*)buf)->incl_len, wth.fp);
            }
        }
    }
    pcap_close(&wth);
    return 0;
}

void edit_pkt(uint8_t *pkt) {
    LayerNode *node = new LayerNode(pkt);
    decode_ether(pkt, node);
    char input[64];
    vector<string> opts;
    vector<string>::iterator opt;

    TCPhdr *tcp_hdr;
    IP4hdr *ip4_hdr;
    bool showInfo = true;
    printf("enter \"help\" to get help\n");
    while (1) {
        if (showInfo)
            node->printInfo();
        showInfo = true;
        printf(">");
        int i = 0;
        while ((input[i] = getchar()) != '\n') {i++;} input[i] = '\0';
        split_string(input, opts, " ", false);
        opt = opts.begin();
        if (opt == opts.end()) {
            continue;
        } else if (0 == strcmp(opt->c_str(), "help")) {
            printf("next: goto next layer\n");
            printf("prev: goto previous layer\n");
            printf("quit: exit\n");
            printf("set: enter \"set help\" to get detail help\n");
            showInfo = false;
        } else if (0 == strcmp(opt->c_str(), "next")) {
            if (node->next)
                node = node->next;
            else {
                printf("last layer yet.\n");
                showInfo = false;
            }
        } else if (0 == strcmp(opt->c_str(), "prev")) {
            if (node->prev)
                node = node->prev;
            else {
                printf("top layer yet.\n");
                showInfo = false;
            }
        } else if (0 == strcmp(opt->c_str(), "quit")) {
            break;
        } else if (0 == strcmp(opt->c_str(), "set")) {
            opt ++;
            if (0 == strcmp(opt->c_str(), "help")) {
                printf("set sip x.x.x.x\n");
                printf("set dip x.x.x.x\n");
                printf("set sport x.x.x.x\n");
                printf("set dport x\n");
                printf("set flags xxx\n");
                showInfo = false;
            } else if (0 == strcmp(opt->c_str(), "sip") || 0 == strcmp(opt->c_str(), "dip")) {
                if (node->layer != Layer_NET) {
                    printf("go to net layer to set ip.\n");
                } else {
                    const char *ip_dir = opt->c_str();
                    opt ++;
                    uint32_t tmp = IP4hdr::IPstr2int(opt->c_str());
                    if (tmp == 0) {
                        printf("ip is invaild\n");
                    } else {
                        if (0 == strcmp(ip_dir, "sip"))
                            ((IP4hdr*)node->pkt)->setSrcAddr(tmp);
                        else
                            ((IP4hdr*)node->pkt)->setDstAddr(tmp);
                    }
                }
            } else if (0 == strcmp(opt->c_str(), "sport") || 0 == strcmp(opt->c_str(), "dport")) {
                if (node->layer != Layer_TRANS) {
                    printf("go to trans layer to set port.\n");
                } else {
                    const char *port_dir = opt->c_str();
                    opt ++;
                    uint16_t port = (uint16_t)atoi(opt->c_str());
                    switch (node->proto)
                    {
                    case TCP:
                        if (0 == strcmp(port_dir, "sport"))
                            ((TCPhdr*)node->pkt)->setSPort(port);
                        else
                            ((TCPhdr*)node->pkt)->setDPort(port);
                        break;
                    default:
                        break;
                    }
                }
            } else if (0 == strcmp(opt->c_str(), "flag")) {
                if (node->layer != Layer_TRANS) {
                    printf("go to trans layer to set flag.\n");
                } else {
                    opt ++;
                    switch (node->proto) {
                        case TCP:
                            tcp_hdr = (TCPhdr*)node->pkt;
                            memset(&(tcp_hdr->flags), 0, sizeof(tcp_hdr->flags));
                            for (char &ch: *opt) {
                                switch (ch) {
                                    case 'F':
                                        tcp_hdr->flags.FIN = 1;break;
                                    case 'S':
                                        tcp_hdr->flags.SYN = 1;break;
                                    case 'R':
                                        tcp_hdr->flags.RST = 1;break;
                                    case 'P':
                                        tcp_hdr->flags.PSH = 1;break;
                                    case 'A':
                                        tcp_hdr->flags.ACK = 1;break;
                                    case 'U':
                                        tcp_hdr->flags.URG = 1;break;
                                    default:
                                        break;
                                }
                            }
                        default:
                            break;
                    }
                }
            }

        }
        
    }
}
