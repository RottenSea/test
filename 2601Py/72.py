from sklearn.datasets import make_blobs
import matplotlib.pyplot as plt 
import numpy as np 

centers = [[-2,1],[-1.5,5],[0,3]]
x,y = make_blobs(n_samples=100,centers=centers,random_state=0,cluster_std=0.7)
plt.figure(figsize=(16,6),dpi=144)
c=np.array(centers)
plt.scatter(x[:,0],x[:,1],c=y,s=100,cmap='cool')
plt.scatter(c[:,0],c[:,1],s=100,marker='^',c='orange')
plt.show()

from sklearn.neighbors import KNeighborsClassifier
k=3
clf=KNeighborsClassifier(n_neighbors=k)
clf.fit(x,y)

x_sample = [-1,2.3]
temp=np.array(x_sample).reshape((1,-1))
y_sample = clf.predict(temp)
neighbors=clf.kneighbors(temp,return_distance=False)

plt.figure(figsize=(8,6),dpi=144)
plt.scatter(x[:,0],x[:,1],c=y,s=100,cmap='cool')
plt.scatter(c[:,0],c[:,1],s=30,maker='^',c=k)
plt.scatter(x_sample[0],x_sample[1],s=100,marker='x',c=y_sample[0],cmap='cool')
for idx in neighbors[0]:
    plt.plot([x_sample[0],x[idx,0]],[x_sample[1],x[idx,1]],'r--',alpha=0.6)
plt.show()