import math
import os
from typing import Sequence, Optional

import numpy as np
from networkx import Graph


class Task:
    def __init__(self, fpath: str):
        self._fpath: str = fpath
        self._fcontent: Optional[Sequence[int]] = None
        self._n: Optional[int] = None
        self._g: Optional[Graph] = None
        self.build_graph()

    def __repr__(self):
        return (
            f"Task: {self.name}\n"
            f"|V| = {self.g.number_of_nodes()}\n"
            f"|E| = {self.g.number_of_edges()}\n"
            f"Target leaves: {self.l}\n"
        )

    @property
    def name(self):
        return os.path.splitext(os.path.basename(self._fpath))[0]

    @property
    def fcontent(self) -> Sequence[str]:
        if self._fcontent is None:
            with open(self._fpath) as fp:
                return fp.readlines()

    @property
    def n(self) -> int:
        if self._n is None:
            self._n = int(self.fcontent[0].split("=")[-1].strip())
        return self._n

    @property
    def adjacency_matrix(self):
        adj_matr = np.zeros((self.n, self.n))
        for k, v in self.g.adjacency():
            for k1, v1 in sorted(v.items()):
                adj_matr[k - 1][k1 - 1] = v1.get('weight')
        return adj_matr

    @property
    def g(self) -> Graph:
        return self._g

    @property
    def l(self) -> int:
        return math.floor(self.n / 10.0)

    def build_graph(self):
        raw_graph_description = self.fcontent[1:]
        assert self.n == len(raw_graph_description)
        g = Graph()
        vertices = list()
        # Parse vertices
        for rd in raw_graph_description:
            raw_vid, raw_x, raw_y = rd.split()
            raw_x, raw_y = int(raw_x), int(raw_y)
            vid = int(raw_vid.replace(")", ""))
            g.add_node(vid)
            vertices.append((vid, raw_x, raw_y))
        # Add all edges
        for i in range(len(vertices)):
            for j in range(i + 1, len(vertices)):
                vi, xi, yi = vertices[i]
                vj, xj, yj = vertices[j]
                w = abs(xi - xj) + abs(yi + yj)
                g.add_edge(vi, vj, weight=w)
        self._g = g
