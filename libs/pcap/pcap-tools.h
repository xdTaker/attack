#pragma once

#include <pcap/pcap.h>
#include <base/link/eth.h>
#include <base/net/net-layer.h>
#include <base/trans/trans-layer.h>

void edit_pkt(uint8_t *pkt);