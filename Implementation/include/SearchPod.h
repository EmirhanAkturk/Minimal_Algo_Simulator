// enum{
//     ADD_ORDER_TYPE='A',
//     ORDER_EXECUTE_TYPE='E',
//     ORDER_DELETE_TYPE='D'
// };

struct AddOrder
{
    uint64_t orderId;
    uint32_t orderPrice;
};

struct OrderExecute
{
    uint64_t orderId;
};

struct OrderDelete
{
    uint64_t orderId;
};
