enum MessageType{
    ADD_ORDER_TYPE='A',
    ORDER_EXECUTED_TYPE='E',
    ORDER_DELETE_TYPE='D'
};

struct AddOrder
{
    uint64_t orderId;
    uint32_t orderPrice;
};

struct OrderExecuted
{
    uint64_t orderId;
};

struct OrderDelete
{
    uint64_t orderId;
};
