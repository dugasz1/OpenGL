#ifndef DEBUGTIMER_H_INCLUDED
#define DEBUGTIMER_H_INCLUDED

#include <GLFW\glfw3.h>
#include <iostream>

class DebugTimer
{
public:
    void Start()
    {
        startTime = glfwGetTime();
    }
    
    void End(const std::string& message)
    {
        unsigned int endTime = glfwGetTime();
        std::cout << message.c_str() << (endTime - startTime) << "ms" << std::endl;
    }
    
protected:
private:
    unsigned int startTime;
};

#endif // DEBUGTIMER_H_INCLUDED
