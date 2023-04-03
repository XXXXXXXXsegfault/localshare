char *gen_page_404(void)
{
	char *src;
	src="HTTP/1.1 404 File Not Exist\r\n\
Connection: close\r\n\
Content-Type: text/html\r\n\
Content-Length: 111\r\n\
\r\n\
<html>\n\
<head>\n\
<title> 404 File Not Exist </title>\n\
</head>\n\
<body>\n\
<h1> 404 File Not Exist </h1>\n\
</body>\n\
</html>\n";
	char *page;
	page=malloc(strlen(src)+1);
	if(page==NULL)
	{
		return NULL;
	}
	strcpy(page,src);
	return page;
}
char *gen_page_redirect(char *req,int *status)
{
	*status=0;
	char *path,*path2,*old_path,*new_path,*tmp;
	char *page;
	char buf[260];
	int x1,x2,x;
	path=malloc(strlen(req)+256);
	if(path==NULL)
	{
		*status=1;
		return NULL;
	}
	path2=malloc(strlen(req)+256);
	if(path2==NULL)
	{
		free(path);
		*status=1;
		return NULL;
	}
	strcpy(path,req);
	old_path=path;
	new_path=path2;
	do
	{
		x1=0;
		x=0;
		new_path[0]=0;
		while(old_path[x1])
		{
			while(old_path[x1]=='/')
			{
				++x1;
			}
			if(!old_path[x1])
			{
				break;
			}
			x2=x1;
			while(old_path[x1]&&old_path[x1]!='/')
			{
				++x1;
			}
			if(x1-x2>255)
			{
				free(path);
				free(path2);
				*status=1;
				return NULL;
			}
			memcpy(buf,old_path+x2,x1-x2);
			buf[x1-x2]=0;
			if(!strcmp(buf,".."))
			{
				while(x>0&&new_path[x]!='/')
				{
					--x;
				}
				new_path[x]=0;
			}
			else if(strcmp(buf,"."))
			{
				strcat(new_path,"/");
				strcat(new_path,buf);
				x=strlen(new_path);
			}
		}
		if(new_path[0]==0)
		{
			new_path[0]='/';
			new_path[1]=0;
		}
		tmp=old_path;
		old_path=new_path;
		new_path=tmp;
	}
	while(strcmp(old_path,new_path));
	free(old_path);
	if(!strcmp(new_path,req))
	{
		free(new_path);
		return NULL;
	}
	page=malloc(strlen(new_path)+1024);
	if(page==NULL)
	{
		free(new_path);
		*status=1;
		return NULL;
	}
	strcpy(page,"HTTP/1.1 301 Redirect\r\n\
Location: ");
	strcat(page,new_path);
	strcat(page,"\r\nConnection: close\r\n\r\n");
	return page;
}
struct files_list
{
	char name[256];
	long is_directory;
	struct files_list *next;
};
int check_file_name(char *str)
{
	int c,x;
	x=0;
	while(c=*str)
	{
		if(!(c>='0'&&c<='9'||c>='A'&&c<='Z'||c>='a'&&c<='z'||c=='/'||c=='_'||c=='.'||c=='-'))
		{
			return 0;
		}
		++str;
		++x;
		if(x>255)
		{
			return 0;
		}
	}
	return 1;
}
char *gen_file_page(char *req,int *status,unsigned long *len,void **fp)
{
	*status=0;
	char *file_path;
	char *page,*page_head;
	file_path=malloc(strlen(req)+strlen(server_root)+256);
	if(file_path==NULL)
	{
		return NULL;
	}
	strcpy(file_path,server_root);
	strcat(file_path,req);
	page=NULL;
	if(is_folder(file_path))
	{
		void *fh;
		struct win32_find_data_a fd;
		struct files_list *head,*node,*p,*pp;
		int page_size,file_path_len;
		file_path_len=strlen(req);
		strcat(file_path,"/*");
		fh=FindFirstFileA(file_path,&fd);
		if(fh==INVALID_HANDLE_VALUE)
		{
			*status=1;
			free(file_path);
			return NULL;
		}
		head=NULL;
		page_size=512+2*strlen(req);
		do
		{
			if(check_file_name(fd.name))
			{
				node=malloc(sizeof(*node));
				if(node==NULL)
				{
					while((p=head)!=NULL)
					{
						head=p->next;
						free(p);
					}
					FindClose(fh);
					free(file_path);
					return NULL;
				}
				strcpy(node->name,fd.name);
				node->is_directory=0;
				if(fd.attr&FILE_ATTRIBUTE_DIRECTORY)
				{
					node->is_directory=1;
				}
				pp=NULL;
				p=head;
				while(p!=NULL)
				{
					if(strcmp(p->name,node->name)>0)
					{
						break;
					}
					pp=p;
					p=p->next;
				}
				if(pp==NULL)
				{
					head=node;
				}
				else
				{
					pp->next=node;
				}
				node->next=p;
				page_size+=strlen(node->name)*2+64+file_path_len;
			}
		}
		while(FindNextFileA(fh,&fd));
		FindClose(fh);
		page=malloc(page_size);
		if(page==NULL)
		{
			while((p=head)!=NULL)
			{
				head=p->next;
				free(p);
			}
			free(file_path);
			return NULL;
		}
		strcpy(page,"<html>\n<head>\n<title> [LocalShare] ");
		strcat(page,req);
		strcat(page," </title>\n</head>\n<body>\n<h1> [LocalShare] ");
		strcat(page,req);
		strcat(page," </h1>\n");
		while((p=head)!=NULL)
		{
			int x;
			strcat(page,"<p> ");
			if(p->is_directory)
			{
				strcat(page,"[DIR] ");
			}
			else
			{
				strcat(page,"      ");
			}
			strcat(page,"<a href=\'");
			/*
			if(req[0]!='/')
			{
				strcat(page,"/");
			}
			*/
			x=strlen(req);
			while(x)
			{
				--x;
				if(req[x]=='/')
				{
					++x;
					break;
				}
			}
			strcat(page,req+x);
			strcat(page,"/");
			strcat(page,p->name);
			strcat(page,"\'> ");
			strcat(page,p->name);
			strcat(page," </a>");
			head=p->next;
			free(p);
			strcat(page," </p>\n");
		}
		strcat(page,"</body>\n");
		strcat(page,"</html>\n");
		page_head=malloc(512+strlen(page));
		if(page_head==NULL)
		{
			free(page);
			free(file_path);
			return NULL;
		}
		strcpy(page_head,"HTTP/1.1 200 OK\r\n\
Connection: close\r\n\
Content-Type: text/html\r\n\
Content-Length: ");
		sprinti(page_head,strlen(page),1);
		strcat(page_head,"\r\n\r\n");
		strcat(page_head,page);
		free(page);
		page=page_head;
	}
	else
	{
		unsigned long file_size;
		page=malloc(512);
		if(page==NULL)
		{
			free(file_path);
			free(page);
			return NULL;
		}
		*fp=fopen(file_path,"rb");
		if(*fp==NULL)
		{
			*status=1;
			free(file_path);
			return NULL;
		}
		fseek(*fp,0,SEEK_END);
		file_size=ftell(*fp);
		fseek(*fp,0,SEEK_SET);
		strcpy(page,"HTTP/1.1 200 OK\r\n\
Connection: close\r\n\
Content-Type: unknown\r\n\
Content-Length: ");
		sprinti(page,file_size,1);
		strcat(page,"\r\n\r\n");
	}
	free(file_path);
	*len=strlen(page);
	return page;
}
char *gen_page(char *req,unsigned long *len,void **fp)
{
	char *page;
	int s;
	*fp=NULL;
	if(req==NULL)
	{
		page=gen_page_404();
		if(page==NULL)
		{
			return NULL;
		}
		*len=strlen(page);
		return page;
	}
	if(page=gen_page_redirect(req,&s))
	{
		*len=strlen(page);
		return page;
	}
	if(s==1)
	{
		return NULL;
	}
	else if(s==2)
	{
		page=gen_page_404();
		if(page==NULL)
		{
			return NULL;
		}
		*len=strlen(page);
		return page;
	}
	if(page=gen_file_page(req,&s,len,fp))
	{
		return page;
	}
	if(s==1)
	{
		page=gen_page_404();
		if(page==NULL)
		{
			return NULL;
		}
		*len=strlen(page);
		return page;
	}
	return NULL;
}
int T_service(void *csock)
{
	char *req,*page;
	unsigned long len,x,size;
	void *fp;
	char buf[2048];
	fp=NULL;
	req=read_http_request(csock);
	page=gen_page(req,&len,&fp);
	free(req);
	if(page!=NULL)
	{
		x=0;
		while(x<len)
		{
			if(x+16384>len)
			{
				size=len-x;
			}
			else
			{
				size=16384;
			}
			if(sock_write2(csock,page+x,size))
			{
				break;
			}
			x+=size;
		}
		free(page);
		if(fp)
		{
			while((size=fread(buf,1,2048,fp))>0)
			{
				if(sock_write2(csock,buf,size))
				{
					break;
				}
			}
		}
	}
	else
	{
		page="HTTP/1.1 500 No Memory Available\r\n\
Connection: close\r\n\
Content-Type: text/html\r\n\
Content-Length: 121\r\n\
\r\n\
<html>\n\
<head>\n\
<title> 500 No Memory Avaliable </title>\n\
</head>\n\
<body>\n\
<h1> 500 No Memory Avaliable </h1>\n\
</body>\n\
</html>\n";
		sock_write2(csock,page,strlen(page));
	}
	if(fp)
	{
		fclose(fp);
	}
	Sleep(100);
	closesocket(csock);
	return 0;
}