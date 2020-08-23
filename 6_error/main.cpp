#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "def.h"
using namespace std;

int row = 0; //��¼����
string lines; //���ж��ļ�


int main()
{
    string fn;
    cout << "Please input the filename: ";
    cin >> fn;
    ifstream ifs(fn, ios::in);
    if(!ifs) {
        cout << "Failed to open the file." << endl;
        return 0;
    }

    ///�ʷ�����
    string s;
    while(getline(ifs, lines)) {
        row++;
        istringstream str(lines);
        while(str >> s) { //s���ո�ָ�����
    //        cout << s << endl;
            int i=0,j=0; //���ÿ���ָ���λ�ã��ʹ������Ӵ�λ��
            int flag = 0;
            //�Էָ����������Ϊ�����������ַ���������ָ���֮ǰ�Ĳ���
            while(i<s.length()) {
                while(i<s.length() && separators[s[i]]==0 && operators1[s[i]]==0) {//Ѱ�ҷָ����������
                    if(s.substr(i,2)=="!=") break;
                    i++; //���Ƿָ���
                }
                if(i==s.length()) {
                    flag = 1;
                    break;//û���ҵ�
                }

                if(j!=i) { //��������֮�������ݣ������м䲿��
                    string tmp = s.substr(j, i-j);
    //                cout << tmp << endl;
                    if(!istoken(tmp)) {
                        cout << "��" << row << "�У�" + tmp + " �ʷ�����" << endl;
                        return 0;
                    }
                }

                //����ָ����������
                if(!isso(s,i)) {
                    cout << "��" << row << "�У�" + s + " �ʷ�����" << endl;
                    return 0;
                }
                j = i; //�ӷָ�����һ��λ�ÿ�ʼ����

            }

            if(flag) { //sû�зָ����������
                if(!istoken(s.substr(j))) {
                    cout << "��" << row << "�У�" + s.substr(j) + " �ʷ�����" << endl; //���ǺϷ���5��token��ֱ�ӱ���
                    return 0;
                }
            }
        }
    }

    ofstream ofs("Word_List.txt", ios::out);
    if(!ofs) {
        cout << "Failed to create the output file." << endl;
        return 0;
    }

    ofs.setf(ios::left);
    for(int i=0; i<ans.size(); i++) {
        ofs << setw(15) << i+1
            << setw(20) << ans[i].type
            << setw(20) << ans[i].val
            << setw(15) << ans[i].num << endl;
    }
    ifs.close();
    ofs.close();
    cout << "�ʷ�������ɣ���ȷ" << endl;



    ///�﷨����
    BLOCK(getNext());
    cout << "�﷨������ɣ���ȷ" << endl;

    return 0;
}
