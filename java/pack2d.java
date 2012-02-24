public class  pack2d {

	
	public static class shape {
		
		int w;
		int h;
		shape d;
		shape r;
	}

	private static int fitCount = 0;


	public static void main(String[] args) {

		shape bin = new shape();
		shape box = new shape();
		
		bin.w = Integer.parseInt(args[0].split(",")[0]);
		bin.h = Integer.parseInt(args[0].split(",")[1]);

		box.w = Integer.parseInt(args[1].split(",")[0]);
		box.h = Integer.parseInt(args[1].split(",")[1]);
		
		long start = System.currentTimeMillis();
		
		packIt(bin, box);

		long end = System.currentTimeMillis();
		long execTime = end - start;	
		System.out.println("found " + fitCount + " fits in " + execTime + " ms");
	}



	private static void packIt(shape bin, shape box) {


		//sort both bin and box
		if ( bin.w < bin.h) {

		        int tmpw = bin.w;
		        bin.w = bin.h;
		        bin.h = tmpw;
		}


		if ( box.w < box.h) {

		        int tmpw = box.w;
		        box.w = box.h;
		        box.h = tmpw;
		}


		if(box.w <= bin.w && box.h <= bin.h) {

		        fitCount++;

		        //if it fits split box and recurse
		        splitBin(bin, box);
		        if ( bin.d != null )
		                packIt(bin.d, box);
		        if( bin.r != null )
		                packIt(bin.r, box);

		}

	
	}
	
	private static void splitBin(shape bin, shape box) {

		int dW = bin.w;
		int dH = bin.h - box.h;

		if ( dH == 0 )
		        bin.d = null;
		else {

			bin.d = new shape();

			bin.d.w = dW;
			bin.d.h = dH;

		}

		
		int rW = bin.w - box.w;
		int rH = box.h;


		if ( rW == 0 )
		        bin.r = null;
		else {

			bin.r = new shape();
			
			bin.r.w = rW;
			bin.r.h = rH;
			
		}


	}


}
