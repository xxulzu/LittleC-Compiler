#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

string ans = "";

int main() {
    string s;
    cin >> s; // start
    getchar(); //start����Ļ��з�
    while(getline(cin, s)) {
        if(s=="end") { break;}
        ans += s;
        ans += "\n";
    }

    int i=0, j=0, flag=0; //flag���/*
    int len = ans.length();
    while(i+1<len) {
        if(ans[i]=='/' && ans[i+1]=='/') { //����ע��//
            j = i+2;
            while(j<len) {
                if(ans[j]=='\n') {
                    ans = ans.substr(0, i) + ans.substr(j); //ȥ��ע����
                    break; //������//
                }
                else j++;
            }
        }
        else if(ans[i]=='/' && ans[i+1]=='*' && !flag) {
            flag=1;
            j=i+2;
            while(j+1<len) {
                if(ans[j]=='*' && ans[j+1]=='/') {
                    flag=0;
                    ans = ans.substr(0, i) + ans.substr(j+2);
                    break; // һ��/**/�������
                }
                else j++;
            }
            if(flag) {
                ans = ans.substr(0,i) + "\n";
                break;//�Ѿ����ַ���β��û���ҵ�*/������ֱ�ӱ�����
            }
        }
        else i++;
    }
    cout << "start\n" << ans;
    if(flag) {
        cout << "error";
    }
    else cout << "end";
    return 0;
}


