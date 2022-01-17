//
//  Weather.cpp
//  7_structure
//
//  Created by HaoyuLu on 2021/12/20.
//

#include "Weather.hpp"
#include <iostream>
using namespace std;

void Weather::ConvertWeek() {
    this->week = (this->total - 1) / 7 + 1;
}

void Weather::ConvertQuarter() {
    if(this->month <= 3) this->quarter = 1;
    else if(this->month >= 4 && this->month <= 6) this->quarter = 2;
    else if(this->month >= 7 && this->month <= 9) this->quarter = 3;
    else this->quarter = 4;
}


string Weather::GetCity() {
    return this->city;
}

string Weather::GetNum() {
    return this->num;
}

double Weather::getAverage() {
    return this->avg;
}

bool Weather::operator < (Weather &w) {
    if(this->month != w.month) return this->month < w.month;
    else {
        if(this->day != w.day) return this->day < w.day;
    }
    return false;
}

bool Weather::operator > (Weather &w) {
    if(this->month != w.month) return this->month > w.month;
    else {
        if(this->day != w.day) return this->day > w.day;
    }
    return false;
}

bool Weather::operator == (Weather &w) {
    return (this->month == w.month && this->day == w.day);
}

istream& operator >> (istream& in, Weather &w) {
    in >> w.num >> w.city >> w.pollution >> w.index >> w.level >> w.quality >> w.year >> w.month >> w.day;
    w.total = w.day;
    for(int i = 0; i < w.month - 1; i++) w.total += mon[i];
    w.ConvertWeek();
    w.ConvertQuarter();
    return in;
}

ostream& operator << (ostream& out, Weather &w) {
    out << w.num << "  " << w.city << "  " << w.pollution << "  " << w.index << "  " << w.level << "  " << w.quality << "  " << w.year << "  " << w.month << "  " << w.day << endl;
    return out;
}

int BinarySearch(vector<Weather> &wea, int m, int d) {
    Weather tmp(m, d);
    int low = 0, high = wea.size() - 1, mid;
    
    while(low <= high) {
        mid = low + (high - low) / 2;
        if(tmp < wea[mid]) low = mid + 1;
        if(tmp > wea[mid]) high = mid - 1;
        else if(tmp == wea[mid]) return mid;
    }
    return 0;
}

vector<Weather> BinarySearchRevised_week(vector<Weather> &w, int we) {
    int first = 0, last = 0;
    int low = 0, high = w.size() - 1, mid;
    vector<Weather> byweek;
    
    while(low <= high) {
        mid = low + (high - low) / 2;
        if(we < w[mid].week) low = mid + 1;
        if(we > w[mid].week) high = mid - 1;
        else if(we == w[mid].week) {
            first = mid;
            last = mid;
            while(first >= 0) {
                if(w[first].week != we) break;
                first--;
            }
            while(last <= w.size() - 1) {
                if(w[last].week != we) break;
                last++;
            }
            // 多减一次？
            break;
        }
    }
    
    for(int i = first + 1; i < last; i++) byweek.push_back(w[i]);
    return byweek;
}

vector<Weather> BinarySearchRevised_month(vector<Weather> &w, int mo) {
    int first = 0, last = 0;
    int low = 0, high = w.size() - 1, mid;
    vector<Weather> bymonth;

    while(low <= high) {
        mid = low + (high - low) / 2;
        if(mo < w[mid].month) low = mid + 1;
        if(mo > w[mid].month) high = mid - 1;
        else if(mo == w[mid].month){
            first = mid;
            last = mid;
            while(first >= 0) {
                if(w[first].month != mo) break;
                first--;
            }
            while(last <= w.size() - 1) {
                if(w[last].month != mo) break;
                last++;
            }
            break;
        }
    }
    
    for(int i = first + 1; i < last; i++) bymonth.push_back(w[i]);
    return bymonth;
}

vector<Weather> BinarySearchRevised_quarter(vector<Weather> &w, int qua) {
    int first = 0, last = 0;
    int low = 0, high = w.size() - 1, mid;
    vector<Weather> byquarter;
    
    while(low <= high) {
        mid = low + (high - low) / 2;
        if(qua < w[mid].quarter) low = mid + 1;
        if(qua > w[mid].quarter) high = mid - 1;
        else if(qua == w[mid].quarter){
            first = mid;
            last = mid;
            while(first >= 0) {
                if(w[first].quarter != qua) break;
                first--;
            }
            while(last <= w.size() - 1) {
                if(w[last].quarter != qua) break;
                last++;
            }
            break;
        }
    }
    
    for(int i = first + 1; i < last; i++) byquarter.push_back(w[i]);
    return byquarter;
}

int StatisticalSearch_city_week(vector<Weather> &w, int we, string qual) {
    vector<Weather> byweek = BinarySearchRevised_week(w, we);
//    vector<Weather> statistic_week;
    int cnt = 0;
    
    for(auto it = byweek.begin(); it != byweek.end(); it++) {
        if(it->quality == qual) cnt++;
    }
    return cnt;
}

int StatisticalSearch_city_month(vector<Weather> &w, int mo, string qual) {
    vector<Weather> bymonth = BinarySearchRevised_month(w, mo);
//    vector<Weather> statistic_month;
    int cnt = 0;
    for(auto it = bymonth.begin(); it != bymonth.end(); it++) {
        if(it->quality == qual) cnt++;
    }
    return cnt;
}

int StatisticalSearch_city_quarter(vector<Weather> &w, int qua, string qual) {
    vector<Weather> byquarter = BinarySearchRevised_quarter(w, qua);
//    vector<Weather> statistic_month;
    int cnt = 0;
    for(auto it = byquarter.begin(); it != byquarter.end(); it++) {
        if(it->quality == qual) cnt++;
    }
    return cnt;
}

int StatisticalSearch_city_year(vector<Weather> &w, string qual) {
    int cnt = 0;
    for(auto it = w.begin(); it != w.end(); it++) {
        if(it->quality == qual) cnt++;
    }
    return cnt;
}

vector<Weather> StatisticalSearch_week(vector< vector<Weather> > &w, int we, string qual, int days) {
    vector<Weather> bycity_week;
    for(auto it1 = w.begin(); it1 != w.end(); it1++) {
        vector<Weather> tmp = BinarySearchRevised_week(*it1, we);
        int cnt = 0;
        for(auto it2 = tmp.begin(); it2 != tmp.end(); it2++) {
            if(it2->quality == qual) cnt++;
            if(cnt > days) {
                bycity_week.push_back(*it2);
                break;
            }
        }
    }
    return bycity_week;
}

vector<Weather> StatisticalSearch_month(vector< vector<Weather> > &w, int mo, string qual, int days) {
    vector<Weather> bycity_month;
    for(auto it1 = w.begin(); it1 != w.end(); it1++) {
        vector<Weather> tmp = BinarySearchRevised_month(*it1, mo);
        int cnt = 0;
        for(auto it2 = tmp.begin(); it2 != tmp.end(); it2++) {
            if(it2->quality == qual) cnt++;
            if(cnt > days) {
                bycity_month.push_back(*it2);
                break;
            }
        }
    }
    return bycity_month;
}


vector<Weather> StatisticalSearch_quarter(vector< vector<Weather> > &w, int qua, string qual, int days) {
    vector<Weather> bycity_quarter;
    for(auto it1 = w.begin(); it1 != w.end(); it1++) {
        vector<Weather> tmp = BinarySearchRevised_quarter(*it1, qua);
        int cnt = 0;
        for(auto it2 = tmp.begin(); it2 != tmp.end(); it2++) {
            if(it2->quality == qual) cnt++;
            if(cnt > days) {
                bycity_quarter.push_back(*it2);
                break;
            }
        }
    }
    return bycity_quarter;
}

vector<Weather> StatisticalSearch_year(vector< vector<Weather> > &w, string qual, int days) {
    vector<Weather> bycity_year;
    for(auto it1 = w.begin(); it1 != w.end(); it1++) {
        int cnt = 0;
        for(auto it2 = it1->begin(); it2 != it1->end(); it2++) {
            if(it2->quality == qual) cnt++;
            if(cnt > days) {
                bycity_year.push_back(*it2);
                break;
            }
        }
    }
    return bycity_year;
}

int partition(vector<Weather> &w, int low, int high) {
    Weather pivot = w[low];
    while(low < high) {
        while(low < high && w[high].getAverage() >= pivot.getAverage()) high--;
        w[low] = w[high];
        while(low < high && w[low].getAverage() <= pivot.getAverage()) low++;
        w[high] = w[low];
    }
    w[low] = pivot;
//    for(auto it = w.begin(); it != w.end(); it++) cout << *it << endl;
    return low;
}

void QuickSort(vector<Weather> &w, int low, int high) {
    if(low < high) {
        int part = partition(w, low, high);
        QuickSort(w, low, part - 1);
        QuickSort(w, part + 1, high);
    }
}

vector<Weather> SortSearch_week(vector< vector<Weather> > &w, int we) {
    vector<Weather> weather;
    for(auto it = w.begin(); it != w.end(); it++) {
        vector<Weather> tmp = BinarySearchRevised_week(*it, we);
        double average = 0.0;
        for(auto it2 = tmp.begin(); it2 != tmp.end(); it2++) {
            average += it2->index;
        }
        average /= tmp.size() * 1.0;
        weather.push_back(Weather(tmp.back().city, tmp.back().num, average));
    }
    
    QuickSort(weather, 0, weather.size() - 1);
    return weather;
}

vector<Weather> SortSearch_month(vector< vector<Weather> > &w, int mo) {
    vector<Weather> weather;
    for(auto it = w.begin(); it != w.end(); it++) {
        vector<Weather> tmp = BinarySearchRevised_month(*it, mo);
        double average = 0.0;
        for(auto it2 = tmp.begin(); it2 != tmp.end(); it2++) {
            average += it2->index;
        }
        average /= tmp.size() * 1.0;
        weather.push_back(Weather(tmp.back().city, tmp.back().num, average));
    }
    
    QuickSort(weather, 0, weather.size() - 1);
    return weather;
}

vector<Weather> SortSearch_quarter(vector< vector<Weather> > &w, int qua) {
    vector<Weather> weather;
    for(auto it = w.begin(); it != w.end(); it++) {
        vector<Weather> tmp = BinarySearchRevised_quarter(*it, qua);
        double average = 0.0;
        for(auto it2 = tmp.begin(); it2 != tmp.end(); it2++) {
            average += it2->index;
        }
        average /= tmp.size() * 1.0;
        weather.push_back(Weather(tmp.back().city, tmp.back().num, average));
    }
    
    QuickSort(weather, 0, weather.size() - 1);
    return weather;
}

vector<Weather> SortSearch_year(vector< vector<Weather> > &w) {
    vector<Weather> weather;
    for(auto it = w.begin(); it != w.end(); it++) {
        double average = 0.0;
        for(auto it2 = it->begin(); it2 != it->end(); it2++) {
            average += it2->index;
        }
        average /= it->size() * 1.0;
        weather.push_back(Weather(it->back().city, it->back().num, average));
    }
    
    QuickSort(weather, 0, weather.size() - 1);
    return weather;
}
