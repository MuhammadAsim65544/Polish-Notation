//Assignment No:2
//Name: Muhammad Asim
//Registration No:3956|FBAS|BSCS|F18 B
//Submitted To: Muhammed Nadeem
#include <iostream>
#include<cmath>
using namespace std;
bool precedinse(char op1, char op2);
//////////////////
class Node
{
    int t,data,x;
    Node *next,*nxt;
    public:
        void setData(int x) { data = x; }
        int getData() { return data; }
        void setNext(Node* nxt) { next = nxt; }
        int getNext() { return next; }
};
class myStack
{
    Node *first;
    Node *cur;
    Node *prev;
    Node *secondLast;
    Node *last;
    public:
        myStack()
        {
            first = NULL;
            cur = NULL;
            prev = NULL;
            last = NULL;
        }
        void push(int T ,int val);
        void display();
        pop();
        peek();
        bool isEmpty() 
        {
            if(first==NULL) return true;
            else return false;
        }
};
void myStack :: push(int t,int val)
{
    if(!first)
    {
        cur = new Node;
        cur->setData(val);
        first = last = cur;
        cur->setNext(NULL);
    }
    else
    {
        last = first;
        while(last->getNext()) last = last->getNext(); //Making last pointer to reach at the END of List
        cur = new Node; 
        cur->setData(val);
        cur->setNext(NULL);
        last->setNext(cur);
        while(last->getNext()) last = last->getNext(); //Again
    }   
}
void myStack<Node T> :: pop()
{
    Node *temp = NULL;
    T tempVal;
    if(first)
    {
        if(last == first)
        {
            temp = first;
            tempVal = first->getData();
            first = NULL;
            delete temp;
            return tempVal;
        }
        else
        {
            cur = first;
            while(cur->getNext())
            {
                secondLast = cur;
                cur = cur->getNext();
            } //Finding SecondLast

            // cout<<"\nCTRL mein Yahan hoon!";
            tempVal = last->getData();
            temp = last;
            secondLast->setNext(NULL);
            last = secondLast;
            delete temp; //Jahan Ganddgi phelao Wahan LOTA b saath lyy k jaao - SirNadeem
            return tempVal;

        }
    }
    else return 0;   
}
////////////
class Polish_Notation
{
    string prefix, infix, postfix;
    myStack<char> char_stk;
    myStack<double> double_stk;
    char token;
    bool balanced;
    public:
    Polish_Notation()
    {
        balanced = true;
        prefix=""; infix =""; prefix="";
    }
    void set_infix();
    void isBalanced();
    void polishIt();
    void rePolishIt();
    void eval_of_prefix();
    void evalPostfix();
};
void Polish_Notation::set_infix()
{
    do
    {   
        if(!balanced) cout<<"\nNotation is NOT Balanced\nEnter Infix Notation Again!\n";
        else cout<<"\nEnter Infix Notation:\n";
        getline(cin, infix);

        balanced = true;
        this->isBalanced();
    }
    while(!balanced);
    
}
void Polish_Notation :: isBalanced()
{
    int i;
    for(i = 0; (i < infix.length() && balanced); i++)
    {
        token = infix[i];
        if((token == '(')||(token == '{')||(token == '[')) char_stk.push(token);
        else if((token == ')')||(token == '}')||(token == ']'))
        {
            do
            {
                switch(char_stk.peek())
                {
                    case '(':
                        if(token!=')') balanced = false;
                        break;
                    case '{':
                        if(token!='}') balanced = false;
                        break;
                    case '[':
                        if(token!=']') balanced = false;
                        break;
                }
                if(!balanced) break;
                char_stk.pop();
                if(i<infix.length()) token  = infix[++i];

                if(char_stk.isEmpty()) break;
            } while ((token == ')')||(token == '}')||(token == ']'));
            if((token == '(')||(token == '{')||(token == '[')) char_stk.push(token);
            
        }
        else continue;
    }
}
void Polish_Notation::rePolishIt()
{
    char temp;
    for(int i = 0; i < infix.length(); i++)
    {
        token = infix[i];
        if((token=='+')||(token=='-')||(token=='*')||(token=='/')||(token=='^'))
        {
            while(precedinse(char_stk.peek(), token) && (!char_stk.isEmpty())) postfix.append(1, char_stk.pop());
            
            char_stk.push(token);
        }
        else if(token == '(') char_stk.push('(');
        else if(token == '{') char_stk.push('{');
        else if(token == '[') char_stk.push('[');
        else if(token == ')')
        {
            while(char_stk.peek() != '(') postfix.append(1, char_stk.pop());

            char_stk.pop();
        }
        else if(token == '}')
        {
            while(char_stk.peek() != '{') postfix.append(1, char_stk.pop());

            char_stk.pop();
        }
        else if(token == ']')
        {
            while(char_stk.peek() != '[') postfix.append(1, char_stk.pop());

            char_stk.pop();
        }
        else postfix.append(1, token);
    }
    while(!char_stk.isEmpty()) postfix.append(1, char_stk.pop());

    cout<<"\nPostfix is as: ";cout<<postfix;
}
void Polish_Notation::polishIt()
{
    char temp;
    for(int i = infix.length()-1; i >=0 ; i--)
    {
        token = infix[i];
        if((token=='+')||(token=='-')||(token=='*')||(token=='/')||(token=='^'))
        {
            while(precedinse(char_stk.peek(), token) && (!char_stk.isEmpty())) prefix.append(1, char_stk.pop());
            
            char_stk.push(token);
        }
        else if(token == ')') char_stk.push(')');
        else if(token == '}') char_stk.push('}');
        else if(token == ']') char_stk.push(']');
        else if(token == '(')
        {
            while(char_stk.peek() != ')') prefix.append(1, char_stk.pop());

            char_stk.pop();
        }
        else if(token == '{')
        {
            while(char_stk.peek() != '}') prefix.append(1, char_stk.pop());

            char_stk.pop();
        }
        else if(token == '[')
        {
            while(char_stk.peek() != ']') prefix.append(1, char_stk.pop());

            char_stk.pop();
        }
        else prefix.append(1, token);
    }
    while(!char_stk.isEmpty()) prefix.append(1, char_stk.pop());

    int j = prefix.length()-1;
    for(int i = 0; i < prefix.length()/2; i++)
    {
        temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = temp;
        j--;
    }
    cout<<"\nPrefix is as: ";cout<<prefix;
}
void Polish_Notation ::eval_of_postfix()
{
    int i = 0;
    char tempChar[MAXARR];
    double doubleop1, doubleop2, value, tempval;
    postfix.append(1, ')');
    for(int i = 0; postfix[i]!=')'; i++)
    {
        token = postfix[i];
        if((token=='+')||(token=='-')||(token=='*')||(token=='/')||(token=='^'))
        {
            doubleop2 = double_stk.pop();
            doubleop1 = double_stk.pop();
            
            //Calculating value now
            if(token == '+') value = doubleop1 + doubleop2;
            else if(token == '-') value = doubleop1 - doubleop2;
            else if(token == '*') value = doubleop1 * doubleop2;
            else if(token == '/') value = doubleop1 / doubleop2;
            else if(token == '^') value = pow(doubleop1, doubleop2);

            double_stk.push(value);
        }
        else
        {
            //Converting to double value
            tempChar[0] = token;
            tempval = strtold(tempChar, NULL);
            //Now Pushing into Stack
            double_stk.push(tempval);
        }
    }
    value = double_stk.pop();
    cout<<"\nPostfix Evaluated as: "<<value; 
}
void Polish_Notation ::eval_of_prefix()
{
    int i = 0;
    char tempChar[MAXARR];
    double doubleop1, doubleop2, value, tempval;
    for(int i = prefix.length()-1; i>=0; i--)
    {
        token = prefix[i];
        if((token=='+')||(token=='-')||(token=='*')||(token=='/'))
        {
            doubleop2 = double_stk.pop();
            doubleop1 = double_stk.pop();
            
            //Calculating value now
            if(token == '+') value = doubleop1 + doubleop2;
            else if(token == '-') value = doubleop1 - doubleop2;
            else if(token == '*') value = doubleop1 * doubleop2;
            else if(token == '/') value = doubleop1 / doubleop2;
            else if(token == '^') value = pow(doubleop1, doubleop2);

            double_stk.push(value);
        }
        else
        {
            //Converting to double value
            tempChar[0] = token;
            tempval = strtold(tempChar, NULL);
            //Now Pushing into Stack
            double_stk.push(tempval);
        }
    }
    value = double_stk.pop();
    cout<<"\nPrefix Evaluated as: "<<value; 
}
//Tester
int main()
{
    Polish_Notation *pn;
    short ch;
    do
    {
        pn = new Polish_Notation();
        cout<<"\n\t---MENU---"
            <<"\n1.Polish a Notation"
            <<"\n2.Polish a Notation & Evaluate (Integer input is Required)"
            <<"\n3.Reverse Polish a Notation"
            <<"\n4.Reverse Polish a Notation & Evaluate (Integer input is Required)"
            <<"\n5.Exit";
        cout<<"\nEnter Choice:\n";cin>>ch;
        system("clear");
        cin.ignore(10, '\n');
        switch(ch)
        {
            case 1:
                pn->set_infix();
                pn->polishIt();
                delete pn;
                break;
            case 2:
                cout<<"\n(NOTE:Integer input is Required)";
                pn->set_infix();
                pn->polishIt();
                pn->eval_of_prefix();
                delete pn;
                break;
            case 3:
                pn->set_infix();
                pn->rePolishIt();
                delete pn;
                break;
            case 4:
                cout<<"\n(NOTE:Integer input is Required)";
                pn->set_infix();
                pn->rePolishIt();
                pn->eval_of_postfix();
                delete pn;
                break;
            case 5:
                return 0;
        }
    } while (1);
    cout<<endl;
    return 0;
}
bool precedinse(char op1, char op2)
{
    if((op1 == '+')||(op1 == '-')||(op1 == '*')||(op1 == '/'))
    {
        if(((op1=='+') || (op1=='-')) && (op2=='^')) return false;
        else if(((op1=='+') || (op1=='-')) && ((op2=='*') || (op2=='/'))) return false;
        else return true;
    }
    else return false;
}
