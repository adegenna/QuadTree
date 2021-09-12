from types import new_class
from typing import List
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Rectangle
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

    @property
    def width( self ):
        return self.se[0] - self.sw[0]

    @property
    def height( self ):
        return self.nw[1] - self.sw[1]

    
def read_qt_buckets( f_qt : str ):

    def read_rgb_mean( line , vals ):
        try:
            assert( 'rgb_mean' in line )
            return vals.append( [ float(el) for el in line.split(' rgb_mean : ')[-1].split(',') ] )
        except: pass

    def read_npts( line , vals ):
        try: 
            assert( 'npts' in line )
            return vals.append( [ float(el) for el in line.split(' npts : ')[-1].split(',') ] )
        except: pass

    data = []
    vals = []

    with open(f_qt) as f:
        
        for line in f:
            
            line = line.strip()
            
            try:
                assert( np.any( [ el in line for el in ['sw','nw','ne','se'] ] ) )
                data.append( [ float(el) for el in line.split(' : ')[-1:][0].split(' , ') ] )
            except:
                pass
            
            try:
                read_rgb_mean( line , vals ) or read_npts( line , vals )
            except:
                raise Exception

    buckets = []
    
    for i in range( len(data) // 4 ):
        
        buckets.append( Bucket( data[4*i] , data[4*i+1] , data[4*i+2] , data[4*i+3] ) )

    return buckets , vals


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


def fill_bucket_rgb( ax , vi , bi : Bucket ):
        
    assert( len(vi) == 3 )

    rgba = [ vij/255. for vij in vi ]
    rgba.append(1)

    ax.add_patch( Rectangle( ( bi.sw[0] , bi.sw[1] ) , bi.width , bi.height , 
             edgecolor = 'pink' ,
             facecolor = rgba ,
             fill=True ,
             lw=1 ) )


def fill_bucket_npts( ax , vi , bi : Bucket , maxval ):
    
    assert( len(vi) == 1 )
    
    rgba = [ vi[0]/maxval[0] for i in range(3) ]
    rgba.append(1)

    ax.add_patch( Rectangle( ( bi.sw[0] , bi.sw[1] ) , bi.width , bi.height , 
             edgecolor = 'pink' ,
             facecolor = rgba ,
             fill=True ,
             lw=1 ) )


def plot_entire_qt( buckets , vals=None , ax=None ):

    if ax is None:
        fig   = plt.figure( 10 , figsize=(8,8) )
        ax    = fig.gca()

    if vals is not None:
        for (vi,bi) in zip(vals,buckets):
            try:
                fill_bucket_rgb( ax , vi , bi )
            except:
                fill_bucket_npts( ax , vi , bi , max(vals) )

    for bi in buckets:
        ax.plot( bi.x , bi.y , 'b' , lw=1 )

    ax.set_aspect('equal')
    ax.set_xticks([])
    ax.set_yticks([])

    plt.tight_layout()
    

if __name__ == "__main__":

    try:
        data    = np.genfromtxt( '../build/qt_data.out' , delimiter=',' )
        plt.figure()
        plt.scatter( data[:,0] , data[:,1] , s=4 , c='r' )
    except:
        pass

    fig , ax = plt.subplots( 2 , 3 )

    for i in range(6):

        buckets , vals = read_qt_buckets( '../build/qt_level_' + str(i+1) + '.out' )

        plot_entire_qt( buckets , vals , ax.ravel()[i] )

    plt.show()

    #make_simdata_video( read_qt_buckets( '../build/qt_level_6.out' ) , data )