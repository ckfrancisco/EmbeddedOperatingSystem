#include "ucode.c"

main(int argc, char *argv[])
{
    int fd, ncount, maxcount;
    char c;

    ncount = 0;
    maxcount = 20;

    fd = open(argv[1], O_RDONLY);

    while(read(fd, &c, 1) > 0)
    {
        mputc(c);

        if(c == '\n')
            ncount++;

        if(ncount == maxcount)
        {
            ncount = 0;
            c = getc();

            if(c == ' ')
                maxcount = 20;
            else
                maxcount = 1;
        }
    }

    close(fd);
}