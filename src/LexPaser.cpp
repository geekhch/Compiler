#include "LexPaser.h"

extern const string KEYW[] = {"else", "if", "int", "return", "void", "while"};
extern const char OPS[] = {'+', '-', '*', '/', '<', '=', '>', '!', ';', ',', '(', ')', '[', ']', '{', '}'};


Token::Token(TYPE type, int value)
{
    this->type = type;
    this->i_value = value;
}

Token::Token(TYPE type, string value)
{
    this->type = type;
    this->s_value = value;
}

LexPaser::LexPaser(const string &filepath)
{
    //��Դ�����ȡ��������
    f_code.open(filepath);
    char tmp;
    int cursor=0;
    while((tmp=f_code.get()) != EOF){
        if(cursor>BUFFER_SIZE-1){
            cout << "Buffer overflow!" << endl;
            exit(-1);
        }
        // ȥ��ע��
        if(cursor>0 && tmp=='*' && s_code[cursor-1]=='/'){
            isEnd: while((tmp=f_code.get()) != EOF && tmp!='*');
            if((tmp=f_code.get())!='/') goto isEnd;
            cursor -= 1; //����ȥ��ǰ���/ע�ͱ��
            continue;
        }
        // ȥ�����з�
        if(tmp != '\n') this->s_code[cursor++] = tmp;
    }
    s_code[cursor] = '\0';
    f_code.close();
}

LexPaser::~LexPaser(){}

void LexPaser::printCode()
{
    cout << s_code << endl;
}