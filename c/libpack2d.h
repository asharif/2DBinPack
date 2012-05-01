struct PACK2D_side 
{
	float size;
	char origSide;
	float tk;


};

struct PACK2D_shape
{
        struct PACK2D_side *w;
        struct PACK2D_side *h;
        struct PACK2D_shape *r;
        struct PACK2D_shape *d;

};

extern int PACK2D_fitCount;

void PACK2D_splitBin(struct PACK2D_shape *bin, struct PACK2D_shape *box);
void PACK2D_packIt( struct PACK2D_shape *bin, struct PACK2D_shape *box);
int PACK2D_getCount(float binsize1, float binsize2, float boxsize1, float boxsize2, float tkw, float tkh);






