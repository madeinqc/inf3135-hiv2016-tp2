import pytmx
tmxdata = pytmx.TiledMap("assets/map1.tmx")

nbLayers = sum(1 for _ in tmxdata.visible_tile_layers)
print(nbLayers)

