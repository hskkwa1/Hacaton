# -*- coding: utf-8 -*-
"""
Created on Sun Oct  6 23:05:12 2024

@author: Xardas
"""

# random forests

import numpy as np
#from sklearn.datasets import load_boston
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from sklearn.utils import Bunch  # Import Bunch for compatibility
from sklearn import svm

import pandas as pd
# Load the Boston Housing dataset from the internet
data_url = "http://lib.stat.cmu.edu/datasets/boston"
raw_df = pd.read_csv(data_url, sep="\\s+", skiprows=22, header=None)


# Process the data to match the original structure
data = np.hstack([raw_df.values[::2, :], raw_df.values[1::2, :2]])
target = raw_df.values[1::2, 2]

# Create a Bunch object similar to the original returned by load_boston()
boston = Bunch(
    data=data,
    target=target,
    feature_names=np.array(['CRIM', 'ZN', 'INDUS', 'CHAS', 'NOX', 'RM',
                            'AGE', 'DIS', 'RAD', 'TAX', 'PTRATIO', 'B', 'LSTAT']),
    DESCR="Boston Housing dataset description"
)

# importovana databaza 
#boston = load_boston()
print (boston.data.shape)
print (boston.feature_names)
#print np.max(boston.target), np.min(boston.target), np.mean(boston.target)
print (boston.DESCR)

# ako vyzera jedna vzorka dat
print (boston.data[0])
#print np.max(boston.data), np.min(boston.data), np.mean(boston.data)

X_train, X_test, y_train, y_test = train_test_split(boston.data, boston.target, test_size=0.25, random_state=33)

x_min, x_max = X_train[:,0].min() - .5, X_train[:, 0].max() + .5
y_min, y_max = y_train.min() - .5, y_train.max() + .5
#fig=plt.figure()
#fig.subplots_adjust(left=0, right=1, bottom=0, top=1, hspace=0.05, wspace=0.05)

# Two subplots, unpack the axes array immediately
fig, axes = plt.subplots(1,5)
fig.set_size_inches(12,12)
'''
for i in range(5):
  #  axes[i].set_aspect('equal')
    axes[i].set_title('Feature ' + str(i))
    axes[i].set_xlabel('Feature')
    axes[i].set_ylabel('Median house value')
    axes[i].set_xlim(x_min, x_max)
    axes[i].set_ylim(y_min, y_max)
    
    plt.sca(axes[i])
    plt.scatter(X_train[:,i],y_train)

plt.show()
'''
svr = svm.SVR(kernel ='linear')
svr.fit(X_train, y_train)
print("Score on test: ", svr.score(X_test, y_test))

svr = svm.SVR(kernel ='poly')
svr.fit(X_train, y_train)
print("Score on test: ", svr.score(X_test, y_test))

svr = svm.SVR(kernel ='rbf')
svr.fit(X_train, y_train)
print("Score on test: ", svr.score(X_test, y_test))