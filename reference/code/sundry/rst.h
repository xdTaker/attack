#ifndef MAIL_KILL_H_INCLUDED
#define MAIL_KILL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "nids.h"
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <linux/tcp.h>
//定义伪TCP首部
typedef struct
{
 struct in_addr saddr; //源IP地址
 struct in_addr daddr; //目的IP地址
 char mbz;                   // mbz = must be zero, 用于填充对齐
 char protocal;             //8位协议号
 unsigned short tcpl;    // TCP包长度
}psdheader_t;

unsigned short checksum(unsigned short *buffer, int size);//计算校验和

int bird_kill(struct tcp_stream *tcp_connection);//构造并发送封堵包
#endif // MAIL_KILL_H_INCLUDED