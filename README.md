# Mesh Tools

## meshconvert 

converts from a given mesh format to another [ply, stl, obj, ...]
all formats are written if possible as binary format

usage: meshconver --input test.ply --output test.stl

## checkholes

reports holes in meshes.

usage: checkholes --input test.ply [--export] 

--export creates a xyz file (to be imported in meshlab) which identifies the border vertices of the holes

