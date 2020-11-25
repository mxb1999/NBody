import matplotlib.pyplot  as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import struct

 #define matplotlib initializer variables
fileIn = "treeResults.txt"

print("File Opened")
output = open(fileIn,"rb")
bound = struct.unpack('d', output.read(8))[0]
num = struct.unpack('i', output.read(4))[0];
print(num)
step = struct.unpack('i', output.read(4))[0];
arr = np.ndarray((2,step, num));
print(step)
fig, ax = plt.subplots()
data, = ax.plot([0,0],'bo')
ax.set_ylim((0,bound))
ax.set_xlim((0,bound))
#ax.set_ylim((bound/2-bound/8,bound/2+bound/8))
#ax.set_xlim((bound/2-bound/8,bound/2+bound/8))

print("File Closed")
def readIn():
    
    for index in range(step):
        #index = 20*index*num#20 bytes per element, index* step is the desired starting point
        for i in range(num):
                x = struct.unpack('d', output.read(8))[0];
                z = struct.unpack('d', output.read(8))[0];
                arr[0,index,i] = x;
                arr[1,index,i] = z;
                #arr[1].append(z);
    #if index == 0:
        #plt.scatter(arrX,arrZ)
def animate(index):
    #ax.clear();
    print(arr[0,index])
    data.set_xdata(arr[0,index]);
    data.set_ydata(arr[1,index]);
    return data
readIn()

ani = FuncAnimation(fig, animate,range(0,step,100), interval=1)
plt.show()

output.close();
