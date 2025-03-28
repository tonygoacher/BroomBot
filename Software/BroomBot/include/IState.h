#ifndef __ISTATE_H__
#define __ISTATE_H__

class IState
{
public:
    virtual void Entry();
    virtual int Run();
};
#endif // __ISTATE_H__