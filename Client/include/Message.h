#ifndef _MESSAGE_H_
#define _MESSAGE_H_

class MessageImp;

class Message{
public:
    virtual ~Message();
    virtual void operation(const char* file)=0;

protected:
    Message();
};

class ClientSearch: public Message{
public:
    ClientSearch(MessageImp* imp);
    ~ClientSearch();

    virtual void operation(const char* file);

private:
    MessageImp * _imp;
};

#endif //~_MESSAGE_H_