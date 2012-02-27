#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct shape
{
	float w;
	float h;
	struct shape *r;
	struct shape *d;

};

int fitCount = 0;
float tolKerf;



void splitBin(struct shape *bin, struct shape *box) {

        float dW = bin->w;
        float dH = bin->h - box->h - tolKerf;
	
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


        float rW = bin->w - box->w - tolKerf;
        float rH = box->h;


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

                fitCount++;

                //if it fits split box and recurse
                splitBin( bin, box );
		
		if ( bin->d != NULL )
		{
                        packIt( bin->d, box );
                	free ( bin->d );
		}
		if( bin->r != NULL )
		{
                        packIt( bin->r, box );
			free ( bin->r );
		}

        }


}



int getCount(float binsize1, float binsize2, float boxsize1, float boxsize2, float tk)
{


	tolKerf = tk;

	struct shape *bin;
	struct shape *box;
	bin = ( struct shape * ) malloc(sizeof( struct shape ));
	box = ( struct shape *) malloc(sizeof( struct shape ) );

	bin->w = binsize1;
	bin->h = binsize2;
	bin->d = NULL;
	bin->r = NULL;
	box->w = boxsize1;
	box->h = boxsize2;

	struct timeval start;
	struct timeval end;
	
	
	packIt(bin, box);


	free ( bin );
	free ( box );

	return fitCount;


}	
