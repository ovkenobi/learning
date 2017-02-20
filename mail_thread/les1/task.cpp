#include <iostream>
#include <map>
#include <utility>
#include <tuple>

#define COEF 1
#define POW 2


void replace_space(std::string &s)
{
    int n;
    while ((n = s.find(' ')) != -1) { 
        s.replace(n,1,"");
    }
}

std::string get_pair(std::string &s)
{
    int p = s.find_first_of("+",1);
    int m = s.find_first_of("-",1);

    int n;

    if (p<0) {
       n=m;
    } else if (m<0) {
       n=p;
    } else if (p<m) {
       n=p;
    } else {
       n=m;
    }

    std::string res = s;
    if (n>0) {
        res = s.substr(0,n);
        s = s.substr(n,s.length());
    } else {
        s="";
    }

//    std::cout << p << " " << m << n << "\n";
//    std::cout << res << " - " << s << "\n";
    return res;
}

std::pair<int,int> parse_stage_2(std::string s)
{
    int posX = s.find("x");
    if (posX==-1) posX = s.find("X");
    if (posX==-1) return std::make_pair(0,0);

    int c,p;
    if (posX==0) c=1;
    else if (posX==1 && s[0] == '+') c=1;
    else if (posX==1 && s[0] == '-') c=-1;
    else c = std::stoi(s);

    if (posX==s.length()-1) p = 1;
    else p = std::stoi(s.substr(posX+2,s.length()));

    return std::make_pair(c,p);
}


int main(int count, char** v)
{
    std::map<int, int> map;
    
    std::string s,d;

    std::getline(std::cin, s);

    replace_space(s);

    while (s.length()) {
        auto p = parse_stage_2(get_pair(s));
 
//        std::cout << p.first << " " << p.second << "\n";
        if (p.second && p.first) {
            if (map[p.second]) map[p.second]+=p.first;
            else map[p.second]=p.first;
        }
    }

    bool sign = false;
    for(auto p = map.rbegin(); p != map.rend(); ++p) {
        if (p->second>0 && sign) {
            std::cout << "+";
        }
        sign = true;
        std::cout << p->second*p->first;
        if (p->first>1) {
            std::cout << "*x";
            if (p->first>2) {
                std::cout << "^" << (p->first-1);
            }
        }
//        std::cout << p.first << " " << p.second << "\n";
    }

    std::cout << "\n";
    return 0;
}
