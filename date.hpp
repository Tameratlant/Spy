#include <iostream>
int parse (char c) {
    return c - '0';
}
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
        y = parse(date[0]) * 1000 + parse(date[1]) * 100 + parse(date[2]) * 10 + parse(date[3]);
        m = parse(date[5]) * 10 + parse(date[6]);
        d = parse(date[8]) * 10 + parse(date[9]);
        h = parse(date[11]) * 10 + parse(date[12]);
        min = parse(date[14]) * 10 + parse(date[15]);
        s = parse(date[17]) * 10 + parse(date[18]);
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
        //printf("!!");
        //std::cout << (*this<other);
        if (*this<other) {
            //printf("!");
            return false;
        }
        return true; 
    }
    bool operator==(const Date& other) const {
        if (!(*this<other) && !(*this>other)) {
            //printf("!");
            return true;
        }
        return false; 
    }

    Date& operator++() {
        //Date tmp = *this;
        this -> d++;
        if (d > 30) {
            d -= 30;
            m++;
        }
        if (m > 12) {
            m-=12;
            y++;
        }
        //tmp.d++;
        return *this;
    }

};
