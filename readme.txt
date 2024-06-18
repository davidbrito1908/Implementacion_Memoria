PROYECTO DE IMPLEMENTACIÓN DE MEMORIA

David Brito 30.521.360
Andrés Gubaira 31.006.669


La PARTE 1 se encuentra en los programas realizados en la raiz del repositorio:

    -memorias.cpp: Es el archivo donde se crean e implementan las clases de los distintos tipos de memeoria (Correspondencia Directa, Asociativa por conjuntos y completamente asociativa).
    
    -directa.cpp: Utiliza los numeros de datos.txt (Se pasa el archivo por entrada estándar "./{ejecutable} < datos.txt") que corresponden al ejemplo del libro y hace el paso a paso de guardarlos a una memoria de correspondencia directa con 4 bloques de 1 palabra.
    
    -conjuntos.cpp: Utiliza los numeros de datos.txt (Se pasa el archivo por entrada estándar "./{ejecutable} < datos.txt") que corresponden al ejemplo del libro y hace el paso a paso de guardarlos a una memoria asociativa por conjuntos con 4 bloques divididos en 2 conjuntos de 2 bloques.
    
    -completamenteAsociativa.cpp: Utiliza los numeros de datos.txt (Se pasa el archivo por entrada estándar "./{ejecutable} < datos.txt") que corresponden al ejemplo del libro y hace el paso a paso de guardarlos a una memoria totalmente asociativa con 4 bloques de 1 palabra.
    
    -ejemplo.cpp: Junta los 3 programas anteriores para poder comparar facilmente con el ejemplo del libro el comportamiento de cada tipo de memoria. (También necesita de entrada estándar)



La PARTE 2 se encuentra dentro de la carpeta dataset, alli se encuentra:

    -data.zip : El comprimido del dataset, al descomprimirlo se obtiene el archivo fer2013.csv, el cual es el dataset utilizado.
    
    -main.cpp: Programa que lee y procesa el dataset caracter a caracter. (Usar entrada estándar para trabajar con el dataset "./{ejecutable} < fer2013.csv") 
        - Imprime por pantalla los fallos, tasa de aciertos y tiempo de ejecucion
    
    -mmap.cpp: Programa que lee el dataset mediante mmap y se procesa en memoria caracter a caracter (No necesita entrada estandar "./{ejecutable}") 
        - Imprime por pantalla los fallos, tasa de aciertos y tiempo de ejecucion
    
    -memorias.cpp: La misma implementación de las memorias solo que en esta se utilizan memorias de 8 bloques de 1 palabra (Esto puede modificarse en el archivo)
