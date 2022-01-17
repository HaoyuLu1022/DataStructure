//
//  main.cpp
//  7_structure
//
//  Created by HaoyuLu on 2021/12/10.
//

#include <iostream>
#include <vector>
#include <map>
#include "Weather.hpp"
using namespace std;
vector< vector<Weather> > w;
map<string, int> cityidx;
map<string, int> citynumber;
//int mark;

void InputWeather() {
    Weather wea;
    freopen("/Users/HalveLuve/Downloads/SortSearch/SortSearch/data.txt", "r", stdin);

    int i = 0;
    string name, n;
    vector<Weather> tmp;
    while(cin >> wea) {
        if(tmp.size() != 0) {
            if(wea.GetCity() == tmp.back().GetCity()) tmp.push_back(wea);
            else if(wea.GetCity() != tmp.back().GetCity()) {
                name = tmp.back().GetCity();
                n = tmp.back().GetNum();
                cityidx.insert(pair<string, int>(name, i));
                citynumber.insert(pair<string, int>(n, i));
                w.push_back(tmp);
                tmp.clear();
                tmp.push_back(wea);
                i++;
            }
        }
        else tmp.push_back(wea);
    }
    w.push_back(tmp);
    n = w.back().back().GetNum();
    name = w.back().back().GetCity();
    cityidx.insert(pair<string, int>(name, i));
    citynumber.insert(pair<string, int>(n, i));
}

int main(int argc, const char * argv[]) {
    int mark;
    string citychoice, citynum;
    int choice, choice2;
    cout << "请输入查询模式（0-普通按年；1-普通按日查询；2-普通按周、月或季度查询；3-统计查询城市对应空气质量天数；4-统计查询满足给当空气质量天数条件的城市；5-指定时间排序查询）：";
    cin >> choice;
    if(choice != 4 && choice != 5) {
        cout << "请确定查询输入（1-城市名称；2-城市代码）：";
        cin >> choice2;
        switch (choice2) {
            case 1:
                cout << "请输入查询城市名称：";
                cin >> citychoice;
                break;
            case 2:
                cout << "请输入查询城市代码：";
                cin >> citynum;
                break;
            default:
                break;
        }
    }
    switch (choice) {
        case 1: { // by day
            int m, d;
            cout << "输入月日（空格隔开）：";
            cin >> m >> d;
            InputWeather();
            if(choice2 == 1) mark = cityidx[citychoice];
            else mark = citynumber[citynum];
            int result = BinarySearch(w[mark], m, d);
            cout << w[mark][result];
            break;
        }
            
        case 2: { // by week, month or quarter
            int ch;
            vector<Weather> ans;
            cout << "请选择查询依据（1-按周；2-按月；3-按季度）：";
            cin >> ch;
            switch (ch) {
                case 1: {
                    int we;
                    cout << "输入查询周数：";
                    cin >> we;
                    InputWeather();
                    if(choice2 == 1) mark = cityidx[citychoice];
                    else mark = citynumber[citynum];
                    ans = BinarySearchRevised_week(w[mark], we);
                    for(auto it = ans.begin(); it != ans.end(); it++)
                        cout << *it << endl;
                    break;
                }
                case 2: {
                    int mo;
                    cout << "输入查询月份：";
                    cin >> mo;
                    InputWeather();
                    if(choice2 == 1) mark = cityidx[citychoice];
                    else mark = citynumber[citynum];
                    ans = BinarySearchRevised_month(w[mark], mo);
                    for(auto it = ans.begin(); it != ans.end(); it++) cout << *it << endl;
                    break;
                }
                case 3: {
                    int qua;
                    cout << "输入查询季度：";
                    cin >> qua;
                    InputWeather();
                    if(choice2 == 1) mark = cityidx[citychoice];
                    else mark = citynumber[citynum];
                    ans = BinarySearchRevised_quarter(w[mark], qua);
                    for(auto it = ans.begin(); it != ans.end(); it++) cout << *it << endl;
                    break;
                }
                default:
                    break;
            }
            break;
        }
            
        case 3: {
            int ch;
            cout << "请选择查询依据（0-按年；1-按周；2-按月；3-按季度）：";
            cin >> ch;
            switch (ch) {
                case 1: {
                    int we;
                    string quality;
                    cout << "输入查询周数、空气质量（以空格隔开）：";
                    cin >> we >> quality;
                    InputWeather();
                    if(choice2 == 1) mark = cityidx[citychoice];
                    else mark = citynumber[citynum];
                    cout << StatisticalSearch_city_week(w[mark], we, quality) << endl;
                    break;
                }
                case 2: {
                    int mo;
                    string quality;
                    cout << "输入查询月份、空气质量（以空格隔开）：";
                    cin >> mo >> quality;
                    InputWeather();
                    if(choice2 == 1) mark = cityidx[citychoice];
                    else mark = citynumber[citynum];
                    cout << StatisticalSearch_city_month(w[mark], mo, quality) << endl;
                    break;
                }
                case 3: {
                    int qua;
                    string quality;
                    cout << "输入查询季度、空气质量（以空格隔开）：";
                    cin >> qua >> quality;
                    InputWeather();
                    if(choice2 == 1) mark = cityidx[citychoice];
                    else mark = citynumber[citynum];
                    cout << StatisticalSearch_city_quarter(w[mark], qua, quality) << endl;
                    break;
                }
                default: {
                    string quality;
                    cout << "输入查询空气质量：";
                    cin >> quality;
                    InputWeather();
                    if(choice2 == 1) mark = cityidx[citychoice];
                    else mark = citynumber[citynum];
                    cout << StatisticalSearch_city_year(w[mark], quality) << endl;
                    break;
                }
            }
            break;
        }
            
        case 4: {
            int ch;
            cout << "请选择查询依据（0-按年；1-按周；2-按月；3-按季度）：";
            cin >> ch;
            switch (ch) {
                case 1: {
                    int we, days;
                    string quality;
                    cout << "输入查询周数、空气质量、该周该空气质量的最少天数（以空格隔开）：";
                    cin >> we >> quality >> days;
                    InputWeather();
                    vector<Weather> byweek = StatisticalSearch_week(w, we, quality, days);
                    for(auto it = byweek.begin(); it != byweek.end(); it++) cout << it->GetCity() << " ";
                    cout << endl;
                    break;
                }
                case 2: {
                    int mo, days;
                    string quality;
                    cout << "输入查询月份、空气质量、该月该空气质量的最少天数（以空格隔开）：";
                    cin >> mo >> quality >> days;
                    InputWeather();
                    vector<Weather> bymonth = StatisticalSearch_month(w, mo, quality, days);
                    for(auto it = bymonth.begin(); it != bymonth.end(); it++) cout << it->GetCity() << " ";
                    cout << endl;
                    break;
                }
                case 3: {
                    int qua, days;
                    string quality;
                    cout << "输入查询季度、空气质量、该季度该空气质量的最少天数（以空格隔开）：";
                    cin >> qua >> quality >> days;
                    InputWeather();
                    vector<Weather> byquarter = StatisticalSearch_quarter(w, qua, quality, days);
                    for(auto it = byquarter.begin(); it != byquarter.end(); it++) cout << it->GetCity() << " ";
                    cout << endl;
                    break;
                }
                default: {
                    int days;
                    string quality;
                    cout << "输入查询空气质量、该年该空气质量的最少天数（以空格隔开）：";
                    cin >> quality >> days;
                    InputWeather();
                    vector<Weather> byyear = StatisticalSearch_year(w, quality, days);
                    for(auto it = byyear.begin(); it != byyear.end(); it++) cout << it->GetCity() << " ";
                    cout << endl;
                    break;
                }
            }
            break;
        }
            
        case 5: { // sort
            int ch, number;
            vector<Weather> ans;
            cout << "请选择查询依据（0-按年；1-按周；2-按月；3-按季度）：";
            cin >> ch;
            cout << "需要看前多少个城市的排名（一共86个）：";
            cin >> number;
            switch (ch) {
                case 1: {
                    int we;
                    cout << "输入查询周数：";
                    cin >> we;
                    InputWeather();
                    ans = SortSearch_week(w, we);
                    int cnt = 0;
                    for(int i = 0; i < number; i++) {
                        cout << ans[i].GetCity() << " " << ans[i].getAverage() << endl;
                    }
                    break;
                }
                case 2: {
                    int mo;
                    cout << "输入查询月份：";
                    cin >> mo;
                    InputWeather();
                    ans = SortSearch_month(w, mo);
                    for(int i = 0; i < number; i++) {
                        cout << ans[i].GetCity() << " " << ans[i].getAverage() << endl;
                    }
                    break;
                }
                case 3: {
                    int qua;
                    cout << "输入查询季度：";
                    cin >> qua;
                    InputWeather();
                    ans = SortSearch_quarter(w, qua);
                    for(int i = 0; i < number; i++) {
                        cout << ans[i].GetCity() << " " << ans[i].getAverage() << endl;
                    }
                    break;
                }
                default: {
                    InputWeather();
                    ans = SortSearch_year(w);
                    for(int i = 0; i < number; i++) {
                        cout << ans[i].GetCity() << " " << ans[i].getAverage() << endl;
                    }
                    break;
                }
            }
            break;
        }
        default: { // by year
            InputWeather();
            mark = cityidx[citychoice];
            for(auto it = w[mark].begin(); it != w[mark].end(); it++) cout << *it << endl;
            break;
        }
    }
     
    return 0;
}
