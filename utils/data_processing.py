import pandas as pd


def clean_dataset(data):
    """
    Cleans the dataset by renaming columns, handling missing values, and dropping duplicates.
    Ensures column names are consistently lowercase for easier handling.
    """
    # Standardize column names to lowercase with underscores
    data.columns = [col.strip().replace(" ", "_").lower() for col in data.columns]

    # Drop duplicates and fill missing values
    data = data.drop_duplicates()
    return data.fillna("N/A")


def analyze_data(data, query):
    """
    Placeholder for analyzing data based on user queries.
    """
    if "show" in query.lower() and "columns" in query.lower():
        return data.columns.tolist()
    elif "summary" in query.lower():
        return data.describe().to_dict()
    return "Query interpretation not implemented yet."
