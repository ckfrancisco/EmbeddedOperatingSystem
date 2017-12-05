#include "ucode.c"

main(int argc, char *argv[])
{
    int in, fd, ncount, maxcount;
    char tty[16], buf[1024];
    STAT ttystat, instat;

    if(argc > 1)
    {
        fd = open(argv[1], O_RDONLY);
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

    ncount = 0;
    maxcount = 20;
        
    if(ttystat.st_dev == instat.st_dev && ttystat.st_ino == instat.st_ino)
        while(gets(buf))
        {
            printf("%s\n\r", buf);
        }

    else
        while(getline(buf))
        {
            printf("%s", buf);
        }

    exit(1);
}