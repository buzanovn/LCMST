import numpy as np


def dump_np_array(np_array: np.ndarray, fpath: str):
    with open(fpath, 'w') as fp:
        for i in range(0, len(np_array)):
            for j in range(0, len(np_array)):
                fp.write(f"{int(np_array[i][j])} ")
            fp.write("\n")
