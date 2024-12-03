#!/bin/bash



EXEC_PATH=$1
LOGS=$2
TEMP_DIR="/tmp"  


touch "$LOGS"
echo "NumberThread, Run1, Run2, Run3, Run4, Run5" > "$LOGS"

# Récupère le nom du programme à partir du chemin (ex. "prodCons" ou "pbPhilo")
PROG=$(basename "$EXEC_PATH")

Threads="2 4 8 16 32"

if [ "$PROG" == "pbPhilo" ]; then
    for t in $Threads; do
        echo -n "$t," >> "$LOGS"  # Ajouter le nombre de threads dans le fichier de log
        echo "Running $t thread(s)..."

        # Exécuter le programme Philosophe 5 fois et enregistrer les temps dans le fichier
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n" >> "$LOGS"
            if [ $i -lt 5 ]; then
                echo -n "," >> "$LOGS"  # Ajouter une virgule entre les résultats
            fi
        done
        echo "" >> "$LOGS"
    done

elif [ "$PROG" == "prodCons" ]; then
    for t in $Threads; do
        echo -n "$t," >> "$LOGS"  # Ajouter le nombre de threads dans le fichier de log
        echo "Running $t thread(s)..."

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n" >> "$LOGS"
            if [ $i -lt 5 ]; then
                echo -n "," >> "$LOGS"  # Ajouter une virgule entre les résultats
            fi
        done
        echo "" >> "$LOGS"
    done

elif [ "$PROG" == "testVerrou" ]; then
    for t in 1 2 4 8 16 32; do
        echo -n "$t," >> "$LOGS"  # Ajouter le nombre de threads dans le fichier de log
        echo "Running $t thread(s)..."

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier

        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n" >> "$LOGS"
            if [ $i -lt 5 ]; then
                echo -n "," >> "$LOGS"  # Ajouter une virgule entre les résultats
            fi
        done
        echo "" >> "$LOGS"
    done 

elif [ "$PROG" == "testANDtest" ]; then
    for t in 1 2 4 8 16 32; do
        echo -n "$t," >> "$LOGS"  # Ajouter le nombre de threads dans le fichier de log
        echo "Running $t thread(s)..."

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier

        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n" >> "$LOGS"
            if [ $i -lt 5 ]; then
                echo -n "," >> "$LOGS"  # Ajouter une virgule entre les résultats
            fi
        done
        echo "" >> "$LOGS"
    done        
elif [ "$PROG" == "testSemaphore" ]; then
    for t in 1 2 4 8 16 32; do
        echo -n "$t," >> "$LOGS"  # Ajouter le nombre de threads dans le fichier de log
        echo "Running $t thread(s)..."

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier

        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n" >> "$LOGS"
            if [ $i -lt 5 ]; then
                echo -n "," >> "$LOGS"  # Ajouter une virgule entre les résultats
            fi
        done
        echo "" >> "$LOGS"
    done   

elif [ "$PROG" == "testSemaphore2" ]; then
    for t in 1 2 4 8 16 32; do
        echo -n "$t," >> "$LOGS"  # Ajouter le nombre de threads dans le fichier de log
        echo "Running $t thread(s)..."

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier

        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n" >> "$LOGS"
            if [ $i -lt 5 ]; then
                echo -n "," >> "$LOGS"  # Ajouter une virgule entre les résultats
            fi
        done
        echo "" >> "$LOGS"
    done 

elif [ "$PROG" == "PhilosopesActive" ]; then
    for t in $Threads; do
        echo -n "$t," >> "$LOGS"  # Ajouter le nombre de threads dans le fichier de log
        echo "Running $t thread(s)..."

        # Exécuter le programme PhilosopesActive 5 fois et enregistrer les temps dans le fichier
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n" >> "$LOGS"
            if [ $i -lt 5 ]; then
                echo -n "," >> "$LOGS"  # Ajouter une virgule entre les résultats
            fi
        done
        echo "" >> "$LOGS"
    done
    
elif [ "$PROG" == "prodConsActive" ]; then
    for t in $Threads; do
        echo -n "$t," >> "$LOGS"  # Ajouter le nombre de threads dans le fichier de log
        echo "Running $t thread(s)..."

        # Exécuter le programme prodConsActive 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n" >> "$LOGS"
            if [ $i -lt 5 ]; then
                echo -n "," >> "$LOGS"  # Ajouter une virgule entre les résultats
            fi
        done
        echo "" >> "$LOGS"
    done


else
    # Si le programme n'est ni "pbPhilo" ni "prodCons"
    for t in $Threads; do
        echo -n "$t," >> "$LOGS"  # Ajouter le nombre de threads dans le fichier de log
        echo "Running $t thread(s)..."

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n" >> "$LOGS"
            if [ $i -lt 5 ]; then
                echo -n "," >> "$LOGS"  # Ajouter une virgule entre les résultats
            fi
        done
        echo "" >> "$LOGS"
    done
fi
