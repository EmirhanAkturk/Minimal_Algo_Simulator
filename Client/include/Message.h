#ifndef _MESSAGE_H_
#define _MESSAGE_H_

class MessageImp;

class Message{
public:
    virtual ~Message();

    // virtual void operation(const char* file)=0;
    
    virtual void fileRead(const char * file)=0;
    virtual inline void print(int treeChoice,int printChoice)=0;

    virtual inline void writeFile(const char* outFile,int treeChoice,int writeChoice)=0;
    
protected:
    Message();
};

class ClientSearch: public Message{
public:
    ClientSearch(MessageImp* imp);
    ~ClientSearch();

    //virtual void operation(const char* file);
    virtual void fileRead(const char * file);
    virtual inline void print(int treeChoice,int printChoice);
    virtual inline void writeFile(const char* outFile,int treeChoice,int writeChoice);
    
private:
    MessageImp * _imp;
};

#endif //~_MESSAGE_H_