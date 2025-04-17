
scale = 1.2;                    
rotation = [0, 0, 0];         
translation = [0, 0, 0]; 

vertices = load('vertices.txt');  

% Scale
S = diag([scale, scale, scale]);
vertices = (S * vertices')';

% Rotation (degrees → radians)
rx = deg2rad(rotation(1));
ry = deg2rad(rotation(2));
rz = deg2rad(rotation(3));
Rx = [1 0 0; 0 cos(rx) -sin(rx); 0 sin(rx) cos(rx)];
Ry = [cos(ry) 0 sin(ry); 0 1 0; -sin(ry) 0 cos(ry)];
Rz = [cos(rz) -sin(rz) 0; sin(rz) cos(rz) 0; 0 0 1];
R = Rz * Ry * Rx;
vertices = (R * vertices')';

% Translation
vertices = vertices + translation;

faceLines = readlines('faces.txt');
nFaces = length(faceLines);
faceData = cell(nFaces, 1);
for i = 1:nFaces
    parts = sscanf(faceLines(i), '%d');
    faceData{i} = parts(:)';
end

outputFile = 'SinglePin_transformed.txt';
fid = fopen(outputFile, 'w');

fprintf(fid, '%d\n', size(vertices, 1));
fprintf(fid, '%.6f %.6f %.6f\n', vertices');
fprintf(fid, '%d\n', nFaces);
for i = 1:nFaces
    fprintf(fid, '%d %d ', faceData{i}(1), faceData{i}(2));
    fprintf(fid, '%d ', faceData{i}(3:end));
    fprintf(fid, '\n');
end

fclose(fid);
fprintf('Mesh transformed and saved to %s\n', outputFile);