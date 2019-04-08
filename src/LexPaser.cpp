#include "LexPaser.h"
#include <cstring>

extern const string KEYW[] = {"else", "if", "int", "return", "void", "while"};
extern const char OPS[] = {'+', '-', '*', '/', '<', '=', '>', '!', ';', ',', '(', ')', '[', ']', '{', '}'};


Token::Token(TYPE type, const long value)
{
    this->type = type;
    this->i_value = value;
}

Token::Token(TYPE type, const string &value)
{
    this->type = type;
    this->s_value = value;
}

string Token::strfToken()
{
    static char tokenString[100];
    if(type == INT)
    {
        sprintf(tokenString,"< %1d   %d >",type,i_value);
    }else
    {
        sprintf(tokenString,"< %1d   %s >",type,s_value.c_str());
    }
    return string(tokenString);
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

    parseToken();
}

LexPaser::~LexPaser(){}

void LexPaser::printCode() const
{
    cout << s_code << endl;
}

bool LexPaser::isOperator(char c)
{
    for(char s:OPS){
        if(s==c) return true;
    }
    return false;
}

void LexPaser::addTokenInt(const char *numStr)
{
    char *endstring;
    long num = strtol(numStr, &endstring, 10);
    Token token(INT, num);
    tokens.push_back(token);
}

void LexPaser::addTokenWord(const string &word)
{
    //���Ϊ������
    for(string w:KEYW){
        if(w==word){
            Token token(KEY, word);
            tokens.push_back(token);
            return;
        }
    }
    //���Ǳ�����
    Token token(ID, word);
    tokens.push_back(token);
}

void LexPaser::addTokenOp(const string &op)
{
    Token token(OP, op);
    tokens.push_back(token);
}

void LexPaser::parseToken()
{
    char TokenBuffer[60];
    for(int i=0; i<strlen(s_code); i++)
    {
        //�����հ׷�
        if(isblank(s_code[i])) continue;
        
        //����int����״̬ת��ͼ
        if(isdigit(s_code[i])){
            int j=0;
            TokenBuffer[j++] = s_code[i];
            while(i<strlen(s_code)-1 && isdigit(s_code[i+1])) {TokenBuffer[j++] = s_code[i+1]; i++;}; //Ԥ��һ���ַ�,���ж��Ƿ񵽴���β
            if(isalpha(s_code[i+1])) throw runtime_error("illegal lexical!");
            TokenBuffer[j] = '\0';
            addTokenInt(TokenBuffer);
            continue;
        }
        //�����ʶ���͹ؼ���״̬ת��ͼ
        if(isalpha(s_code[i])){
            int j=0;
            TokenBuffer[j++] = s_code[i];
            while(i<strlen(s_code)-1 && isalpha(s_code[i+1])) {TokenBuffer[j++] = s_code[i+1]; i++;}; //Ԥ��һ���ַ�,���ж��Ƿ񵽴���β
            TokenBuffer[j] = '\0';
            addTokenWord(string(TokenBuffer));
            continue;
        }

        //������ʶ��
        if(isOperator(s_code[i])){
            int j=0;
            TokenBuffer[j++] = s_code[i];
            if(s_code[i]=='<' || s_code[i]=='>' || s_code[i]=='!' || s_code[i]=='='){
                if(i<strlen(s_code)-1 && s_code[i+1]=='=') {TokenBuffer[j++] = s_code[i+1]; i++;};
            }
            TokenBuffer[j] = '\0';
            addTokenOp(string(TokenBuffer));
            continue;
        }

        //�쳣
        throw runtime_error("thers is an illegal charactor!");
    }
}

void LexPaser::printTokenList() const
{
    for(Token token: tokens){
        cout << token.strfToken() << endl;
    }
    cout << tokens.size() << " tokens in total!" << endl;
}

Token& LexPaser::nextToken()
{
    if(cursor<tokens.size())
    {
        uint32_t next = cursor;
        ++cursor;
        return tokens[next];
    }else
    {
        throw runtime_error("no more tokens!"); //����쳣δ��catch, ���򽫵ݹ���ֹ
    }
}