


def bin =  [ x:0, y:0, w: args[0].split(',')[0] as int, h: args[0].split(',')[1] as int, sbind: null, sbinr:null, t: 'root', used: false ]

def box =  [ x:0, y:0, w: args[1].split(',')[0] as int , h: args[1].split(',')[1] as int]

fitCount =0


def startTime = System.currentTimeMillis()

packIt(bin, box)

def stopTime = System.currentTimeMillis()

def calcTime = stopTime - startTime
println "fount $fitCount fits in $calcTime ms"


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
		
	//println "sorted bin: $bin.w x $bin.h, sorted box: $box.w x $box.h"
	//println "bin type: $bin.t bin size: $bin.w x $bin.h"

	if(box.w <= bin.w && box.h <= bin.h) {
			
		fitCount++
		//set this bin as used
		bin.used = true

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

	if ( sbindW == 0 || sbindH == 0 )
		bin.sbind = null
	else
		bin.sbind = [ x: bin.x, y: bin.y + box.h, w: sbindW, h: sbindH , t: 'd']
	
	def sbinrW = bin.w - box.w
	def sbinrH = box.h

	
	if ( sbinrW == 0 || sbinrH == 0 )
		bin.sbinr = null
	else
		bin.sbinr = [ x: bin.x + box.w, y: bin.y, w: sbinrW, h: sbinrH , t: 'r']


}



/*
//draw bin

String[][]  graph = new String[bin[1] as int][bin[0] as int]

for (def i=0; i < (bin[1] as int) ;i++) {

	//graph[i][0] = '-'

	for( def j=0; j < (bin[0] as int); j++) {

		graph[i][j] = '|'
		print graph[i][j]
	}

	println ''
	
}




//draw box

String[][]  graph2 = new String[box[1] as int][box[0] as int]

for (def i=0; i < (box[1] as int) ;i++) {

        //graph[i][0] = '-'

        for( def j=0; j < (box[0] as int); j++) {

                graph2[i][j] = '*'
        	print graph2[i][j]
	}

	println ''

}
*/


