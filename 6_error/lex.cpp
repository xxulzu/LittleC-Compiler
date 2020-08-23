#include "def.h"
/**
    ���дʷ���������ʵ��
**/

unordered_map<string, int> keywords = {{"int",1}, {"if",2}, {"else",3},
                                       {"while", 4}};
unordered_map<char, int> separators = {{'{',5}, {'}',6}, {';', 7}, {'(', 8}, {')', 9},
                                       {',', 10}};
unordered_map<char, int> operators1 = {{'=', 11}, {'+', 12}, {'-', 13}, {'*', 14},
                                        {'/', 15}, {'>', 16}, {'<', 17}};
unordered_map<string, int> operators2 = {{">=", 18}, {"<=", 19}, {"==", 20}, {"!=", 21}};

vector<string> ids; //���б�ʶ��
vector<token> ans;  //���ű�
int cnt1 = 0;

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
    regex e("[a-zA-Z_][a-z0-9A-Z_]{0,19}", regex_constants::icase);
    return regex_match(s, e);
}

//�����������ͷָ��������
bool istoken(string s) {
//    cout << s << endl;
    if(keywords[s]!=0) { // keyword
        ans.push_back({s, "keyword", keywords[s], row});
    }
    else if(alldigit(s)) { //��number
        ans.push_back({s, "number", 0, row});
    }
    else if(isid(s)) { //id
        if(find(ids.begin(), ids.end(), s)!=ids.end()) { //new id
            ans.push_back({s, "id", ID+(cnt1++), row});
        }
        else {  //existing id
            int tmp = find(ids.begin(), ids.end(), s) - ids.begin(); //�ҵ�id�����ֱ���
            ans.push_back({s, "id", ID + tmp, row});
        }
    }
    else {return false;}
    return true;
}

//����ָ����������
bool isso(string s, int& i) {
//    cout << s[i] << s[i+1] << endl;
    if(separators[s[i]]!=0) { //�ָ���
        string tmp;
        tmp.push_back(s[i]);
//        cout << tmp << endl;
        ans.push_back({tmp, "separator", separators[s[i]], row});
        i++;
    }
    else if(operators2[s.substr(i,2)]!=0) { //˫�ַ��������һ��Ҫ�ȴ���˫�ַ�������
        ans.push_back({s.substr(i,2), "operator", operators2[s.substr(i,2)], row});
        i += 2;
    }
    else if(operators1[s[i]]!=0) { //���ַ������
        string tmp;
        tmp.push_back(s[i]);
//        cout << tmp << endl;
        ans.push_back({tmp, "operator", operators1[s[i]], row});
        i++;
    }
    else {return false;}
    return true;
}
