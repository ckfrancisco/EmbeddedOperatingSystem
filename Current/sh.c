#include "ucode.c"

int pipec;
char *pipev[32];

int rdirc;
char *rdirv[32];


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

int rdirtoken(char *cmd)
{
  char *cp;
  cp = cmd;
  rdirc = 0;
  
  while (*cp != 0){
       while (*cp == ' ') *cp++ = 0;        
       if (*cp != 0)
           rdirv[rdirc++] = cp;         
       while (*cp != ' ' && *cp != 0) cp++;                  
       if (*cp != 0)   
           *cp = 0;                   
       else 
            break; 
       cp++;
  }
  rdirv[rdirc] = 0;
}

void showpipe()
{
  int i;
  printf("pipec=%d\n\r", pipec);
  for (i=0; i<pipec; i++)
    printf("    %s\n\r", pipev[i]);
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

int mstrcpy(char *dst, char *src)
{
    while(*dst++ = *src++);
}

int checkredirect(char *cmd)
{
    int i, fdi, fdo;
    char buf[32], *cp;

    mstrcpy(buf, cmd);
    // printf("    REDIRECT %s\n\r", buf);
    rdirtoken(buf);

    i = 0;
    while(i < rdirc)
    {
        // printf("    BUF %d %s\n\r", i, rdirv[i]);
        i++;
    }

    i = 0;
    while(i < rdirc)
    {
        // printf("    LOOP %d %s\n\r", i, rdirv[i]);

        if(mstrncmp(rdirv[i], ">>", 2))
        {
            i++;
            if(i < rdirc)
            {
                fdo = open(rdirv[i], O_WRONLY | O_APPEND | O_CREAT);
                if(fdo < 0)
                {
                    // printf("Error: %s does not exist\n\r", rdirv[i]);
                    exit(0);
                }

                // printf("        DUP2 APPEND %s\n\r", i, argv[i]);
                dup2(fdo, 1);
            }
        }

        else if(mstrncmp(rdirv[i], ">", 1))
        {
            i++;
            if(i < rdirc)
            {
                fdo = open(rdirv[i], O_WRONLY | O_CREAT | O_TRUNC);
                if(fdo < 0)
                {
                    // printf("Error: %s does not exist\n\r", rdirv[i]);
                    exit(0);
                }

                // printf("        DUP2 WRITE %s\n\r", i, argv[i]);
                dup2(fdo, 1);
            }
        }

        else if(mstrncmp(rdirv[i], "<", 1))
        {
            i++;
            if(i < rdirc)
            {
                fdi = open(rdirv[i], O_RDONLY);
                if(fdi < 0)
                {
                    // printf("Error: %s does not exist\n\r", rdirv[i]);
                    exit(0);
                }

                // printf("        DUP2 READ %s\n\r", i, argv[i]);
                dup2(fdi, 0);
            }
        }

        i++;
    }

    // printf("    CHECKED REDIRECT\n\r");

    cp = cmd;
    while(*cp)
    {
        if(*cp == '>' || *cp == '<')
        {
            *cp = 0;
            break;
        }
        cp++;
    }

    // printf("    RUNNING %s\n\r", cmd);
    exec(cmd);
}

int checkpipe(int pipec, char *pipev[], int *pd)
{
    int pid;
    int newpd[2];

    // printf("    PIPEC=%d PIPEV=%s PD=%d\n", pipec, pipev[pipec - 1], pd);
    if(pd)
    {
        // printf("    %s IS GOING TO WRITE\n", pipev[pipec - 1]);
        close(pd[0]); dup2(pd[1], 1);
    }

    if(pipec > 1) // work for first cmd in pipe
    {
        // printf("    STILL NEED TO PIPE\n\r");
        pipe(newpd);
		
		if(pid = fork())
		{
            // printf("    %s IS GOING TO READ\n", pipev[pipec - 1]);
            close(newpd[1]); dup2(newpd[0], 0);
			checkredirect(pipev[pipec - 1]);
			exit(1);
		}
		
		else
		{
            checkpipe(pipec - 1, pipev, newpd);
			exit(1);
		}
    }

    else
    {
        // printf("    NO NEED TO PIPE\n\r");
        checkredirect(pipev[pipec - 1]);
        exit(1);
    }
} 

main()
{
    int pid, status;
    char cmd[256];

    signal(2, &main);
    
    while(1)
    {
        printf("cf: ");
        if(!gets(cmd) || cmd[0] == 0)
            continue;

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
            checkpipe(pipec, pipev, 0);
        }
    }
}