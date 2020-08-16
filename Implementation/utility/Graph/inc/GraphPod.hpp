struct Bar{
    Bar(const Bar& b):open{b.open},high{b.high},
    low{b.low},close{b.close},quantity{b.quantity}
    {}

    Bar(uint32_t newPrice,uint32_t newQuantity):open{newPrice},
    high{newPrice},low{newPrice},close{newPrice},quantity{newQuantity}
    {}
    
    Bar(uint32_t o,uint32_t h,uint32_t l,uint32_t c,uint32_t q):
    open{o},high{h},low{l},close{c},quantity{q}
    {}
    uint32_t open;
    uint32_t high;
    uint32_t low;
    uint32_t close;
    uint32_t quantity;
};

struct Value{
    
    Value(const Bar&  newBar):
    bar{Bar(newBar)},next{nullptr}
    { }

    Value(uint32_t newPrice,uint32_t newQuantity):
    bar{Bar(newPrice,newQuantity)},next{nullptr}
    { }

    Bar bar;
    Value* next;
};
