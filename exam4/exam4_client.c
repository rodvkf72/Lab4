#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 100
#define NAMESIZE 50

void * send_message(void *arg);         
void * recv_message(void *arg);        
void   error_handling(char *message);   

char name[NAMESIZE] = "";   
char message[BUFSIZE];      

int main(int argc, char *argv[])
{
    int sock;                           // 접속할 서버 서켓 핸들
    struct sockaddr_in serv_addr;       // 접속할 서버 서켓의 주소 구조체
    pthread_t snd_thread, rcv_thread;   // 전송 thread ID, 수신할 thread ID 생성
    void *thread_result;                // thread 함수에서 반환되는 반환값 변수 선언

    // 입력 인자값 체크
    if(argc!=4){
        printf("Usage : %s <IP> <PORT> <name>\n", argv[0]);
        exit(1);
    }

    // 사용자명 복사
    strcpy(name, argv[3]);

    // 서버소켓 핸들 생성
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket() error");

    // 서버소켓 주소 구조체 초기화 및 설정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons((unsigned short)atoi(argv[2]));

    // 서버 주소구조체 정보를 사용하여 서버에 연결요청
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connet() error");

    // 메시지 전송 / 메시지 수신 thread 함수 호출과 함께 thread 생성
    pthread_create(&snd_thread, NULL, send_message, (void *)sock);
    pthread_create(&rcv_thread, NULL, recv_message, (void *)sock);

    // 메시지 전송 / 메시지 수신 thread가 끝났때 까지 대기함
    pthread_join(snd_thread, &thread_result);
    pthread_join(rcv_thread, &thread_result);

    //서버 소켓 종료
    close(sock);

    return EXIT_SUCCESS;
}

// 메시지 전송 thread 함수
void * send_message(void * arg)
{

    int sock = (int)arg;
    char name_message[NAMESIZE+BUFSIZE];

    // 전송할 메시지를 입력 반
    while(1){

        fgets(message, BUFSIZE, stdin);
        // 입력값이 "q\n"일 경우 thread함수를 빠져나와 실질적으로 main함수로 돌아감
        if(!strcmp(message, "q\n")){
            close(sock);
             exit(0);
        }
        // 입력한 메시지와 사용자 이름을 조합하여 전송할 메시지를 완성
        strcpy(name_message, "[");
        strcat(name_message, name);
        strcat(name_message, "] ");
        strcat(name_message, message);
        // 조합된 메시지를 전송
        write(sock, name_message, strlen(name_message));
    }
}

// 메시지 수신 thread 함수
void * recv_message(void * arg)
{
    int sock = (int)arg;
    char name_message[NAMESIZE+BUFSIZE];
    int str_len;    
    int rtn;        


    while(1){
        str_len = read(sock, name_message, NAMESIZE+BUFSIZE-1);
        // 메시지의 길이가 -1(연결종료)이면 thread함수를 빠져 나
        if(str_len==-1)
        {
            rtn = 1;    // thread함수의 반환 값을 1로 설정
            return (void *)rtn;
        }
        name_message[str_len] = 0;  // 수신된 메시지의 끝에 NULL종료문자를 지정
        fputs(name_message, stdout);    // 수신된 메시지를 출력
    }
}

// 에러 발생 처리 함수
void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
