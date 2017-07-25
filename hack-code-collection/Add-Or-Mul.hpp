// 判断类型的函数。如果类型为int,做加法运算，否则做乘法运算
// 摘自 https://github.com/wuye9036/CppTemplateTutoria 2.2

#define BIN_OP(type, a, op, b, result) (*(type *)(result)) = (*(type const *)(a)) op (*(type const*)(b))
void doDiv(void* out, void const* data0, void const* data1, DATA_TYPE type)
{
    if(type == TYPE_INT)
    {
        BIN_OP(int, data0, *, data1, out);
    }
    else
    {
        BIN_OP(float, data0, +, data1, out);
    }
}
