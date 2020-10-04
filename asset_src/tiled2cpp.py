import pytiled_parser
from jinja2 import Template
from pathlib import Path
from collections import defaultdict

known_types = ['bg','oneway','rslope','lslope','solid','breakable']

level = pytiled_parser.parse_tile_map("level.tmx")
tileset = None
for ts in level.tile_sets.values():
    if ts.name == 'mario':
        tileset = ts.tiles
        tileset_cols = ts.columns
        break

entities = None
areas = None
for l in level.layers:
    if l.name == "Entities":
        entities = l.tiled_objects
    elif l.name == "Areas":
        areas = l.tiled_objects


entities_by_type = defaultdict(list)
for e in entities:
    type_ = e.type if e.type != None else tileset[e.gid-1].type_
    entities_by_type[type_].append((e.location.x, e.location.y))

areas_by_type = defaultdict(list)
polygons_by_type = defaultdict(list)
for e in areas:
    if e.points:
        if e.type in polygons_by_type:
            print("Warning, more than one polygon of the same type is not supported", e.type, "will be overwritten")
        points = []
        for p in e.points:
            points.append((p[0]+e.location.x, p[1]+e.location.y))
        polygons_by_type[e.type] = points
    else:
        areas_by_type[e.type].append((e.location.x, e.location.y, e.size.width, e.size.height))

tm = Template(Path('tiledexport.h.tmpl').read_text())
out_h = tm.render(
    entities_by_type=entities_by_type,
    areas_by_type=areas_by_type,
    polygons_by_type=polygons_by_type,
)

try:
    current = Path('../src/tiledexport.h').read_text()
except FileNotFoundError:
    current = ""
if out_h == current:
    print("Skipping header generation, no changes detected")
else:
    Path('../src/tiledexport.h').write_text(out_h)
                
tm = Template(Path('tiledexport.cpp.tmpl').read_text())
#template.globals['custom_function'] = custom_function
out_cpp = tm.render(
    entities_by_type=entities_by_type,
    areas_by_type=areas_by_type,
    polygons_by_type=polygons_by_type,
    debug = False,
)

try:
    current = Path('../src/tiledexport.cpp').read_text()
except FileNotFoundError:
    current = ""
if out_cpp == current:
    print("Skipping cpp generation, no changes detected")
else:
    Path('../src/tiledexport.cpp').write_text(out_cpp)
