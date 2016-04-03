''' 
NOTES:
	On assume qu'on peut avoir des elements sur le sable, terre et gason seulement a l'exeption de la terre qui peut etre sur une case d'eau (pont).
	On peut avoir qu'une maison et personnage par carte. 
	Il faut avoir au moins une roche par carte. 
	On permet des tuiles dur des tules vides (sinon map2 invalide)

TODOS:
	Check pourquoi carte invalide. 
	Test toutes les cartes d'un dossier
'''

import pytmx
data = pytmx.TiledMap("assets/map1_test1.tmx")

def print_GID_by_layer():
	''' Imprime les tuiles diponibles dans chaque niveau avec le GID et proprietes '''
	tileSet = set()

	for noLayer in data.visible_tile_layers:
		print noLayer
		for tile in data.get_tile_properties_by_layer(noLayer):
			print tile 	
			tileSet.add(tile[0])
	tileSet = sorted(tileSet)

	o = [(i,data.get_tile_properties_by_gid(i)) for i in tileSet]

	#for item in o:
		#print(item)

def print_GID_by_map():
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

def get_tile_dict():
	''' Retourne un dictionnaire qui a pour cle le nom de la tuile et pour valeur le GID correspondant.'''
	tileSet = get_set_GID()
	tileDict = dict((data.get_tile_properties_by_gid(i)['source'][:-4], i) for i in tileSet)
	return tileDict

def get_dict_by_GID(gid):
	''' Retourne le le nom correspondant au GID demande'''
	tileSet = get_set_GID()
	tileDict = dict((i, data.get_tile_properties_by_gid(i)['source'][:-4]) for i in tileSet)
	tileDict[0] = 'empty'
	return tileDict[gid]

def get_dict_by_type(name):
	''' Retourne le le GID correspondant au nom demande.'''
	tileDict = get_tile_dict()
	tileDict['empty'] = 0
	return tileDict[name]

def validate_level0():
	''' Verifie que le level 0 ait seulement des tuiles valides (eau, terre, sable et gazon). Retourne False si invalide. '''
	tileSet = set()
	tileDict = get_tile_dict()
	tileAllowed = set([value for key, value in tileDict.items() if 'water' in key])
	tileAllowed.add(get_dict_by_type('earth'))
	tileAllowed.add(get_dict_by_type('sand'))
	tileAllowed.add(get_dict_by_type('grass'))
	for tile in data.get_tile_properties_by_layer(0):
		tileSet.add(tile[0])
	if tileSet.difference(tileAllowed) != set():
		return False 
	else:
		return True

def is_tile_type(tile, tileType):
	''' Retourne True si le type de la tuile est celui demande. 
	Water, water-front, water-left et water-right sont tous de type water.''' 
	tileGID = data.get_tile_gid(tile[0], tile[1], tile[2])
	tileName = get_dict_by_GID(tileGID)
	if tileType in tileName:
		return True
	else:
		return False

def is_valide_tile(tile):
	''' Retourne False si la tuile n'est pas valide 
	La tuile est valide seulement si elle est sur la terre, sur du sable ou sur du gazon a l'exeption de la terre qui peu etre sur l'eau. '''
	temp = list(tile)
	temp[2] -= 1
	underTile = tuple(temp)
	temp[2] += 1

	if not is_tile_type(underTile, 'grass') and not is_tile_type(underTile, 'sand') and not is_tile_type(underTile, 'earth') and not is_tile_type(underTile, 'empty'):
		if is_tile_type(tile, 'earth') and is_tile_type(underTile, 'water'):
			return True
		else:
			print '%s of type %s' %(str(underTile), str(get_dict_by_GID(data.get_tile_gid(underTile[0], underTile[1], underTile[2]))))
			print '%s of type %s' %(str(tile), str(get_dict_by_GID(data.get_tile_gid(tile[0], tile[1], tile[2]))))
			return False
	return True

def validate_levels():
	''' Recupere chaque tuple de tuile qui n'est pas au level 0. Pour chaque tuile recuperees, appelle la function is_valide_tile(). 
	Retourne False si un truile est invalide.'''
	locationList = []
	tileSet = get_set_GID()
	for gid in tileSet:
		locationList.extend(list(data.get_tile_locations_by_gid(gid)))
	locationList = filter(lambda x: x[2] != 0, locationList) #enleve les tuples du level 0
	while locationList != []:
		tile = locationList.pop()
		if not is_valide_tile(tile):
			print " Position error: %s " %(str(tile))
			return False
	return True

def is_map_complete():
	''' Verifie qu'il y a seulement une maison et un seul personnage sur la carte et au moins une roche.'''
	elemList = []
	elemList.extend(list(data.get_tile_locations_by_gid(get_dict_by_type('house'))))
	if len(elemList) != 1:
		return False
	elemList.pop()
	elemList.extend(list(data.get_tile_locations_by_gid(get_dict_by_type('character'))))
	if len(elemList) != 1:
		return False
	elemList.pop()
	elemList.extend(list(data.get_tile_locations_by_gid(get_dict_by_type('rock'))))
	if len(elemList) < 1:
		return False
	return True

def continuous_levels():
	''' Verifie qu'il y ait 4 niveaux consecutifs. '''
	layerList = list(data.visible_tile_layers)
	if len(layerList) != 4:
		return False
	for i in range(len(layerList) -2):
		if i+1-i != 1:
			return False
	return True

def validate_size():
	''' Verifie que la largeur et la longueur de la carte permet d'avoir des sous-cates de 14x14 avec des tules de transition entre chanque sous-carte.'''
	locationList = []
	tileSet = get_set_GID()
	for gid in tileSet:
		locationList.extend(list(data.get_tile_locations_by_gid(gid)))
	width = max(locationList, key=lambda item: item[0])[0] +1
	height = max(locationList, key=lambda item: item[1])[1] +1
	if width // 14 != width % 14 +1:
		return False
	elif height // 14 != height % 14 +1:
		return False
	else:
		return True
	return True


#---------------------------------#
#print_GID_by_map()
#print_GID_by_layer()

if not continuous_levels():
	print 'Invalid Map! It is required to have 4 continuous levels.'
elif not validate_size():
	print 'Invalid Map! The map size is not valid.'
elif not validate_level0():
	print 'Invalid Map! Level 0 contains invalid tiles.'
elif not validate_levels():
	print 'Invalid Map! Position Error.'
elif not is_map_complete():
	print 'Invalid Map! Missing a required element.'
else:
	print 'Valid Map'
