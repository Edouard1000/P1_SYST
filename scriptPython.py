import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

# Vérifier si le fichier CSV a bien été passé en argument
if len(sys.argv) < 3:
    print("Usage : python script.py <fichier_entree.csv>")
    sys.exit(1)

fileCSV = sys.argv[1]

# Vérifier si le fichier existe
if not os.path.isfile(fileCSV):
    print(f"Erreur : Le fichier '{fileCSV}' n'existe pas.")
    sys.exit(1)

fileName = os.path.splitext(fileCSV)[0]
outputFile = sys.argv[2]

# Extraction et traitement des données
data = pd.read_csv(fileCSV)

# Calculer la moyenne et l'écart-type pour chaque ligne (à partir de la 2ème colonne)
data['mean_time'] = data.iloc[:, 1:].mean(axis=1)
data['std_time'] = data.iloc[:, 1:].std(axis=1)

# Fonction de création du graphique
def creer_graphique(titre, nom_sortie):
    plt.figure(figsize=(10, 6))
    
    # Tracer avec les points reliés par une ligne
    plt.errorbar(
        data['NumberThread'],
        data['mean_time'],
        yerr=data['std_time'],  # Ecart-type
        fmt='o-',                # 'o-' signifie points reliés par une ligne
        ecolor='red',
        capsize=5,
        label="Temps Moyen +/- Ecart-type"
    )

    # Ajouter un titre et des labels
    plt.title(titre)
    plt.xlabel("Nombre de Threads")
    plt.ylabel("Temps Moyen (ms)")
    plt.legend()

    # Fixer les ticks de l'axe des X (2, 4, 8, 16, 32)
    plt.xticks([2, 4, 8, 16, 32])

    # Configurer les axes et le fond
    plt.ylim(0)  # Limiter l'axe des ordonnées à partir de 0
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    
    # Ajuster la disposition pour éviter le chevauchement
    plt.tight_layout()
    
    # Sauvegarder le graphique
    plt.savefig(nom_sortie)
    plt.show()  # Afficher le graphique


if fileName == 'Csvfile/pbPhilo':
    titre = "Test de Performance Philosophe"
elif fileName == 'Csvfile/ProdCons':
    titre = "Test de Performance Producteur-Consommateur"
elif fileName == 'Csvfile/EcritLect':
    titre = "Test de Performance Ecriture-Lecture"
else:
    titre = "Test de Performance Non Défini"

creer_graphique(titre, outputFile)
    
