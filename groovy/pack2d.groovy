


def bin =  [ x:0, y:0, w: args[0].split(',')[0] as int, h: args[0].split(',')[1] as int, sbind: null, sbinr:null, t: 'root' ]

def box =  [ x:0, y:0, w: args[1].split(',')[0] as int , h: args[1].split(',')[1] as int]

fitCount =0


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
		if ( bin.sbind != null )
			packIt(bin.sbind, box)
		if( bin.sbinr != null )
			packIt(bin.sbinr, box)
			
	}
	

}


def splitBin(bin, box) {

	def sbindW = bin.w
	def sbindH = bin.h - box.h

	if ( sbindH == 0 )
		bin.sbind = null
	else
		bin.sbind = [ x: bin.x, y: bin.y + box.h, w: sbindW, h: sbindH , t: 'd']
	
	def sbinrW = bin.w - box.w
	def sbinrH = box.h

	
	if ( sbinrW == 0 )
		bin.sbinr = null
	else
		bin.sbinr = [ x: bin.x + box.w, y: bin.y, w: sbinrW, h: sbinrH , t: 'r']


}


