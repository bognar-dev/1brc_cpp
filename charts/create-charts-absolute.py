import pandas as pd
import matplotlib.pyplot as plt


def human_readable(num):
    for unit in ['', 'K', 'M', 'B']:
        if abs(num) < 1000.0:
            return "%3.1f%s" % (num, unit)
        num /= 1000.0
    return "%.1f%s" % (num, 'T')


if __name__ == '__main__':

    df = pd.read_csv('charts/runtimes.csv',index_col='Program')
    df['File Size (Lines)'] = df['File'].apply(lambda x: int(x.split('_')[1].split('.')[0]))
    df['AvGRuntime'] = df[['Runtime1', 'Runtime2', 'Runtime3']].mean(axis=1)
    pivot_df = df.pivot_table(index='File Size (Lines)', columns='Program', values='AvGRuntime', aggfunc='sum')

    # Reset the index to make 'File Size (Lines)' a regular column
    pivot_df.reset_index(inplace=True)

    # Plot
    plt.figure(figsize=(10, 6))

    # craete colour dict for each method
    colour_dict = {'linear-search': 'red', 'hashmap': 'blue', 'parse-double': 'green', 'fread-chunks': 'orange',
                   'loop-unrolling': 'purple', 'parallelize': 'cyan', 'mmap': 'magenta'}

    for column in pivot_df.columns[1:]:
        plt.plot(pivot_df["File Size (Lines)"], pivot_df[column], marker='o', label=column, color=colour_dict[column])

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
    plt.savefig('charts/performance.png')
    plt.show()
