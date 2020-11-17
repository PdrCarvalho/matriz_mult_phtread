#!/bin/bash

#SBATCH --partition=cluster
#SBATCH --job-name=Serial_rand
#SBATCH --output=SerialRandOutput.out
#SBATCH --error=SerialRandError.err
#SBATCH --time=0-02:0
#SBATCH --hint=compute_bound 

#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

#No Supercomputador, 1 nó = 32 Cores (ou CPUs)
#Lembrar que: TASK = PROCESSO

#A configuração acima reserva 1 nó inteiro (32 cpus no mesmo processador), vai rodar apenas 1 processo por vez,
# mas este processo terá acesso a 32 cores

#Loop principal de execuções. São 10 tentativas

	tentativas=10 #Quantas vezes o código será executado


    for size in 1440 1600 1800 2080 #tamanho do problema
    do   	
        #echo -e "\n$cores\t$size\t\t\c" >> "tempo_de_mm.txt" 

        for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
        do
            srun serail_code_rand $size  #atualizar de acordo com OpenMP
        done
    done

	
	exit 

