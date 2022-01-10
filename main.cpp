#include <iostream> //입출력
#include <fstream> //파일 입출력
#include <string> //문자열 처리
#include <vector> //벡터
#include <ctime> //시간
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

int ids[100000000]; //카드 아이디 저장

int main() {
    bool flag;
    int cnt = 0, i, x;
    card input;
    vector<card> cards; //카드 목록
    ifstream cdb; //DB 파일

    cout << "DB 로딩 시작" << endl;
    double start_time = clock();
    cdb.open("cdb.txt");
    if(cdb.fail()) {
        cout << "오류 : DB 파일이 없습니다";
        return -1;
    }
    while(!cdb.eof()) { //파일의 끝까지
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
        if(input.pendulum) getline(cdb, input.pen_text); //펜듈럼 몬스터라면 펜듈럼 효과 입력
        else input.pen_text = "";

        if(input.token) continue;
        input.name.erase(0, 1); //getline 함수로 인해 함께 입력된 맨 앞자리 띄어쓰기 제거
        if(cnt != 0) if(input.name == cards[cnt - 1].name) continue; //직전에 입력받은 카드와 같은 이름이면 저장하지 않고 넘어감 (다른 일러스트 정보)
        cards.push_back(input);
        ids[input.id] = cnt++;
    }
    cdb.close();
    cout << "DB 로딩 완료! (소요 시간 : " << (clock() - start_time) / CLOCKS_PER_SEC << "초)" << endl << endl;

    string keyword, atts[] = {"땅", "물", "화염", "바람", "빛", "어둠", "신"}; //속성
    string types[] = {"전사", "마법사", "천사", "악마", "언데드", "기계", "물", "화염", "암석", "비행야수", "식물", "곤충", "번개",
                      "드래곤", "야수", "야수전사", "공룡", "어류", "해룡", "파충류", "사이킥", "환신야수", "창조신", "환룡", "사이버스"}; //종족
    vector<int> reslist;

    cout << "프로그램을 종료하려면 \"Quit\" 입력" << endl;
    while(true) {
        cout << "검색어 입력 : ";
        do {
        keyword = "\0";
        getline(cin, keyword);
        } while(keyword == "\0"); //아무것도 입력되지 않았을때 프로그램의 진행을 막음

        if(keyword == "Quit") return 0; // 프로그램 종료
        cout << endl << "검색 시작 (" << keyword << ")" << endl;
        start_time = clock();
        vector<int>().swap(reslist); //검색 결과 리스트 초기화
        for(i = 0; i < cnt; i++)
            if(cards[i].name.find(keyword, 0) != string::npos ||
               cards[i].text.find(keyword, 0) != string::npos ||
               cards[i].pen_text.find(keyword, 0) != string::npos) //검색어가 포함되어있는지 검사
                reslist.push_back(i);
        cout << "검색 완료! (검색 결과 : " << reslist.size() << "개, 소요 시간 : " << (clock() - start_time) / CLOCKS_PER_SEC << "초)" << endl << endl;
        for(i = 0; i < reslist.size(); i++) //검색 결과 리스트 출력
            cout << "[" << i << "] " << cards[reslist[i]].name << endl;

        if(reslist.size() == 0) { //검색 결과가 없으면 다시 되돌아감
            cout << "찾는 카드가 없습니다." << endl << endl;
            continue;
        }
        else if(reslist.size() == 1) x = 0; //검색 결과가 1개면 바로 진행
        else { //검색 결과가 2개 이상이면 목록 중 선택
            cout << endl << "번호 입력 : ";
            cin >> x;
        }
        x = reslist[x];

        flag = false;
        cout << endl << endl << cards[x].name << endl << endl;
        if(cards[x].monster) {
            if(cards[x].xyz) cout << "랭크";
            else if(cards[x].link) { //링크 마커 출력
                cout << (cards[x].marker[5] ? "↖" : "  ") << (cards[x].marker[6] ? "↑" : "  ") << (cards[x].marker[7] ? "↗" : "  ") << endl
                << (cards[x].marker[3] ? "←" : "  ") << "  " << (cards[x].marker[4] ? "→" : "  ") << endl
                << (cards[x].marker[0] ? "↙" : "  ") << (cards[x].marker[1] ? "↓" : "  ") << (cards[x].marker[2] ? "↘" : "  ") << " 링크";
            }
            else cout << "레벨";
            cout << " " << cards[x].level << " | " << atts[cards[x].attribute] << " 속성 | " << types[cards[x].type] << "족";
            if(cards[x].pendulum) //펜듈럼 스케일 출력
                cout << " | 펜듈럼 스케일 : " << cards[x].scale;
            cout << endl;
            //몬스터 분류 출력
            if(cards[x].flip) {
                cout << "리버스";
                flag = true;
            }
            if(cards[x].union_) {
                if(flag) cout << " / ";
                cout << "유니온";
                flag = true;
            }
            if(cards[x].special) {
                if(flag) cout << " / ";
                cout << "특수 소환";
                flag = true;
            }
            if(cards[x].ritual) {
                if(flag) cout << " / ";
                cout << "의식";
                flag = true;
            }
            if(cards[x].fusion) {
                if(flag) cout << " / ";
                cout << "융합";
                flag = true;
            }
            if(cards[x].synchro) {
                if(flag) cout << " / ";
                cout << "싱크로";
                flag = true;
            }
            if(cards[x].xyz) {
                if(flag) cout << " / ";
                cout << "엑시즈";
                flag = true;
            }
            if(cards[x].link) {
                if(flag) cout << " / ";
                cout << "링크";
                flag = true;
            }
            if(cards[x].pendulum) {
                if(flag) cout << " / ";
                cout << "펜듈럼";
                flag = true;
            }
            if(cards[x].tuner) {
                if(flag) cout << " / ";
                cout << "튜너";
                flag = true;
            }
            if(cards[x].toon) {
                if(flag) cout << " / ";
                cout << "툰";
                flag = true;
            }
            if(cards[x].normal) {
                if(flag) cout << " / ";
                cout << "일반";
                flag = true;
            }
            if(cards[x].effect) {
                if(flag) cout << " / ";
                cout << "효과";
                flag = true;
            }
            if(cards[x].gemini) {
                if(flag) cout << " / ";
                cout << "듀얼";
                flag = true;
            }
            cout << " 몬스터";
            if(cards[x].pendulum) { //펜듈럼 효과 출력
                cout << endl << endl << "[펜듈럼 효과]" << endl;
                for(i = 0; i < cards[x].pen_text.length(); i++)
                    cout << (cards[x].pen_text[i] == '|' ? '\n' : cards[x].pen_text[i]); //줄바꿈 처리
            }
            cout << endl << endl;
            if(cards[x].normal) cout << "[플레이버 텍스트]";
            else cout << "[효과]";
        }
        else {
            if(cards[x].continuous) cout << "지속"; //마법/함정 카드 분류 출력
            else if(cards[x].equip) cout << "장착";
            else if(cards[x].quickplay) cout << "속공";
            else if(cards[x].field) cout << "필드";
            else if(cards[x].ritual) cout << "의식";
            else if(cards[x].counter) cout << "카운터";
            else cout << "일반";
            if(cards[x].spell) cout << " 마법";
            else cout << " 함정";
            cout << endl << endl << "[효과]";
        }
        cout << endl;
        for(i = 0; i < cards[x].text.length(); i++)
            cout << (cards[x].text[i] == '|' ? '\n' : cards[x].text[i]); //줄바꿈 처리
        if(cards[x].monster) //몬스터 카드일 경우 공/수 출력
            cout << endl << endl << "ATK / " << cards[x].attack << " | DEF / " << cards[x].defense;
        cout << endl << endl << endl;
    }//다시 검색어 입력으로 되돌아감
    return 0;
}
