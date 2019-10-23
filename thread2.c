#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define MUTEX_ENABLE 1

	pthread_t thread_object[2];	//스레드 1,2
	int ready =0;			//입력 받았는지 상태
	pthread_mutex_t lockinput;	//buffer와 ready를 보호
	char buffer[201];		//gets 입력받는 버퍼

void *dosomething(void *arg)
{
	#if MUTEX_ENABLE
	pthread_mutex_lock(&lockinput);
	#endif

	unsigned long i = 0;
	while(1)
	{
        	if(ready == 0)
		{
			printf("Thread 1 :$ ");
			gets(buffer);
			printf("--> Thread 2 : Output [%s]\n", buffer);	
		
		}
		else if(ready != 0)
		{
			pthread_mutex_unlock(&lockinput);
	
		}
	}
	usleep(1);
	#if MUTEX_ENABLE
	pthread_mutex_unlock(&lockinput);
	#endif
}
int main(void)
{
        int i;
        int err;
        if (pthread_mutex_init(&lockinput, NULL) != 0) /*mutex 객체 초기화를 실패했을시(성공하면 0이 반환되므로)*/
        {
                printf ("\n Mutex Init Failed!!\n");
                return 1;
        }
        while(i<2)
        {
                err = pthread_create(&(thread_object[i]), NULL, &dosomething, NULL);	/*생성된 스레드 구분자, NULL, 스레드가 수행할 함수의 포인터(함수 포인터), NULL)*/
                if (err != 0)           /*err에 0이아닌 숫자가 들어간다면*/
                        printf ("Thread Create Error: [%d]\n", err);    /*에러 출력*/
		i++; //증가
        }
        pthread_join(thread_object[0], NULL);     /*tid[0] 종료시까지 기다림*/
        pthread_join(thread_object[1], NULL);     /*tid[1] 종료시까지 기다림*/
        return 0;       /*0을 반환*/
}

	





