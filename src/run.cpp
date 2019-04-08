#include "LexPaser.h"

void stars();
void showMenu();

int main(int argv, char* args[])
{
    if(argv<2){
        printf("use: %s filename",args[0]);
        exit(0);
    }
    //call lex paser
    LexPaser paser(args[1]);
    //input commands
    showMenu();
    char cmd;
    while(cin>>cmd,cmd!='q')
    {
        switch(cmd)
        {
            case 'p': paser.printCode(); break;
            case 'h': showMenu(); break;
        }
        stars();
    }

    return 0;
}

void stars()
{
    cout << endl << string(20,'*') << endl << endl;
}

void showMenu()
{
    printf("c    print token numbers\n");
    printf("t    print token lists\n");
    printf("p    print the raw code\n");
    printf("h    print this showMenu\n");
    printf("q    quit\n");
}