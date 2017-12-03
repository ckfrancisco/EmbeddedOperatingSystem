#include "ucode.c"

main(int argc, char *argv[])
{
    int fd, ncount, maxcount;
    char c;

    if(argc < 2)
    {
        printf("Usage:\n"
                "   more [options] <file>...\n"

                "A file perusal filter for CRT viewing.\n"

                "Options:\n"
                "   -d          display help instead of ringing bell\n"
                "   -f          count logical rather than screen lines\n"
                "   -l          suppress pause after form feed\n"
                "   -c          do not scroll, display text and clean line ends\n"
                "   -p          do not scroll, clean screen and display text\n"
                "   -s          squeeze multiple blank lines into one\n"
                "   -u          suppress underlining\n"
                "   -<number>   the number of lines per screenful\n"
                "   +<number>   display file beginning from line number\n"
                "   +/<string>  display file beginning from search string match\n"
                "   -V          display version information and exit\n"

                "For more details see more(1).\n\r");
    }
    else
    {
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

    

    close(fd);
}