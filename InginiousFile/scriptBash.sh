#!/bin/bash



EXEC_PATH=$1
LOGS=$2
TEMP_DIR="/tmp"  


touch "$LOGS"
echo "NumberThread, Run1, Run2, Run3, Run4, Run5"


# Récupère le nom du programme à partir du chemin (ex. "prodCons" ou "pbPhilo")
PROG=$(basename "$EXEC_PATH")


Threads="2 4 8 16 32"

if [ "$PROG" == "pbPhilo" ]; then
    
    echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t,"  # Afficher le nombre de threads dans la sortie standard


        # Exécuter le programme Philosophe 5 fois et afficher les temps dans la sortie standard
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            
            # Si ce n'est pas la dernière exécution, ajouter une virgule
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""  # Saut de ligne après avoir affiché les 5 résultats
    done

elif [ "$PROG" == "philosophesActive" ]; then
    
    echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t,"  # Afficher le nombre de threads dans la sortie standard


        # Exécuter le programme Philosophe 5 fois et afficher les temps dans la sortie standard
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            
            # Si ce n'est pas la dernière exécution, ajouter une virgule
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""  # Saut de ligne après avoir affiché les 5 résultats
    done
elif [ "$PROG" == "philosophesActive2" ]; then
    
    echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t,"  # Afficher le nombre de threads dans la sortie standard


        # Exécuter le programme Philosophe 5 fois et afficher les temps dans la sortie standard
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            
            # Si ce n'est pas la dernière exécution, ajouter une virgule
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""  # Saut de ligne après avoir affiché les 5 résultats
    done


elif [ "$PROG" == "prodCons" ]; then

    echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t," # Ajouter le nombre de threads dans le fichier dans la sortie Standart

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""
    done

elif [ "$PROG" == "prodCons2" ]; then

    echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t," # Ajouter le nombre de threads dans le fichier dans la sortie Standart

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""
    done

elif [ "$PROG" == "testVerrou" ]; then

    echo -e "Running $PROG...\n"
    for t in 1 2 4 8 16 32; do
        echo -n "$t,"  # Ajouter le nombre de threads dans le fichier de log
        

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier

        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n"

            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""
    done 

elif [ "$PROG" == "testANDtest" ]; then
    
    echo -e "Running $PROG...\n"
    for t in 1 2 4 8 16 32; do
        echo -n "$t,"  # Ajouter le nombre de threads dans le fichier de log
        
        
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$t"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""
    done 

elif [ "$PROG" == "prodConsActive" ]; then
    echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t," # Ajouter le nombre de threads dans le fichier dans la sortie Standart

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""
    done

elif [ "$PROG" == "readActive" ]; then
  echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t," # Ajouter le nombre de threads dans le fichier dans la sortie Standart

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""
    done 

elif [ "$PROG" == "readActive2" ]; then
  echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t," # Ajouter le nombre de threads dans le fichier dans la sortie Standart

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""
    done      

elif [ "$PROG" == "readerWriter" ]; then

        echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t,"  # Ajouter le nombre de threads dans le fichier de log

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n"
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""
    done

else
    # Si le programme n'est ni "pbPhilo" ni "prodCons"

    echo -e "Running $PROG...\n"
    for t in $Threads; do
        echo -n "$t,"  # Ajouter le nombre de threads dans le fichier de log

        # Exécuter le programme ProdCons 5 fois et enregistrer les temps dans le fichier
        arg1=$((t/2))
        arg2=$((t/2))
        for i in {1..5}; do
            /usr/bin/time -f "%e" -o "$TEMP_DIR/measures" "$EXEC_PATH" "$arg1" "$arg2"
            cat "$TEMP_DIR/measures" | tr -d "\n"        
            if [ $i -lt 5 ]; then
                echo -n ","  # Ajouter une virgule entre les résultats
            fi
        done
        echo ""
    done
fi
