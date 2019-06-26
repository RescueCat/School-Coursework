import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from tkinter import *
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, confusion_matrix

def print_function_name(funcName):
    print(funcName)


def execute_Algo(filename, textArea):
    # Assign column names to the dataset
    names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'Class']

    # Read dataset to pandas dataframe
    dataset = pd.read_csv(filename, names=names)

    # Split our dataset into its attributes and labels. To do so, use the following code:
    X = dataset.iloc[:, :-1].values
    y = dataset.iloc[:, 4].values

    # print(dataset.head(5))

    # Train test split
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20)

    # Feature Scaling
    scaler = StandardScaler()
    scaler.fit(X_train)

    X_train = scaler.transform(X_train)
    X_test = scaler.transform(X_test)

    # Training and Predictions
    classifier = KNeighborsClassifier(n_neighbors=5)
    classifier.fit(X_train, y_train)

    y_pred = classifier.predict(X_test)

    confMatr = confusion_matrix(y_test, y_pred)
    classRep = classification_report(y_test, y_pred)

    print(confusion_matrix(y_test, y_pred))
    print(classification_report(y_test, y_pred))

    textArea.insert(END, "K-Nearest Neighbor\n")
    textArea.insert(END, confMatr)
    textArea.insert(END, "\n")
    textArea.insert(END, classRep)
