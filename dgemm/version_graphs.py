import sys
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

def get_data(file_path):
    with open(file_path, "r") as file:
        lines = file.readlines()
    
    data = {}
    for line in lines:
        n, t = map(float, line.split())
        if n not in data:
            data[n] = []
        data[n].append(t)
    
    return data

def get_mean_runtimes(data):
    means = {n: np.mean(times) for n, times in data.items()}
    return means

def main(file_path):
    data = get_data(file_path)
    means = get_mean_runtimes(data)

    n = list(means.keys())
    t = list(means.values())

    # chapter 1: dodgerblue
    # chapter 2: darkorange
    # chapter 3: forestgreen
    # chapter 4: red
    # chapter 5: slateblue
    # chapter 6: sienna
    plt.figure(figsize=(7, 4))
    ax = sns.barplot(x=n, y=t, color="dodgerblue")
    ax.bar_label(ax.containers[0], fmt="%.2f", fontsize=8, fontweight="bold")

    plt.xlabel("Tamanho da matriz")
    plt.ylabel("Média do Tempo de execução (s)")
    plt.title("Média do Tempo de execução (s) x Tamanho da matriz")
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Número incorreto de parâmetros passados. Encerrando programa.\n")
        sys.exit(1)
    
    n = str(sys.argv[1])
    main(n)