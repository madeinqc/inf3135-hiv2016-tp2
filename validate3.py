''' 
NOTES:
	j'assume qu'on peut avoir des elements sur le sable, terre et gason. Seules les tules d'eau et vides ne sont pas valides 
	a l"exeption de terre qui peut etre sur l'eau (pont)
'''

import pytmx
data = pytmx.TiledMap("assets/map1.tmx")

def print_GID():
	''' Imprime les tuiles diponibles dans la carte avec le GID et proprietes '''
	tileSet = set()

	for noLayer in data.visible_tile_layers:
		for tile in data.get_tile_properties_by_layer(noLayer):
			tileSet.add(tile[0])
	tileSet = sorted(tileSet)

	o = [(i,data.get_tile_properties_by_gid(i)) for i in tileSet]

	for item in o:
		print(item)

def get_set_GID():
	''' Retourne un set de tous les GIDs diponibles dans la carte '''
	tileSet = set()

	for noLayer in data.visible_tile_layers:
		for tile in data.get_tile_properties_by_layer(noLayer):
			tileSet.add(tile[0])
	tileSet = sorted(tileSet)
	return tileSet

def get_dict_by_GID(gid):
	tileSet = get_set_GID()
	tileDict = dict((i, data.get_tile_properties_by_gid(i)['source'][:-4]) for i in tileSet)
	tileDict[0] = 'vide'
	return tileDict[gid]

def get_dict_by_type():
	tileSet = get_set_GID()
	tileDict = dict((data.get_tile_properties_by_gid(i)['source'][:-4], i) for i in tileSet)
	tileDict['vide'] = 0
	return tileDict

def validate_level0():
	''' Verifie que le level 0 ait seulement des tuiles valides. Retourne False si invalide. '''
	tileSet = set()
	tileAllowed = [1, 2, 3, 4, 5, 6, 7]
	for tile in data.get_tile_properties_by_layer(0):
		tileSet.add(tile[0])
	if tileSet.difference(tileAllowed) != set():
		return False 
	else:
		return True

def is_tile_type(tile, tileType):
	''' Retourne True sur le type de la tuile est celui demande ''' 
	tileGID = data.get_tile_gid(tile[0], tile[1], tile[2])
	tileName = get_dict_by_GID(tileGID)
	if tileName == tileType:
		return True
	else:
		return False

def is_valide_tile(tile):
	''' Retourne False si la tuile n'est pas valide '''
	# on verifie si la tuile est sur l'eau ou sur une case vide 
	temp = list(tile)
	temp[2] -= 1
	underTile = tuple(temp)
	temp[2] += 1

	if is_tile_type(underTile, 'vide'):
		return False
	elif is_tile_type(underTile, 'water'):
		if not is_tile_type(tile, 'earth'):
			return False
	return True 

def validate_levels():
	positionList = []
	tileSet = get_set_GID()
	for gid in tileSet:
		positionList.extend(list(data.get_tile_locations_by_gid(gid)))
	positionList = filter(lambda x: x[2] != 0, positionList) #enleve les tuples du level 0
	while positionList != []:
		tile = positionList.pop()
		if not is_valide_tile(tile):
			print " Position error: %s " %(str(tile))
			return False
	return True

#def complete_map():


#--------------------------------#
if not validate_level0():
	print 'Invalid Map! Level 0 contains invalid tiles'
elif not validate_levels():
	print 'Invalid Map! Position Error'
else:
	print 'Valid Map'