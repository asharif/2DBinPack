#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<time.h>
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
		printf("3 arguments required: bin size (eg. 5x5), box size (eg. 1x1) and tol+kerf (eg 1.25)\n");
		exit(1);

	}
	
	float binSizeV[2];
	float boxSizeV[2];

	PACK2D_tolKerf = atof(argv[3]);
	getSizeVector(argv[1], binSizeV, "x");
	getSizeVector(argv[2], boxSizeV, "x");	

	struct PACK2D_shape *bin;
	struct PACK2D_shape *box;
	bin = ( struct PACK2D_shape * ) malloc(sizeof( struct PACK2D_shape ));
	box = ( struct PACK2D_shape *) malloc(sizeof( struct PACK2D_shape ) );

	bin->w = binSizeV[0];
	bin->h = binSizeV[1];
	bin->d = NULL;
	bin->r = NULL;
	box->w = boxSizeV[0];
	box->h = boxSizeV[1];

//	struct timeval start;
//	struct timeval end;
	
//	gettimeofday(&start);
	
	PACK2D_packIt(bin, box);


	free ( bin );
	free ( box );

//	gettimeofday(&end);
	
//	long execTimeS = end.tv_sec - start.tv_sec;
//      long execTimeMicS = end.tv_usec  - start.tv_usec ;

//      float fexecTime = (execTimeS*1000) + ((float)execTimeMicS)/1000;

//	printf("found %d fits in %f ms\n", PACK2D_fitCount, fexecTime);
	printf("found %d fits\n", PACK2D_fitCount);

}	
