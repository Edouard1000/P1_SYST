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

$(OBJ_DIR)/readerWriter: $(SRC_DIR)/read2.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@


############Tache 2.1 ################
$(OBJ_DIR)/verrou.o: $(SRC_DIR)/testANDset.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/testANDset.c -o $@

$(OBJ_DIR)/testVerrou.o: $(SRC_DIR)/testVerrou.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/testVerrou.c -o $@


OBJ_FILES = $(OBJ_DIR)/testVerrou.o $(OBJ_DIR)/verrou.o

$(OBJ_DIR)/testVerrou: $(OBJ_FILES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ -lpthread	

############Tache 2.2 ################



$(OBJ_DIR)/testANDtest.o: $(SRC_DIR)/testANDtest.c $(SRC_DIR)/headers.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/testANDtest.c -o $@

OBJ_FILES2 = $(OBJ_DIR)/testANDtest.o $(OBJ_DIR)/verrou.o

$(OBJ_DIR)/testANDtest: $(OBJ_FILES2) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES2) -o $@ -lpthread


CsvpbPhilo: $(OBJ_DIR)/pbPhilo | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/pbPhilo $(CSV_DIR)/pbPhilo.csv

CsvProdCons: $(OBJ_DIR)/prodCons | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/prodCons $(CSV_DIR)/ProdCons.csv

CsvReaderWriter: $(OBJ_DIR)/readerWriter | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/readerWriter $(CSV_DIR)/EcritLect.csv

CsvTestVerrou: $(OBJ_DIR)/testVerrou | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/testVerrou $(CSV_DIR)/TestVerrou.csv

CsvTestAndTest: $(OBJ_DIR)/testANDtest | $(CSV_DIR)
	chmod +x scriptBash.sh
	./scriptBash.sh $(OBJ_DIR)/testANDtest $(CSV_DIR)/TestAndTest.csv

allCsv: CsvpbPhilo CsvProdCons CsvReaderWriter CsvTestVerrou CsvTestAndTest

plotPhilo: CsvpbPhilo | $(PLOT_DIR)
	python3 scriptPython.py $(CSV_DIR)/pbPhilo.csv $(PLOT_DIR)/philo_plot.png

plotProdCons: CsvProdCons | $(PLOT_DIR)
	python3 ./scriptPython.py $(CSV_DIR)/ProdCons.csv $(PLOT_DIR)/prodcons_plot.png

plotReaderWriter: CsvReaderWriter | $(PLOT_DIR)

	
	python3 ./scriptPython.py $(CSV_DIR)/EcritLect.csv $(PLOT_DIR)/readerwriter_plot.png

plotTestVerrou: CsvTestVerrou | $(PLOT_DIR)
	python3 ./scriptPython.py $(CSV_DIR)/TestVerrou.csv $(PLOT_DIR)/TestVerrou_plot.png

###La commande à corriger pour avoir testAndTest et TestAndSet sur la meme figure   ( je fais ca le soir)
plotTestAndTestAndSet: CsvTestVerrou  CsvTestAndTest $(PLOT_DIR)
	python3 ./scriptPython.py $(CSV_DIR)/TestVerrou.csv $(PLOT_DIR)/TestAndTestAndSet_plot.png $(CSV_DIR)/TestAndTest.csv


###Cette commande ne sert à rien juste pour voir que testANdTest fonctionne quand on le genere seul mais sur la meme figure avec test and set non
plotTestAndTest: CsvTestAndTest $(PLOT_DIR)
	python3 ./scriptPython.py $(CSV_DIR)/TestAndTest.csv $(PLOT_DIR)/TestAndTestAndSet_plot.png


allPlot: plotPhilo plotProdCons plotReaderWriter plotTestVerrou

# Nettoyage des fichiers objets et exécutables
clean:
	rm -rf $(OBJ_DIR) $(CSV_DIR) $(PLOT_DIR)

