void *server_socket;

void _T_service(void);
asm "@_T_service"
asm "push %rcx"
asm "call @T_service"
asm "pop %rcx"
asm "ret"
int sock_read(void *csock,void *buf,int size)
{
	struct fd_set fdset;
	long timeout[2];
	int n;
	fdset.nfds=1;
	fdset.pad=0;
	fdset.sock[0]=csock;
	timeout[0]=8;
	timeout[1]=0;
	if(select(1,&fdset,NULL,NULL,timeout)!=1)
	{
		return 0;
	}
	n=recv(csock,buf,size,0);
	if(n<=0)
	{
		return 0;
	}
	return n;
}
int sock_write(void *csock,void *buf,int size)
{
	struct fd_set fdset;
	long timeout[2];
	int n;
	fdset.nfds=1;
	fdset.pad=0;
	fdset.sock[0]=csock;
	timeout[0]=8;
	timeout[1]=0;
	if(select(1,NULL,&fdset,NULL,timeout)!=1)
	{
		return 0;
	}
	n=send(csock,buf,size,0);
	if(n<=0)
	{
		return 0;
	}
	return n;
}
int sock_read2(void *csock,void *buf,int size)
{
	int n;
	while(size)
	{
		n=sock_read(csock,buf,size);
		if(n==0)
		{
			return 1;
		}
		size-=n;
		buf=(char *)buf+n;
	}
	return 0;
}
int sock_write2(void *csock,void *buf,int size)
{
	int n;
	while(size)
	{
		n=sock_write(csock,buf,size);
		if(n==0)
		{
			return 1;
		}
		size-=n;
		buf=(char *)buf+n;
	}
	return 0;
}
char *read_http_request(void *csock)
{
	char buf[256];
	char *ret,*new_str;
	int n,len,x,x2;
	int s;
	if(sock_read2(csock,buf,4))
	{
		return NULL;
	}
	if(memcmp(buf,"GET ",4))
	{
		return NULL;
	}
	ret=NULL;
	len=0;
	s=1;
	while(s)
	{
		n=sock_read(csock,buf,256);
		if(n==0)
		{
			break;
		}
		new_str=malloc(n+len+1);
		if(new_str==NULL)
		{
			break;
		}
		if(ret!=NULL)
		{
			memcpy(new_str,ret,len);
			free(ret);
		}
		ret=new_str;
		x=0;
		x2=0;
		while(x<n)
		{
			if(!(buf[x]>='0'&&buf[x]<='9'||buf[x]>='A'&&buf[x]<='Z'||buf[x]>='a'&&buf[x]<='z'||buf[x]=='/'||buf[x]=='_'||buf[x]=='.'||buf[x]=='-'))
			{
				if(buf[x]==' ')
				{
					s=0;
					break;
				}
				free(ret);
				return NULL;
			}
			ret[len+x2]=buf[x];
			++x;
			++x2;
		}
		ret[len+x2]=0;
		len+=n;
	}
	return ret;
}
#include "pages.c"

void T_server(void)
{
	void *csock,*th;
	while(1)
	{
		csock=accept(server_socket,NULL,NULL);
		if(csock!=INVALID_SOCKET)
		{
			th=CreateThread(NULL,0,_T_service,csock,0,NULL);
			if(th==NULL)
			{
				closesocket(csock);
			}
			else
			{
				CloseHandle(th);
			}
		}
	}
}
int server_init(unsigned int server_addr)
{
	struct sockaddr_in addr;
	server_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(server_socket==INVALID_SOCKET)
	{
		return 1;
	}
	memset(&addr,0,sizeof(addr));
	addr.family=AF_INET;
	addr.port=htons(SERVER_PORT);
	addr.addr=htonl(server_addr);
	if(bind(server_socket,&addr,sizeof(addr)))
	{
		closesocket(server_socket);
		return 1;
	}
	if(listen(server_socket,16))
	{
		closesocket(server_socket);
		return 1;
	}
	if(CreateThread(NULL,0,T_server,NULL,0,NULL)==NULL)
	{
		closesocket(server_socket);
		return 1;
	}
	return 0;
}
