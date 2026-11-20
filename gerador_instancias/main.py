import random

def generate_rectangle(max_w, max_h):
    w = random.randint(2, max_w)
    h = random.randint(2, max_h)
    return [(0.0, 0.0), (float(w), 0.0), (float(w), float(h)), (0.0, float(h))]

def generate_triangle(max_w, max_h):
    w = random.randint(2, max_w)
    h = random.randint(2, max_h)
    return [(0.0, 0.0), (float(w), 0.0), (0.0, float(h))]

def generate_trapezoid(max_w, max_h):
    w = random.randint(4, max_w)
    h = random.randint(2, max_h)
    offset = random.randint(1, w // 2)
    return [(0.0, 0.0), (float(w), 0.0), (float(w - offset), float(h)), (float(offset), float(h))]

def generate_pentagon(max_w, max_h):
    w = random.randint(3, max_w)
    h1 = random.randint(2, max_h - 1)
    h2 = random.randint(h1 + 1, max_h)
    peak_x = random.randint(1, w - 1)
    return [(0.0, 0.0), (float(w), 0.0), (float(w), float(h1)), (float(peak_x), float(h2)), (0.0, float(h1))]

def generate_instance(num_pieces, filename="instancia_gerada.txt"):
    generators = [generate_rectangle, generate_triangle, generate_trapezoid, generate_pentagon]
    
    with open(filename, 'w') as f:
        for i in range(1, num_pieces + 1):
            # Escolhe uma forma aleatória e gera os vértices (dimensões máximas 10x10)
            shape_gen = random.choice(generators)
            vertices = shape_gen(10, 10)
            quantity = random.randint(1, 4)
            
            f.write(f"PIECE {i}\n")
            f.write("QUANTITY\n")
            f.write(f"{quantity}\n")
            f.write("NUMBER OF VERTICES\n")
            f.write(f"{len(vertices)}\n")
            f.write("VERTICES (X,Y)\n")
            
            for x, y in vertices:
                f.write(f" {x:.6f}   {y:.6f}\n")
            
            if i < num_pieces:
                f.write("\n")
                
    print(f"Instância '{filename}' gerada com sucesso com {num_pieces} tipos de peças!")

if __name__ == "__main__":

    generate_instance(5, "dataset/a_simples.txt")
    generate_instance(5, "dataset/b_simples.txt")