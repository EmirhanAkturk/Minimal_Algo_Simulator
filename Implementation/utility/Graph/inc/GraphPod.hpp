struct Bar{
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
