#include "tcp_server.h"

#if LWIP_TCP


static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void tcp_server_error(void *arg, err_t err);

void tcp_server_init(uint16_t _PortNumber)
{
  /* create new tcp pcb */
	static struct tcp_pcb *tcp_server_pcb;
  tcp_server_pcb = tcp_new();

  if (tcp_server_pcb != NULL)
  {
    err_t err;
    
    err = tcp_bind(tcp_server_pcb, IP_ADDR_ANY, _PortNumber);
    
    if (err == ERR_OK)
    {
      /* start tcp listening for pcb */
      tcp_server_pcb = tcp_listen(tcp_server_pcb);
      
      /* initialize LwIP tcp_accept callback function */
      tcp_accept(tcp_server_pcb, tcp_server_accept);
    }
    else 
    {
      /* deallocate the pcb */
      memp_free(MEMP_TCP_PCB, tcp_server_pcb);
    }
  }
}

static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  err_t ret_err;

  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(err);

  /* set priority for the newly accepted tcp connection newpcb */
  tcp_setprio(newpcb, TCP_PRIO_MIN);
	
	if(err == ERR_OK)
	{
    tcp_arg(newpcb, NULL);
    
    /* initialize lwip tcp_recv callback function for newpcb  */ 
    tcp_recv(newpcb, tcp_server_recv);
    
    /* initialize lwip tcp_err callback function for newpcb  */
    tcp_err(newpcb, tcp_server_error);
		
		tcp_Server_NewConnection(newpcb);
    
    ret_err = ERR_OK;
  }
  else
  {
    /*  close tcp connection */
    tcp_close(newpcb);
    ret_err = ERR_MEM;
  }
  return ret_err;  
}


static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
  err_t ret_err;
	
  if (p == NULL)
  {
    tcp_close(tpcb);
    ret_err = ERR_OK;
  }
  else if(err != ERR_OK)
  {
    pbuf_free(p);
    ret_err = err;
  }
  else
	{
		tcp_Server_Recieve(tpcb,p->payload,p->len);
		tcp_recved(tpcb,p->len);
		tcp_sent(tpcb, NULL);
		pbuf_free(p);
    ret_err = ERR_OK;
  }
  return ret_err;
}

static void tcp_server_error(void *arg, err_t err)
{
  LWIP_UNUSED_ARG(err);
}

void tcp_server_connection_close(struct tcp_pcb *tpcb)
{
  
  /* remove all callbacks */
  tcp_arg(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  
  /* close tcp connection */
  tcp_close(tpcb);
}

void tcp_Server_SendString(struct tcp_pcb *tpcb,uint8_t * str , uint16_t _Len)
{
	if(_Len == 0)
	{
		while(str[_Len] != 0)_Len++;
	}
  tcp_write(tpcb,str,_Len,1);
}

__weak void tcp_Server_NewConnection(struct tcp_pcb *newpcb)
{
	
}

__weak void tcp_Server_Recieve(struct tcp_pcb *tpcb,uint8_t *Buf,uint32_t _Len)
{
	
}

#endif /* LWIP_TCP */
