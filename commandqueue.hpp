#pragma once

#include "command.hpp"
#include <queue>

class CommandQueue
{
public:
    explicit CommandQueue();
    void push(const Command& command);
    Command pop();
    bool isEmpty() const;

private:
    std::queue<Command> mQueue;
};
