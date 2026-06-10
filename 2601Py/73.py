import matplotlib.pyplot as plt
import numpy as np 

from sklearn import datasets,linear_model
from sklearn.model_selection import train_test_split

diabetes = datasets.load_diabetes()
diabetes_x = diabetes.data[:,np.newaxis,2]
diabetes_x_train,diabetes_x_test,diabetes_y_train,diabetes_y_test = train_test_split(diabetes_x,diabetes['target'],test_size=0.1,random_state=0)
regr=linear_model.LinearRegression()
regr.fit(diabetes_x_train,diabetes_y_train)
plt.scatter(diabetes_x_test,diabetes_y_test,color='black')
plt.plot(diabetes_x_test,regr.predict(diabetes_x_test),color='blue',linewidth=3)
plt.show()