#include <bits/stdc++.h>
#define NUMBER 0
#define ID     27
using namespace std;

///����ģ��
struct token {
    string val;     //����ֵ
    string type;    //��������, keyword, separator, operator, id, number
    int num;        //�����ֱ���
};

unordered_map<string, int> keywords = {{"int",1}, {"if",2}, {"else",3},
                                       {"while", 4}, {"main", 5}, {"return", 6}};
unordered_map<char, int> separators = {{'{',7}, {'}',8}, {';', 9}, {'(', 10}, {')', 11},
                                       {'\\', 12}, {'"', 13}, {',', 14}};
unordered_map<char, int> operators1 = {{'=', 15}, {'+', 16}, {'-', 17}, {'*', 18},
                                        {'/', 19}, {'>', 20}, {'<', 21}, {'%', 22}};
unordered_map<string, int> operators2 = {{">=", 23}, {"<=", 24}, {"==", 25}, {"!=", 26}};
vector<string> ids; //���б�ʶ��
vector<token> ans;  //���ű�
int cnt = 0; //��¼id����

//�ж������ַ����Ƿ�Ϊ��number
bool alldigit(string s) {
    if(s[0]=='-') s = s.substr(1); //����ȥ������
    for(int i=0; i<s.length(); i++) {
        if(!isdigit(s[i])) return false;
    }
    if(s.length()>15) return false;
    return true;
}

//�ж��Ƿ�Ϊ�Ϸ����ַ���
bool isid(string s) {
    regex e("[a-zA-Z_][a-z0-9A-Z_]{0,18}", regex_constants::icase);
    return regex_match(s, e);
}

//�����������ͷָ��������
bool istoken(string s) {
//    cout << s << endl;
    if(keywords[s]!=0) { // keyword
        ans.push_back({s, "keyword", keywords[s]});
    }
    else if(alldigit(s)) { //��number
        ans.push_back({s, "number", 0});
    }
    else if(isid(s)) { //id
        if(find(ids.begin(), ids.end(), s)!=ids.end()) { //new id
            ans.push_back({s, "id", ID+(cnt++)});
        }
        else {  //existing id
            int tmp = find(ids.begin(), ids.end(), s) - ids.begin(); //�ҵ�id�����ֱ���
            ans.push_back({s, "id", ID + tmp});
        }
    }
    else {return false;}
    return true;
}

bool isso(string s, int& i) {
//    cout << s[i] << s[i+1] << endl;
    if(separators[s[i]]!=0) { //�ָ���
        string tmp;
        tmp.push_back(s[i]);
//        cout << tmp << endl;
        ans.push_back({tmp, "separator", separators[s[i]]});
        i++;
    }
    else if(operators2[s.substr(i,2)]!=0) { //˫�ַ��������һ��Ҫ�ȴ���˫�ַ�������
        ans.push_back({s.substr(i,2), "operator", operators2[s.substr(i,2)]});
        i += 2;
    }
    else if(operators1[s[i]]!=0) { //���ַ������
        string tmp;
        tmp.push_back(s[i]);
//        cout << tmp << endl;
        ans.push_back({tmp, "operator", operators1[s[i]]});
        i++;
    }
    else {return false;}
    return true;
}


///����ģ��
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

    string s;
    while(ifs >> s) { //string���԰��ո�ָ��ַ�������
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
                    cout << "Error!" << endl;
                    return 0;
                }
            }

            //����ָ����������
            if(!isso(s,i)) {
                cout << "Error!" << endl;
                return 0;
            }
            j = i; //�ӷָ�����һ��λ�ÿ�ʼ����

        }

        if(flag) { //sû�зָ����������
            if(!istoken(s.substr(j))) {
                cout << "Error!" << endl; //���ǺϷ���5��token��ֱ�ӱ���
                return 0;
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
    return 0;
}
