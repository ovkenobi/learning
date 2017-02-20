#include <iostream>
#include <string>

class StringPointer
{
public:
    std::string *operator->() 
    {
        if (!s) {
            s= new std::string();
        }
        return s;
    }
    operator std::string*() 
    {   
        if (!s) {
            s = new std::string();
        }
        return s;
    }
    StringPointer(std::string *Pointer) : s(Pointer) {}
    
private:
    std::string *s;
};


int main(int c, char **v)
{
    std::string s = "Hello";
    StringPointer p(&s);
    StringPointer p1(NULL);
 
    std::cout << *p << "\n";
    std::cout << p->length() << "\n";

    std::cout << *p1 << "\n";
    std::cout << p1->length() << "\n";

    return 0;
}
