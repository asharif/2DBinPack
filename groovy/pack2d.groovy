

if(args.length < 3) {
	
	println"3 arguments required: bin size (eg. 5x5), box size (eg. 1x1) and tol+kerf (eg 1.25)"
	return;
}

def bin =  [  w: args[0].split('x')[0] as float, h: args[0].split('x')[1] as float, d: null, r:null ]

def box =  [  w: args[1].split('x')[0] as float , h: args[1].split('x')[1] as float]



fitCount =0
tolKerf = args[2] as float

def startTime = System.currentTimeMillis()

packIt(bin, box)

def stopTime = System.currentTimeMillis()

def calcTime = stopTime - startTime
println "found $fitCount fits in $calcTime ms"


def packIt(bin, box) {
			

	//sort both bin and box
	if ( bin.w < bin.h) {

		def tmpw = bin.w
		bin.w = bin.h
		bin.h = tmpw
	}


	if ( box.w < box.h) {

               	def tmpw = box.w
     		box.w = box.h
      		box.h = tmpw
       	}
		

	if(box.w <= bin.w && box.h <= bin.h) {
			
		fitCount++

		//if it fits split box and recurse
		splitBin(bin, box)
		if ( bin.d != null )
			packIt(bin.d, box)
		if( bin.r != null )
			packIt(bin.r, box)
			
	}
	

}


def splitBin(bin, box) {

	def dW = bin.w
	def dH = bin.h - box.h -tolKerf

	if ( dH <= 0 )
		bin.d = null
	else
		bin.d = [ w: dW, h: dH]
	
	def rW = bin.w - box.w - tolKerf
	def rH = box.h

	
	if ( rW <= 0 )
		bin.r = null
	else
		bin.r = [  w: rW, h: rH ]


}


