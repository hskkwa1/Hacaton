import openai
from utils.boot import OPENAI_KEY

# Set your OpenAI API key
openai.api_key = OPENAI_KEY

def interpret_query_with_openai(query, data):
    """
    Use OpenAI to interpret natural language queries and generate actionable insights.
    """
    # Create a descriptive prompt using dataset summary
    column_summary = ", ".join(data.columns.tolist())
    missing_values = data.isnull().sum().to_dict()
    prompt = f"""
    You are an expert data analyst. Below is the dataset metadata:
    - Columns: {column_summary}
    - Missing Values per Column: {missing_values}
    - Sample Data:
    {data.head(5).to_dict()}

    Answer the following query based on the dataset: "{query}".
    """

    # Use ChatCompletion API
    response = openai.ChatCompletion.create(
        model="gpt-4",
        messages=[
            {"role": "system", "content": "You are a data analysis assistant."},
            {"role": "user", "content": prompt}
        ],
    )
    return response['choices'][0]['message']['content']

