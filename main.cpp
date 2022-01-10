#include <iostream> //�����
#include <fstream> //���� �����
#include <string> //���ڿ� ó��
#include <vector> //����
#include <ctime> //�ð�
using namespace std;

struct card {
    int id;
    bool monster, spell, trap, normal, effect;
    bool fusion, ritual, spirit, union_, gemini;
    bool tuner, synchro, token, quickplay, continuous;
    bool equip, field, counter, flip, toon;
    bool xyz, pendulum, special, link;
    int level, type, attribute;
    bool marker[8];
    int scale, attack, defense;
    string name, text, pen_text;
};

int ids[100000000]; //ī�� ���̵� ����

int main() {
    bool flag;
    int cnt = 0, i, x;
    card input;
    vector<card> cards; //ī�� ���
    ifstream cdb; //DB ����

    cout << "DB �ε� ����" << endl;
    double start_time = clock();
    cdb.open("cdb.txt");
    if(cdb.fail()) {
        cout << "���� : DB ������ �����ϴ�";
        return -1;
    }
    while(!cdb.eof()) { //������ ������
        cdb >> input.id >> input.monster >> input.spell >> input.trap >> input.normal
        >> input.effect >> input.fusion >> input.ritual >> input.spirit >> input.union_
        >> input.gemini >> input.tuner >> input.synchro >> input.token >> input.quickplay
        >> input.continuous >> input.equip >> input.field >> input.counter >> input.flip
        >> input.toon >> input.xyz >> input.pendulum >> input.special >> input.link
        >> input.level >> input.type >> input.attribute;
        for(i = 0; i < 8; i++) cdb >> input.marker[i];
        cdb >> input.scale >> input.attack >> input.defense;
        getline(cdb, input.name);
        getline(cdb, input.text);
        if(input.pendulum) getline(cdb, input.pen_text); //��ⷳ ���Ͷ�� ��ⷳ ȿ�� �Է�
        else input.pen_text = "";

        if(input.token) continue;
        input.name.erase(0, 1); //getline �Լ��� ���� �Բ� �Էµ� �� ���ڸ� ���� ����
        if(cnt != 0) if(input.name == cards[cnt - 1].name) continue; //������ �Է¹��� ī��� ���� �̸��̸� �������� �ʰ� �Ѿ (�ٸ� �Ϸ���Ʈ ����)
        cards.push_back(input);
        ids[input.id] = cnt++;
    }
    cdb.close();
    cout << "DB �ε� �Ϸ�! (�ҿ� �ð� : " << (clock() - start_time) / CLOCKS_PER_SEC << "��)" << endl << endl;

    string keyword, atts[] = {"��", "��", "ȭ��", "�ٶ�", "��", "���", "��"}; //�Ӽ�
    string types[] = {"����", "������", "õ��", "�Ǹ�", "�𵥵�", "���", "��", "ȭ��", "�ϼ�", "����߼�", "�Ĺ�", "����", "����",
                      "�巡��", "�߼�", "�߼�����", "����", "���", "�ط�", "�����", "����ű", "ȯ�ž߼�", "â����", "ȯ��", "���̹���"}; //����
    vector<int> reslist;

    cout << "���α׷��� �����Ϸ��� \"Quit\" �Է�" << endl;
    while(true) {
        cout << "�˻��� �Է� : ";
        do {
        keyword = "\0";
        getline(cin, keyword);
        } while(keyword == "\0"); //�ƹ��͵� �Էµ��� �ʾ����� ���α׷��� ������ ����

        if(keyword == "Quit") return 0; // ���α׷� ����
        cout << endl << "�˻� ���� (" << keyword << ")" << endl;
        start_time = clock();
        vector<int>().swap(reslist); //�˻� ��� ����Ʈ �ʱ�ȭ
        for(i = 0; i < cnt; i++)
            if(cards[i].name.find(keyword, 0) != string::npos ||
               cards[i].text.find(keyword, 0) != string::npos ||
               cards[i].pen_text.find(keyword, 0) != string::npos) //�˻�� ���ԵǾ��ִ��� �˻�
                reslist.push_back(i);
        cout << "�˻� �Ϸ�! (�˻� ��� : " << reslist.size() << "��, �ҿ� �ð� : " << (clock() - start_time) / CLOCKS_PER_SEC << "��)" << endl << endl;
        for(i = 0; i < reslist.size(); i++) //�˻� ��� ����Ʈ ���
            cout << "[" << i << "] " << cards[reslist[i]].name << endl;

        if(reslist.size() == 0) { //�˻� ����� ������ �ٽ� �ǵ��ư�
            cout << "ã�� ī�尡 �����ϴ�." << endl << endl;
            continue;
        }
        else if(reslist.size() == 1) x = 0; //�˻� ����� 1���� �ٷ� ����
        else { //�˻� ����� 2�� �̻��̸� ��� �� ����
            cout << endl << "��ȣ �Է� : ";
            cin >> x;
        }
        x = reslist[x];

        flag = false;
        cout << endl << endl << cards[x].name << endl << endl;
        if(cards[x].monster) {
            if(cards[x].xyz) cout << "��ũ";
            else if(cards[x].link) { //��ũ ��Ŀ ���
                cout << (cards[x].marker[5] ? "��" : "  ") << (cards[x].marker[6] ? "��" : "  ") << (cards[x].marker[7] ? "��" : "  ") << endl
                << (cards[x].marker[3] ? "��" : "  ") << "  " << (cards[x].marker[4] ? "��" : "  ") << endl
                << (cards[x].marker[0] ? "��" : "  ") << (cards[x].marker[1] ? "��" : "  ") << (cards[x].marker[2] ? "��" : "  ") << " ��ũ";
            }
            else cout << "����";
            cout << " " << cards[x].level << " | " << atts[cards[x].attribute] << " �Ӽ� | " << types[cards[x].type] << "��";
            if(cards[x].pendulum) //��ⷳ ������ ���
                cout << " | ��ⷳ ������ : " << cards[x].scale;
            cout << endl;
            //���� �з� ���
            if(cards[x].flip) {
                cout << "������";
                flag = true;
            }
            if(cards[x].union_) {
                if(flag) cout << " / ";
                cout << "���Ͽ�";
                flag = true;
            }
            if(cards[x].special) {
                if(flag) cout << " / ";
                cout << "Ư�� ��ȯ";
                flag = true;
            }
            if(cards[x].ritual) {
                if(flag) cout << " / ";
                cout << "�ǽ�";
                flag = true;
            }
            if(cards[x].fusion) {
                if(flag) cout << " / ";
                cout << "����";
                flag = true;
            }
            if(cards[x].synchro) {
                if(flag) cout << " / ";
                cout << "��ũ��";
                flag = true;
            }
            if(cards[x].xyz) {
                if(flag) cout << " / ";
                cout << "������";
                flag = true;
            }
            if(cards[x].link) {
                if(flag) cout << " / ";
                cout << "��ũ";
                flag = true;
            }
            if(cards[x].pendulum) {
                if(flag) cout << " / ";
                cout << "��ⷳ";
                flag = true;
            }
            if(cards[x].tuner) {
                if(flag) cout << " / ";
                cout << "Ʃ��";
                flag = true;
            }
            if(cards[x].toon) {
                if(flag) cout << " / ";
                cout << "��";
                flag = true;
            }
            if(cards[x].normal) {
                if(flag) cout << " / ";
                cout << "�Ϲ�";
                flag = true;
            }
            if(cards[x].effect) {
                if(flag) cout << " / ";
                cout << "ȿ��";
                flag = true;
            }
            if(cards[x].gemini) {
                if(flag) cout << " / ";
                cout << "���";
                flag = true;
            }
            cout << " ����";
            if(cards[x].pendulum) { //��ⷳ ȿ�� ���
                cout << endl << endl << "[��ⷳ ȿ��]" << endl;
                for(i = 0; i < cards[x].pen_text.length(); i++)
                    cout << (cards[x].pen_text[i] == '|' ? '\n' : cards[x].pen_text[i]); //�ٹٲ� ó��
            }
            cout << endl << endl;
            if(cards[x].normal) cout << "[�÷��̹� �ؽ�Ʈ]";
            else cout << "[ȿ��]";
        }
        else {
            if(cards[x].continuous) cout << "����"; //����/���� ī�� �з� ���
            else if(cards[x].equip) cout << "����";
            else if(cards[x].quickplay) cout << "�Ӱ�";
            else if(cards[x].field) cout << "�ʵ�";
            else if(cards[x].ritual) cout << "�ǽ�";
            else if(cards[x].counter) cout << "ī����";
            else cout << "�Ϲ�";
            if(cards[x].spell) cout << " ����";
            else cout << " ����";
            cout << endl << endl << "[ȿ��]";
        }
        cout << endl;
        for(i = 0; i < cards[x].text.length(); i++)
            cout << (cards[x].text[i] == '|' ? '\n' : cards[x].text[i]); //�ٹٲ� ó��
        if(cards[x].monster) //���� ī���� ��� ��/�� ���
            cout << endl << endl << "ATK / " << cards[x].attack << " | DEF / " << cards[x].defense;
        cout << endl << endl << endl;
    }//�ٽ� �˻��� �Է����� �ǵ��ư�
    return 0;
}
