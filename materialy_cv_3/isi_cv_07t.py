# random forests

import numpy as np
from sklearn import datasets
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split

from isi_cv_03_task import X_train, X_test, y_test
from materialy_cv_3.isi_cv_08 import y_train, y_predict

# Create the dataset with 1,000 samples.
X, y = datasets.make_classification(1000, random_state=500)
X_train, X_test, y_train, y_test = train_test_split(X,y, test_size=0.25, random_state = 14)
# Split generated data into training and testing part
rf= RandomForestClassifier(random_state=100)
rf.fit(X_train, y_train)
y_predict= rf.predict(X_test)
print("Accuracy: ", accuracy_score(y_train, y_predict))
print("Total Correct:\t", (y_test==y_predict).sum())
# Perform classification using Random Forrest

# Calculate accuracy of classification
