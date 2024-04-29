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

    # remove the Method 1,Method 2,Method 3,Method 4,Method 5,Method 6,Method 7
    df = df.drop(columns=['Version 1', 'Version 2', 'Version 3', 'Version 4', 'Version 5', 'Version 6', 'Version 7'])
    # drop first 2 rows
    df = df.drop([0, 1])

    # Plot
    plt.figure(figsize=(10, 6))

    for column in df.columns[1:]:
        plt.plot(df["File Size (Lines)"], df[column], marker='o', label=column)

    plt.title('Relative Speedup of Methods compared to Different Versions')
    plt.xlabel('File Size (Lines)')
    plt.ylabel('Relative Speedup (%)')
    plt.xscale('log')
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
    plt.show()
