#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"libpack2d.h"


int PACK2D_fitCount;
float PACK2D_tolKerf;


void PACK2D_splitBin(struct PACK2D_shape *bin, struct PACK2D_shape *box) {

        float dW = bin->w;
        float dH = bin->h - box->h - PACK2D_tolKerf;
	
	if ( dH == 0 )
                bin->d = NULL;
        else
	{
		struct PACK2D_shape *binD;
		binD = ( struct PACK2D_shape *) malloc(sizeof( struct PACK2D_shape ) );
		binD->w = dW;
		binD->h = dH;
		bin->d = binD;

	}


        float rW = bin->w - box->w - PACK2D_tolKerf;
        float rH = box->h;


        if ( rW == 0 )
                bin->r = NULL;
        else
	{

		struct PACK2D_shape *binR;
		binR = ( struct PACK2D_shape *) malloc( sizeof ( struct PACK2D_shape ) );
		binR->w = rW;
		binR->h = rH;
		bin->r = binR;
	}


}


void PACK2D_packIt( struct PACK2D_shape *bin, struct PACK2D_shape *box)
{
	
	//sort both bin and box
        if ( bin->w < bin->h ) 
	{

                float tmpw = bin->w;
                bin->w = bin->h;
                bin->h = tmpw;
        }


        if ( box->w < box->h ) 
	{

                float tmpw = box->w;
                box->w = box->h;
                box->h = tmpw;
        }


        if( box->w <= bin->w && box->h <= bin->h ) 
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



int PACK2D_getCount(float binsize1, float binsize2, float boxsize1, float boxsize2, float tk)
{

	
	PACK2D_fitCount = 0;

	PACK2D_tolKerf = tk;

	struct PACK2D_shape *bin;
	struct PACK2D_shape *box;
	bin = ( struct PACK2D_shape * ) malloc(sizeof( struct PACK2D_shape ));
	box = ( struct PACK2D_shape *) malloc(sizeof( struct PACK2D_shape ) );

	bin->w = binsize1;
	bin->h = binsize2;
	bin->d = NULL;
	bin->r = NULL;
	box->w = boxsize1;
	box->h = boxsize2;

	struct timeval start;
	struct timeval end;
	
	
	PACK2D_packIt(bin, box);


	free ( bin );
	free ( box );
	

	return PACK2D_fitCount;


}	
