# random forests

import numpy as np
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.metrics import accuracy_score

# Create the dataset with 1,000 samples.
X, y = datasets.make_classification(1000, random_state = 1)
X_train, X_test, y_train, y_test = train_test_split(X,y, test_size=0.25, random_state = 14)


rf = RandomForestClassifier(random_state=500)
rf.fit(X_train, y_train)
y_predict = rf.predict(X_test)

print ("Accuracy:\t", accuracy_score(y_test, y_predict))
print ("Total Correct:\t", (y_test == y_predict).sum())


probs = rf.predict_proba(X_test)
probs = np.around(probs, 1)
probs_df = pd.DataFrame(probs, columns=['0', '1'])
probs_df['was_correct'] = rf.predict(X_test) == y_test


f, ax = plt.subplots(figsize=(7, 5))
probs_df.groupby('0').was_correct.mean().plot(kind='bar', ax=ax)
ax.set_title("Accuracy at 0 class probability")
ax.set_ylabel("% Correct")
ax.set_xlabel("% trees for 0")
plt.show()
