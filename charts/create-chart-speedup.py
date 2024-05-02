import pandas as pd
import matplotlib.pyplot as plt


def human_readable(num):
    for unit in ['', 'K', 'M', 'B']:
        if abs(num) < 1000.0:
            return "%3.1f%s" % (num, unit)
        num /= 1000.0
    return "%.1f%s" % (num, 'T')


if __name__ == '__main__':

    # Continue with your plotting code...
    # Load data from CSV into a DataFrame
    df = pd.read_csv('charts/performance.csv')

    df = df.drop(
        columns=['linear-search', 'hashmap', 'parse-double', 'fread-chunks', 'loop-unrolling', 'parallelize', 'mmap'])
    # drop first 2 rows
    df = df.drop([0, 1])

    colour_dict = {'linear-search': 'red', 'Relative Speedup hashmap': 'blue', 'Relative Speedup parse-double': 'green',
                   'Relative Speedup fread-chunks': 'orange', 'Relative Speedup loop-unrolling': 'purple',
                   'Relative Speedup parallelize': 'cyan', 'Relative Speedup mmap': 'magenta'}
    # Plot
    plt.figure(figsize=(10, 6))

    for column in df.columns[1:]:
        plt.plot(df["File Size (Lines)"], df[column], marker='o', label=column, color=colour_dict[column])

    plt.title('Relative Speedup of Methods compared to Linear Search')
    plt.xlabel('File Size (Lines)')
    plt.ylabel('Relative Speedup (%)')
    plt.xscale('log')
    plt.yscale('log')
    plt.grid(True, which="both", ls="--")

    # Get x-ticks and convert them to human readable format
    xticks = plt.xticks()[0]
    plt.xticks(xticks, [human_readable(xtick) for xtick in xticks], rotation='vertical')
    # remove the first 2 and last 2 x-ticks and start at the new first x-tick
    plt.xticks(xticks[2:-2])
    # start from the 100000 x-tick
    padding_left = 10000
    padding_right = 10000000
    plt.xlim(100000 - padding_left, 1000000000 + padding_right)

    plt.legend()
    plt.tight_layout()
    plt.savefig('charts/performance-speedup.png')
    plt.show()
