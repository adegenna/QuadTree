from types import new_class
from typing import List
import numpy as np
import matplotlib.pyplot as plt
from dataclasses import dataclass


@dataclass
class Bucket:

    sw : List[ float ]
    nw : List[ float ]
    ne : List[ float ]
    se : List[ float ]

    @property
    def x( self ):
        return [ self.sw[0] , self.nw[0] , self.ne[0] , self.se[0] , self.sw[0] ]

    @property
    def y( self ):
        return [ self.sw[1] , self.nw[1] , self.ne[1] , self.se[1] , self.sw[1] ]

    
def read_qt_buckets( f_qt : str ):

    data = []

    with open(f_qt) as f:
        
        for line in f:
            
            line = line.strip()
            
            try:
                data.append( [ float(el) for el in line.split(' : ')[-1:][0].split(' , ') ] )
            except:
                pass

    buckets = []
    
    for i in range( len(data) // 4 ):
        
        buckets.append( Bucket( data[4*i] , data[4*i+1] , data[4*i+2] , data[4*i+3] ) )

    return buckets


def main( f_qt : str , f_data : str ):

    data    = np.genfromtxt( f_data , delimiter=',' )
    buckets = read_qt_buckets( f_qt )
    
    plt.plot( data[:,0] , data[:,1] , 'o' )

    for boxi in buckets:
        plt.plot( boxi.x , boxi.y , 'b' )

    plt.gca().set_aspect('equal')

    plt.show()


if __name__ == "__main__":

    main( '../build/qt.out' , '../build/qt_data.out' )