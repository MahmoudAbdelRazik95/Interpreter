#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxSize 100
#define TYPE char*
typedef struct
{
    char whi[100];
} wloop;
typedef struct
{
    char left[100];
    char right[100];
    char ext[100];
} equator;
typedef struct
{
    char key[100];
    float value;
} table;
table tab[1000];
int y=0,temp,ms;
float tempans;

typedef struct
{
    float items[MaxSize];
    char top;
} Stack;
void init(Stack * s);
void push(Stack *s,float data);
float pop(Stack * s);
int unary(char ex[]);
int isEmpty(Stack * s);
int isFull(Stack * s);
float peep(Stack *s);
int priority(char c);
char *infix(char exp[]);
float eval(char exp []);
char* spacer(char exp[]);
int checkduplicate(char exp[]);
char* replacer(char ex[]);
int nesting(char ex[]);
int isoperation(char xo[1]);
void ifcond(char ex[]);
void func(char ex[]);
int main()
{
    char cpy[30];
    char exp[30];
    char cc[30];
    char o=175;
    float xyz;
    char ef[10]="QUIT";
    char *token;
    char s[1];
    s[0]='\0';
    while(strcmpi(exp,ef))

    {

        printf("%c",o);
        gets(exp);
        strcpy(cpy,exp);
        if(strncmp(exp,s,1)==0)
            continue;
        token=strtok(exp," ");
        if(strcmpi(token,"if")==0)
        {
            token=strtok(NULL,s);
            ifcond(token);
            continue;
        }

        else if(strcmpi(token,"function")==0)
        {
            token=strtok(NULL,s);

            func(token);
            continue;
        }
        else if (strcmpi(token,"display")==0)
        {
            int i;
            for(i=0; i<y; i++)
                printf("%s = %f\n",tab[i].key,tab[i].value);
            continue;
        }
        else if(strcmpi(token,"call")==0)
        {
            token=strtok(NULL,s);

            call(token);
            continue;
        }
        if(strcmpi(exp,ef)==0)
            continue;
        if(nesting(exp)==0||unary(exp)==0)
        {

            continue;
        }
        int qc=0;
        int i;
        for(i=0; i<strlen(cpy); i++)
        {
            if(!isspace(cpy[i]))
            {
                cc[qc]=cpy[i];
                qc++;
            }
        }
        cc[qc]='\0';
        xyz=eval(cc);
        if(temp==-1)
            ms=y;
        else
            ms=temp;
        if(xyz!=0)
        {
            printf("%s = %f\n",tab[ms].key,tab[ms].value);
            y++;
        }








    }






    return 0;
}
void init(Stack * s)
{
    s->top=0;
}
void push(Stack *s,float data)
{
    s->items[s->top++]=data;
}
float pop(Stack * s)
{
    return   s->items[--s->top];
}
int isEmpty(Stack * s)
{
    if(s->top==0)
        return 1;
    return 0;
}
int isFull(Stack * s)
{
    if(s->top==MaxSize)
        return 1;
    return 0;
}
float peep(Stack *s)
{
    int x=pop(s);
    push(s,x);
    return x;
}

int priority(char c)
{
    switch(c)
    {
    case '(':
    case')':
        return 2;
    case '*':
    case '/':
    case '%':
        return 1;
    case '+':
    case '-':
        return 0;

    }
}
char *infix(char exp[])
{
    char x[100];
    int i;
    int c=0,h=0,m=0;
    Stack s;
    init(&s);
    char a;
    char name[100];
    strcpy(exp,spacer(exp));
    if(exp[0]=='\0')
        return exp;
    for(i=0; i<strlen(exp); i++)
    {
        if (isdigit(exp[i])||exp[i]=='.')
        {
            x[c++]=exp[i];

        }
        else if(exp[i]=='(')
        {
            push(&s,'(');
        }
        else if(exp[i]==')')
        {
            while(!isEmpty(&s)&&peep(&s)!='(')
            {
                a=pop(&s);
                x[c++]=' ';
                x[c++]=a;
                x[c++]=' ';
            }
            pop(&s);
        }
        else if(exp[i]=='-'&&isdigit(exp[i+1])&&(isoperation(exp[i-2])||exp[i-2]=='(')&&exp[i-1]==' ')
        {
            x[c++]=' ';
            x[c++]='-';
            continue;

        }




        else if (exp[i]=='+'||exp[i]=='*'||exp[i]=='/'||exp[i]=='-'||exp[i]=='-')
        {

            x[c++]=' ';




            if(isEmpty(&s))
                push(&s,exp[i]);
            else
            {
                while(!isEmpty(&s)&&priority(exp[i])<=priority(peep(&s))&& peep(&s)!='(')
                {
                    char uu=pop(&s);
                    if(uu!='(')
                    {
                        x[c++]=uu;
                        x[c++]=' ';

                    }
                }

                push(&s,exp[i]);
            }
        }
        else if(exp[i]== ' ')
            continue;
        else if(exp[i]=='=')
        {
            m=i;
        }

    }
    while(!isEmpty(&s))
    {
        x[c++]=' ';
        x[c++]=pop(&s);
    }
    x[c++]=NULL;

    return x;
}
char * corrector(char exp[])
{
    int i,j=0;
    char ex[100];
    for(i=0; i<strlen(exp); i++)
    {
        if(!isspace(exp[i]))
        {
            ex[j++]=exp[i];
        }

    }
    ex[j]='\0';
    for(i=0; i<=strlen(ex); i++)
    {
        if(ex[i]=='-')
        {
            if(ex[i]==ex[i+1])
            {
                ex[i+1]='+';
                ex[i]=' ';

                i=0;
            }

        }
    }
    for(i=0; i<=strlen(ex); i++)
    {
        if(ex[i]=='+')
        {
            if(ex[i]==ex[i+1]||ex[i]==ex[i+1])
            {
                ex[i+1]=ex[i];
                ex[i]=' ';

                i=0;
            }
            else if((ex[i]=='+'&&ex[i+1]=='+'))
            {

                ex[i+2]=ex[i];
                ex[i]=' ';

                i=0;
            }


        }
    }
    for(i=0; i<=strlen(ex); i++)
    {
        if(ex[i]=='-'&&ex[i+1]=='+')
        {
            ex[i+1]=' ';
        }
    }
    for(i=0; i<strlen(ex); i++)
    {
        if(ex[i]=='*'||ex[i]=='/')
        {
            if(ex[i+1]=='+')
            {
                ex[i+1]=ex[i];
                ex[i]=' ';

                i=0;
            }

        }
    }

    return ex;
}
int unary(char ex[])
{
    int i;
    char exp[1000];
    exp[0]='\0';
    for(i=0; i<strlen(ex); i++)
    {
        if(ex[i]==' '||ex[i]=='('||ex[i]==')')
            continue;
        sprintf(exp, "%s%c",exp,ex[i]);
    }

    for(i=0; i<strlen(exp); i++)
    {
        if(exp[i]=='*'||exp[i]=='/')
        {
            if(isoperation(exp[i-1])==1)
            {
                printf("Unexpected Use for Unary \"%c\" please Recheck !\n",exp[i]);
                return 0;
            }
        }

    }
    return 1;
}

float eval(char exp [])
{
    int i,c=0,o,k;
    float a,b,p;
    Stack s;
    init(&s);
    char*u;
    strcpy(exp,corrector(exp));
    strcpy(exp,corrector(exp));
    u=infix(exp);
    if (u[0]=='\0')
        return 0;
    char z[100];
    char strname[100];
    strcpy(z,u);
    char x[100];
    char *token;
    char tok;
    token=strtok(z," ");
    while(token!=NULL)
    {
        if(isdigit(token[0]))
        {
            p=atof(token);
            push(&s,p);
        }
        else if(token[0]=='-'&&isdigit(token[1]))
        {
            p=atof(token);
            push(&s,p);
        }
        else if(token[0]=='+'||token[0]=='-'||token[0]=='*'||token[0]=='/'&&token[1]=='\0')
        {
            a=pop(&s);
            b=pop(&s);
            tok=token[0];
            switch(tok)
            {
            case '+':
                push(&s,a+b);
                break;
            case '-':
                push(&s,b-a);
                break;
            case '*':
                push(&s,a*b);
                break;
            case '/':
                push(&s,b/a);
                break;
            default:
                printf("ERROR!");
            }
        }

        token=strtok(NULL," ");


    }
    if(temp==-1)
        tab[y].value=tempans= pop(&s);
    else
    {
        tab[temp].value=tempans=pop(&s);
        y--;
    }
    return -1;
}

char* spacer(char exp[])
{
    int i,c=0,o,m,l=0;
    char z[100];
    char x[100];
    char strname[100];
    strcpy(z,exp);
    for(i=0; i<strlen(z); i++)
    {
        if(z[i]=='=')
        {
            o=i;
            break;
        }
        else
            o=-1;

    }


    for(i=o+1; i<=strlen(z); i++)
    {
        if(z[i]=='-'&&isdigit(z[i+1])&&isoperation(z[i-1]))
        {
            x[c++]=' ';
            x[c++]='-';
            l++;
            l++;
            continue;

        }
        else    if(z[i]=='-'&&isdigit(z[i+1])&&z[i-1]=='(')
        {
            x[c++]=' ';
            x[c++]='-';
            l++;
            l++;
            continue;

        }
        if(z[i]=='+'||z[i]=='-'||z[i]=='*'||z[i]=='/'||z[i]=='('||z[i]==')')
        {
            x[c++]=' ';
            l++;
            x[c++]=z[i];
            x[c++]=' ';
            l++;
            l++;


        }
        if(isdigit(z[i])||isalpha(z[i])||z[i]=='.')
        {
            l++;
            x[c++]=z[i];
        }
        if(z[i]==' ')
            continue;

        else
            continue;




    }
    for(m=0; m<o; m++)
    {
        strname[m]=z[m];
    }
    if(m==0)
        strcpy(strname,"Ans");
    else
        strname[m]=NULL;
    x[l++]=' ';
    x[l]=NULL;
    char ll;
    char pos[2];
    if(isalpha(strname[0])==0)
    {
        printf("Expression (%s) is Not Valid!\n",strname);
        pos[0]='\0';
        return pos;

    }
    for(i=0; i<m; i++)
    {
        ll=strname[i];
        if(ll!='_'&&isdigit(ll)==0&&isalpha(ll)==0)
        {
            printf("Expression (%s) is Not Valid!\n",strname);
            pos[0]='\0';
            return pos;

        }

    }

    temp=checkduplicate(strname);

    char xy[1000];
    strcpy(xy,replacer(x));
    if(xy[0]=='\0')
        return xy;
    if(temp==-1)
        strcpy(tab[y].key,strname);
    else
        strcpy(tab[temp].key,strname);

    return xy;
}
int checkduplicate(char exp[])
{
    int i,x=0;
    for(i=0; i<y; i++)
    {
        if (strcmp(exp,tab[i].key)==0)
            return i;
    }
    return -1;
}
char* replacer(char ex[])
{
    char *token;

    token=strtok(ex," ");
    int xa;
    char op[100];
    double b;
    char sa[100]="\0";
    while(token!=NULL)
    {
        xa=checkduplicate(token);




        if(isdigit(token[0])||token[0]=='+'||token[0]=='-'||token[0]=='*'||token[0]=='/'||token[0]=='('||token[0]==')')
        {
            sprintf(sa, "%s %s",sa,token);
        }
        else if (xa==-1&&isalpha(token[0]))
        {
            printf("ERROR Variable (%s) Not Found!\n",token);
            sa[0]=NULL;
            return sa ;
        }
        else if(xa!=-1)
        {
            b=tab[xa].value;
            sprintf(sa, "%s %.2f",sa,b);



        }


        token=strtok(NULL," ");

    }
    return sa;
}
int nesting(char ex[])
{
    Stack s;
    init(&s);
    int i;
    for(i=0; i<strlen(ex); i++)
    {
        if(ex[i]=='(')
        {
            push(&s,'(');

        }
        else if(ex[i]==')')
        {

            if(isEmpty(&s))
                push(&s,')');
            while(!isEmpty(&s))
            {
                if(peep(&s)=='(')
                {
                    pop(&s);

                }
                break;
            }

        }
        else continue;

    }
    if(!isEmpty(&s))
    {
        printf("Error in Brackets Nesting! please Recheck Expression \n");
        return 0;
    }

    return 1;
}
int isoperation(char xo[1])
{
    if(xo=='-'||xo=='+'||xo=='*'||xo=='/')
        return 1;
    return 0;
}
int booleans(char ex[])
{
    int j;
    char exp[100];
    int kk=0;
    for(j=0; j<strlen(ex); j++)
    {
        if(isalpha(ex[j])||isdigit(ex[j])||isoperation(ex[j]))
            exp[kk++]=ex[j];
        else if(ex[j]=='='||ex[j]=='<'||ex[j]=='>'||ex[j]=='!')
        {
            exp[kk++]=' ';
            exp[kk++]=ex[j];
            exp[kk++]=' ';
        }
    }
    exp[kk]='\0';
    char *token;
    char *token2;
    char *token3;
    char up[1000];
    char op[1000];
    float boola,boolb;
    int i,i2,choice=0;
    token3=strtok(exp," ");
    while(token3!=NULL)
    {
        if(strcmp(token3,"<")==0)
            choice=1;
        else if(strcmp(token3,">")==0)
            choice=2;
        else if(strcmp(token3,"=")==0&&choice==1)
            choice=3;
        else if(strcmp(token3,"=")==0&&choice==2)
            choice=4;
        else if(strcmp(token3,"=")==0&&choice==0)
            choice=5;
        else if(strcmp(token3,"!")==0)
            choice=6;
        token3=strtok(NULL," ");

    }
    sprintf(up, "%s`",ex);
    token=strtok(up,"!<>=");
    token2=strtok(NULL,"`");
    i=unary(token);
    i2=unary(token2);
    if(i==0||i2==0)
        return 0;
    strcpy(op,token2);
    eval(token);
    boola=tempans;
    eval(op);
    boolb=tempans;

    if(choice==5)
    {
        if(boola==boolb)
        {
            return 1;
        }
        else
            return 0;

    }
    else if(choice==1)
    {
        if(boola<boolb)
        {
            return 1;
        }
        else
            return 0;

    }
    else  if(choice==2)
    {
        if(boola>boolb)
        {
            return 1;
        }
        else
            return 0;

    }
    else  if(choice==3)
    {
        if(boola<=boolb)
        {
            return 1;
        }
        else
            return 0;

    }
    else   if(choice==4)
    {
        if(boola>=boolb)
        {
            return 1;
        }
        else
            return 0;

    }
    else  if(choice==6)
    {
        if(boola!=boolb)
        {
            return 1;
        }
        else
            return 0;

    }
}
void ifcond(char ex[])
{
    char exp[1000];
    char cpy[1000];
    int i,ms;
    i=booleans(ex);
    char *token;
    if(i==1)
    {
        while(strcmp(exp,"End")!=0)
        {
            printf(">");
            gets(exp);
            if(strcmp(exp,"End")==0)
                continue;
            strcpy(cpy,exp);
            sprintf(cpy, "%s`",cpy);
            token=strtok(cpy," ");
            if(strcmp(token,"print")==0)
            {
                token=strtok(NULL,"`");
                puts(token);
                continue;
            }
            else if(eval(exp)==-1)
            {
                if(temp==-1)
                    ms=y;
                else
                    ms=temp;
            }
            printf("%s = %f\n",tab[ms].key,tab[ms].value);
            y++;


        }
    }
}
void func(char ex[])
{
    char *token1;
    char*token2;
    char param[1000];
    char fn[1000];
    char s[1];
    char expr[1000];
    s[0]='\0';
    token1=strtok(ex,"(");
    token2=strtok(NULL,s);
    sprintf(param, "%s;",token2);
    param[strlen(param)-2]=',';
    sprintf(fn,"%s.txt",token1);
    FILE *p;
    p=fopen(fn,"w");
    int i;
    fputs(param,p);
    fprintf(p,"\n");
    while(strcmpi(expr,"End;")!=0)
    {
        printf(">>");
        gets(expr);
        i=strlen(expr);
        if(expr[i-1]!=';')
        {
            printf("Expected \";\" At The End of the Expression Please Retype\n");
            continue;
        }
        fputs(expr,p);
        fprintf(p,"\n");

    }
    fclose(p);

}
void call(char ex[])
{
    equator eq[100];
    int l,r;
    l=r=-1;
    char *token;
    char *token2;
    char *tok;
    char *tok2;
    char functo[100];
    char param[1000];
    char param2[1000];
    char expe[1000];
    char s[1];
    int boo=-1;
    s[0]='\0';
    token=strtok(ex,"(");
    token2=strtok(NULL,s);
    sprintf(param2,"%s",token2);
    strcpy(functo,token);
    FILE *p;
    sprintf(token,"%s.txt",token);
    p=fopen(token,"r");
    if(p==NULL)
    {
        printf("Function %s Not Found!\n",functo);
        return;
    }
    else
    {
        fscanf(p,"%[^;];",param);
        fscanf(p,"\n");



    }
    tok=strtok(param2,",)");

    while(tok!=NULL)
    {
        r++;
        strcpy(eq[r].right,tok);
        tok=strtok(NULL,"(,)");

    }
    tok2=strtok(param,",");
    while(tok2!=NULL)
    {
        l++;
        strcpy(eq[l].left,tok2);
        tok2=strtok(NULL,",");

    }
    if(l!=r)
    {
        printf("Error in Given parameters Please Recheck!\n");
        return;
    }
    int i;
    for(i=0; i<=l; i++)
    {
        sprintf(eq[i].ext, "%s=%s",eq[i].left,eq[i].right);
        eval(eq[i].ext);
        y++;
    }
    char cpy[1000];
    char cpy2[1000];
    char *toke;
    int lol=0;
    while(!feof(p))
    {
        fscanf(p,"%[^;];",expe);
        fscanf(p,"\n");
        strcpy(cpy,expe);

        sprintf(cpy, "%s`",cpy);

        token=strtok(cpy," ");
        if(strcmpi(token,"print")==0)
        {
            token=strtok(NULL,"`");
            printf("%s",token);


        }

        else if(strcmpi(token,"println")==0)
        {
            token=strtok(NULL,"`");
            printf("%s\n",token);



        }
        else if(strcmpi(token,"if")==0)
        {
            token=strtok(NULL,"`");
            i=booleans(token);
            if(i==0)
            {
                lol=1;
                fscanf(p,"%[^;];",expe);
                fscanf(p,"\n");
                while(strcmpi(expe,"Endif")!=0&&strcmpi(expe,"else")!=0&&strcmpi(toke,"elseif")!=0)
                {
                    fscanf(p,"%[^;];",expe);
                    fscanf(p,"\n");
                    strcpy(cpy2,expe);
                    sprintf(cpy2, "%s`",cpy2);
                    toke= strtok(cpy2," ");
                }
                if(strcmpi(toke,"elseif")==0)
                    goto KL;



                continue;


            }
            else
                continue;

        }
        else if(strcmpi(token,"else")==0)
        {
KK:
            if(lol==1)
                continue;
            else
            {
                fscanf(p,"%[^;];",expe);
                fscanf(p,"\n");
                while(strcmpi(expe,"Endif")!=0)
                {
                    fscanf(p,"%[^;];",expe);
                    fscanf(p,"\n");
                }

            }
        }
        else if(strcmpi(token,"while")==0)
        {
            char *ttoken=strtok(NULL,"`");
            char bb[100];
            strcpy(bb,ttoken);
            wloop w[100];
            int jj=0;
            fscanf(p,"%[^;];",expe);
            fscanf(p,"\n");

            while(strcmpi(expe,"EndWhile")!=0)
            {
                strcpy(w[jj].whi,expe);
                jj++;
                fscanf(p,"%[^;];",expe);
                fscanf(p,"\n");
            }

            while(booleans(bb)==1)
            {


                int kx=0;

                while(kx<jj)
                {
                    strcpy(expe,w[kx++].whi);

                    strcpy(cpy,expe);

                    sprintf(cpy, "%s`",cpy);

                    token=strtok(cpy," ");

                    fscanf(p,"%[^;];",expe);
                    fscanf(p,"\n");

                    strcpy(cpy,expe);

                    sprintf(cpy, "%s`",cpy);

                    token=strtok(cpy," ");

                    if(strcmpi(token,"print")==0)
                    {
                        token=strtok(NULL,"`");
                        printf("%s",token);


                    }

                    else if(strcmpi(token,"println")==0)
                    {
                        token=strtok(NULL,"`");
                        printf("%s\n",token);



                    }
                    else if(strcmpi(token,"if")==0)
                    {
                        token=strtok(NULL,"`");
                        i=booleans(token);
                        if(i==0)
                        {
                            lol=1;
                            fscanf(p,"%[^;];",expe);
                            fscanf(p,"\n");
                            while(strcmpi(expe,"Endif")!=0&&strcmpi(expe,"else")!=0&&strcmpi(toke,"elseif")!=0)
                            {
                                fscanf(p,"%[^;];",expe);
                                fscanf(p,"\n");
                                strcpy(cpy2,expe);
                                sprintf(cpy2, "%s`",cpy2);
                                toke= strtok(cpy2," ");
                            }
                            if(strcmpi(toke,"elseif")==0)
                                goto KF;



                            continue;


                        }
                        else
                            continue;

                    }
                    else if(strcmpi(token,"else")==0)
                    {
KC:
                        if(lol==1)
                            continue;
                        else
                        {
                            fscanf(p,"%[^;];",expe);
                            fscanf(p,"\n");
                            while(strcmpi(expe,"Endif")!=0)
                            {
                                fscanf(p,"%[^;];",expe);
                                fscanf(p,"\n");
                            }

                        }

                    }
                    else if(strcmpi(token,"elseif")==0)
                    {
KF:
                        if(lol==1)
                        {
                            token=strtok(NULL,"`");
                            i=booleans(token);
                            if(i==0)
                            {
                                lol=0;
                                fscanf(p,"%[^;];",expe);
                                fscanf(p,"\n");

                                toke="1";
                                while(strcmpi(expe,"Endif")!=0&&strcmpi(expe,"else")!=0&&strcmpi(toke,"elseif")!=0)
                                {
                                    fscanf(p,"%[^;];",expe);
                                    fscanf(p,"\n");
                                    strcpy(cpy2,expe);
                                    sprintf(cpy2, "%s`",cpy2);
                                    toke= strtok(cpy2," ");
                                }
                                if(strcmpi(toke,"elseif")==0)
                                {
                                    goto KF;

                                }
                                continue;


                            }


                        }
                        else if(lol==0)
                        {
                            fscanf(p,"%[^;];",expe);
                            fscanf(p,"\n");
                            while(strcmpi(expe,"Endif")!=0)
                            {
                                fscanf(p,"%[^;];",expe);
                                fscanf(p,"\n");
                            }
                            continue;


                        }


                    }
                    else if(strcmpi(token,"printvar")==0)
                    {
                        token=strtok(NULL,"`");
                        i=checkduplicate(token);
                        if(i==-1)
                        {
                            printf("Variable %s Not Found!\n",token);
                            return;

                        }
                        printf("%f",tab[i].value);



                    }

                    else if(strcmpi(token,"printvarn")==0)
                    {
                        token=strtok(NULL,"`");
                        i=checkduplicate(token);
                        if(i==-1)
                        {
                            printf("Variable %s Not Found!\n",token);
                            return;

                        }
                        printf("%f\n",tab[i].value);



                    }
                    else if(strcmpi(expe,"End")==0||strcmpi(expe,"Endif")==0||strcmpi(expe,"EndWhile")==0)
                    {
                        lol=0;
                        continue;
                    }
                    else if(strcmpi(expe,"else")==0)
                        goto KC;
                    else
                    {
                        eval(expe);
                        y++;
                    }


                }

            }
        }
            else if(strcmpi(token,"elseif")==0)
            {
KL:
                if(lol==1)
                {
                    token=strtok(NULL,"`");
                    i=booleans(token);
                    if(i==0)
                    {
                        lol=0;
                        fscanf(p,"%[^;];",expe);
                        fscanf(p,"\n");

                        toke="1";
                        while(strcmpi(expe,"Endif")!=0&&strcmpi(expe,"else")!=0&&strcmpi(toke,"elseif")!=0)
                        {
                            fscanf(p,"%[^;];",expe);
                            fscanf(p,"\n");
                            strcpy(cpy2,expe);
                            sprintf(cpy2, "%s`",cpy2);
                            toke= strtok(cpy2," ");
                        }
                        if(strcmpi(toke,"elseif")==0)
                        {
                            goto KL;

                        }
                        continue;


                    }


                }
                else if(lol==0)
                {
                    fscanf(p,"%[^;];",expe);
                    fscanf(p,"\n");
                    while(strcmpi(expe,"Endif")!=0)
                    {
                        fscanf(p,"%[^;];",expe);
                        fscanf(p,"\n");
                    }
                    continue;


                }


            }
            else if(strcmpi(token,"printvar")==0)
            {
                token=strtok(NULL,"`");
                i=checkduplicate(token);
                if(i==-1)
                {
                    printf("Variable %s Not Found!\n",token);
                    return;

                }
                printf("%f",tab[i].value);



            }

            else if(strcmpi(token,"printvarn")==0)
            {
                token=strtok(NULL,"`");
                i=checkduplicate(token);
                if(i==-1)
                {
                    printf("Variable %s Not Found!\n",token);
                    return;

                }
                printf("%f\n",tab[i].value);



            }
            else if(strcmpi(expe,"End")==0||strcmpi(expe,"Endif")==0||strcmpi(expe,"EndWhile")==0)
            {
                lol=0;
                continue;
            }
            else if(strcmpi(expe,"else")==0)
                goto KK;
            else
            {
                eval(expe);
                y++;
            }



        }
        fclose(p);



    }
