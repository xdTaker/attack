#include <pcap/pcap.h>
#include <base/common.h>

void pcaprec_hdr::printInfo() {
    printf("pcaprec info\n");
    printf("  sec: %u\n", ts_sec);
    printf("  usec: %u\n", ts_usec);
    printf("  incl len: %u\n", incl_len);
    printf("  orig len: %u\n", orig_len);
}

open_pcap_code pcap_open(const char *file, wtap *wth) {
    int skip_size = 0;
    int skip_bytes;
    bool byte_swapped = false;
    bool modified = false;

    pcap_file_hdr *hdr = &wth->file_hdr;
#if PCAP_DEBUG
    // cout<<"file len: "<<getFileLen(file)<<endl;
#endif

    wth->fp = fopen(file, "rb");
    if (wth->fp <= 0)
        return OPEN_FILE_FAIL;
    fread(hdr, 1, sizeof(pcap_file_hdr), wth->fp);
    switch (hdr->magic) {
        case PCAP_IXIAHW_MAGIC:
        case PCAP_IXIASW_MAGIC:
            skip_size = 1;
        case PCAP_MAGIC:
            break;
        case PCAP_MODIFIED_MAGIC:
            modified = true;
            break;
        case PCAP_SWAPPED_IXIAHW_MAGIC:
        case PCAP_SWAPPED_IXIASW_MAGIC:
            skip_size = 1;
        case PCAP_SWAPPED_MAGIC:
            byte_swapped = true;
            break;
        case PCAP_NSEC_MAGIC:
            break;
        case PCAP_SWAPPED_NSEC_MAGIC:
            byte_swapped = true;
            break;
        default:
            return PCAP_FILE_HDR_ERR;
    }

    if (skip_size > 0 && !fread(&skip_bytes, 1, skip_size, wth->fp))
        return READ_FILE_FAIL;

    if (byte_swapped) {
        hdr->version_major = swap_bytes<uint16_t>(hdr->version_major);
        hdr->version_minor = swap_bytes<uint16_t>(hdr->version_minor);
        hdr->snaplen = swap_bytes<uint32_t>(hdr->snaplen);
        hdr->network = swap_bytes<uint32_t>(hdr->network);
    }

    if (hdr->version_major < 2) {
        return NOT_SUPPORTED;
    }

    wth->byte_swapped = byte_swapped;
    wth->skip_size = skip_size;

#if PCAP_DEBUG
    cout<<"pcap info:"<<endl;
    cout<<"  magic: ";print_hex<uint32_t>(hdr->magic);
    cout<<"  swapped: "<<byte_swapped<<endl;
    cout<<"  modified: "<<modified<<endl;
    cout<<"  skipbytes: "<<skip_size<<endl;
#endif
}

void pcap_close(wtap *wth) {
    fclose(wth->fp);
}

int pcap_read(wtap *wth, char *buf) {
    pcaprec_hdr *hdr = (pcaprec_hdr *)buf;
    if(sizeof(pcaprec_hdr) != fread(hdr, 1, sizeof(pcaprec_hdr), wth->fp))
        return 0;
#if PCAP_DEBUG
#if PCAP_PKT_MSG
    cout<<"  packet"<<endl;
    cout<<"timesec: "<<hdr->ts_sec<<endl;
    cout<<"timeusec: "<<hdr->ts_usec<<endl;
    cout<<"origlen: "<<hdr->orig_len<<endl;
#endif
    // cout<<"caplen: "<<hdr->incl_len<<endl;
#endif
    int readlen = fread(hdr+1, 1, hdr->incl_len, wth->fp);
    if (hdr->incl_len != readlen) {
        cout<<"caplen: "<<hdr->incl_len<<"  readlen: "<<readlen<<endl;
    }
    return sizeof(pcaprec_hdr) + hdr->incl_len;
}