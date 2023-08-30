#pragma once

#include "logger.hpp"

#include <iostream>

class ApplicationBase
{
private:
    static const Logger log_msg;

public:
    void start();

    virtual void init() = 0;
    virtual void render() = 0;
};

// TODO:
const Logger ApplicationBase::log_msg{std::clog};
