#pragma once


#include <iostream>


namespace cbtc { namespace utils {

class simple_logger
{
public:
    enum class level { NONE = 0, ERROR = 1, WARNING = 5, DEBUG = 10 };
    static level enabled_level_;

    simple_logger(level current_level);

    template<typename T>
    simple_logger& operator<<(const T &t)
    {
        if(output_)
        {
            std::cout << t;
            return *this;
        }    

        return *this;
    }
  
    simple_logger& operator<<(std::ostream &(*f)(std::ostream &)) 
    {
        if(output_)
        {
            std::cout << f;
            return *this;
        }  
    
        return *this;
    }

private:
    bool output_;
};

}}
