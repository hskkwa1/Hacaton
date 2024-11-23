import streamlit as st
import pandas as pd
from utils.validation import validate_document

st.title("LLM Document Validator with Human-in-the-Loop")

# Upload dokumentu
uploaded_file = st.file_uploader("Nahrajte dokument (CSV alebo TXT)", type=["csv", "txt"])

if uploaded_file:
    if uploaded_file.name.endswith(".csv"):
        data = pd.read_csv(uploaded_file)
    else:
        data = pd.read_csv(uploaded_file, delimiter="\t", header=None, names=["Text"])

    st.write("Nahraný dokument:")
    st.dataframe(data)

    # Validácia dokumentu
    st.write("Validácia dokumentu:")
    validated_data = validate_document(data)
    st.dataframe(validated_data)

    # Možnosť manuálnej korekcie
    st.write("Manuálna korekcia:")
    for index, row in validated_data.iterrows():
        st.text_input(f"Riadok {index + 1}:", row["Text"], key=f"text_{index}")

st.sidebar.title("Nastavenia")
st.sidebar.write("Zvoľte parametre pre validáciu dokumentu.")