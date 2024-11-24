import pandas as pd


def filter_dataset(data, keywords):

    filtered_data = data.copy()

    for column in ["kingdom", "phylum", "class", "order", "family", "genus", "species"]:
        if column in data.columns:
            matching_keywords = [kw for kw in keywords if kw in data[column].str.lower().unique()]
            if matching_keywords:
                filtered_data = filtered_data[filtered_data[column].str.lower().isin(matching_keywords)]

    return filtered_data



def count_values(data, column):

    if column in data.columns:
        return data[column].value_counts()
    return pd.Series(dtype='int')


def find_extreme(data, column, extreme="highest"):

    if column in data.columns:
        if extreme == "highest":
            return data.sort_values(by=column, ascending=False).head(1)
        elif extreme == "lowest":
            return data.sort_values(by=column, ascending=True).head(1)
    return pd.DataFrame()


def summarize_dataset(data):

    summary = {
        "Total Rows": len(data),
        "Columns": list(data.columns),
        "Unique Kingdoms": data["Kingdom"].nunique(),
        "Unique Species": data["Species"].nunique(),
    }
    return summary


def reject_unrelated_query():

    return "I'm designed to answer questions specifically about the taxonomy dataset. Please ask a relevant question."

