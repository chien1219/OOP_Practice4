#include "polynomial.h"
#include <cmath>
#include <string>
#include <sstream>

polynomial::polynomial(const int x0) {
    if (x0) {
        this->data[0] = x0;
    }
}

polynomial::polynomial(const std::vector<int>& v) {
    for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); i ++) {
        this->data[i - v.begin()] += *i;
    }
}

polynomial::polynomial(const polynomial& p) {
    *this = p;
}

polynomial::~polynomial() {}

polynomial& polynomial::operator=(const polynomial& p) {
    this->data = p.data;
}

polynomial operator-(polynomial p) {
    polynomial q;
    return q -= p;
}

polynomial operator+(polynomial p, const polynomial& q) {
    return p += q;
}

polynomial operator-(polynomial p, const polynomial& q) {
    return p -= q;
}

polynomial operator*(polynomial p, const polynomial& q) {
    polynomial result;
    for (std::map<int, double>::const_iterator i = p.data.begin(); i != p.data.end(); ++ i) {
        for (std::map<int, double>::const_iterator j = q.data.begin(); j != q.data.end(); ++ j) {
            result.data[i->first + j->first] = i->second * j->second;
        }
    }
    return result;
}

polynomial& operator+=(polynomial& self, const polynomial& other) {
    for (std::map<int, double>::const_iterator i = other.data.begin(); i != other.data.end(); ++ i) {
        self.data[i->first] += i->second;
    }
    return self;
}

polynomial& operator-=(polynomial& self, const polynomial& other) {
    for (std::map<int, double>::const_iterator i = other.data.begin(); i != other.data.end(); ++ i) {
        self.data[i->first] -= i->second;
    }
    return self;
}

polynomial& operator*=(polynomial& self, const polynomial& other) {
    return self = self * other;
}

double polynomial::operator()(const double x) const {
    double result = 0;
    for (std::map<int, double>::const_iterator i = this->data.begin(); i != this->data.end(); i ++) {
        result += pow(x, i->first) * i->second;
    }
    return result;
}

bool operator==(const polynomial& self, const polynomial& other) {
    return self.data == other.data;
}

bool operator!=(const polynomial& self, const polynomial& other) {
    return self.data != other.data;
}

polynomial::operator bool() const {
    for (std::map<int, double>::const_iterator i = this->data.begin(); i != this->data.end(); ++ i) {
        if (i->second) return true;
    }
    return false;
}

size_t polynomial::degree() const {
    for (std::map<int, double>::const_reverse_iterator i = this->data.rbegin(); i != this->data.rend(); ++ i) {
        if (i->second) return i->first;
    }
    return 0;
}

polynomial polynomial::derivate() const {
    polynomial p;
    for (std::map<int, double>::const_iterator i = this->data.begin(); i != this->data.end(); ++ i) {
        if (i->first) {
            p.data[i->first - 1] = i->second * i->first;
        }
    }
    return p;
}

std::istream& operator>>(std::istream& is, polynomial& p) {
    std::string line;
    std::stringstream ss;
    std::getline(is, line);
    ss << line;
    double value;
    int counter = 0;
    while (ss >> value) {
        p.data[counter++] = value;
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const polynomial& p) {
    const int degree = p.degree();
    std::map<int, double>::const_iterator i = p.data.find(0);
    if (i == p.data.end()) {
        os << 0;
    } else {
        os << i->second;
    }
    for (int d = 1; d <= degree; ++ d) {
        os << ' ';
        i = p.data.find(d);
        if (i == p.data.end()) {
            os << 0;
        } else {
            os << i->second;
        }
    }
    return os;
}
