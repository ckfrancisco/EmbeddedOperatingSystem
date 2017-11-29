/****************** Algorithm of login *******************/
// login.c : Upon entry, argv[0]=login, argv[1]=/dev/ttyX #include "ucode.c"
int in, out, err; char name[128],password[128]
main(int argc, char *argv[])
{
    close(0); close(1);
    open()
(3) settty(argv[1]); // set tty name string in PROC.tty
(4) open /etc/passwd file for READ;

    while(1){
(5)     printf("login:");
        gets(name);
        printf("password:");
        gets(password);
        for each line in /etc/passwd file do{
            tokenize user account line;
(6)         if (user has a valid account){
(7)             change uid, gid to users uid, gid;  // chuid()
                change cwd to users home DIR        // chdir()
                close opened /etc/passwd file       // close()
                exec to program in user account     // exec()
            }
        }
(8)     printf("login failed, try again\n");
    }
}

  



