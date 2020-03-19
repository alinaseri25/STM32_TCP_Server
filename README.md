# STM32_TCP_Server

void tcp_server_init(uint16_t _PortNumber); create a tcp server to listen to _PortNumber<br/>
void tcp_Server_SendString(struct tcp_pcb *tpcb,uint8_t * str , uint16_t len); send a buffer to each connection<br/>
void tcp_server_connection_close(struct tcp_pcb *tpcb); close each connection<br/>
add this callback to your project file (main.c or ...) that you need to process recieved buffer like this : <br/>
void tcp_server_Recieve(struct tcp_pcb *tpcb,uint8_t *Buf,uint32_t _Len) <br/>
{<br/>
  //your code; <br/>
} <br/>
add this callback to your project file (main.c or ...) that you need to process new connections : <br/>
void tcp_server_NewConnection(struct tcp_pcb *newpcb) <br/>
{ <br/>
  //your code;<br/>
}<br/>
