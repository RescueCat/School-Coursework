from sklearn.ensemble import RandomForestClassifier
import pandas as pd
from tkinter import *
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix

class_labels = ['Iris-setosa', 'Iris-versicolor', 'Iris-virginica']
percent_test = 0.2


def print_function_name(funcName):
    print(funcName)


def parse(filename):
    # Assign column names to the dataset
    features = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'Class']

    # read data file
    dataset = pd.read_csv(filename, names=features)

    # split data into features and classes
    X = dataset.iloc[:, :-1].values
    y = dataset.iloc[:, 4].values

    return train_test_split(X, y, test_size=percent_test)


def execute_Algo(filename, textArea):
    # initialize classifier
    clf = RandomForestClassifier(n_estimators=100)

    # read the data file and split them into train and test sets
    X_train, X_test, y_train, y_test = parse(filename)

    # train model
    clf.fit(X_train, y_train)

    # test model
    y_pred = clf.predict(X_test)

    # prints
    print(confusion_matrix(y_test, y_pred))
    print(classification_report(y_test, y_pred))

    textArea.insert(END, "Random Forest\n")
    textArea.insert(END, confusion_matrix(y_test, y_pred))
    textArea.insert(END, "\n")
    textArea.insert(END, classification_report(y_test, y_pred))
