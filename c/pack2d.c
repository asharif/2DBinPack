#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libpack2d.h"

void getSizeVector(char size[], float sizeV[], char *del )
{


        char * pchar;
        pchar = strtok ( size,  del );

        
        int i = 0;

        while ( pchar != NULL)
        {
                sizeV[i] = atof(pchar);
                i++;
                pchar = strtok ( NULL, del );

        }



}

main(int argc, char * argv[])
{

	if ( argc < 4 )
	{
		printf("3 arguments required: bin size (eg. 5x5), box size (eg. 1x1) and tol+kerf (eg 0.25,0.25)\n");
		exit(1);

	}
	
	float binSizeV[2];
	float boxSizeV[2];
	float tolKerfV[2];

	getSizeVector(argv[1], binSizeV, "x");
	getSizeVector(argv[2], boxSizeV, "x");	
	getSizeVector(argv[3], tolKerfV, ",");

	struct PACK2D_shape *bin;
	struct PACK2D_shape *box;
	bin = ( struct PACK2D_shape * ) malloc(sizeof( struct PACK2D_shape ));
	box = ( struct PACK2D_shape *) malloc(sizeof( struct PACK2D_shape ) );

	bin->w = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
	bin->w->size = binSizeV[0];
	bin->w->origSide = 'w';
	bin->w->tk = tolKerfV[0];

	bin->h = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
	bin->h->size = binSizeV[1];
	bin->h->origSide = 'h';
	bin->h->tk = tolKerfV[1];

	bin->d = NULL;
	bin->r = NULL;

	box->w = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
	box->w->size = boxSizeV[0];
	box->w->origSide = 'w';

	box->h = ( struct PACK2D_side *) malloc(sizeof( struct PACK2D_side ) );
	box->h->size = boxSizeV[1];
	box->h->origSide = 'h';

	

	PACK2D_packIt(bin, box);


	free ( bin->w );
	free ( bin->h );
	free ( bin );
	free ( box->w );
	free ( box->h );
	free ( box );


	printf("found %d fits\n", PACK2D_fitCount);
}	
