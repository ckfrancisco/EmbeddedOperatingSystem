#include "ucode.c"

main(int argc, char *argv[])
{
    int fdi, fdo;
    char c;

    if(argc < 3)
        return;

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
            printf("Error: %s does not exist\n\r", argv[1]);
        }

        while(read(fdi, &c, 1))
            write(fdo, &c, 1);

        close(fdi); close(fdo);
    }
}