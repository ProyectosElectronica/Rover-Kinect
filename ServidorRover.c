/*
 Este código ha modificado a partir del código desarrollado por Oscar Sanchez en este enlace:
 https://github.com/labcoder/simple-webserver
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/syscall.h>


#define BUFSIZE 8096
#define ERROR 42
#define SORRY 43
#define LOG   44

struct {
	char *ext;
	char *filetype;
} extensions [] = {
	{"gif", "image/gif" },  
	{"jpg", "image/jpeg"}, 
	{"jpeg","image/jpeg"},
	{"png", "image/png" },  
	{"zip", "image/zip" },  
	{"gz",  "image/gz"  },  
	{"tar", "image/tar" },  
	{"htm", "text/html" },  
	{"html","text/html" },  
	{"php", "image/php" },  
	{"cgi", "text/cgi"  },  
	{"asp","text/asp"   },  
	{"jsp", "image/jsp" },  
	{"xml", "text/xml"  },
	{"txt", "text/txt"  },  
	{"js","text/js"     },
   {"css","test/css"   }, 

	{0,0} };

void log(int type, char *s1, char *s2, int num)
{
	int fd ;
	char logbuffer[BUFSIZE*2];

	switch (type) {
	case ERROR: (void)sprintf(logbuffer,"ERROR: %s:%s Errno=%d exiting pid=%d",s1, s2, errno,getpid()); break;
	case SORRY: 
		(void)sprintf(logbuffer, "<HTML><BODY><H1>Web Server Sorry: %s %s</H1></BODY></HTML>\r\n", s1, s2);
		(void)write(num,logbuffer,strlen(logbuffer));
		(void)sprintf(logbuffer,"SORRY: %s:%s",s1, s2); 
		break;
	case LOG: (void)sprintf(logbuffer," INFO: %s:%s:%d",s1, s2,num); break;
	}	
	
	if((fd = open("server.log", O_CREAT| O_WRONLY | O_APPEND,0644)) >= 0) {
		(void)write(fd,logbuffer,strlen(logbuffer)); 
		(void)write(fd,"\n",1);      
		(void)close(fd);
	}
	if(type == ERROR || type == SORRY) exit(3);
}

void getID(){
	
}

void web(int fd, int hit)
{
	int j, file_fd, buflen, len;
	long i, ret;
	char * fstr;
	static char buffer[BUFSIZE+1];

	ret =read(fd,buffer,BUFSIZE); 
	if(ret == 0 || ret == -1) {
		log(SORRY,"failed to read browser request","",fd);
	}
	if(ret > 0 && ret < BUFSIZE)	
		buffer[ret]=0;	
	else buffer[0]=0;

	for(i=0;i<ret;i++)	
		if(buffer[i] == '\r' || buffer[i] == '\n')
			buffer[i]='*';
	log(LOG,"request",buffer,hit);

	if( strncmp(buffer,"GET ",4) && strncmp(buffer,"get ",4) )
		log(SORRY,"Only simple GET operation supported",buffer,fd);

	for(i=4;i<BUFSIZE;i++) { 
		if(buffer[i] == ' ') { 
			buffer[i] = 0;
			break;
		}
	}

	for(j=0;j<i-1;j++) 	
		if(buffer[j] == '.' && buffer[j+1] == '.')
			log(SORRY,"Parent directory (..) path names not supported",buffer,fd);

	if( !strncmp(&buffer[0],"GET /\0",6) || !strncmp(&buffer[0],"get /\0",6) ) 
		(void)strcpy(buffer,"GET /index.html");

	buflen=strlen(buffer);
	fstr = (char *)0;
	for(i=0;extensions[i].ext != 0;i++) {
		len = strlen(extensions[i].ext);
		if( !strncmp(&buffer[buflen-len], extensions[i].ext, len)) {
			fstr =extensions[i].filetype;
			break;
		}
	}

	

	if(fstr == 0) log(SORRY,"file extension type not supported",buffer,fd);

	if(( file_fd = open(&buffer[5],O_RDONLY)) == -1) 
		log(SORRY, "failed to open file",&buffer[5],fd);

	log(LOG,"SEND",&buffer[5],hit);

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////		Movimientos            ///////////////////////////////////

	if( (strncmp(buffer,"GET /rover/ade.txt",strlen(buffer)) && strncmp(buffer,"get /rover/ade.txt",strlen(buffer))) == 0 ){
		FILE *file = fopen("/home/pi/ProyectoFinalEmbebidos/Proyecto_final/rover/accion.txt", "w");
		if(file != NULL){
				
			fwrite("1010" , 1, 4 , file );      
			fclose(file);
		}
		
	}
	if( (strncmp(buffer,"GET /rover/atr.txt",strlen(buffer)) && strncmp(buffer,"get /rover/atr.txt",strlen(buffer))) == 0 ){
		FILE *file = fopen("/home/pi/ProyectoFinalEmbebidos/Proyecto_final/rover/accion.txt", "w");
		if(file != NULL){
				
			fwrite("0101" , 1, 4 , file );      
			fclose(file);
		}
		
		
	}
	if( (strncmp(buffer,"GET /rover/izq.txt",strlen(buffer)) && strncmp(buffer,"get /rover/izq.txt",strlen(buffer))) == 0 ){

		FILE *file = fopen("/home/pi/ProyectoFinalEmbebidos/Proyecto_final/rover/accion.txt", "w");
		if(file != NULL){
					
			fwrite("1110" , 1, 4 , file );      
			fclose(file);
		}
		
		
	}
	if( (strncmp(buffer,"GET /rover/der.txt",strlen(buffer)) && strncmp(buffer,"get /rover/der.txt",strlen(buffer))) == 0 ){
		
		FILE *file = fopen("/home/pi/ProyectoFinalEmbebidos/Proyecto_final/rover/accion.txt", "w");
		if(file != NULL){
		
			fwrite("1011" , 1, 4 , file );      
			fclose(file);
		}
		
	}
	if( (strncmp(buffer,"GET /rover/freno.txt",strlen(buffer)) && strncmp(buffer,"get /rover/freno.txt",strlen(buffer))) == 0 ){
		
		FILE *file = fopen("/home/pi/ProyectoFinalEmbebidos/Proyecto_final/rover/accion.txt", "w");
		if(file != NULL){
		
			fwrite("0000" , 1, 4 , file );      
			fclose(file);
		}
		
	}
///////////////////////////////////////////////////Override//////////////////
	if( (strncmp(buffer,"GET /rover/overrideon.txt",strlen(buffer)) && strncmp(buffer,"get /rover/override.txt",strlen(buffer))) == 0 ){
		///MODO MANUAL ACTIVADO
		FILE *file = fopen("/home/pi/ProyectoFinalEmbebidos/Proyecto_final/rover/override.txt", "w");
		if(file != NULL){
		
			fwrite("0" , 1, 1 , file );      
			fclose(file);
		}
		
	}
if( (strncmp(buffer,"GET /rover/overrideoff.txt",strlen(buffer)) && strncmp(buffer,"get /rover/override.txt",strlen(buffer))) == 0 ){
		//MODO AUTONOMO ACTIVADO
		FILE *file = fopen("/home/pi/ProyectoFinalEmbebidos/Proyecto_final/rover/override.txt", "w");
		if(file != NULL){
		
			fwrite("1" , 1, 1 , file );      
			fclose(file);
		}
		
	}
	




	(void)sprintf(buffer,"HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", fstr);
	(void)write(fd,buffer,strlen(buffer));

	while (	(ret = read(file_fd, buffer, BUFSIZE)) > 0 ) {
		(void)write(fd,buffer,ret);
	}
#ifdef LINUX
	sleep(1);
#endif
	exit(1);
}


int main(int argc, char **argv)
{

FILE *file = fopen("/home/pi/ProyectoFinalEmbebidos/Proyecto_final/rover/override.txt", "w");
		if(file != NULL){
		
			fwrite("0" , 1, 1 , file );      
			fclose(file);
		}
	int i, port, pid, listenfd, socketfd, hit;
	size_t length;
	static struct sockaddr_in cli_addr; 
	static struct sockaddr_in serv_addr;

	if(fork() != 0)
		return 0; 
	(void)signal(SIGCLD, SIG_IGN); 
	(void)signal(SIGHUP, SIG_IGN); 
	for(i=0;i<32;i++)
		(void)close(i);	
	(void)setpgrp();	

	log(LOG,"http server starting",argv[1],getpid());

	if((listenfd = socket(AF_INET, SOCK_STREAM,0)) <0)
		log(ERROR, "system call","socket",0);
	port = atoi(argv[1]);
	if(port < 0 || port >60000)
		log(ERROR,"Invalid port number try [1,60000]",argv[1],0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);
	if(bind(listenfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0)
		log(ERROR,"system call","bind",0);
	if( listen(listenfd,64) <0)
		log(ERROR,"system call","listen",0);

	for(hit=1; ;hit++) {
		length = sizeof(cli_addr);
		if((socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length)) < 0)
			log(ERROR,"system call","accept",0);

		if((pid = fork()) < 0) {
			log(ERROR,"system call","fork",0);
		}
		else {
			if(pid == 0) {
				(void)close(listenfd);
				web(socketfd,hit);
			} else {
				(void)close(socketfd);
			}
		}
	}
}
