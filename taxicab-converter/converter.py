import argparse

from helpers import dump_np_array
from task import Task

parser = argparse.ArgumentParser()
parser.add_argument("taxicab_task_file", type=str, help="Path to taxicab task file")
parser.add_argument("output", type=str, help="Path to output file")
args = parser.parse_args()

task = Task(args.taxicab_task_file)
dump_np_array(task.adjacency_matrix, args.output)
