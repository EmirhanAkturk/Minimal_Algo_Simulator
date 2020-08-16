enum MessageType{
    SECONDS='T',
    ADD_ORDER_TYPE='A',
    ORDER_EXECUTED_TYPE='E',
    ORDER_DELETE_TYPE='D'
};

enum PRINT{
    INORDER=1,
    PREORDER=2,
    POSTORDER=3
};

struct Seconds{
    uint32_t timestamp;
};

struct AddOrder
{   
    uint32_t timestamp;
    uint32_t nanosecond;
    uint64_t orderId;
    uint32_t orderBookId;
    uint32_t quantity;
    uint32_t orderPrice;

};

struct OrderExecuted
{
    uint32_t nanosecond;
    uint64_t orderId;
};

struct OrderDelete
{
    uint32_t nanosecond;
    uint64_t orderId;
};
