import openai
import re
import pandas as pd
from dataset_handler import filter_dataset, count_values, find_extreme, summarize_dataset
from boot import OPENAI_KEY

openai.api_key = OPENAI_KEY


def reject_unrelated_query():

    return "I'm designed to answer questions specifically about the taxonomy dataset. Please ask a relevant question."


def extract_keywords(query):

    keywords = re.findall(r'\b\w+\b', query)
    return [kw.lower() for kw in keywords]

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


def interpret_query_with_openai(query, data, max_rows=50, max_token_limit=3000):

    keywords = extract_keywords(query)
    query_lower = query.lower()

    unrelated_keywords = ["script", "code", "age", "politics", "current events"]
    if any(word in query_lower for word in unrelated_keywords):
        return reject_unrelated_query()

    filtered_data = filter_dataset(data, keywords)

    if filtered_data.empty:
        return f"Your query: '{query}' did not match any data. Ensure the query matches the dataset's structure."

    if "how many" in query_lower or "count" in query_lower:

        for column in ["species", "genus", "family", "class", "order", "phylum", "kingdom"]:
            if column in data.columns and column in query_lower:
                count = filtered_data[column].nunique()
                return f"There are {count} unique {column} matching your query in the dataset."

        count = len(filtered_data)
        return f"There are {count} records matching your query in the dataset."

    total_rows = filtered_data.shape[0]
    filtered_table = filtered_data.head(max_rows).to_string(index=False)

    prompt = f"""
    You are an expert data analyst working with a taxonomy dataset. Here is some metadata:

    Total Rows in Filtered Data: {total_rows}
    Columns: {', '.join(data.columns)}
    Filtered Dataset (First {min(max_rows, total_rows)} Rows for Context):
    {filtered_table}

    Based on this dataset, answer the user's query: "{query}". Use only the dataset to respond.
    """

    if len(prompt) > max_token_limit:
        prompt = f"""
        You are an expert data analyst working with a taxonomy dataset. Here is some metadata:

        Total Rows: {total_rows}
        Columns: {', '.join(data.columns)}

        Based on this dataset, answer the user's query: "{query}". Use only the dataset to respond.
        """

    response = openai.ChatCompletion.create(
        model="gpt-4",
        messages=[
            {"role": "system", "content": "You are an expert data analyst. Use the dataset to answer the query."},
            {"role": "user", "content": prompt}
        ],
    )

    return response['choices'][0]['message']['content']