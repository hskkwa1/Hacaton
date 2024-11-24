import pandas as pd


def clean_dataset(data):

    data.columns = [col.strip().replace(" ", "_").lower() for col in data.columns]

    data = data.drop_duplicates()
    return data.fillna("N/A")


def analyze_data(data, query):

    if "show" in query.lower() and "columns" in query.lower():
        return data.columns.tolist()
    elif "summary" in query.lower():
        return data.describe().to_dict()
    return "Query interpretation not implemented yet."
