from tkinter import *
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import KFold
from sklearn.metrics import classification_report, confusion_matrix


def print_function_name(functionName):
    print(functionName)


def transform_data(filename):
    # create data frame
    features = ['buying', 'maint', 'doors', 'persons', 'lug_boot', 'safety', 'Class']
    dataset = pd.read_csv(filename, names=features)

    # clean data
    di = {'vhigh': 0, 'high': 1, 'med': 2, 'low': 3}
    dataset['buying'] = dataset['buying'].map(di)
    dataset['maint'] = dataset['maint'].map(di)

    dataset.loc[dataset['doors'] == '5more', 'doors'] = 5
    dataset.loc[dataset['persons'] == 'more', 'persons'] = 5

    di = {'small': 0, 'med': 1, 'big': 2}
    dataset['lug_boot'] = dataset['lug_boot'].map(di)

    di = {'low': 0, 'med': 1, 'high': 2}
    dataset['safety'] = dataset['safety'].map(di)

    # split data into features and labels
    X = dataset.iloc[:, :-1].values.astype(np.float64)
    Y = dataset.iloc[:, -1].values

    # return split data
    return X, Y

    # return train_test_split(X, Y, test_size=0.2)

def execute_Algo(filename, textArea):
    # split data into train and test sets
    # x_train, x_test, y_train, y_test = transform_data(filename)

    textArea.insert(END, "Multinominal Logistic Regression\n")

    # retrieve features and labels
    X, Y = transform_data(filename)

    num_fold = 1

    # split test and train data
    kf = KFold(n_splits=10, shuffle=True)
    for train_index, test_index in kf.split(X):
        x_train, x_test = X[train_index], X[test_index]
        y_train, y_test = Y[train_index], Y[test_index]

        # scale data
        scaler = StandardScaler()
        scaler.fit(x_train)
        x_train = scaler.transform(x_train)
        x_test = scaler.transform(x_test)

        # initialize model
        model = LogisticRegression(solver='lbfgs', multi_class='auto')

        # train model
        model.fit(x_train, y_train)

        # model predictions
        y_predictions = model.predict(x_test)

        print(confusion_matrix(y_test, y_predictions))
        print(classification_report(y_test, y_predictions))

        textArea.insert(END, "KFold {}\n".format(num_fold))
        textArea.insert(END, confusion_matrix(y_test, y_predictions))
        textArea.insert(END, "\n")
        textArea.insert(END, classification_report(y_test, y_predictions)+"\n")
        num_fold += 1





