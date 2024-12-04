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

# Liste des fichiers CSV
CSV_FILES = \
	EcritLect2Ingi.csv \
	EcritLectIngi.csv \
	pbPhiloIngi.csv \
	ProdCons2Ingi.csv \
	ProdConsActiveIngi.csv \
	ProdConsIngi.csv \
	TestAndTestIngi.csv \
	TestVerrouIngi.csv



all: CsvTestVerrou CsvTestAndTest CsvProdConsActive

#CsvpbPhilo CsvProdCons CsvProdCons2 CsvReaderWriter CsvReaderWriter2 CsvTestVerrou CsvTestAndTest CsvProdConsActive

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

$(OBJ_DIR)/prodCons: $(SRC_DIR)/prodConsvf.c | $(OBJ_DIR)
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

############Tache 2.1 : Test and Set ################
$(OBJ_DIR)/verrou.o: $(SRC_DIR)/testANDset.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/testANDset.c -o $@

$(OBJ_DIR)/testVerrou.o: $(SRC_DIR)/testVerrou.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/testVerrou.c -o $@


OBJ_FILES = $(OBJ_DIR)/testVerrou.o $(OBJ_DIR)/verrou.o

$(OBJ_DIR)/testVerrou: $(OBJ_FILES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ -lpthread	

############Tache 2.2 : Test and Test ################

$(OBJ_DIR)/testANDtest.o: $(SRC_DIR)/testANDtest.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/testANDtest.c -o $@

OBJ_FILES2 = $(OBJ_DIR)/testANDtest.o $(OBJ_DIR)/verrou.o

$(OBJ_DIR)/testANDtest: $(OBJ_FILES2) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES2) -o $@ -lpthread

########Tache 2.5 : Utilisation des semaphores ( pas complet) ##########
$(OBJ_DIR)/philosophesActive.o: $(SRC_DIR)/philosophesActive.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/philosophesActive.c -o $@

$(OBJ_DIR)/philosophesActive: $(OBJ_DIR)/philosophesActive.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/philosophesActive.o $(OBJ_DIR)/verrou.o -o $@ -lpthread
$(OBJ_DIR)/philosophesActive2.o: $(SRC_DIR)/philosophesActive2.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/philosophesActive2.c -o $@

$(OBJ_DIR)/philosophesActive2: $(OBJ_DIR)/philosophesActive2.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/philosophesActive2.o $(OBJ_DIR)/verrou.o -o $@ -lpthread



$(OBJ_DIR)/prodConsActive.o: $(SRC_DIR)/prodConsActive.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/prodConsActive.c -o $@

$(OBJ_DIR)/prodConsActive: $(OBJ_DIR)/prodConsActive.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/prodConsActive.o $(OBJ_DIR)/verrou.o -o $@ -lpthread
$(OBJ_DIR)/prodConsActive2.o: $(SRC_DIR)/prodConsActive2.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/prodConsActive2.c -o $@

$(OBJ_DIR)/prodConsActive2: $(OBJ_DIR)/prodConsActive2.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/prodConsActive2.o $(OBJ_DIR)/verrou.o -o $@ -lpthread

$(OBJ_DIR)/readActive.o: $(SRC_DIR)/readActive.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/readActive.c -o $@
$(OBJ_DIR)/readActive: $(OBJ_DIR)/readActive.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/readActive.o $(OBJ_DIR)/verrou.o -o $@ -lpthread
$(OBJ_DIR)/readActive2.o: $(SRC_DIR)/readActive2.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/readActive2.c -o $@
$(OBJ_DIR)/readActive2: $(OBJ_DIR)/readActive2.o $(OBJ_DIR)/verrou.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/readActive2.o $(OBJ_DIR)/verrou.o -o $@ -lpthread

############# Fin Tache 2 ##################

##########Debut des cibles pour le Csv ###############

CsvpbPhilo: $(OBJ_DIR)/pbPhilo | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/pbPhilo $(CSV_DIR)/pbPhilo.csv

CsvProdCons: $(OBJ_DIR)/prodCons | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/prodCons $(CSV_DIR)/ProdCons.csv

CsvProdCons2: $(OBJ_DIR)/prodCons2 | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/prodCons2 $(CSV_DIR)/ProdCons2.csv

CsvReaderWriter: $(OBJ_DIR)/readerWriter | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/readerWriter $(CSV_DIR)/EcritLect.csv

CsvReaderWriter2: $(OBJ_DIR)/readerWriter2 | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/readerWriter2 $(CSV_DIR)/EcritLect2.csv

###### Csv De test and (Test) and set#################
CsvTestVerrou: $(OBJ_DIR)/testVerrou | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/testVerrou $(CSV_DIR)/TestVerrou.csv

CsvTestAndTest: $(OBJ_DIR)/testANDtest | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/testANDtest $(CSV_DIR)/TestAndTest.csv
CsvPhilosopesActive: $(OBJ_DIR)/philosophesActive | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/philosophesActive $(CSV_DIR)/philosophesActive.csv
CsvPhilosopesActive2: $(OBJ_DIR)/philosophesActive2 | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/philosophesActive2 $(CSV_DIR)/philosophesActive2.csv


CsvProdConsActive: $(OBJ_DIR)/prodConsActive | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/prodConsActive $(CSV_DIR)/ProdConsActive.csv
CsvProdConsActive2: $(OBJ_DIR)/prodConsActive2 | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/prodConsActive2 $(CSV_DIR)/prodConsActive2.csv

CsvReadActive: $(OBJ_DIR)/readActive | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/readActive $(CSV_DIR)/readActive.csv

CsvReadActive2: $(OBJ_DIR)/readActive2 | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/readActive2 $(CSV_DIR)/readActive2.csv
####### Fin des cibles pour Csv: (Attention) Pas complet #######

# Génération des graphes pour tous les fichiers CSV

CSV_FILES = $(wildcard $(DATA_DIR)/*.csv)
PNG_FILES = $(patsubst $(DATA_DIR)/%.csv, $(PLOT_DIR)/%.png, $(CSV_FILES))

plot: $(PNG_FILES)

$(PLOT_DIR)/%.png: $(DATA_DIR)/%.csv $(SCRIPT) | $(PLOT_DIR)
	python3 $(SCRIPT) $< $@

# plot TASvsTATAS
PLOT_OUTPUT = plots/TASvsTATAS.png
TASvsTATAS: $(SCRIPT)
	python3 $(SCRIPT) $(DATA_DIR)/TestVerrouIngi.csv $(PLOT_OUTPUT) $(DATA_DIR)/TestAndTestIngi.csv

#allCsv: CsvpbPhilo CsvProdCons CsvReaderWriter CsvTestVerrou CsvTestAndTest CsvProdConsActive  //Je sais pas si c'est necessaire pour Inginious


# Nettoyage des fichiers objets et exécutables
clean:
	rm -rf $(OBJ_DIR) $(CSV_DIR) $(PLOT_DIR)
