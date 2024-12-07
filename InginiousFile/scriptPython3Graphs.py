import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

# Vérifier si les fichiers CSV et l'argument de sortie sont passés
if len(sys.argv) < 5:
    print("Usage : python script.py <fichier_csv1> <fichier_sortie.png> <fichier_csv2> <fichier_csv3>")
    sys.exit(1)

# Récupérer les fichiers d'entrée et le fichier de sortie
fileCSV1 = sys.argv[1]
outputFile = sys.argv[2]
fileCSV2 = sys.argv[3]
fileCSV3 = sys.argv[4]

# Vérifier si les fichiers existent
for file in [fileCSV1, fileCSV2, fileCSV3]:
    if not os.path.isfile(file):
        print(f"Erreur : Le fichier '{file}' n'existe pas.")
        sys.exit(1)

# Charger les données des fichiers CSV
data1 = pd.read_csv(fileCSV1)
data2 = pd.read_csv(fileCSV2)
data3 = pd.read_csv(fileCSV3)


#data1.iloc[:, 1:] = data1.iloc[:, 1:] / 1000 
#data2.iloc[:, 1:] = data2.iloc[:, 1:] / 1000
#data3.iloc[:, 1:] = data3.iloc[:, 1:] / 1000

# Calculer la moyenne et l'écart-type pour chaque fichier
data1['mean_time'] = data1.iloc[:, 1:].mean(axis=1)
data1['std_time'] = data1.iloc[:, 1:].std(axis=1)

data2['mean_time'] = data2.iloc[:, 1:].mean(axis=1)
data2['std_time'] = data2.iloc[:, 1:].std(axis=1)

data3['mean_time'] = data3.iloc[:, 1:].mean(axis=1)
data3['std_time'] = data3.iloc[:, 1:].std(axis=1)

defaultCase=True

# Fonction de création du graphique
def creer_graphique_combine(titre, nom_sortie, defaut):
    plt.figure(figsize=(10, 6))

    # Tracer les courbes avec les points reliés par une ligne
    plt.errorbar(
        data1['NumberThread'],
        data1['mean_time'],
        yerr=data1['std_time'],
        fmt='o-', 
        ecolor='red',
        capsize=5,
        label="Sans TAS"
    )

    plt.errorbar(
        data2['NumberThread'],
        data2['mean_time'],
        yerr=data2['std_time'],
        fmt='s-', 
        ecolor='blue',
        capsize=5,
        label="Avec TAS"
    )

    plt.errorbar(
        data3['NumberThread'],
        data3['mean_time'],
        yerr=data3['std_time'],
        fmt='^-', 
        ecolor='green',
        capsize=5,
        label="Avec TATAS"
    )

    # Ajouter un titre et des labels
    plt.title(titre)
    plt.xlabel("Nombre de Threads")
    plt.ylabel("Temps Moyen (ms)")
    plt.legend()

    # Fixer les ticks de l'axe des X (2, 4, 8, 16, 32)
    plt.xticks([2, 4, 8, 16, 32])

    if not defaut:
        plt.yscale('log')  # Appliquer l'échelle logarithmique à l'axe Y
        plt.ylim(0.0001, 1000)
    else:
        plt.ylim(0)    

    # Ajuster la disposition pour éviter le chevauchement
    plt.tight_layout()

    # Sauvegarder le graphique
    plt.savefig(nom_sortie)
    plt.show()  # Afficher le graphique

# Déterminer le titre basé sur les fichiers d'entrée
base_name = os.path.splitext(os.path.basename(fileCSV1))[0]
if base_name == "pbPhiloIngi":
    titre = "Comparaison des Performances Philosophes : Sans TAS, Avec TAS, Avec TATAS"
if base_name == "pbPhilo":
    titre = "Comparaison des Performances Philosophes : Sans TAS, Avec TAS, Avec TATAS (Donées Locale)"

elif base_name == "ProdCons2Ingi":
    titre = "Comparaison des Performances Prod/cons : Sans TAS, Avec TAS, Avec TATAS"
elif base_name == "ProdCons2":
    titre = "Comparaison des Performances Prod/cons : Sans TAS, Avec TAS, Avec TATAS (Donées Locale)"

elif base_name == "EcritLect2Ingi":
    defaultCase=False
    titre = "Comparaison des Performances Writer/reader : Sans TAS, Avec TAS, Avec TATAS"
elif base_name == "EcritLect2":
    titre = "Comparaison des Performances Writer/reader : Sans TAS, Avec TAS, Avec TATAS (Donées Locale)"
    defaultCase=False

# Créer le graphique combiné
creer_graphique_combine(titre, outputFile,defaultCase)
