import pandas as pd


def filter_dataset(data, keywords):
    """
    Filter the dataset based on the given keywords.
    Handles Kingdom, Phylum, Class, Family, Genus, and Species dynamically.
    """
    # Assume columns are already cleaned to lowercase by clean_dataset
    filtered_data = data.copy()

    # Dynamically check each column for matching keywords
    for column in ["kingdom", "phylum", "class", "order", "family", "genus", "species"]:
        if column in data.columns:  # Ensure the column exists
            matching_keywords = [kw for kw in keywords if kw in data[column].str.lower().unique()]
            if matching_keywords:
                filtered_data = filtered_data[filtered_data[column].str.lower().isin(matching_keywords)]

    return filtered_data




def count_values(data, column):
    """
    Count unique values in a specified column.
    """
    if column in data.columns:
        return data[column].value_counts()
    return pd.Series(dtype='int')  # Return empty series if column not found


def find_extreme(data, column, extreme="highest"):
    """
    Find the row with the highest or lowest value in a specified column.
    """
    if column in data.columns:
        if extreme == "highest":
            return data.sort_values(by=column, ascending=False).head(1)
        elif extreme == "lowest":
            return data.sort_values(by=column, ascending=True).head(1)
    return pd.DataFrame()  # Return empty DataFrame if column not found


def summarize_dataset(data):
    """
    Provide a quick summary of the dataset, including column names and counts.
    """
    summary = {
        "Total Rows": len(data),
        "Columns": list(data.columns),
        "Unique Kingdoms": data["Kingdom"].nunique(),
        "Unique Species": data["Species"].nunique(),
    }
    return summary


def reject_unrelated_query():
    """
    Standard response for unrelated queries.
    """
    return "I'm designed to answer questions specifically about the taxonomy dataset. Please ask a relevant question."

