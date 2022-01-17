//
//  Weather.hpp
//  7_structure
//
//  Created by HaoyuLu on 2021/12/20.
//

#ifndef Weather_hpp
#define Weather_hpp

#include <iostream>
#include <vector>
using namespace std;

static int mon[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Weather {
public:
    Weather(): num(""), year(2006), month(0), day(0), week(0), quarter(0), city(""), index(0), quality(""), level(""), pollution(""), total(0) {};
    Weather(string n, int y, int m, int d, int idx, string c, string p, string q, string l): num(n), year(y), month(m), day(d), week(0), quarter(0), city(c), index(idx), quality(q), level(l), pollution(p), total(0) {
        total = this->day;
        for(int i = 0; i < this->month - 1; i++) total += mon[i];
        ConvertWeek();
        ConvertQuarter();
    };
    Weather(int m, int d): num(""), year(2006), month(m), day(d), week(0), quarter(0), city(""), index(0), quality(""), level(""), pollution(""), total(0) {
        total = this->day;
        for(int i = 0; i < this->month - 1; i++) total += mon[i];
        ConvertWeek();
        ConvertQuarter();
    };
    Weather(string ci, string n, double average): num(n), year(2006), month(0), day(0), week(0), quarter(0), city(ci), index(0), quality(""), level(""), pollution(""), total(0), avg(average) {
        total = this->day;
        for(int i = 0; i < this->month - 1; i++) total += mon[i];
        ConvertWeek();
        ConvertQuarter();
    };
    void ConvertWeek();
    void ConvertQuarter();
    string GetCity();
    string GetNum();
    double getAverage();
    bool operator > (Weather &w);
    bool operator < (Weather &w);
    bool operator == (Weather &w);
    
    friend istream &operator >> (istream &in, Weather &w);
    friend ostream &operator << (ostream &out, Weather &w);
    // 指定城市按周、月、季度查找
    friend int BinarySearch(vector<Weather> &w, int m, int d);
    friend vector<Weather> BinarySearchRevised_week(vector<Weather> &w, int we);
    friend vector<Weather> BinarySearchRevised_month(vector<Weather> &w, int mo);
    friend vector<Weather> BinarySearchRevised_quarter(vector<Weather> &w, int qua);
    // 指定城市，按周、月、季度查找返回指定空气质量的天数
    friend int StatisticalSearch_city_week(vector<Weather> &w, int week, string quality);
    friend int StatisticalSearch_city_month(vector<Weather> &w, int month, string quality);
    friend int StatisticalSearch_city_quarter(vector<Weather> &w, int quarter, string quality);
    friend int StatisticalSearch_city_year(vector<Weather> &w, string quality);
    // 返回周、月、季度各城市为指定空气质量的天数
    friend vector<Weather> StatisticalSearch_week(vector< vector<Weather> > &w, int we, string qual, int days);
    friend vector<Weather> StatisticalSearch_month(vector< vector<Weather> > &w, int mo, string qual, int days);
    friend vector<Weather> StatisticalSearch_quarter(vector< vector<Weather> > &w, int qua, string qual, int days);
    friend vector<Weather> StatisticalSearch_year(vector< vector<Weather> > &w, string qual, int days);
    // 按周、月、季度对各城市平均空气质量排序
    friend vector<Weather> SortSearch_week(vector< vector<Weather> > &w, int we);
    friend vector<Weather> SortSearch_month(vector< vector<Weather> > &w, int mo);
    friend vector<Weather> SortSearch_quarter(vector< vector<Weather> > &w, int qua);
    friend vector<Weather> SortSearch_year(vector< vector<Weather> > &w);
    
private:
    int year, month, day, index, week, quarter, total;
    double avg;
    string num, pollution, city, quality, level;
};

#endif /* Weather_hpp */
