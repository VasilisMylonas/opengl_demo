#pragma once

class app
{
    virtual void init() = 0;
    virtual void render() = 0;
    virtual bool should_close() = 0;
};
