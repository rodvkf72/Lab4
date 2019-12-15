#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUFSIZE 100

void * clnt_connection(void *arg);
void send_message(char * message, int len);
void error_handling(char *message);

int clnt_number = 0;        
int clnt_socks[10];        

pthread_mutex_t     mutx;   // mutex 동기화 하기 위한 mutex선언


int main(int argc, char *argv[])
{
    int     serv_sock;                  
    int     clnt_sock;                  
    struct  sockaddr_in     serv_addr;  
    struct  sockaddr_in     clnt_addr;  
    int     clnt_addr_size;             
    pthread_t   thread;              
    void     *thread_rtn;

    // port번호 인자값 확인
    if(argc!=2){
        printf("Usage : %s <port> \n", argv[0]); exit(1);
    }

    // mutex 초기화
    if(pthread_mutex_init(&mutx, NULL))
        error_handling("pthread_mutex_init() error");

    // server socket handle 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    // server socket address 설정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons((unsigned short)atoi(argv[1]));

    // server socket handle에  server address 정보 bind
    if(bind(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    // server socket handle의 연결 대기 상태로 변경
    if(listen(serv_sock, 10) == -1)
        error_handling("listen() error");

    while(1){
        clnt_addr_size = sizeof(clnt_addr);
        // 연결을 수락하여 client socket handle을 생성
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

        pthread_mutex_lock(&mutx);
        // 연결되어 생성된 client handle을 client handle소켓 배열에 저장
        clnt_socks[clnt_number++]=clnt_sock;
        pthread_mutex_unlock(&mutx);

        // 연결된 client 소켓의 handle을 clnt_connection함수 호출 시 인자로 넘겨주어 thread를 생성
        pthread_create(&thread, NULL, clnt_connection, (void *)clnt_sock);
        printf("New client connected, IP: %s \n", inet_ntoa(clnt_addr.sin_addr));
    }

    pthread_join(thread, &thread_rtn);
    
    // mutex를 해제
    pthread_mutex_destroy(&mutx);
    return EXIT_SUCCESS;
}

void * clnt_connection(void * arg)
{
    int clnt_sock = (int)arg;   
    int str_len = 0;           
    char message[BUFSIZE];      
    int i;

    // client로 부터 메시지 수신
    while( (str_len=read(clnt_sock, message, sizeof(message))) != 0)
        send_message(message, str_len);  // 수신된 메시지를 모든 클라이언트에 전송

    // 전역으로 선언된 변수가 임계영역으로 다른 thread의 영향을 받으므로 mutex lock
    pthread_mutex_lock(&mutx);
    for(i=0; i<clnt_number; i++){

        if(clnt_sock == clnt_socks[i]){
            for( ; i<clnt_number-1; i++)    
                clnt_socks[i]=clnt_socks[i+1];
            break;
        }
    }
    clnt_number--;
    // mutex unlock으로 해제
    pthread_mutex_unlock(&mutx);

    close(clnt_sock);
    return 0;
}

// 현재 연결되어 있는 모든 client에게 메시지 전송
void send_message(char * message, int len)
{
    int i;

    pthread_mutex_lock(&mutx);
    for(i=0; i<clnt_number; i++)
        // 모든 client에게 같은 메시지를 전송한다.
        write(clnt_socks[i], message, len);
    pthread_mutex_unlock(&mutx);
}

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
