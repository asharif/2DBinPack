struct PACK2D_shape
{
        float w;
        float h;
        struct PACK2D_shape *r;
        struct PACK2D_shape *d;

};

extern int PACK2D_fitCount;
extern float PACK2D_tolKerf;

void PACK2D_splitBin(struct PACK2D_shape *bin, struct PACK2D_shape *box);
void PACK2D_packIt( struct PACK2D_shape *bin, struct PACK2D_shape *box);
int PACK2D_getCount(float binsize1, float binsize2, float boxsize1, float boxsize2, float tk);






