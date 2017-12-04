#include "ucode.c"

int pipec;
char *pipev[32];


int pipetoken(char *cmd)
{
  char *cp;
  cp = cmd;
  pipec = 0;
  
  while (*cp != 0){
       while (*cp == '|' || *cp == ' ') *cp++ = 0;        
       if (*cp != 0)
           pipev[pipec++] = cp;         
       while (*cp != '|' && *cp != 0) cp++;                  
       if (*cp != 0)   
           *cp = 0;                   
       else 
            break; 
       cp++;
  }
  pipev[pipec] = 0;
}

void showpipe()
{
  int i;
  printf("pipec=%d\n\r", pipec);
  for (i=0; i<pipec; i++)
    printf("    1%s1\n\r", pipev[i]);
  prints("\n");
}

int mstrncmp(char *s1, char *s2, int n)
{
    int count = 0;

    while(*s1 == *s2 && *s1 && *s2 && n)
    {
        s1++; s2++; n--;
    }

    if(!n)
        return 1;
    return 0;
}

int run(int pipec, char *pipev[], int *pd)
{
    int pid;
    int newpd[2];

    printf("    PIPEC=%d PIPEV=%s PD=%d\n", pipec, pipev[pipec - 1], pd);
    if(pd)
    {
        printf("    %s IS GOING TO WRITE\n", pipev[pipec - 1]);
        close(pd[0]); dup2(pd[1], 1);
    }

    if(pipec > 1) // work for first cmd in pipe
    {
        printf("    STILL NEED TO PIPE\n\r");
        pipe(newpd);
		
		if(pid = fork())
		{
            printf("    %s IS GOING TO READ\n", pipev[pipec - 1]);
            close(newpd[1]); dup2(newpd[0], 0);
			exec(pipev[pipec - 1]);
			exit(1);
		}
		
		else
		{
            run(pipec - 1, pipev, newpd);
			exit(1);
		}
    }

    else
    {
        printf("    NO NEED TO PIPE\n\r");
        exec(pipev[pipec - 1]);
        exit(1);
    }
} 

main()
{
    int pid, status;
    char cmd[256];

    
    while(1)
    {
        printf("cf: ");
        if(!gets(cmd))
            exit(1);

        pipetoken(cmd);
        //showpipe();

        if(mstrncmp(cmd, "cd", 2))
        {
            token(cmd);
            chdir(argv[1]);
            continue;
        }

        if(pid = fork())
		{
            pid = wait(&status);
        }
		else
		{
            run(pipec, pipev, 0);
            printf("cf: ");
        }
    }
}