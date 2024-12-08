#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::vector<std::vector<int>>& grid) = 0; 
};

#endif 
