#include <iostream>
struct Date {
private:
    int y;
    int m;
    int d;
    int h;
    int min;
    int s;
public:
    Date(int y_, int m_, int d_, int h_, int min_, int s_): y(y_), m(m_), d(d_), h(h_), min(min_), s(s_) {}
    Date() {
        y = 0;
    }
    Date(std::string date) {
        y =  std::stoi(date[0]) * 1000 + std::stoi(date[1]) * 100 + std::stoi(date[2]) * 10 + std::stoi(date[3]);
        m = std::stoi(date[5]) * 10 + std::stoi(date[6]);
        d = std::stoi(date[8]) * 10 + std::stoi(date[9]);
        h = std::stoi(date[11]) * 10 + std::stoi(date[12]);
        min = std::stoi(date[14]) * 10 + std::stoi(date[15]);
        s = std::stoi(date[17]) * 10 + std::stoi(date[18]);
    }
    void dump() {
        std::cout << y << "-" << m << "-" << d << "-" << h << "-" << min << "-" << s << '\n';
    }
    bool operator<(const Date& other) const {
        if (y < other.y)
            return true;
        else if (y > other.y)
            return false;
        else {
            if (m < other.m)
                return true;
            else if (m > other.m)
                return false;
            else {
                if (d < other.d)
                    return true;
                else if (d > other.d)
                    return false;
                else {
                    if (h < other.h)
                        return true;
                    else if (h > other.h)
                        return false;
                    else {
                        if (min < other.min)
                            return true;
                        else if (min > other.min)
                            return false;
                        else {
                        if (s < other.s)
                            return true;
                        else if (s > other.s)
                            return false;
                        }
                    }   
                }
            }   
        }
        return true;
    }
    bool operator>(const Date& other) const {
        if (*this<other) {
            return false;
        }
        return true; 
    }
    bool operator==(const Date& other) const {
        if (!(*this<other) && !(*this>other)) {
            return true;
        }
        return false; 
    }

    Date& operator++() {
        this -> d++;
        if (d > 30) {
            d -= 30;
            m++;
        }
        if (m > 12) {
            m-=12;
            y++;
        }
        return *this;
    }
};
