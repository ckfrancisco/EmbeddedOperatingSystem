#include "ucode.c"

main(int argc, char *argv[])
{
    int in, fd, ncount, maxcount, i;
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
    fstat(0, &instat);

    ncount = 0;
    maxcount = 20;
        
    if(ttystat.st_dev == instat.st_dev && ttystat.st_ino == instat.st_ino)
        exit(1);

    else
        in = open("/dev/tty0", O_RDONLY);
        
    while(read(0, &c, 1))
        {
            mputc(c);

            if(c == '\n')
            {
                ncount++;
            }

            if(ncount >= maxcount)
            {
                ncount = 0;

                read(in, &c, 1);

                if(c == ' ')
                    maxcount = 20;
                else if(c == 'q')
                    exit(1);
                else
                    maxcount = 1;
            }
        }

    exit(1);
}