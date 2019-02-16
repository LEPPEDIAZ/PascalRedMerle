#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<wait.h>
int main(void)
{
        pid_t pid;
        int r;
        char buf[1024];
        char cp[50];
        char ans;
        int readpipe[2];
        int writepipe[2];
        long int a;
        int b;
        a=pipe(readpipe);
        b=pipe(writepipe);

        if (a == -1) { perror("pipe"); exit(EXIT_FAILURE); }
        if (b == -1) { perror("pipe"); exit(EXIT_FAILURE); }
       
        scanf("%[^\n]%*c",&ans);
        fflush(stdin);
        pid=fork();
        if(pid==-1)
        {
                printf("pid:main");
                exit(1);
        }
        while(1)
        {
                if(pid==0)
                { 
             
                         if(ans=='n')
                        {
                             
                                kill(pid,SIGKILL);
                        }

                        close(readpipe[1]);
                        close(writepipe[0]);
                        if(read(readpipe[0],buf,sizeof(buf)) < 0)
                        {
                            break;
                        }
                        printf("\nCreated new shared mem obj: %s\n",buf);
                        printf("\n(child)a: \t");
                        fflush(stdin);
                        fgets(cp, 50, stdin);
                        printf("\n(Parent)b: %s",cp);
                        if(/*!strncmp("Q",cp,1) || */write(writepipe[1],cp,strlen(cp)+1) < 0)
                        {
                            break;
                        }
                        

                }
                else
                {
                        close(readpipe[0]);
                        close(writepipe[1]);
                        printf("\n(Parent)b:  \t");
                        fgets(cp, 50, stdin);
                        printf("\nshared memory has: %s",cp);
                        if(/*!strncmp("Q",cp,1) ||*/ write(readpipe[1],cp,strlen(cp)+1) < 0)
                        {
                            break;
                        }        

                        if(read(writepipe[0],buf,sizeof(buf)) < 0)
                        {
                            break;
                        }
                        printf("\n (parent)a: %s\n",buf);
                     
                        fflush(stdin);
                        scanf(" %[^\n]%*c",&ans);
                        if(ans=='n')
                        {
                                kill(pid,SIGKILL);
                        }
                }


        }
        close(readpipe[1]);
        close(writepipe[0]);
        close(readpipe[0]);
        close(writepipe[1]);
        return 0;
}
