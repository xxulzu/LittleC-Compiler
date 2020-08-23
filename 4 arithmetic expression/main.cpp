#include <bits/stdc++.h>
using namespace std;
//�趨�����������ʽֻ��һ��

string s;
int cnt = 0;
vector<char> in;    //��׺���ʽ
vector<char> post;  //��׺���ʽ
stack<char> help;
map<int, char> ans;


void F(char token);
void E(char token);

char getNext() {
    while(s[cnt]==' ' && cnt<s.length()) cnt++; //ȥ���ո�
    if(cnt==s.length()) return '$';       //�ַ�������
    return s[cnt++];
}

void A(char token) {
//    cout << token << endl;
    if(token=='+' | token=='-') return;
    else {
        cout << "Error!" << endl;
        exit(0);
    }
}

void M(char token) {
   if(token=='*' | token=='/') return;
    else {
        cout << "Error!" << endl;
        exit(0);
    }
}

void F(char token) {
//    cout << token << endl;
    if(isalnum(token)) return;  // id��number
    else if(token=='(') {
        char c = getNext();
        if(c=='$') {
            cout << "Error!" << endl;
            exit(0);
        }
        E(c);
        c = getNext();
        if(c!=')') {
            cout << "Error!" << endl;
            exit(0);
        }
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
        char c = getNext();
        if(c=='$') {                    //M��FOLLOWû��$
            cout << "Error!" << endl;
            exit(0);
        }
        F(c);
        c = getNext();
        if(c=='$') return;              //F��FOLLOW��$
        T1(c);
    }
}

void T(char token) {
//    cout << token << endl;
    F(token);
    char c = getNext();
    if(c=='$') return;
    T1(c);
}

void E1(char token) {
//    cout << token << endl;
    if(token==')' || token=='$') {  //FOLLOW������)��$
        cnt--;
        return;
    }
    else {
        A(token);
        char c = getNext();
        if(c=='$') {
            cout << "Error!" << endl;
            exit(0);
        }
        T(c);
        c = getNext();
        if(c=='$') return;
        E1(c);
    }
}

void E(char token) {
//    cout << token << endl;
    T(token);
    char c = getNext();
    if(c=='$') return;      //T��FOLLOW����$
    E1(c);
}

int cmp(char a, char b) {
    // 2:a>b, 1:a<b, 0:a=b
    if(b=='(') return 2; //(���ȼ����
    if((a=='*'|| a=='/') && (b=='+'|| b=='-')) return 2; //>
    if((a=='+'|| a=='-') && (b=='*'|| b=='/')) return 1; //<
    if((a=='+'|| a=='-') && (b=='+'|| b=='-')) return 0; //=
    if((a=='*'|| a=='/') && (b=='*'|| b=='/')) return 0; //=
}

///��׺���ʽת��׺���ʽ
void in2post() {
    for(int i=0; i<s.length(); i++) {
//        cout << s[i] << endl;
        if(s[i]==' ') continue; //ȥ�ո�
        if(isalnum(s[i])) { //id��numberֱ�����
            in.push_back(s[i]);
            post.push_back(s[i]);
        }
        else if(s[i]=='(') { //����ջ�����ȼ������
            help.push(s[i]);
        }
        else if(s[i]==')') {
            while(help.top()!='(') { //(ǰ���
//                cout << help.top()<<endl;
                post.push_back(help.top());
                help.pop();
            }
            help.pop(); //'('��ջ
        }
        else if(help.empty()) { //�������������ջ�գ�ֱ����ջ
            in.push_back(s[i]);
            help.push(s[i]);
        }
        else if (cmp(s[i], help.top())==2) { //���ȼ�����ջ��
            in.push_back(s[i]);
//            cout << help.top()<<endl;
            help.push(s[i]);
        }
        else { //���ȼ�С�ڵ���ջ��
            in.push_back(s[i]);
            while(!help.empty() && (cmp(help.top(), s[i])==2 || cmp(help.top(), s[i])==0)) {
//                cout << help.top()<<endl;
                post.push_back(help.top());
                help.pop();
            }
            help.push(s[i]);
        }
    }
    while(!help.empty()) {
//        cout << help.top()<<endl;
        post.push_back(help.top());
        help.pop();
    }
}

///�к�ת��
void level(int root, int start, int end, int index) {
    if(start>end) return;
    int i = start;
    while(i<end && in[i]!=post[root]) i++; //�ҵ������е�root
    ans[index] = post[root];
    level(root-(end-i+1), start, i-1, 2*index+1);
    level(root-1, i+1, end, 2*index+2);
}

int main()
{
    getline(cin, s);

    ///�ж�������Ƿ�����ķ�
    E(getNext());
    cout <<"Right."<<endl;

    ///�����﷨��

    ///1 ��׺ת��׺
    in2post();
    ///2 �������ת����
    int n = post.size();
    level(n-1, 0, n-1, 0);

    cout << "Inorder: ";
    for(auto it=in.begin(); it!=in.end(); it++) cout << *it;
    cout << endl;
    cout << "Postorder: ";
    for(auto it=post.begin(); it!=post.end(); it++) cout << *it;
    cout << endl;

    ///3 �������
    cout << "Levelorder: ";
    for(auto it=ans.begin(); it!=ans.end(); it++) {
        cout << it->second;
    }

    return 0;
}
