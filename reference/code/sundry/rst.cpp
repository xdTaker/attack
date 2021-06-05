#include "rst.h"

unsigned short checksum(unsigned short *buffer, int size)
{
    unsigned long cksum = 0;
    while(size>1)
    {
        cksum += *buffer++;
        size -= sizeof(unsigned short);
    }
    if(size)
    {
        cksum += *(unsigned char*)buffer;
    }
    cksum = (cksum>>16) + (cksum&0xffff);
    cksum += (cksum>>16);
    return (unsigned short)(~cksum);
}
int bird_kill(struct tcp_stream *tcp_connection)
{
    psdheader_t tcp_psdhead;
    int skfd_1=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
    int skfd_2=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
    char *buf_client,*buf_server,*tcp_psd_buffer;
    setsockopt(skfd_1,IPPROTO_IP,IP_HDRINCL,"1",sizeof("1"));
    setsockopt(skfd_2,IPPROTO_IP,IP_HDRINCL,"1",sizeof("1"));
    int ip_len;
    int i =0;
    u_int16_t win = 32000;

    ip_len = sizeof(struct ip)+sizeof(struct tcphdr);
    buf_client=malloc(ip_len);
    buf_server=malloc(ip_len);
    tcp_psd_buffer=malloc(ip_len);
    struct ip *ip_client=(struct ip *)buf_client;
    struct ip *ip_server=(struct ip *)buf_server;
    struct tcphdr *tcp_client=(struct tcphdr*)(buf_client+sizeof(struct ip));
    struct tcphdr *tcp_server=(struct tcphdr*)(buf_server+sizeof(struct ip));
    struct sockaddr_in target_1,target_2;

    bzero(&target_1,sizeof(struct sockaddr_in));//客户端
    bzero(&target_2,sizeof(struct sockaddr_in));//服务器端
    target_1.sin_family=AF_INET;
    target_1.sin_port=htons(tcp_connection->addr.source);//客户端端口
    target_1.sin_addr.s_addr=tcp_connection->addr.saddr;//客户端地址
    target_2.sin_family=AF_INET;
    target_2.sin_port=htons(tcp_connection->addr.dest);//服务器端口
    target_2.sin_addr.s_addr=tcp_connection->addr.daddr;//服务器地址

    /*****************客户端**********************/
    /*****************IP 头构造**********************/
    ip_client->ip_v = 4;
    ip_client->ip_hl = 5;
    ip_client->ip_tos = 0;
    ip_client->ip_len = sizeof(struct ip)+sizeof(struct tcphdr);
    ip_client->ip_id=htons(12345);
    ip_client->ip_off=0;
    ip_client->ip_ttl=64;
    ip_client->ip_p=IPPROTO_TCP;
    ip_client->ip_sum=0;
    ip_client->ip_dst=target_2.sin_addr;//目的地址
    ip_client->ip_src=target_1.sin_addr;//源地址
    ip_client->ip_sum=checksum((unsigned short*)buf_client,sizeof(struct ip));
    /*****************伪头构造**********************/
    bzero(&tcp_psdhead,sizeof(tcp_psdhead));
    bzero(tcp_psd_buffer,ip_len);
    tcp_psdhead.mbz=0;
    tcp_psdhead.saddr=target_1.sin_addr;
    tcp_psdhead.daddr=target_2.sin_addr;
    tcp_psdhead.protocal=IPPROTO_TCP;
    tcp_psdhead.tcpl=htons(20);
    /*****************TCP头构造**********************/
    tcp_client->source = target_1.sin_port;
    tcp_client->dest = target_2.sin_port;
    tcp_client->seq =htonl(tcp_connection->client.seq + tcp_connection->server.window / 2);
    tcp_client->ack_seq=0;
    tcp_client->doff=5;
    tcp_client->window=htons(win);//htobe16(tcp_connection->server.window);
    tcp_client->rst= 1;
    tcp_client->fin=0;
    tcp_client->syn=0;
    tcp_client->urg=0;
    tcp_client->ack=0;
    tcp_client->psh=0;
    tcp_client->check = 0;

    printf("  #发给客户端的包\n");
    memcpy(tcp_psd_buffer,&tcp_psdhead,sizeof(tcp_psdhead));
    memcpy(tcp_psd_buffer+sizeof(tcp_psdhead),tcp_client,sizeof(struct tcphdr));
    tcp_client->check=checksum((unsigned short*)tcp_psd_buffer,sizeof(tcp_psdhead)+sizeof(struct tcphdr));
    sendto(skfd_2,buf_client,ip_len,0,(struct sockaddr *)&target_2,sizeof(struct sockaddr));

    /*****************服务器端**********************/
    /*****************IP 头构造**********************/
    //开始填充IP首部
    ip_server->ip_v = 4;
    ip_server->ip_hl = 5;
    ip_server->ip_tos = 0;
    ip_server->ip_len = sizeof(struct ip)+sizeof(struct tcphdr);
    ip_server->ip_id=htons(12345);
    ip_server->ip_off=0;
    ip_server->ip_ttl=64;
    ip_server->ip_p=IPPROTO_TCP;
    ip_server->ip_sum=0;
    ip_server->ip_dst=target_1.sin_addr;//目的地址
    ip_server->ip_src=target_2.sin_addr;//源地址
    ip_server->ip_sum=checksum((unsigned short*)buf_server,sizeof(struct ip));
    /*****************伪头构造**********************/
    bzero(&tcp_psdhead,sizeof(tcp_psdhead));
    bzero(tcp_psd_buffer,ip_len);
    tcp_psdhead.mbz=0;
    tcp_psdhead.saddr=target_2.sin_addr;
    tcp_psdhead.daddr=target_1.sin_addr;
    tcp_psdhead.protocal=IPPROTO_TCP;
    tcp_psdhead.tcpl=20;
    /*****************TCP头构造**********************/
    tcp_server->source = target_2.sin_port;
    tcp_server->dest = target_1.sin_port;
    tcp_server->seq =htonl(tcp_connection->server.seq + tcp_connection->client.window / 2);
    tcp_server->ack_seq=0;
    tcp_server->doff=5;
    tcp_server->window=htons(win);
    tcp_server->rst= 1;
    tcp_server->fin=0;
    tcp_server->syn=0;
    tcp_server->urg=0;
    tcp_server->ack=0;
    tcp_server->psh=0;
    tcp_server->check = 0;
    memcpy(tcp_psd_buffer,&tcp_psdhead,sizeof(tcp_psdhead));
    memcpy(tcp_psd_buffer+sizeof(tcp_psdhead),&tcp_server,sizeof(struct tcphdr));
    tcp_server->check=checksum((unsigned short*)tcp_psd_buffer,sizeof(tcp_psdhead)+sizeof(struct tcphdr));
    /*****************发送包**********************/
    sendto(skfd_2,buf_server,ip_len,0,(struct sockaddr *)&target_2,sizeof(struct sockaddr));
    printf(" #发送给服务端的包\n");

    free(buf_client);
    free(buf_server);
    free(tcp_psd_buffer);
    close(skfd_1);
    close(skfd_2);
    return 0;
}