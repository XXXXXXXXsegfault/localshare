asm ".entry"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "call @__init"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int WSAStartup(int ver,void *wsadata);
asm "@WSAStartup"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "sub $16,%rsp"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"ws2_32.dll\" \"WSAStartup\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int WSACleanup(void);
asm "@WSACleanup"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "sub $32,%rsp"
asm ".dllcall \"ws2_32.dll\" \"WSACleanup\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int __getmainargs(int *argc,char ***argv);
asm "@__getmainargs"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "pushq $0"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "xor %r8d,%r8d"
asm "mov $1,%r9d"
asm "push %r8"
asm "lea 8(%rsp),%r8"
asm "push %r8"
asm "push %r9"
asm "lea 16(%rsp),%r8"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"__getmainargs\""
asm "add $48,%rsp"
asm "add $256,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int _main(int argc,char **argv,void *hInstance);
asm "@_main"
asm "jmp @main"
void exit(int code);
asm "@exit"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $8,%rsp"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"exit\""
asm "add $16,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int __init(void)
{
	int argc;
	char **argv;
	int ret;
	unsigned char buf[1024];
	if(WSAStartup(0x1,buf))
	{
		return -1;
	}
	if(__getmainargs(&argc,&argv))
	{
		return -1;
	}
	ret=_main(argc,argv,(void *)0x400000);
	WSACleanup();
	exit(ret);
}
void puts(char *str);
asm "@puts"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rdx"
asm "mov $@__puts__format,%rcx"
asm "push %r9"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"printf\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
asm "@__puts__format"
asm ".string \"%s\""
void *malloc(unsigned long size);
asm "@malloc"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $24,%rsp"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"malloc\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
void free(void *ptr);
asm "@free"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $24,%rsp"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"free\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int getch(void);
asm "@getch"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "sub $32,%rsp"
asm ".dllcall \"msvcrt.dll\" \"_getch\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int getchar(void);
asm "@getchar"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "sub $32,%rsp"
asm ".dllcall \"msvcrt.dll\" \"getchar\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int putchar(void *fp);
asm "@putchar"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $24,%rsp"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"putchar\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
void *fopen(char *name,char *mode);
asm "@fopen"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "sub $16,%rsp"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"fopen\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int fclose(void *fp);
asm "@fclose"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $24,%rsp"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"fclose\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int fread(void *buf,int size,int count,void *fp);
asm "@fread"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "mov 32(%rbp),%r8"
asm "mov 40(%rbp),%r9"
asm "push %r9"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"fread\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
void *FindFirstFileA(char *name,void *data);
asm "@FindFirstFileA"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "sub $16,%rsp"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"kernel32.dll\" \"FindFirstFileA\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int FindNextFileA(void *dh,void *data);
asm "@FindNextFileA"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "sub $16,%rsp"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"kernel32.dll\" \"FindNextFileA\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int FindClose(void *dh);
asm "@FindClose"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $24,%rsp"
asm "push %rcx"
asm ".dllcall \"kernel32.dll\" \"FindClose\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
void *socket(int family,int type,int proto);
asm "@socket"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "mov 32(%rbp),%r8"
asm "sub $8,%rsp"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"ws2_32.dll\" \"socket\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int bind(void *sock,void *addr,int addr_size);
asm "@bind"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "mov 32(%rbp),%r8"
asm "sub $8,%rsp"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"ws2_32.dll\" \"bind\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int listen(void *sock,int bl);
asm "@listen"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "sub $16,%rsp"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"ws2_32.dll\" \"listen\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
void *accept(void *sock,void *addr,void *addr_size);
asm "@accept"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "mov 32(%rbp),%r8"
asm "sub $8,%rsp"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"ws2_32.dll\" \"accept\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int send(void *sock,void *buf,int size,int flags);
asm "@send"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "mov 32(%rbp),%r8"
asm "mov 40(%rbp),%r9"
asm "push %r9"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"ws2_32.dll\" \"send\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int recv(void *sock,void *buf,int size,int flags);
asm "@recv"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "mov 32(%rbp),%r8"
asm "mov 40(%rbp),%r9"
asm "push %r9"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"ws2_32.dll\" \"recv\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int closesocket(void *sock);
asm "@closesocket"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $24,%rsp"
asm "push %rcx"
asm ".dllcall \"ws2_32.dll\" \"closesocket\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
void *CreateThread(void *sattr,long stack_size,void *fun,void *param,int flags,void *id);
asm "@CreateThread"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "mov 32(%rbp),%r8"
asm "mov 40(%rbp),%r9"
asm "pushq 56(%rbp)"
asm "pushq 48(%rbp)"
asm "push %r9"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"kernel32.dll\" \"CreateThread\""
asm "add $48,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int CloseHandle(void *h);
asm "@CloseHandle"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $24,%rsp"
asm "push %rcx"
asm ".dllcall \"kernel32.dll\" \"CloseHandle\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
long clock(void);
asm "@clock"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "sub $32,%rsp"
asm ".dllcall \"msvcrt.dll\" \"clock\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
int select(int nfds,void *rfds,void *wfds,void *efds,void *timeout);
asm "@select"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "mov 32(%rbp),%r8"
asm "mov 40(%rbp),%r9"
asm "sub $8,%rsp"
asm "pushq 48(%rbp)"
asm "push %r9"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"ws2_32.dll\" \"select\""
asm "add $48,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
void *fseek(void *fp,long off,int w);
asm "@fseek"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "mov 24(%rbp),%rdx"
asm "mov 32(%rbp),%r8"
asm "sub $8,%rsp"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"fseek\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
long ftell(void *fp);
asm "@ftell"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $24,%rsp"
asm "push %rcx"
asm ".dllcall \"msvcrt.dll\" \"ftell\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"
void Sleep(int msec);
asm "@Sleep"
asm "push %rbp"
asm "mov %rsp,%rbp"
asm "and $0xf0,%spl"
asm "push %r8"
asm "push %r9"
asm "push %r10"
asm "push %r11"
asm "mov 16(%rbp),%rcx"
asm "sub $24,%rsp"
asm "push %rcx"
asm ".dllcall \"kernel32.dll\" \"Sleep\""
asm "add $32,%rsp"
asm "pop %r11"
asm "pop %r10"
asm "pop %r9"
asm "pop %r8"
asm "mov %rbp,%rsp"
asm "pop %rbp"
asm "ret"