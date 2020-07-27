#ifndef _MESSAGEIMP_H_
#define _MESSAGEIMP_H_

class MessageImp{
public:
    virtual ~MessageImp();
    virtual void operation(const char * file)=0;

protected:
    MessageImp();
};

#endif
