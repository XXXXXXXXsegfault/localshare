#include "../include/windows.c"
#include "../include/windef.c"
#include "../include/mem.c"
#include "../include/iformat.c"

#define SERVER_PORT 2047
int is_folder(char *path)
{
	void *fh;
	struct win32_find_data_a fd;
	char *new_path;
	new_path=malloc(strlen(path)+5);
	if(new_path==NULL)
	{
		return 0;
	}
	strcpy(new_path,path);
	strcat(new_path,"/*");
	fh=FindFirstFileA(new_path,&fd);
	if(fh==INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	FindClose(fh);
	return 1;
}
int get_ip_addr(unsigned int *result)
{
	char buf[20];
	int x;
	int c;
	int dots;
	unsigned long num;
	x=0;
	dots=0;
	*result=0;
	while(1)
	{
		c=getchar();
		if(x<19)
		{
			if(c>='0'&&c<='9')
			{
				buf[x]=c;
				++x;
			}
			else if(c=='.')
			{
				if(x==0)
				{
					return 0;
				}
				buf[x]=0;
				++dots;
				x=0;
				sinputi(buf,&num);
				if(num>255)
				{
					return 0;
				}
				*result=*result<<8|num;
			}
			else if(c!='\n')
			{
				return 0;
			}
		}
		if(c=='\n')
		{
			if(x==0)
			{
				return 0;
			}
			buf[x]=0;
			x=0;
			sinputi(buf,&num);
			if(num>255)
			{
				return 0;
			}
			*result=*result<<8|num;
			break;
		}
	}
	if(dots!=3)
	{
		return 0;
	}
	return 1;
}
char server_ipaddr_str[40];
void put_ip_addr(unsigned int ip_addr)
{
	char *buf;
	buf=server_ipaddr_str;
	strcpy(buf,"http://");
	sprinti(buf,ip_addr>>24&0xff,1);
	strcat(buf,".");
	sprinti(buf,ip_addr>>16&0xff,1);
	strcat(buf,".");
	sprinti(buf,ip_addr>>8&0xff,1);
	strcat(buf,".");
	sprinti(buf,ip_addr&0xff,1);
	strcat(buf,":");
	sprinti(buf,SERVER_PORT,1);
}
char *server_root;
#include "server.c"
int main(int argc,char **argv)
{
	unsigned int server_ipaddr;
	if(argc<2)
	{
		puts("Usage: ./localshare.exe <Folder>\n");
		puts("Press any key to continue.\n");
		getch();
		return 1;
	}
	if(!is_folder(argv[1]))
	{
		puts(argv[1]);
		puts(": Not a folder\n");
		puts("Press any key to continue.\n");
		getch();
		return 1;
	}
	server_root=argv[1];
	puts("Input the IP address of your server: ");
	if(!get_ip_addr(&server_ipaddr))
	{
		puts("Not a valid IP address\n");
		puts("Press any key to continue.\n");
		getch();
		return 1;
	}
	put_ip_addr(server_ipaddr);
	if(server_init(server_ipaddr))
	{
		puts("Failed to initialize server\n");
		puts("Press any key to continue.\n");
		getch();
		return 1;
	}
	puts("Now you can access ");
	puts(argv[1]);
	puts(" (");
	puts(server_ipaddr_str);
	puts(") through your web browser.\n");
	puts("Press any key to shut down the server.\n");
	getch();
	return 0;
}