#ifndef BASE_H
#define BASE_H

#include <string>

class Printable {
    public:
        virtual std::string getInfo() const = 0;
        virtual ~Printable() {}
};

class Named : public virtual Printable {
    public:
        Named(std::string const name): m_name(name) {}
        virtual ~Named() {}
        
        virtual std::string getInfo() const {
            return m_name;
        }

    private:
        std::string m_name;
};

#endif