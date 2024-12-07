# Compilateur et options
CC = gcc
CFLAGS = -lpthread
OBJ_DIR = Objectfile
CSV_DIR = Csvfile
SRC_DIR = Sourcefile
BASH_DIR = Bashfile



# Chemins des dossiers pour les plots
PLOT_DIR = plots
DATA_DIR = DataInginious
SCRIPT = scriptPython.py
SCRIPT2 = scriptPython3Graphs.py
# Liste des fichiers CSV
CSV_FILES = \
	EcritLect2Ingi.csv \
	EcritLectIngi.csv \
	pbPhiloIngi.csv \
	ProdCons2Ingi.csv \
	ProdConsActiveIngi.csv \
	ProdConsIngi.csv \
	TestAndTestIngi.csv \
	TestVerrouIngi.csv \
	readActive.csv \
	readActive2.csv



all: plots/pbPhiloIngi.png plots/ProdCons2Ingi.png plots/EcritLect2Ingi.png TASvsTATAS Comparaison3Graphs1 Comparaison3Graphs2 Comparaison3Graphs3 help



# Créer les répertoires nécessaires
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(CSV_DIR):
	mkdir -p $(CSV_DIR)
$(PLOT_DIR):
	mkdir -p $(PLOT_DIR)

# Règles de compilation des fichiers objets

######## Debut Tache 1#########

$(OBJ_DIR)/pbPhilo: $(SRC_DIR)/pbPhilosophesVF.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

#########Prod Cons Version 2 ##########
$(OBJ_DIR)/prodCons2: $(SRC_DIR)/prodCons2.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@
#########Fin Prod Cons Version 2 ##########

$(OBJ_DIR)/readerWriter: $(SRC_DIR)/read.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

#########Ecrivain Lecteur Version 2 ##########
$(OBJ_DIR)/readerWriter2: $(SRC_DIR)/read2.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@
#########Fin Ecrivain Lecteur Version 2 ##########

############Fin Tache 1################

############Tache 2.1 : Test and Set compilation(Objets) et cibles ################
$(OBJ_DIR)/verrou.o: $(SRC_DIR)/testANDset.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/testANDset.c -o $@

$(OBJ_DIR)/testVerrou.o: $(SRC_DIR)/testVerrou.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/testVerrou.c -o $@


OBJ_FILES = $(OBJ_DIR)/testVerrou.o $(OBJ_DIR)/verrou.o

$(OBJ_DIR)/testVerrou: $(OBJ_FILES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ -lpthread	

############Tache 2.2 : Test and Test compilation(Objets) et cibles################

$(OBJ_DIR)/testANDtest.o: $(SRC_DIR)/testANDtest.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/testANDtest.c -o $@

OBJ_FILES2 = $(OBJ_DIR)/testANDtest.o $(OBJ_DIR)/verrou.o

$(OBJ_DIR)/testANDtest: $(OBJ_FILES2) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES2) -o $@ -lpthread

########Tache 2.5 : Utilisation des semaphores ##########

#Philosophes actifs 1 & 2 (fichiers objets et cibles)
$(OBJ_DIR)/philosophesActive.o: $(SRC_DIR)/philosophesActive.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/philosophesActive.c -o $@
$(OBJ_DIR)/philosophesActive: $(OBJ_DIR)/philosophesActive.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/philosophesActive.o $(OBJ_DIR)/verrou.o -o $@ -lpthread

$(OBJ_DIR)/philosophesActive2.o: $(SRC_DIR)/philosophesActive2.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/philosophesActive2.c -o $@
$(OBJ_DIR)/philosophesActive2: $(OBJ_DIR)/philosophesActive2.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/philosophesActive2.o $(OBJ_DIR)/verrou.o -o $@ -lpthread
#Fin Philosophes actifs 1 & 2 (fichiers objets et cibles)

#Production et consommation active 1 & 2 (fichiers objets et cibles)
$(OBJ_DIR)/prodConsActive.o: $(SRC_DIR)/prodConsActive.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/prodConsActive.c -o $@
$(OBJ_DIR)/prodConsActive: $(OBJ_DIR)/prodConsActive.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/prodConsActive.o $(OBJ_DIR)/verrou.o -o $@ -lpthread

$(OBJ_DIR)/prodConsActive2.o: $(SRC_DIR)/prodConsActive2.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/prodConsActive2.c -o $@
$(OBJ_DIR)/prodConsActive2: $(OBJ_DIR)/prodConsActive2.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/prodConsActive2.o $(OBJ_DIR)/verrou.o -o $@ -lpthread
#Fin Production et consommation active 1 & 2 (fichiers objets et cibles)

#Ecritures et Lectures active 1 & 2 (fichiers objets et cibles)
$(OBJ_DIR)/readActive.o: $(SRC_DIR)/readActive.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/readActive.c -o $@
$(OBJ_DIR)/readActive: $(OBJ_DIR)/readActive.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/readActive.o $(OBJ_DIR)/verrou.o -o $@ -lpthread

$(OBJ_DIR)/readActive2.o: $(SRC_DIR)/readActive2.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/readActive2.c -o $@
$(OBJ_DIR)/readActive2: $(OBJ_DIR)/readActive2.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/readActive2.o $(OBJ_DIR)/verrou.o -o $@ -lpthread
#Ecritures et Lectures active  1 & 2 (fichiers objets et cibles)

############# Fin Tache 2 ##################

##########Debut des cibles pour le Csv ###############

CsvpbPhilo: $(OBJ_DIR)/pbPhilo | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/pbPhilo $(CSV_DIR)/pbPhilo.csv


CsvProdCons2: $(OBJ_DIR)/prodCons2 | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/prodCons2 $(CSV_DIR)/ProdCons2.csv

CsvReaderWriter: $(OBJ_DIR)/readerWriter | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/readerWriter $(CSV_DIR)/EcritLect.csv

CsvReaderWriter2: $(OBJ_DIR)/readerWriter2 | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/readerWriter2 $(CSV_DIR)/EcritLect2.csv

###### Csv De test and (Test) and set#################
CsvTestVerrou: $(OBJ_DIR)/testVerrou | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/testVerrou $(CSV_DIR)/TestVerrou.csv

CsvTestAndTest: $(OBJ_DIR)/testANDtest | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/testANDtest $(CSV_DIR)/TestAndTest.csv
CsvPhilosopesActive: $(OBJ_DIR)/philosophesActive | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/philosophesActive $(CSV_DIR)/philosophesActive.csv
CsvPhilosopesActive2: $(OBJ_DIR)/philosophesActive2 | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/philosophesActive2 $(CSV_DIR)/philosophesActive2.csv


CsvProdConsActive: $(OBJ_DIR)/prodConsActive | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/prodConsActive $(CSV_DIR)/ProdConsActive.csv
CsvProdConsActive2: $(OBJ_DIR)/prodConsActive2 | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/prodConsActive2 $(CSV_DIR)/prodConsActive2.csv

CsvReadActive: $(OBJ_DIR)/readActive | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/readActive $(CSV_DIR)/readActive.csv

CsvReadActive2: $(OBJ_DIR)/readActive2 | $(CSV_DIR)
	chmod +x scriptBash2.sh
	./scriptBash2.sh $(OBJ_DIR)/readActive2 $(CSV_DIR)/readActive2.csv
####### Fin des cibles pour Csv: (Attention) Pas complet #######
allCsv: CsvpbPhilo CsvProdCons2 CsvReaderWriter CsvTestVerrou CsvTestAndTest CsvPhilosopesActive CsvPhilosopesActive2 CsvProdConsActive CsvProdConsActive2 CsvReadActive CsvReadActive2  

	
# Génération des graphes pour tous les fichiers CSV

CSV_FILES = $(wildcard $(DATA_DIR)/*.csv)
PNG_FILES = $(patsubst $(DATA_DIR)/%.csv, $(PLOT_DIR)/%.png, $(CSV_FILES))
print_csv_length:
	@echo "Number of CSV files: $(words $(CSV_FILES))"
plot: $(PNG_FILES)

$(PLOT_DIR)/%.png: $(DATA_DIR)/%.csv $(SCRIPT) | $(PLOT_DIR)
	python3 $(SCRIPT) $< $@


##### Cibles pour les plots de la tache 1 ########
plots/pbPhiloIngi.png: plots/pbPhiloIngi.png
plots/ProdCons2Ingi.png: plots/ProdCons2Ingi.png

plots/EcritLect2Ingi.png: plots/EcritLect2Ingi.png

plotPhilo: CsvpbPhilo | $(PLOT_DIR)
	python3 scriptPython.py $(CSV_DIR)/pbPhilo.csv $(PLOT_DIR)/philo_plot.png

plotProdCons: CsvProdCons2 | $(PLOT_DIR)
	python3 ./scriptPython.py $(CSV_DIR)/ProdCons2.csv $(PLOT_DIR)/prodcons_plot.png

plotReaderWriter: CsvReaderWriter | $(PLOT_DIR)
	python3 ./scriptPython.py $(CSV_DIR)/EcritLect.csv $(PLOT_DIR)/readerwriter_plot.png

##### Fin Cibles pour les plots de la tache 1 ########

###### Plots à partir des données Inginious ######## 
# plot TASvsTATAS
PLOT_OUTPUT = plots/TASvsTATAS.png
TASvsTATAS: $(SCRIPT) | $(PLOT_DIR)
	python3 $(SCRIPT) $(DATA_DIR)/TestVerrouIngi.csv $(PLOT_OUTPUT) $(DATA_DIR)/TestAndTestIngi.csv
#plot comparaison 3 graphs : 
PLOT_OUTPUT_COMPARAISON1 = plots/Comparaison3Graphs1.png
Comparaison3Graphs1: $(SCRIPT2) | $(PLOT_DIR)
	python3 $(SCRIPT2) $(DATA_DIR)/pbPhiloIngi.csv $(PLOT_OUTPUT_COMPARAISON1) $(DATA_DIR)/philosophesActiveIngi.csv $(DATA_DIR)/philosophesActive2Ingi.csv 
PLOT_OUTPUT_COMPARAISON2 = plots/Comparaison3Graphs2.png
Comparaison3Graphs2: $(SCRIPT2) | $(PLOT_DIR)
	python3 $(SCRIPT2) $(DATA_DIR)/ProdCons2Ingi.csv $(PLOT_OUTPUT_COMPARAISON2) $(DATA_DIR)/ProdConsActiveIngi.csv $(DATA_DIR)/prodConsActive2Ingi.csv 
PLOT_OUTPUT_COMPARAISON3 = plots/Comparaison3Graphs3.png
Comparaison3Graphs3: $(SCRIPT2) | $(PLOT_DIR)
	python3 $(SCRIPT2) $(DATA_DIR)/EcritLect2Ingi.csv $(PLOT_OUTPUT_COMPARAISON3) $(DATA_DIR)/readActiveIngi.csv $(DATA_DIR)/readActive2Ingi.csv 

###### Fin Plots à partir des données Inginious ########


###### Plots à partir des données Genérée apres l'execution actuelles (données locales) ########

PLOT_OUTPUT_LOCALE = plots/TASvsTATASloc.png
TASvsTATASloc: $(SCRIPT) CsvTestVerrou CsvTestAndTest | $(PLOT_DIR)
	python3 $(SCRIPT) $(CSV_DIR)/TestVerrou.csv $(PLOT_OUTPUT_LOCALE) $(CSV_DIR)/TestAndTest.csv 

PLOT_OUTPUT_COMPARAISON1_LOCALE = plots/Comparaison3Graphs1loc.png
Comparaison3Graphs1loc: $(SCRIPT2) CsvpbPhilo CsvPhilosopesActive CsvPhilosopesActive2 | $(PLOT_DIR)
	python3 $(SCRIPT2) $(CSV_DIR)/pbPhilo.csv $(PLOT_OUTPUT_COMPARAISON1_LOCALE) $(CSV_DIR)/philosophesActive.csv $(CSV_DIR)/philosophesActive2.csv 

PLOT_OUTPUT_COMPARAISON2_LOCALE = plots/Comparaison3Graphs2loc.png
Comparaison3Graphs2loc: $(SCRIPT2) CsvProdCons2 CsvProdConsActive CsvProdConsActive2 | $(PLOT_DIR)
	python3 $(SCRIPT2) $(CSV_DIR)/ProdCons2.csv $(PLOT_OUTPUT_COMPARAISON2_LOCALE) $(CSV_DIR)/prodConsActive2.csv $(CSV_DIR)/ProdConsActive.csv


PLOT_OUTPUT_COMPARAISON3_LOCALE = plots/Comparaison3Graphs3loc.png
Comparaison3Graphs3loc: $(SCRIPT2) CsvReaderWriter CsvReadActive CsvReadActive2 | $(PLOT_DIR)
	python3 $(SCRIPT2) $(CSV_DIR)/EcritLect.csv $(PLOT_OUTPUT_COMPARAISON3_LOCALE) $(CSV_DIR)/readActive2.csv $(CSV_DIR)/readActive.csv
make allPlot: plotPhilo plotProdCons plotReaderWriter TASvsTATASloc Comparaison3Graphs1loc Comparaison3Graphs2loc Comparaison3Graphs3loc
# Nettoyage des fichiers objets et exécutables
clean:
	rm -rf $(OBJ_DIR) $(CSV_DIR) $(PLOT_DIR)


help:
	@echo "Usage: make <target>"
	@echo ""
	@echo "Targets disponibles :"
	@echo ""
	@echo "1. Générer les fichiers CSV :"
	@echo "   - CsvpbPhilo           : Génère le fichier CSV pour le problème des philosophes."
	@echo "   - CsvProdCons2         : Génère le fichier CSV pour le problème producteur-consommateur."
	@echo "   - CsvReaderWriter      : Génère le fichier CSV pour le problème lecteur-écrivain."
	@echo "   - CsvReaderWriter2     : Génère le fichier CSV pour le problème lecteur-écrivain (version 2)."
	@echo "   - CsvTestVerrou        : Génère le fichier CSV pour le test de verrou (TestAndSet)."
	@echo "   - CsvTestAndTest       : Génère le fichier CSV pour le test de synchronisation TestAndTest."
	@echo "   - CsvPhilosopesActive  : Génère le fichier CSV pour le problème des philosophes actifs (avec TAS)."
	@echo "   - CsvPhilosopesActive2 : Génère le fichier CSV pour le problème des philosophes actifs (Avec TATAS)."
	@echo "   - CsvProdConsActive    : Génère le fichier CSV pour le problème producteur-consommateur actif (avec TAS)."
	@echo "   - CsvProdConsActive2   : Génère le fichier CSV pour le problème producteur-consommateur actif (avec TATAS)."
	@echo "   - CsvReadActive        : Génère le fichier CSV pour le problème lecteur-écrivain actif (avec TAS)."
	@echo "   - CsvReadActive2       : Génère le fichier CSV pour le problème lecteur-écrivain actif (avec TATAS)."
	@echo ""
	@echo "2. Générer les plots (graphes) :"
	@echo "   - plotPhilo            : Génère le graphique pour le problème des philosophes."
	@echo "   - plotProdCons         : Génère le graphique pour le problème producteur-consommateur."
	@echo "   - plotReaderWriter     : Génère le graphique pour le problème lecteur-écrivain."
	@echo "   - TASvsTATAS           : Génère un graphique comparatif entre TestVerrou et TestAndTest avec les données Inginious."
	@echo "   - TASvsTATASloc        : Génère un graphique comparatif entre TestVerrou et TestAndTest avec les données locales."
	@echo "   - Comparaison3Graphs1  : Génère un graphique comparatif pour les philosophes avec les données Inginious (comparaison POxis TAS et TATAS)."
	@echo "   - Comparaison3Graphs1loc: Génère un graphique comparatif pour les philosophes avec les données locales (comparaison POxis TAS et TATAS)."
	@echo "   - Comparaison3Graphs2  : Génère un graphique comparatif pour les producteurs-consommateurs avec les données Inginious (comparaison POxis TAS et TATAS)."
	@echo "   - Comparaison3Graphs2loc: Génère un graphique comparatif pour les producteurs-consommateurs avec les données locales (comparaison POxis TAS et TATAS)."
	@echo "   - Comparaison3Graphs3  : Génère un graphique comparatif pour les lecteurs-écrivains avec les données Inginious (comparaison POxis TAS et TATAS)."
	@echo "   - Comparaison3Graphs3loc: Génère un graphique comparatif pour les lecteurs-écrivains avec les données locales (comparaison POxis TAS et TATAS)."
	@echo "   - readvslec            : Génère un graphique comparatif entre les lectures et les écritures avec les données Inginious."
	@echo "   - readvslecloc         : Génère un graphique comparatif entre les lectures et les écritures avec les données locales."
	@echo ""
	@echo "3. Cibles supplémentaires :"
	@echo "   - clean                : Supprime les fichiers objets, les fichiers CSV, et les graphiques générés."

