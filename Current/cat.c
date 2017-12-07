#include "ucode.c"

main(int argc, char *argv[])
{
    int fd;
    char tty[16], c;
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
    fstat(1, &instat);
        
    if(ttystat.st_dev == instat.st_dev && ttystat.st_ino == instat.st_ino)
        while(read(0, &c, 1))
            mputc(c);

    else
        while(read(0, &c, 1))
            write(1, &c, 1);

    exit(1);
}