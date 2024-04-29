import pandas as pd
import matplotlib.pyplot as plt


def human_readable(num):
    for unit in ['', 'K', 'M', 'B']:
        if abs(num) < 1000.0:
            return "%3.1f%s" % (num, unit)
        num /= 1000.0
    return "%.1f%s" % (num, 'T')


if __name__ == '__main__':

    df = pd.read_csv('charts/performance.csv')

    df = df.drop(columns=['Relative Speedup V2', 'Relative Speedup V3', 'Relative Speedup V4', 'Relative Speedup V5',
                          'Relative Speedup V6', 'Relative Speedup V7'])
    # drop first 2 rows
    df = df.drop([0, 1])

    # Plot
    plt.figure(figsize=(10, 6))

    for column in df.columns[1:]:
        plt.plot(df["File Size (Lines)"], df[column], marker='o', label=column)

    plt.title('Absolute Runtimes of Methods')
    plt.xlabel('File Size (Lines)')
    plt.ylabel('Runtime (s)')
    plt.xscale('log')
    plt.yscale('log')
    plt.grid(True, which="both", ls="--")

    # Get x-ticks and convert them to human readable format
    xticks = plt.xticks()[0]
    plt.xticks(xticks, [human_readable(xtick) for xtick in xticks], rotation='vertical')

    padding_left = 10
    padding_right = 100000000
    plt.xlim(100000 - padding_left, 1000000000 + padding_right)

    plt.legend()
    plt.tight_layout()
    plt.show()
