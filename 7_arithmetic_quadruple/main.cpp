#include <bits/stdc++.h>
using namespace std;
//�趨�����������ʽֻ��һ��

string s;
struct quad {
    char op;
    string arg1, arg2, res;
};
int cnt = 0;//ȡ�ַ����е��ַ�
int ti = 1; //ti�е�i����

stack<string> num; //������ջ
stack<char> ope; //�����ջ
vector<quad> ans;


void F(char token);
void E(char token);

///��������ȼ��Ƚ�
int cmp(char a, char b) {
    // 2:a>b, 1:a<b, 0:a=b
    if(b=='(') return 2; //(���ȼ����
    if((a=='*'|| a=='/') && (b=='+'|| b=='-')) return 2; //>
    if((a=='+'|| a=='-') && (b=='*'|| b=='/')) return 1; //<
    if((a=='+'|| a=='-') && (b=='+'|| b=='-')) return 0; //=
    if((a=='*'|| a=='/') && (b=='*'|| b=='/')) return 0; //=
}

///������Ԫʽ
string generquad(char op, string arg1, string arg2) {
    string tmp = "t" + to_string(ti++);
    ans.push_back(quad{op, arg1, arg2, tmp});
    return tmp; //������Ԫʽ��result
}

///��ȡ���ʽs��һ���ַ�
char getNext() {
    while(s[cnt]==' ' && cnt<s.length()) cnt++; //ȥ���ո�
    if(cnt==s.length()) {cnt++;return '$';}             //�ַ�������
    return s[cnt++];
}

void A(char token) {
//    cout << token << endl;
    if(token=='+' | token=='-') {
        if(ope.empty()) { ///�����ջ�գ�ֱ����ջ
            ope.push(token);
        }
        else { ///�����ջ����
            if(cmp(token, ope.top())==2) {///���ȼ�>ջ��
                ope.push(token);
            }
            else {///���ȼ�<=ջ��
                while(!ope.empty()&&(cmp(token, ope.top())!=2)) {
                    string a1 = num.top(); num.pop();
                    string a2 = num.top(); num.pop();
                    char o = ope.top(); ope.pop();
                    string tmp = generquad(o, a2, a1);
                    num.push(tmp);
                }
                ope.push(token);
            }
        }
        return;
    }
    else {
        cout << "Error!" << endl;
        exit(0);
    }
}

void M(char token) {
   if(token=='*' | token=='/') {
        if(ope.empty()) { ///�����ջ�գ�ֱ����ջ
            ope.push(token);
        }
        else { ///�����ջ����
            if(cmp(token, ope.top())==2) {///���ȼ�>ջ��
                ope.push(token);
            }
            else {///���ȼ�<=ջ��
                while(!ope.empty()&&(cmp(token, ope.top())!=2)) {
                    string a1 = num.top(); num.pop();
                    string a2 = num.top(); num.pop();
                    char o = ope.top(); ope.pop();
                    string tmp = generquad(o, a2, a1);
                    num.push(tmp);
                }
                ope.push(token);
            }
        }
        return;
   }
    else {
        cout << "Error!" << endl;
        exit(0);
    }
}

void F(char token) {
//    cout << token << endl;
    if(isalnum(token)) {
        ///id��number��ջ
        string tmp;
        tmp.push_back(token);
        num.push(tmp);
        return;  // id��number
    }
    else if(token=='(') {
        ope.push('(');
        E(getNext());
        char c = getNext();
        if(c!=')') {
            cout << "Error!" << endl;
            exit(0);
        }
        ///cΪ������
        while(ope.top()!='(') {
            string a1 = num.top(); num.pop();
            string a2 = num.top(); num.pop();
            char o = ope.top(); ope.pop();
            string tmp = generquad(o, a2, a1);
            num.push(tmp);
        }
        ope.pop(); //(��ջ

    }
    else {
        cout << "Error!" << endl;
        exit(0);
    }
}


void T1(char token) {
//    cout << token << endl;
    if(token=='+' || token=='-' || token==')' || token=='$') {
        cnt--;
        return;  //FOLLOW����+-)$
    }
    else {
        M(token);
        F(getNext());
        T1(getNext());
    }
}

void T(char token) {
//    cout << token << endl;
    F(token);
    T1(getNext());
}

void E1(char token) {
//    cout << token << endl;
    if(token==')' || token=='$') {  //FOLLOW������)��$
        cnt--;
        return;
    }
    else {
        A(token);
        T(getNext());
        E1(getNext());
    }
}

void E(char token) {
//    cout << token << endl;
    T(token);
    E1(getNext());
}


int main()
{
    getline(cin, s);

    ///�ж�������Ƿ�����ķ�
    E(getNext());
    if(num.size()==1) {
        string tmp = num.top();
        ans.push_back(quad{'_', tmp, "_", "_"});
    }
    while(!ope.empty()) {
        string a1 = num.top(); num.pop();
        string a2 = num.top(); num.pop();
        char o = ope.top(); ope.pop();
        string tmp = generquad(o, a2, a1);
        num.push(tmp);
    }
    cout <<"�﷨������ȷ����Ԫʽ���£�"<<endl;
    for(int i=0; i<ans.size(); i++) {
        cout << setw(5) << ans[i].op
             << setw(5) << ans[i].arg1
             << setw(5) << ans[i].arg2
             << setw(5) << ans[i].res << endl;
    }
    return 0;
}
