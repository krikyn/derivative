#include<fstream>
#include<iostream>
#include<vector>
#include <algorithm>
#include <string>

using namespace std;

struct node{

    string s,
           sign;

    node* left;
    node* right;

    node(string ss, string si, node* l ,node* r)
    {
        s = ss;
        sign = si;
        left = l;
        right = r;
    }
};

bool ex(string s)
{

    bool k = false;
    for (int i=0;i<s.length();i++)
        if (s[i]=='x')
            k = true;

    //cout<<s<<" "<<k<<endl;

    return k;
}

node* build(string s)
{
    //cout<<s<<endl;

    if (s[0]=='(') {
        int i = 0, k = 1;
        while (k > 0) {
            i++;
            if (s[i] == '(') k++;
            if (s[i] == ')') k--;
        }
        //cout<<i;
        if (i == s.length() - 1)
            return build(s.substr(1, s.length() - 2));
        else {
            /*int j = i+2;
            string symbol="";
            symbol+=s[i+1];

            *//*if (symbol=="*"&&s[i+2]=='*')
            {
                symbol+='*';
                j++;
            }*//*

            node* newnode = new node(s,symbol,build(s.substr(1,i-1)),build(s.substr(j,s.length()-j)));
            return newnode;*/
        }
    }
    if (s[0]=='l'||s[0]=='s'||s[0]=='c'||s[0]=='t'||s[0]=='a')
    {
        int i=0;
        while(s[i]!='(') i++;

        string sign = s.substr(0,i);

        s = s.substr(i,s.length()-i);
        i=0;
        int k=0;

        while(k>=0)
        {
            i++;
            if (s[i]=='(') k++;
            if (s[i]==')') k--;
        }
        if (i==s.length()-1)
        {
            node* newnode = new node(sign+s.substr(0,s.length()),sign,build(s.substr(1,s.length()-2)),NULL);
            return newnode;
        } else
        {
            int j = i+2;

            string symbol="";
            symbol+=s[i+1];

            /*if (symbol=="*"&&s[i+2]=='*')
            {
                symbol+='*';
                j++;
            }*/

            node* newnode = new node(sign+s,symbol,build(sign + s.substr(0,i+1)),build(s.substr(j,s.length()-j)));
            return newnode;
        }
    } else
    {
        ///+ -
        int i = 0;
        int k = 0;
        while(true)
        {
            if (s[i]=='(') k++;
            if (s[i]==')') k--;

            if (k==0&&(i>=s.length()||s[i]=='+'||s[i]=='-'))
            {
                break;
            }
            i++;
        }

        if (i!=s.length())
        {
            string sss = "";
            sss+=s[i];
            node* newnode = new node(s,sss,build(s.substr(0,i)),build(s.substr(i+1,s.length()-i-1)));
            return newnode;
        }


        //// * /
        i = 0;
        k = 0;

        while(true)
        {
            if (s[i]=='(') k++;
            if (s[i]==')') k--;

            if (k==0&&(i>=s.length()||s[i]=='*'||s[i]=='/'))
            {
                break;
            }
            i++;
        }

        if (i!=s.length())
        {
            string sss = "";
            sss+=s[i];
            node* newnode = new node(s,sss,build(s.substr(0,i)),build(s.substr(i+1,s.length()-i-1)));
            return newnode;
        }

        //// ^
        i = 0;
        k = 0;

        while(true)
        {
            if (s[i]=='(') k++;
            if (s[i]==')') k--;

            if (k==0&&(i>=s.length()||s[i]=='^'))
            {
                break;
            }
            i++;
        }

        if (i!=s.length())
        {
            string sss = "";
            sss+=s[i];
            node* newnode = new node(s,sss,build(s.substr(0,i)),build(s.substr(i+1,s.length()-i-1)));
            return newnode;
        }

        //// "const"
        node* newnode = new node(s,"=",NULL,NULL);
        return newnode;
    }
}

string derivative(node* nod)
{
    //cout<<nod->left->s<<"  "<<nod->sign<<"   "<<nod->right->s<<endl;

    if (nod->sign == "=")
    {
        if (nod->s=="x")
            return "1";
        else return "0";
    }

    if (nod->sign=="+"||nod->sign=="-")
    {
        string l = derivative(nod->left);
        string r = derivative(nod->right);
        return "(" + l + nod->sign + r + ")";
    }


    if (nod->sign=="*")
    {
        /*if(!exist_x(nod->left->s))
            return "(" + nod->left->s + "*" + derivative(nod->right) + ")";
        if(!exist_x(nod->right->s))
            return "(" + derivative(nod->left) + "*" + nod->right->s + ")";*/
        string l = derivative(nod->left);
        string r = derivative(nod->right);
        return "(" + l + "*(" + nod->right->s + ")+(" + nod->left->s + ")*" + r + ")";
    }

    if (nod->sign=="/")
    {
        if (!ex(nod->right->s)&&!ex(nod->left->s))
            return "0";

        string l = derivative(nod->left);
        string r = derivative(nod->right);
        return "((" + l + "*(" + nod->right->s + ")-(" + nod->left->s + ")*" + r + ")" + "/" + "(" + nod->right->s + ")^2" + ")";
    }

    if (nod->sign=="^")
    {
        if (!ex(nod->right->s)&&!ex(nod->left->s))
            return "0";

        string l = derivative(nod->left);

        if (!ex(nod->right->s)&&ex(nod->left->s))
        {
            //cout<<"9"<<endl;
            return "(((" + nod->right->s + ")*" "(" + nod->left->s + ")^" + "(" + nod->right->s + "-1))*" + l + ")";
            //hazard!
        }


        string r = derivative(nod->right);
        if (ex(nod->right->s)&&!ex(nod->left->s))
            return "(((" + nod->left->s + ")^" + "(" + nod->right->s + "))*ln(" + nod->left->s + ")*" + r + ")";

        if (ex(nod->right->s)&&ex(nod->left->s))
            return "(("+nod->left->s+")^(" + nod->right->s+"))*((" + nod->right->s+")/("+nod->left->s+")*" + l + "+ln("+nod->left->s+")*"+ r + ")";
    }

    if (nod->sign=="ln")
    {
        if (!ex(nod->left->s))
            return "0";
        else
        {
            string l = derivative(nod->left);
            return "(1/(" + nod->left->s + ")*" + l + ")";
        }
    }

    if (nod->sign=="sin")
    {
        if (!ex(nod->left->s))
            return "0";
        else
        {
            string l = derivative(nod->left);
            return "(cos(" + nod->left->s + ")*" + l + ")";
        }
    }

    if (nod->sign=="cos")
    {
        if (!ex(nod->left->s))
            return "0";
        else
        {
            string l = derivative(nod->left);
            return "(-sin(" + nod->left->s + ")*" + l + ")";
        }
    }

    if (nod->sign=="tg")
    {
        if (!ex(nod->left->s))
            return "0";
        else
        {
            string l = derivative(nod->left);
            return "(1/(cos(" + nod->left->s + ")^2)*" + l + ")";
        }
    }

    if (nod->sign=="ctg")
    {
        if (!ex(nod->left->s))
            return "0";
        else
        {
            string l = derivative(nod->left);
            return "(-1/(sin(" + nod->left->s + ")^2)*" + l + ")";
        }
    }

    if (nod->sign=="arcsin")
    {
        if (!ex(nod->left->s))
            return "0";
        else
        {
            string l = derivative(nod->left);
            //return "(1/sqrt(1-(" + nod->left->s + ")^2)*" + l + ")";
            return "(1/(1-(" + nod->left->s + ")^2)^0.5*" + l + ")";
        }
    }

    if (nod->sign=="arctg")
    {
        if (!ex(nod->left->s))
            return "0";
        else
        {
            string l = derivative(nod->left);
            return "(1/(1+(" + nod->left->s + ")^2)*" + l + ")";
        }
    }
}

///"(" +  + ")"

int main() {

    ifstream cin("deriv.in");
    ofstream cout("deriv.out");

    string s;
    while(getline(cin, s))
    {
        string ss="";
        for (int i=0;i<s.length();i++)
            if (s[i]!=' ')
            {
                if (s[i]!='*')
                    ss+=s[i];
                else
                {
                    if (s[i+1]=='*')
                    {
                        ss+='^';
                        i++;
                    }
                    else
                        ss+='*';
                }
            }

            /*if(s[i]!=' ')
                if (s[i]!='*')
                    ss+=s[i];
                else if (s[i+1]=='*')
                    ss+='^';
                else ss+='*';*/

        //cout<<ss<<"      ";
        //cout<<ss<<endl;
        node* root = build(ss);

        string fetch_string,finish_string;
        fetch_string = derivative(root);
        for (int i=0;i<fetch_string.length();i++)
            if (fetch_string[i]=='^')
                finish_string+="**";
            else finish_string+=fetch_string[i];

        //cout<<fetch_string<<"   ";
        cout<<finish_string<<endl;
    }


}