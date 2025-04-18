#!/usr/bin/env python3

def read_input_file(filename):
    """Read a raytracer input file and return vertices and faces data."""
    with open(filename, 'r') as f:
        lines = f.readlines()
    
    # Find the indices where Vertices and Faces sections start
    vertices_index = -1
    faces_index = -1
    
    for i, line in enumerate(lines):
        if line.startswith("Vertices"):
            vertices_index = i
        elif line.startswith("Faces"):
            faces_index = i
    
    if vertices_index == -1 or faces_index == -1:
        raise ValueError(f"File {filename} does not have the expected format")
    
    # Extract number of vertices
    vertices_count = int(lines[vertices_index].split()[1])
    
    # Extract vertices data
    vertices = []
    for i in range(vertices_index + 1, vertices_index + vertices_count + 1):
        if i < len(lines):
            vertices.append(lines[i].strip())
    
    # Extract number of faces
    faces_count = int(lines[faces_index].split()[1])
    
    # Extract faces data
    faces = []
    for i in range(faces_index + 1, faces_index + faces_count + 1):
        if i < len(lines):
            faces.append(lines[i].strip())
    
    return vertices, faces

def merge_files(file1, file2, output_file):
    """Merge two raytracer input files."""
    # Read input files
    vertices1, faces1 = read_input_file(file1)
    vertices2, faces2 = read_input_file(file2)
    
    # Calculate new counts
    total_vertices = len(vertices1) + len(vertices2)
    total_faces = len(faces1) + len(faces2)
    
    # Update vertex IDs in the second file's faces
    updated_faces2 = []
    for face in faces2:
        parts = face.split()
        matID = parts[0]
        num_vertices = int(parts[1])
        
        # Start building the new face line
        new_face = [matID, parts[1]]
        
        # Update vertex IDs (add the number of vertices from the first file)
        for i in range(2, 2 + num_vertices):
            new_vertex_id = str(int(parts[i]) + len(vertices1))
            new_face.append(new_vertex_id)
        
        updated_faces2.append(" ".join(new_face))
    
    # Write merged data to output file
    with open(output_file, 'w') as f:
        # Write vertices section
        f.write(f"Vertices {total_vertices}\n")
        for vertex in vertices1:
            f.write(f"{vertex}\n")
        for vertex in vertices2:
            f.write(f"{vertex}\n")
        
        # Write faces section
        f.write(f"Faces {total_faces}\n")
        for face in faces1:
            f.write(f"{face}\n")
        for face in updated_faces2:
            f.write(f"{face}\n")

def main():
    import argparse
    
    parser = argparse.ArgumentParser(description='Merge two raytracer input files.')
    parser.add_argument('file1', help='First input file')
    parser.add_argument('file2', help='Second input file')
    parser.add_argument('output', help='Output file')
    
    args = parser.parse_args()
    
    try:
        merge_files(args.file1, args.file2, args.output)
        print(f"Successfully merged {args.file1} and {args.file2} into {args.output}")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()