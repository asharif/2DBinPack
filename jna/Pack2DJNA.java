
import com.sun.jna.Library;
import com.sun.jna.Native;


interface NativePack2D extends Library {

	NativePack2D INSTANCE = (NativePack2D) Native.loadLibrary("pack2d", NativePack2D.class);
	int getCount(float binsize1, float binsize2, float boxsize1, float boxsize2, float tk);
}

public class Pack2DJNA {


	public static void main( String[] args ) {
		NativePack2D lib = NativePack2D.INSTANCE;
		int res = lib.getCount(5,5,1,1.25f,0);

		System.out.println( res);
	}


}
