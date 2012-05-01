public class  pack2d {

	
	public static class shape {
		
		side w;
		side h;
		shape d;
		shape r;
	}


	public static class side {

		float size;
		char origSide;
		float tk;

	}

	private static int fitCount = 0;
	private static float tolKerf;

	public static void main(String[] args) {

		if ( args.length < 3 ) {
			System.out.println("3 arguments required: bin size (eg. 5x5), box size (eg. 1x1) and tol+kerf (eg 0.25,0.25)");
			System.exit(1);
		}

		shape bin = new shape();
		shape box = new shape();
		
		bin.w = new side();
		bin.w.size = Float.parseFloat(args[0].split("x")[0]);
		bin.w.origSide = 'w';
		bin.w.tk = Float.parseFloat(args[2].split(",")[0]);

		bin.h = new side();		
		bin.h.size = Float.parseFloat(args[0].split("x")[1]);
		bin.h.origSide = 'h'; 
		bin.h.tk = Float.parseFloat(args[2].split(",")[1]);

		box.w = new side();
		box.w.size = Float.parseFloat(args[1].split("x")[0]);
		box.w.origSide = 'w';

		box.h = new side();
		box.h.size = Float.parseFloat(args[1].split("x")[1]);
		box.h.origSide = 'h';


		long start = System.currentTimeMillis();
		
		packIt(bin, box);

		long end = System.currentTimeMillis();
		long execTime = end - start;	
		System.out.println("found " + fitCount + " fits in " + execTime + " ms");
	}



	private static void packIt(shape bin, shape box) {


		//sort both bin and box
		if ( bin.w.size < bin.h.size) {

		        side tmpw = bin.w;
		        bin.w = bin.h;
		        bin.h = tmpw;
		}


		if ( box.w.size < box.h.size) {

		        side tmpw = box.w;
		        box.w = box.h;
		        box.h = tmpw;
		}


		if(box.w.size <= bin.w.size && box.h.size <= bin.h.size) {

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

		float dW = bin.w.size;
		float dH = bin.h.size - box.h.size - bin.h.tk;

		if ( dH <= 0 )
		        bin.d = null;
		else {

			bin.d = new shape();
			
			bin.d.w = new side();
			bin.d.w.size = dW;
			bin.d.w.origSide = bin.w.origSide;
			bin.d.w.tk = bin.w.tk;

			bin.d.h = new side();
			bin.d.h.size = dH;
			bin.d.h.origSide = bin.h.origSide;
			bin.d.h.tk = bin.h.tk;

		}

		
		float rW = bin.w.size - box.w.size - bin.w.tk;
		float rH = box.h.size;


		if ( rW <= 0 )
		        bin.r = null;
		else {

			bin.r = new shape();
			
			bin.r.w = new side();
			bin.r.w.size = rW;
			bin.r.w.origSide = bin.w.origSide;
			bin.r.w.tk = bin.w.tk;

			bin.r.h = new side();
			bin.r.h.size = rH;
			bin.r.h.origSide = bin.h.origSide;
			bin.r.h.tk = bin.h.tk;

		}


	}


}
