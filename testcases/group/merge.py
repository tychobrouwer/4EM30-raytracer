#!/usr/bin/env python3
import math

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

def rotate_vertex(vertices, rotation):
    """Rotate vertices around the X, Y, and Z axes by the given angles (in degrees)."""
    def rotate_x(x, y, z, angle):
        rad = math.radians(angle)
        new_y = y * math.cos(rad) - z * math.sin(rad)
        new_z = y * math.sin(rad) + z * math.cos(rad)
        return x, new_y, new_z

    def rotate_y(x, y, z, angle):
        rad = math.radians(angle)
        new_x = x * math.cos(rad) + z * math.sin(rad)
        new_z = -x * math.sin(rad) + z * math.cos(rad)
        return new_x, y, new_z

    def rotate_z(x, y, z, angle):
        rad = math.radians(angle)
        new_x = x * math.cos(rad) - y * math.sin(rad)
        new_y = x * math.sin(rad) + y * math.cos(rad)
        return new_x, new_y, z

    rotated_vertices = []
    for vertex in vertices:
        coords = vertex.split()
        x, y, z = float(coords[0]), float(coords[1]), float(coords[2])

        # Apply rotations
        x, y, z = rotate_x(x, y, z, rotation[0])
        x, y, z = rotate_y(x, y, z, rotation[1])
        x, y, z = rotate_z(x, y, z, rotation[2])

        rotated_vertices.append(f"{x} {y} {z}")

    return rotated_vertices


def translate_vertex(vertices, translation):
    """Translate a vertex by a given translation vector."""
    translated_vertex = []
    for vertex in vertices:
        coords = vertex.split()
        x = float(coords[0]) + translation[0]
        y = float(coords[1]) + translation[1]
        z = float(coords[2]) + translation[2]

        translated_vertex.append(f"{x} {y} {z}")

    return translated_vertex

def merge_files(files, translations, rotations, output_file):
    """Merge multiple raytracer input files."""
    all_vertices = []
    all_faces = []
    vertex_offset = 0

    for i, file in enumerate(files):
        # Read input file
        vertices, faces = read_input_file(file)

        # Translate vertices
        if len(translations) > i:
            vertices = translate_vertex(vertices, translations[i])
        
        # Rotate vertices
        if len(rotations) > i:
            vertices = rotate_vertex(vertices, rotations[i])

        # Update vertex IDs in faces
        updated_faces = []
        for face in faces:
            parts = face.split()
            matID = parts[0]
            num_vertices = int(parts[1])
            
            # Start building the new face line
            new_face = [matID, parts[1]]
            
            # Update vertex IDs (add the current vertex offset)
            for j in range(2, 2 + num_vertices):
                new_vertex_id = str(int(parts[j]) + vertex_offset)
                new_face.append(new_vertex_id)
            
            updated_faces.append(" ".join(new_face))
        
        # Append translated vertices and updated faces
        all_vertices.extend(vertices)
        all_faces.extend(updated_faces)

        # Update vertex offset
        vertex_offset += len(vertices)

    # Write merged data to output file
    with open(output_file, 'w') as f:
        f.write("""Filename output.bmp

Camera
  Centre -60. 4.5 10
  Rotation 0. -8. 0.
  Fov    15.
  Samples 64
  Stratified 1
  Aperture 0.06
  Focallength 45.
End

Film
  Resolution 1800 3000
End

Materials

End

Sun
  Direction -10.0 -15.5 5.0;
  Intensity 1.0
End

Spheres 1
  2 0.   0.  -10000. 10001.3
End

BackGround
  Image rural_asphalt_road_4k.hdr
End

Spotlights
1
-12.0 0.0 5.0 0.0 0.0 -1.0 0.4
80.0 0.2

""")

        # Write vertices section
        f.write(f"Vertices {len(all_vertices)}\n")
        for vertex in all_vertices:
            f.write(f"{vertex}\n")
        
        f.write("\n")

        # Write faces section
        f.write(f"Faces {len(all_faces)}\n")
        for face in all_faces:
            f.write(f"{face}\n")

        f.write("\n")
        f.write("EndInput\n")

def main():
    files = [
        "only_bmw.in",
        "only_singlePin.in", "only_singlePin.in", "only_singlePin.in", 
        "only_singlePin.in", "only_singlePin.in", "only_singlePin.in", 
        "only_singlePin.in", "only_singlePin.in", "only_singlePin.in", 
        "only_singlePin.in", "only_singlePin.in", "only_singlePin.in",
        "only_singlePin.in", "only_singlePin.in", "only_singlePin.in"
    ]
    translations = [
        [-12, 0, 2.686],
        
        # First row
        [-38, 10, 0],
        [-36.5, 10.5, 0],
        [-35, 11, 0],
        [-33.5, 11.5, 0],
        
        # Second row
        [-37.5, 11, 0],
        [-36, 11.5, 0],
        [-34.5, 12, 0],
        
        # Third row
        [-37, 12, 0],
        [-35.5, 12.5, 0],
        
        # Fourth row
        [-36.5, 13, 0],
        
        [-35, 5, 2],  # Flying pin 1
        [-34, 5, -1.5],  # Flying pin 2
        [-33, 4, 0.5],  # Flying pin 3
        [-33, 5.5, 0],
        [-33.5, 7, 0],
    ]
    
    rotations = [
        [0, 0, 0],
        
        [0, 0, 0],
        [0, 0, 0],
        [0, 0, 0],
        [0, 0, 0],
        
        [0, 0, 0],
        [0, 0, 0],
        [0, 0, 0],   
        
        [0, 0, 0],
        [0, 0, 0],
        
        [0, 0, 0],
        
        # Flying pins
        # [30, 45, 0],  # Flying pin 1 rotation
        # [45, 60, 15], # Flying pin 2 rotation
        # [60, 75, 30], # Flying pin 3 rotation
        [85, 0, 0],  # Flying pin 1 rotation
        [45, 0, 0],  # Flying pin 2 rotation
        [60, 0, 0],  # Flying pin 3 rotation
        [0, 0, 0],  # Flying pin 3 rotation
        [0, 0, 0],  # Flying pin 3 rotation
    ]

    output = "showcase.in"
    
    try:
        merge_files(files, translations, rotations, output)
        print(f"Successfully merged {len(files)} files into {output}")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
