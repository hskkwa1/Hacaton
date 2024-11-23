import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
from data_processing import clean_dataset
from main import interpret_query_with_openai

# Streamlit app configuration
st.set_page_config(
    page_title="Data Management Ally",
    page_icon="📊",
    layout="wide",
)

# Title
st.title("📊 Data Management Ally - Explore, Analyze, and Visualize")

# Sidebar: File Upload
st.sidebar.header("📂 Upload Your Dataset")
uploaded_file = st.sidebar.file_uploader("Upload a CSV file", type=["csv"])

if uploaded_file:
    try:
        # Load dataset
        data = pd.read_csv(uploaded_file)
        st.success("Dataset uploaded successfully!")
        st.write("Dataset Preview:")
        st.dataframe(data, use_container_width=True)

        # Data Cleaning
        if st.checkbox("🧹 Clean Dataset"):
            data = clean_dataset(data)
            st.info("Dataset cleaned successfully!")
            st.write("Cleaned Dataset:")
            st.dataframe(data, use_container_width=True)

        # Generate Insights
        if st.button("📊 Generate Insights"):
            st.subheader("Dataset Insights")
            st.write("Basic Statistics:")
            st.write(data.describe())
            st.write("Column Data Types:")
            st.write(data.dtypes)

        # Query Input
        st.sidebar.subheader("🔍 Query the Data")
        user_question = st.text_input(
            "Ask a question about the dataset (e.g., 'Show sales trends over time' or 'How many rows are empty?')"
        )

        if st.button("🔎 Run Query"):
            if uploaded_file:
                try:
                    # Handle predefined queries with pandas
                    if "empty rows" in user_question.lower():
                        empty_rows = data.isnull().any(axis=1).sum()
                        st.subheader("Query Results")
                        st.write(f"Your query: {user_question}")
                        st.write(f"There are {empty_rows} empty rows in the dataset.")
                    elif "missing values" in user_question.lower():
                        missing_summary = data.isnull().sum().to_dict()
                        st.subheader("Query Results")
                        st.write(f"Your query: {user_question}")
                        st.write("Missing Values Summary:")
                        st.write(missing_summary)
                    else:
                        # Use OpenAI for other natural language queries
                        result = interpret_query_with_openai(user_question, data)
                        st.subheader("Query Results")
                        st.write(f"Your query: {user_question}")
                        st.write(result)
                except Exception as e:
                    st.error(f"An error occurred: {e}")
            else:
                st.warning("Please upload a dataset before asking a question.")

        # Visualization Options
        st.sidebar.subheader("📊 Data Visualization")
        selected_columns = st.sidebar.multiselect("Select columns for visualization", data.columns)
        chart_type = st.sidebar.selectbox("Select chart type", ["Line", "Bar", "Scatter"])

        if len(selected_columns) == 2:
            st.subheader("Visualization")
            fig, ax = plt.subplots()
            if chart_type == "Line":
                data.plot(x=selected_columns[0], y=selected_columns[1], kind="line", ax=ax)
            elif chart_type == "Bar":
                data.plot(x=selected_columns[0], y=selected_columns[1], kind="bar", ax=ax)
            elif chart_type == "Scatter":
                data.plot(x=selected_columns[0], y=selected_columns[1], kind="scatter", ax=ax)
            st.pyplot(fig)
        elif len(selected_columns) > 2:
            st.warning("Please select only two columns for visualization.")

        # Download Cleaned Dataset
        if st.button("💾 Download Cleaned Dataset"):
            csv = data.to_csv(index=False).encode('utf-8')
            st.download_button(
                label="Download CSV",
                data=csv,
                file_name="cleaned_dataset.csv",
                mime="text/csv",
            )
    except Exception as e:
        st.error(f"Failed to process the uploaded file: {e}")
else:
    st.info("Please upload a dataset to get started.")
