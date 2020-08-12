struct Bar{
    Bar(uint32_t newPrice):open{newPrice},
    high{newPrice},low{newPrice},close{newPrice}
    {}
    
    Bar(uint32_t o,uint32_t h,uint32_t l,uint32_t c):
    open{o},high{h},low{l},close{c}
    {}
    uint32_t open;
    uint32_t high;
    uint32_t low;
    uint32_t close;
};