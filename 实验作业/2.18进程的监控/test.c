#include <unistd.h> 
#include <assert.h> 
#include <sys/mman.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <string.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/ptrace.h> 
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/syscall.h>
#include <sys/user.h>
void mmapcopy(int src_fd, size_t src_len, int dst_fd); 
int main(int argc, char *argv[]) 
{ 
if (argc != 3) { 
printf("Usage: %s<src_file><dst_file>\n", argv[0]); 
return -1; 
}

//文件复制模块
int src_fd ; 
int dst_fd; 
if ((src_fd = open(argv[1], O_RDONLY)) < 0){ 
printf("file1 open failed！\n"); 
return -1; 
}        
if ((dst_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0) { 
printf("file2 open failed! \n"); 
return -1; 
} 
struct stat stat; 
fstat(src_fd, &stat); // 获取文件信息 
truncate(argv[2], stat.st_size); // 设置文件大小 
mmapcopy(src_fd, stat.st_size, dst_fd); 
Close(src_fd); 
close(dst_fd); 
return 0; 
} 

    
void mmapcopy(int src_fd, size_t src_len, int dst_fd) 
{ 
void *src_ptr, *dst_ptr; 
src_ptr = mmap(NULL, src_len, PROT_READ, MAP_PRIVATE, src_fd, 0); 
dst_ptr = mmap(NULL, src_len, PROT_WRITE | PROT_READ, MAP_SHARED, dst_fd, 0); 
if (dst_ptr == MAP_FAILED) { 
printf("mmap error: %s\n", strerror(errno)); 
return ; 
}    
memcpy(dst_ptr, src_ptr, src_len); // 实现拷贝 
munmap(src_ptr, src_len); 
munmap(dst_ptr, src_len); 
} 