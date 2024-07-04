import matplotlib.pyplot as plt
import networkx as nx

def read_input():
    n_vertices, n_edges = map(int, input().split())
    vertices = {}
    edges = []

    for i in range(1, n_vertices + 1):
        data = list(map(float, input().split()))
        x, y, degree = data[0], data[1], int(data[2])
        neighbors = list(map(int, data[3:]))
        vertices[i] = (x, y)
        for neighbor in neighbors:
            if neighbor < i:
                edges.append((i, neighbor))

    return vertices, edges

def read_faces():
    n_faces = int(input())
    faces = []

    for _ in range(n_faces):
        face_data = list(map(int, input().split()))
        face = face_data[1:]
        faces.append(face)

    return faces

def draw_face(vertices, face, face_number):
    G = nx.Graph()

    # Add vertices
    for v, coords in vertices.items():
        G.add_node(v, pos=coords)

    pos = nx.get_node_attributes(G, 'pos')

    cycle = face + [face[0]]  # To form a closed loop
    edges = [(cycle[i], cycle[i + 1]) for i in range(len(cycle) - 1)]

    plt.figure()
    nx.draw_networkx_nodes(G, pos, nodelist=face, node_color='r')
    nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='b')
    nx.draw_networkx_labels(G, pos)
    plt.title(f'Face {face_number}')
    plt.show()

def main():
    vertices, edges = read_input()
    faces = read_faces()

    for i, face in enumerate(faces):
        draw_face(vertices, face, i + 1)

if __name__ == "__main__":
    main()