#ifndef __IREMOTE_H__
#define __IREMOTE_H__

class IRemote
{
public:
    enum Button
    {
        NOTHING,
        A,
        B,
        C,
        D
    };

    virtual IRemote::Button GetRemote() = 0;
};
#endif // __IREMOTE_H__