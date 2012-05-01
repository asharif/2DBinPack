#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libpack2d.h"


int PACK2D_fitCount;

void PACK2D_splitBin(struct PACK2D_shape *bin, struct PACK2D_shape *box) {

        float dW = bin->w->size;
        float dH = bin->h->size - box->h->size - bin->h->tk;
	
	if ( dH <= 0 )
                bin->d = NULL;
        else
	{
		struct PACK2D_shape *binD;
		binD = ( struct PACK2D_shape *) malloc(sizeof( struct PACK2D_shape ) );
		binD->w = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
		binD->w->size = dW;
		binD->w->origSide = bin->w->origSide;
		binD->w->tk = bin->w->tk;

		binD->h = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
		binD->h->size = dH;
		binD->h->origSide = bin->h->origSide;
		binD->h->tk = bin->h->tk;
		
		bin->d = binD;

	}


        float rW = bin->w->size - box->w->size - bin->w->tk;
        float rH = box->h->size;


        if ( rW <= 0 )
                bin->r = NULL;
        else
	{

		struct PACK2D_shape *binR;
		binR = ( struct PACK2D_shape *) malloc( sizeof ( struct PACK2D_shape ) );

		binR = ( struct PACK2D_shape *) malloc(sizeof( struct PACK2D_shape ) );
		binR->w = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
		binR->w->size = rW;
		binR->w->origSide = bin->w->origSide;
		binR->w->tk = bin->w->tk;

		binR->h = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
		binR->h->size = rH;
		binR->h->origSide = bin->h->origSide;
		binR->h->tk = bin->h->tk;

		bin->r = binR;
	}


}


void PACK2D_packIt( struct PACK2D_shape *bin, struct PACK2D_shape *box)
{
	
	//sort both bin and box
        if ( bin->w->size < bin->h->size ) 
	{

                struct PACK2D_side *tmpw = bin->w;
                bin->w = bin->h;
                bin->h = tmpw;
        }


        if ( box->w->size < box->h->size ) 
	{

                struct PACK2D_side *tmpw = box->w;
                box->w = box->h;
                box->h = tmpw;
        }


	
        if( box->w->size <= bin->w->size && box->h->size <= bin->h->size ) 
	{

                PACK2D_fitCount++;

                //if it fits split box and recurse
                PACK2D_splitBin( bin, box );
		
		if ( bin->d != NULL )
		{
                        PACK2D_packIt( bin->d, box );
                	free ( bin->d );

		}
		if( bin->r != NULL )
		{
                        PACK2D_packIt( bin->r, box );
			free ( bin->r );
		}

        }


}



int PACK2D_getCount(float binsize1, float binsize2, float boxsize1, float boxsize2, 
		    float tkw, float tkh )
{

	
	PACK2D_fitCount = 0;


	struct PACK2D_shape *bin;
	struct PACK2D_shape *box;
	bin = ( struct PACK2D_shape * ) malloc(sizeof( struct PACK2D_shape ));
	box = ( struct PACK2D_shape *) malloc(sizeof( struct PACK2D_shape ) );

	bin->w = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
	bin->w->size = binsize1;
	bin->w->origSide = 'w';
	bin->w->tk = tkw;

	bin->h = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
	bin->h->size = binsize2;
	bin->h->origSide = 'h';
	bin->h->tk = tkh;

	bin->d = NULL;
	bin->r = NULL;
	
	box->w = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
	box->w->size = boxsize1;
	box->w->origSide = 'w';

	box->h = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
	box->h->size = boxsize2;
	box->h->origSide = 'h';

	PACK2D_packIt(bin, box);


	free ( bin->w );
	free ( bin->h );
	free ( bin );
	free ( box->w );
	free ( box->h );
	free ( box );
	

	return PACK2D_fitCount;


}	
