#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct shape
{
	int w;
	int h;
	struct shape *r;
	struct shape *d;

};

int fitCount = 0;




void getSizeVector(char size[], int sizeV[], char *del )
{


        char * pchar;
        pchar = strtok ( size,  del );

        
        int i = 0;

        while ( pchar != NULL)
        {
                sizeV[i] = atoi(pchar);
                i++;
                pchar = strtok ( NULL, del );

        }



}

void splitBin(struct shape *bin, struct shape *box) {

        int dW = bin->w;
        int dH = bin->h - box->h;
	
	if ( dH == 0 )
                bin->d = NULL;
        else
	{
		struct shape *binD;
		binD = ( struct shape *) malloc(sizeof( struct shape ) );
		binD->w = dW;
		binD->h = dH;
		bin->d = binD;

	}


        int rW = bin->w - box->w;
        int rH = box->h;


        if ( rW == 0 )
                bin->r = NULL;
        else
	{

		struct shape *binR;
		binR = ( struct shape *) malloc( sizeof ( struct shape ) );
		binR->w = rW;
		binR->h = rH;
		bin->r = binR;
	}


}


void packIt( struct shape *bin, struct shape *box)
{
	
	//sort both bin and box
        if ( bin->w < bin->h ) 
	{

                int tmpw = bin->w;
                bin->w = bin->h;
                bin->h = tmpw;
        }


        if ( box->w < box->h ) 
	{

                int tmpw = box->w;
                box->w = box->h;
                box->h = tmpw;
        }


        if( box->w <= bin->w && box->h <= bin->h ) 
	{

                fitCount++;

                //if it fits split box and recurse
                splitBin( bin, box );
		
		if ( bin->d != NULL )
                        packIt( bin->d, box );
                if( bin->r != NULL )
                        packIt( bin->r, box );

        }


}



main(int argc, char * argv[])
{

	int binSizeV[2];
	int boxSizeV[2];

	getSizeVector(argv[1], binSizeV, ",");
	getSizeVector(argv[2], boxSizeV, ",");	

	struct shape *bin;
	struct shape *box;
	bin = ( struct shape * ) malloc(sizeof( struct shape ));
	box = ( struct shape *) malloc(sizeof( struct shape ) );

	bin->w = binSizeV[0];
	bin->h = binSizeV[1];
	bin->d = NULL;
	bin->r = NULL;
	box->w = boxSizeV[0];
	box->h = boxSizeV[1];

	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start);
	
	packIt(bin, box);

	gettimeofday(&end);
	
	long execTimeS = end.tv_sec - start.tv_sec;
        long execTimeMicS = end.tv_usec  - start.tv_usec ;

        float fexecTime = (execTimeS*1000) + ((float)execTimeMicS)/1000;


	printf("found %d fits in %f ms\n", fitCount, fexecTime);
}	
