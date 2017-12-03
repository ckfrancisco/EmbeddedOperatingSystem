#include "ucode.c"

char capitalize(char c)
{
    if(c >= 97 && c <= 122)
        return c - 32;
    return c;
}

main(int argc, char *argv[])
{
    int in, out, fdi, fdo;
    char c;

    if(argc < 3)
    {
        while(c = getc())
        {
            c = capitalize(c);
            mputc(c);
            if(c == '\r')
                mputc('\n');
        }
    }

    else
    {
        fd = open(argv[2], O_RDONLY);
        if(fd < 0)
        {
            printf("Error: %s does not exist\n\r", argv[1]);
        }
        
        in = dup(0);
        dup2(fd, 0);

        dup2(in, 0);
        close(in); close(fd);
    }
}