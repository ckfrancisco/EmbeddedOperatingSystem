#include "ucode.c"

int substring(char *pattern, char *s)
{
    char *p = pattern;

    while(*s)
    {
        if(*s == *p)
        {
            while(*s++ && *p++)
            {
                if(*p == '\0')
                    return 1;
                
                if(*s != *p)
                    break;
            }

            p = pattern;
        }
        s++;
    }

    return 0;
}

main(int argc, char *argv[])
{
    int fd;
    char tty[16], buf[1024];
    STAT ttystat, instat;

    if(argc < 2)
        exit(0);
    if(argc > 2)
    {
        fd = open(argv[2], O_RDONLY);
        if(fd < 0)
        {
            printf("Error: %s does not exist\n\r", argv[2]);
            exit(0);
        }

        dup2(fd, 0); 
    }

    gettty(tty);
    stat(tty, &ttystat);
    fstat(0, &instat);
        
    if(ttystat.st_dev == instat.st_dev && ttystat.st_ino == instat.st_ino)
        while(gets(buf))
        {
            if(substring(argv[1], buf))
                printf("%s\n\r", buf);
        }

    else
        while(getline(buf))
        {
            if(substring(argv[1], buf))
                printf("%s", buf);
        }

    exit(1);
}