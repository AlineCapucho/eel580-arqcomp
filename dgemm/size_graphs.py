import sys
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

files = [
   "./dgemm/runtimes/Runtimes_c1.txt",
    "./dgemm/runtimes/Runtimes_c2.txt",
    "./dgemm/runtimes/Runtimes_c3.txt",
    "./dgemm/runtimes/Runtimes_c4.txt",
    "./dgemm/runtimes/Runtimes_c5.txt",
    "./dgemm/runtimes/Runtimes_c6.txt"
]

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

def get_mean_runtime_for_n(data, n):
    times_for_n = data.get(n, [])
    mean_time_for_n = np.mean(times_for_n)
    return mean_time_for_n

def plot_means(means):
    plt.figure(figsize=(10, 6))

    palette = [
        "dodgerblue",
        "darkorange",
        "forestgreen",
        "red",
        "slateblue",
        "sienna"
    ]

    ax = sns.barplot(x=np.arange(2, 7), y=means, palette=palette)
    
    for container in ax.containers:
        ax.bar_label(container, fmt="%.2f", fontsize=8, fontweight="bold")

    plt.xlabel("Capítulo")
    plt.ylabel("Média do Tempo de execução (s)")
    plt.title("Média do Tempo de execução (s) x Capítulo")
    plt.show()

def main(n):
    all_data = [get_data(file_path) for file_path in files]
    means = [get_mean_runtime_for_n(data, int(n)) for data in all_data]

    plot_means(means)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Número incorreto de parâmetros passados. Encerrando programa.\n")
        sys.exit(1)

    n = str(sys.argv[1])
    main(n)
