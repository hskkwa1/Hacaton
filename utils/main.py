import openai
import re
import pandas as pd
from dataset_handler import filter_dataset, count_values, find_extreme, summarize_dataset
from boot import OPENAI_KEY

# Set your OpenAI API key
openai.api_key = OPENAI_KEY


def reject_unrelated_query():
    """
    Standard response for unrelated queries.
    """
    return "I'm designed to answer questions specifically about the taxonomy dataset. Please ask a relevant question."


def extract_keywords(query):
    """
    Extract keywords from the user's query for optimized dataset handling.
    """
    keywords = re.findall(r'\b\w+\b', query)  # Simple word extractor
    return [kw.lower() for kw in keywords]

def count_values(data, column):
    if column in data.columns:
        return data[column].value_counts()
    return pd.Series(dtype='int')  # Empty series if column is not found


def find_extreme(data, column, extreme="highest"):
    if column in data.columns:
        if extreme == "highest":
            return data.sort_values(by=column, ascending=False).head(1)
        elif extreme == "lowest":
            return data.sort_values(by=column, ascending=True).head(1)
    return pd.DataFrame()  # Empty DataFrame if column is not found


def interpret_query_with_openai(query, data, max_rows=50, max_token_limit=3000):
    """
    Enhanced AI integration for dataset-specific querying.
    Ensures dataset-specific responses and handles queries dynamically.
    """
    # Extract keywords and clean the query
    keywords = extract_keywords(query)
    query_lower = query.lower()

    # Step 1: Reject unrelated queries
    unrelated_keywords = ["script", "code", "age", "politics", "current events"]
    if any(word in query_lower for word in unrelated_keywords):
        return reject_unrelated_query()

    # Step 2: Filter the dataset using the keywords
    filtered_data = filter_dataset(data, keywords)

    # Check if the filtered dataset is empty
    if filtered_data.empty:
        return f"Your query: '{query}' did not match any data. Ensure the query matches the dataset's structure."

    # Step 3: Handle specific queries
    if "how many" in query_lower or "count" in query_lower:
        # Dynamically determine the column to count
        for column in ["species", "genus", "family", "class", "order", "phylum", "kingdom"]:
            if column in data.columns and column in query_lower:
                count = filtered_data[column].nunique()
                return f"There are {count} unique {column} matching your query in the dataset."

        # Default count if no specific column is mentioned
        count = len(filtered_data)
        return f"There are {count} records matching your query in the dataset."

    # Handle highest/lowest queries
    # Additional code...

    # Step 4: Generate metadata for AI prompt
    total_rows = filtered_data.shape[0]
    filtered_table = filtered_data.head(max_rows).to_string(index=False)

    # Send data to OpenAI
    prompt = f"""
    You are an expert data analyst working with a taxonomy dataset. Here is some metadata:

    Total Rows in Filtered Data: {total_rows}
    Columns: {', '.join(data.columns)}
    Filtered Dataset (First {min(max_rows, total_rows)} Rows for Context):
    {filtered_table}

    Based on this dataset, answer the user's query: "{query}". Use only the dataset to respond.
    """

    # Send to OpenAI...
    # Additional code...
    # Ensure the prompt fits within the token limits
    if len(prompt) > max_token_limit:
        prompt = f"""
        You are an expert data analyst working with a taxonomy dataset. Here is some metadata:

        Total Rows: {total_rows}
        Columns: {', '.join(data.columns)}

        Based on this dataset, answer the user's query: "{query}". Use only the dataset to respond.
        """

    # Step 5: Use OpenAI API to process the prompt
    response = openai.ChatCompletion.create(
        model="gpt-4",
        messages=[
            {"role": "system", "content": "You are an expert data analyst. Use the dataset to answer the query."},
            {"role": "user", "content": prompt}
        ],
    )

    return response['choices'][0]['message']['content']