#ifndef KEYINFO_H
#define KEYINFO_H

#include "baseprocess.h"

typedef enum {
    KEYPRESS_PWR,
    KEYPRESS_VUP,
    KEYPRESS_VDOWN,
}KEYPRESS;

class KeyInfo : public BaseProcess
{
    Q_OBJECT
public:
    KeyInfo();
    void StartCmd();

private slots:
    void KeyInfoStdOut();
    void KeyInfoStdErr();

signals:
    void onKeyPress(KEYPRESS key);
};

#endif // KEYINFO_H
