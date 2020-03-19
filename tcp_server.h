#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "string.h"

void tcp_server_init(uint16_t _PortNumber);
void tcp_Server_SendString(struct tcp_pcb *tpcb,uint8_t * str , uint16_t len);
void tcp_server_connection_close(struct tcp_pcb *tpcb);
__weak void tcp_Server_Recieve(struct tcp_pcb *tpcb,uint8_t *Buf,uint32_t _Len);
__weak void tcp_Server_NewConnection(struct tcp_pcb *newpcb);

#endif /* __TCP_SERVER */
