#ifndef COMPARABLE_H
#define COMPARABLE_H

template <typename T> class Comparable {
    public:        
        virtual int compareTo(const T &n) const = 0;
              
        bool eq(const T &n) const { return compareTo(n)==0; }
        bool ne(const T &n) const { return          !eq(n); }
        bool ge(const T &n) const { return compareTo(n)>=0; }
        bool le(const T &n) const { return compareTo(n)<=0; }
        bool gt(const T &n) const { return compareTo(n)> 0; }
        bool lt(const T &n) const { return compareTo(n)< 0; }
        
        bool operator==(const T &n) const { return eq(n); }
        bool operator!=(const T &n) const { return ne(n); }
        bool operator>=(const T &n) const { return ge(n); }
        bool operator<=(const T &n) const { return le(n); }
        bool operator> (const T &n) const { return gt(n); }
        bool operator< (const T &n) const { return lt(n); }
};

#endif
