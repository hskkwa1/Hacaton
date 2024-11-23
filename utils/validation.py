import pandas as pd


def validate_document(data):
    """
    Validuje dokument pomocou pravidiel.
    Zatiaľ ide len o ukážku pravidiel (napr. kontrola prázdnych hodnôt).
    """
    if "Text" not in data.columns:
        data["Text"] = data.iloc[:, 0]  # Pre prípad TXT dokumentov

    data["Validation"] = data["Text"].apply(lambda x: "Valid" if len(str(x).strip()) > 0 else "Invalid")
    return data