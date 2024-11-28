# Compilateur et options
CC = gcc
CFLAGS = -lpthread
OBJ_DIR = Objectfile
CSV_DIR = Csvfile
SRC_DIR = Sourcefile
BASH_DIR = Bashfile
PLOT_DIR = plots

# Créer les répertoires nécessaires
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(CSV_DIR):
	mkdir -p $(CSV_DIR)
$(PLOT_DIR):
	mkdir -p $(PLOT_DIR)

# Règles de compilation des fichiers objets
$(OBJ_DIR)/pbPhilo: $(SRC_DIR)/pbPhilosophesVF.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/prodCons: $(SRC_DIR)/prodConsvf.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/readerWriter: $(SRC_DIR)/read.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Règle pour copier ou exécuter le script Bash (s'il y a un objectif associé)
CsvpbPhilo: $(OBJ_DIR)/pbPhilo | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/pbPhilo $(CSV_DIR)/pbPhilo.csv

CsvProdCons: $(OBJ_DIR)/prodCons | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/prodCons $(CSV_DIR)/ProdCons.csv

CsvReaderWriter: $(OBJ_DIR)/readerWriter | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/readerWriter $(CSV_DIR)/EcritLect.csv

allCsv: CsvpbPhilo CsvProdCons CsvReaderWriter

plotPhilo: CsvpbPhilo | $(PLOT_DIR)
	python3 scriptPython.py $(CSV_DIR)/pbPhilo.csv $(PLOT_DIR)/philo_plot.png

plotProdCons: CsvProdCons | $(PLOT_DIR)
	python3 ./scriptPython.py $(CSV_DIR)/ProdCons.csv $(PLOT_DIR)/prodcons_plot.png

plotReaderWriter: CsvReaderWriter | $(PLOT_DIR)

	
	python3 ./scriptPython.py $(CSV_DIR)/EcritLect.csv $(PLOT_DIR)/readerwriter_plot.png


allPlot: plotPhilo plotProdCons plotReaderWriter

# Nettoyage des fichiers objets et exécutables
clean:
	rm -rf $(OBJ_DIR) $(CSV_DIR) $(PLOT_DIR)

