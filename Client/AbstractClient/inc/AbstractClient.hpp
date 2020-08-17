#ifndef _ABSTRACT_CLIENT_HPP_
#define _ABSTRACT_CLIENT_HPP_

//forward declaration
class AbstractImp;

class AbstractClient {
public:
    virtual ~AbstractClient();
    virtual void compute(const char* file,char calculateChoice)=0;

protected:
    AbstractClient();

private:
};

class RefinedAbstractClient: public AbstractClient {
public:
    RefinedAbstractClient(AbstractImp* imp);
    ~RefinedAbstractClient();
    virtual void compute(const char* file,char calculateChoice);

protected:

private:
    AbstractImp* _imp;
};

#endif //~_ABSTRACT_CLIENT_HPP