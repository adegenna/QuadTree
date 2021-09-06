from types import new_class
from typing import List
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
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


def plot_state_snapshot( bucket , data , ax=None ):

    if ax is None:
        fig   = plt.figure( 10 , figsize=(8,8) )
        ax    = fig.gca()

    ax.scatter( data[:,0] , data[:,1] , c='r' , s=4 )

    ai , = ax.plot( bucket.x , bucket.y , 'b' )

    ax.set_aspect('equal')
    ax.set_xticks([])
    ax.set_yticks([])

    plt.tight_layout()

    return ai

def make_simdata_video( buckets , data , mp4name='simvideo.mp4' , fig=None ):

    if fig is None:
        fig   = plt.figure( 10 , figsize=(8,8) )
    ax    = fig.gca()
    
    plotframe_qt = lambda xi : [ plot_state_snapshot( xi , data , ax ) ]

    ani = animation.FuncAnimation( fig , plotframe_qt , frames=buckets , interval=20 , blit=True )

    ani.save('qt.mp4' )


def plot_entire_qt( buckets , data ):

    plt.scatter( data[:,0] , data[:,1] , s=4 )

    for bi in buckets:
        plt.plot( bi.x , bi.y , 'b' )

    plt.gca().set_aspect('equal')
    plt.xticks([])
    plt.yticks([])

    plt.tight_layout()
    
    plt.show()


if __name__ == "__main__":

    data    = np.genfromtxt( '../build/qt_data.out' , delimiter=',' )
    buckets = read_qt_buckets( '../build/qt.out' )

    plot_entire_qt( buckets , data )

    #make_simdata_video( buckets , data )