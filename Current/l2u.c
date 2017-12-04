#include "ucode.c"

char capitalize(char c)
{
    if(c >= 97 && c <= 122)
        return c - 32;
    return c;
}

main(int argc, char *argv[])
{
    int fdi, fdo;
    char c;

    if(argc < 3)
    {
        while(read(0, &c, 1))
        {
            c = capitalize(c);
            mputc(c);
            if(c == '\r')
                mputc('\n');
        }
    }

    else
    {
        fdi = open(argv[1], O_RDONLY);
        if(fdi < 0)
        {
            printf("Error: %s does not exist\n\r", argv[1]);
        }

        fdo = open(argv[2], O_WRONLY | O_CREAT);
        if(fdo < 0)
        {
            close(fdi);
            printf("Error: %s does not exist\n\r", argv[2]);
        }

        while(read(fdi, &c, 1))
        {
            c = capitalize(c);
            write(fdo, &c, 1);
        }

        close(fdi); close(fdo);
    }
}