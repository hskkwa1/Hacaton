import streamlit as st
import pandas as pd
import time
import plotly.express as px
from data_processing import clean_dataset
from main import interpret_query_with_openai

# Page Configuration
st.set_page_config(
    page_title="Smart Data Ally",
    page_icon="📊",
    layout="wide"
)

# Main Banner
st.markdown("""
    <style>
        .main-banner {
            background-color: #4CAF50;
            padding: 20px;
            border-radius: 10px;
            text-align: center;
            color: white;
            font-size: 1.5rem;
            margin-bottom: 20px;
        }
    </style>
    <div class="main-banner">
        <h1>📊 Smart Data Ally</h1>
        <p>Hackathon 2024 | Empowering data for everyone</p>
    </div>
""", unsafe_allow_html=True)

# Sidebar - File Upload and Task Selection
st.sidebar.title("🔍 Data Explorer")
uploaded_file = st.sidebar.file_uploader("Upload a CSV file", type=["csv"])
task = st.sidebar.radio("Choose a task:", ["Overview", "Analyze", "Visualize", "AI Insights"])

# Preload the taxonomy dataset
@st.cache
def load_preloaded_taxonomy_data():
    try:
        file_path = "data/taxonomy_dataset.csv"  # Update path if needed
        data = pd.read_csv(file_path)
        data = clean_dataset(data)  # Ensure data is cleaned
        return data
    except FileNotFoundError:
        st.error("Preloaded dataset not found. Please ensure 'taxonomy_dataset.csv' is in the 'data' directory.")
        return pd.DataFrame()  # Return an empty DataFrame as fallback


# Load dataset
if uploaded_file:
    # Load and display user-provided data
    raw_data = pd.read_csv(uploaded_file)
    data = clean_dataset(raw_data)  # Clean the dataset
    st.sidebar.success("Dataset uploaded and cleaned!")
else:
    # Load preloaded taxonomy dataset
    st.sidebar.info("Using preloaded taxonomy dataset.")
    data = load_preloaded_taxonomy_data()

# Task: Dataset Overview
if task == "Overview":
    st.header("📋 Dataset Overview")
    st.write("Below is the dataset used for analysis (cleaned if uploaded):")
    st.dataframe(data)
    st.success("Data loaded successfully!")

    st.subheader("Dataset Summary")
    st.write(data.describe())

# Task: Analyze Dataset
elif task == "Analyze":
    st.header("📈 Data Analysis")
    st.write("Perform quick analysis on your dataset.")

    metric = st.selectbox("Choose a metric to analyze:", data.select_dtypes(include=['number']).columns)
    st.write(f"Average {metric}: {data[metric].mean():.2f}")
    st.write(f"Total {metric}: {data[metric].sum()}")

    if "Region" in data.columns:
        st.write(f"Data breakdown by region for {metric}:")
        breakdown = data.groupby("Region")[metric].sum().reset_index()
        st.dataframe(breakdown)

# Task: Visualize Dataset
elif task == "Visualize":
    st.header("📊 Data Visualization")
    st.write("Create charts to visualize your data.")

    chart_type = st.selectbox("Choose a chart type:", ["Bar", "Line", "Pie"])
    x_axis = st.selectbox("Select X-axis:", data.columns)
    y_axis = st.selectbox("Select Y-axis (numerical):", data.select_dtypes(include=['number']).columns)

    if chart_type == "Bar":
        fig = px.bar(data, x=x_axis, y=y_axis, color="Region" if "Region" in data.columns else None,
                     title=f"{y_axis} by {x_axis}")
        st.plotly_chart(fig, use_container_width=True)
    elif chart_type == "Line":
        fig = px.line(data, x=x_axis, y=y_axis, title=f"{y_axis} Trend by {x_axis}")
        st.plotly_chart(fig, use_container_width=True)
    elif chart_type == "Pie":
        fig = px.pie(data, names=x_axis, values=y_axis, title=f"{y_axis} Distribution by {x_axis}")
        st.plotly_chart(fig, use_container_width=True)

# Task: AI Insights
elif task == "AI Insights":
    st.header("🤖 AI Insights")
    st.write("Ask natural language questions about your dataset, and let AI analyze it for you.")

    user_query = st.text_input("Ask your question (e.g., 'What is the average sales by region?'):")
    if st.button("Run AI Query"):
        if user_query:
            with st.spinner("AI is analyzing your question..."):
                response = interpret_query_with_openai(user_query, data)
                st.subheader("AI Response")
                st.write(response)
        else:
            st.warning("Please enter a question before running the query.")

# Footer
st.markdown("""
    <hr>
    <p style="text-align: center; font-size: 0.8rem;">
        Created for Hackathon 2024 | Powered by Streamlit, Plotly & OpenAI
    </p>
""", unsafe_allow_html=True)
