import jinja2
import os
import subprocess

# Configuration

CONTEXT = {
    "University": "Universidad de la Habana",
    "TeamName": "UH-Top",
    "Event": "ICPC World Final 2023",
    "TeamMembers": [
        "Marcelo Jos\\'e Fornet Forn\\'es",
        "Ariel Cruz Cruz",
        "Eloy P\\'erez Torres"
    ],
    "Coach": "Jos\\'e Carlos Guti\\'errez P\\'erez"
}

ALG_NAMES = {
    "area2_pol" : "Polygon Area",
    "contains" : "Points in Polygon",
    "point3d" : "Points 3D",
    
    "arborescence" : "Chu-Liu/Edmonds $O(E\log V)$",
    "arborescence2" : "Chu-Liu/Edmonds $O(EV)$",
    "hopcroft_karp" : "Bipartite Matching (Hopcroft-Karp)",
    "min_cost_flow2" : "Min-cost Flow (Dijkstra)",
    "min_cost_flow4" : "Min-cost Flow",
    "offline_lca" : "Off-line LCA (Tarjan)",
    "lca_sparse_table" : "LCA (Euler-tour + RMQ)",
    "scc_gabow" : "Gabow SCC",

    "assignment" : "Minimum assignment (Jonker-Volgenant)",
    "matrix_double" : "Matrix Computation Algorithms",
    "sat2" : "2-SAT",
    "simplex" : "Simplex",

    "partition" : "Partition $O(n \sqrt n)$",

    "ext_gcd" : "Extended GCD",
    "C_n_k" : "$C(n, m)\mod p$",

    "kmp" : "KMP",
    "suffix_array1" : "Suffix Array $O(n \log n)$",
    "suffix_array2" : "Suffix Array $O(n \log^2 n)$",
    "suffix_array3" : "Suffix Array $O(n)$",
    "zfunction" : "Z-function"
}

COMPILE = True

def humanize(name):
    return " ".join(map(lambda s : s.capitalize(), name.split('_')))


def get_algorithm_name(name):
    return ALG_NAMES.get(name, humanize(name))


def main():
    with open("template.tex") as f:
        template = f.read()

    context = CONTEXT
    
    data = []

    for section in os.listdir():
        if section[0] == '.' or not os.path.isdir(section):
            continue

        cur_section = {}
        cur_section["Name"] = humanize(section)
        cur_section["NameSnake"] = section        
        
        algorithms = []
        for algorithm in os.listdir(section):
            if algorithm[0] == '_':
                continue

            cur_algorithm = {}
            name, ext = os.path.splitext(algorithm)
            
            cur_algorithm["Language"] = ext[1:]
            cur_algorithm["NameSnake"] = name
            cur_algorithm["Name"] = get_algorithm_name(name)

            algorithms.append(cur_algorithm)
            
        cur_section["Algorithms"] = algorithms
        data.append(cur_section)

    context["Sections"] = data
    print(context)
    t = jinja2.Template(template)

    with open("reference.tex", "w") as f:
        tex = t.render(context)
        print(tex)
        f.write(tex)

    if COMPILE:
        subprocess.call(["pdflatex", "-synctex=1", "-interaction=nonstopmode", "reference.tex"])


if __name__ == "__main__":
    main()
    # print(humanize("arbol_de_costo"))